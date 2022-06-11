#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Instructions.h"
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/ADT/IndexedMap.h"
#include <iostream>
#include "AST.hpp"
using namespace std;
using namespace llvm;


static std::unique_ptr<LLVMContext>MilaContext;
static std::unique_ptr<Module> MilaModule;
static std::unique_ptr<IRBuilder<>> MilaBuilder;
static Value *globalNumberPrintFormat;
static Value *globalPrintfNewLineFormat;
static map <string, AllocaInst *> NamedValues;
static map <string, Value *>  ConstValues;
static map <string, GlobalVariable *> GlobalValues;
static map <string, Value *> GlobalConstValues;
static map <string,Value *> GlobalArrayLowerBound;
static map <string, Value *> ArrayLowerBound;
static BasicBlock * placeToBreak;
static bool BreakedInBlock = false;
static bool ExitedInBlock = false;


/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static AllocaInst * CreateEntryBlockAlloca(Function *TheFunction, StringRef VarName, Type * type) {
			IRBuilder<> TmpB(&TheFunction->getEntryBlock(), TheFunction->getEntryBlock().begin());
			return TmpB.CreateAlloca (type, ConstantInt::get(Type::getInt32Ty(*MilaContext), 
									 (type->isArrayTy() ? type->getArrayNumElements() : 0), false), VarName); }

Type * AST::Integer::codegenType( ) {
	return Type::getInt32Ty(*MilaContext);
}
Constant * AST::Integer::getInitValue( ) {
	return ConstantInt::get(*MilaContext, APInt(32, 0, true));
}

Type * AST::Array::codegenType( ) {
	Type *innerType = this->type->codegenType();
	return ArrayType::get(innerType, this->startIndex->val - this->startIndex->val + 1);
}
Constant * AST::Array::getInitValue( ) {
	return ConstantArray::get((ArrayType *)this->codegenType(), this->type->getInitValue());
}

Value *AST::Number::codegenValue( ) {
	return ConstantInt::get(*MilaContext, APInt(32, val, true));
}

Value *AST::String::codegenValue( ) {
	return ConstantDataArray::getString(*MilaContext, this->words);
}

void AST::VarDeclaration::codegenTranslation(bool isGlobal) {
	auto type = this->type->codegenType();
	if (isGlobal) {
		if (type->isArrayTy()) {
			int lowerBound = ((Array *)this->type.get())->startIndex->val;
			GlobalArrayLowerBound[this->identifier] = ConstantInt::get(Type::getInt32Ty(*MilaContext), lowerBound, true);
			MilaModule->getOrInsertGlobal(this->identifier, type);
			GlobalVariable *gVar =MilaModule->getNamedGlobal(this->identifier);
			gVar->setLinkage(GlobalValue::CommonLinkage);
			gVar->setAlignment(MaybeAlign(16));
			gVar->setInitializer(this->type->getInitValue());
			GlobalValues.insert(make_pair(this->identifier, gVar));

		}else {
			MilaModule->getOrInsertGlobal(this->identifier, type);
			GlobalVariable *gVar =MilaModule->getNamedGlobal(this->identifier);
			gVar->setLinkage(GlobalValue::CommonLinkage);
			gVar->setAlignment(MaybeAlign(4));
			gVar->setInitializer(this->type->getInitValue());
			GlobalValues.insert(make_pair(this->identifier, gVar));
		}
	}else {
		if (type->isArrayTy()){
			int lowerBound = ((Array *)this->type.get())->startIndex->val;
			ArrayLowerBound[this->identifier] = ConstantInt::get(Type::getInt32Ty(*MilaContext), lowerBound, true);
			NamedValues[this->identifier] = MilaBuilder->CreateAlloca(type, NULL, this->identifier);
		}
		else NamedValues[this->identifier] = MilaBuilder->CreateAlloca(type, NULL, this->identifier);
	}
}

void AST::ConstDeclaration::codegenTranslation(bool isGlobal) {
	auto tmp = ConstantInt::get(*MilaContext, APInt(32, this->value, true));
	if (isGlobal){
		GlobalConstValues.insert(make_pair(this->identifier, tmp));}
	else ConstValues[this->identifier] = tmp;
}

Function *AST::FunctionProto::codegen( ) {
	std::vector<Type *> params;
	for (int i = 0; i < this->parameters.size(); i++) {
		params.push_back(this->parameters[i]->type->codegenType());}
	FunctionType *FT = FunctionType::get(this->retType->codegenType(), params, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, this->name,MilaModule.get());
	// Set names for all arguments.
	unsigned Idx = 0;
	for (auto &Arg : F->args())
		Arg.setName(this->parameters[Idx++]->identifier);
	return F;
}

Function *AST::ProcedureProto::codegen( ) {
	std::vector<Type *> params;
	for (int i = 0; i < this->parameters.size(); i++) {
		params.push_back(this->parameters[i]->type->codegenType());
	}
	FunctionType *FT = FunctionType::get(Type::getVoidTy(*MilaContext), params, false);
	Function *F = Function::Create(FT, Function::ExternalLinkage, this->name,MilaModule.get());
	// Set names for all arguments.
	unsigned Idx = 0;
	for (auto &Arg : F->args())
		Arg.setName(this->parameters[Idx++]->identifier);
	return F;
}

void AST::Body::codegen( ) {
	for (auto &statement : statements)
		statement->codegenTranslation();
}

void AST::FunctionDeclaration::codegenTranslation(bool isGlobal) {
	Function *TheFunction =MilaModule->getFunction(this->proto->name);
	if (!TheFunction)
		TheFunction = this->proto->codegen();
	if (!TheFunction) return;
	if (!this->body) return;
	// Create a new basic block to start insertion into.
	BasicBlock *BB = BasicBlock::Create(*MilaContext, "procedure "+proto->name+ " block", TheFunction);
	auto prevBB = MilaBuilder->GetInsertBlock();
	MilaBuilder->SetInsertPoint(BB);
	NamedValues[this->proto->name] = CreateEntryBlockAlloca(TheFunction, this->proto->name, this->proto->retType->codegenType());
	for (auto &Arg : TheFunction->args()) {
		AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, Arg.getName(), Arg.getType());
		// Store the initial value into the alloca.
		MilaBuilder->CreateStore(&Arg, Alloca);
		// Add arguments to variable symbol table.
		NamedValues[(std::string)Arg.getName()] = Alloca; 
	}
	for (auto &it : declarations) {
		it->codegenTranslation(true);	}
	ExitedInBlock = false;
	this->body->codegen();
	if (!ExitedInBlock)
		MilaBuilder->CreateRet(MilaBuilder->CreateLoad(NamedValues[this->proto->name]));
	MilaBuilder->SetInsertPoint(prevBB);
}

void AST::ProcedureDeclaration::codegenTranslation(bool isGlobal) {
	Function *TheFunction =MilaModule->getFunction(this->proto->name);
	if (!TheFunction)
		TheFunction = this->proto->codegen();
	if (!TheFunction) return;
	if (!this->body)  return;
	// Create a new basic block to start insertion into.
	BasicBlock *BB = BasicBlock::Create(*MilaContext, "procedure"+proto->name+"block", TheFunction);
	auto prevBB = MilaBuilder->GetInsertBlock();
	MilaBuilder->SetInsertPoint(BB);
	for (auto &Arg : TheFunction->args()) {
		// Create an alloca for this variable.
		AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, Arg.getName(), Arg.getType());
		// Store the initial value into the alloca.
		MilaBuilder->CreateStore(&Arg, Alloca);
		// Add arguments to variable symbol table.
		NamedValues[(std::string)Arg.getName()] = Alloca; }
	for (auto &it : declarations) {
		it->codegenTranslation();}
	this->body->codegen();
	MilaBuilder->CreateRetVoid();
	MilaBuilder->SetInsertPoint(prevBB);
}

Value *AST::ArrayVariable::codegenValue( ) {
	return MilaBuilder->CreateLoad(this->codegenAddress());
}
Value *AST::ArrayVariable::codegenAddress( ) {
	string arrayName = ((Variable *)this->var.get())->name;
	if (GlobalValues.find(arrayName) != GlobalValues.end()){
		vector<Value *> inx;
		inx.push_back(ConstantInt::get(Type::getInt32Ty(*MilaContext), 0));
		inx.push_back(MilaBuilder->CreateSub(index->codegenValue(), GlobalArrayLowerBound[arrayName]));
		return MilaBuilder->CreateGEP(GlobalValues[arrayName], inx);}
	else if (NamedValues.find(arrayName) != NamedValues.end()){
		vector<Value *> inx;
		inx.push_back(ConstantInt::get(Type::getInt32Ty(*MilaContext), 0));
		inx.push_back(MilaBuilder->CreateSub(index->codegenValue(), ArrayLowerBound[arrayName]));
		return MilaBuilder->CreateGEP(NamedValues.at(arrayName), inx);
	} else return nullptr;
}

Value *AST::Variable::codegenValue( ) {
	if (ConstValues.find(this->name) != ConstValues.end()){
		return ConstValues.at(this->name); }
	if (NamedValues.find(this->name) != NamedValues.end()){
		return MilaBuilder->CreateLoad(NamedValues.at(this->name), this->name); }
	if (GlobalConstValues.find(this->name) != GlobalConstValues.end()){
		return GlobalConstValues.at(this->name); }
	if (GlobalValues.find(this->name) != GlobalValues.end()){
		return MilaBuilder->CreateLoad(GlobalValues.at(this->name), this->name);
	}throw "Unknown var";
}
Value *AST::Variable::codegenAddress( ) {
	if (NamedValues.find(this->name) != NamedValues.end()){
		return NamedValues.at(this->name);}
	if (GlobalValues.find(this->name) != GlobalValues.end()){
		return GlobalValues.at(this->name);}
	throw "Either const or unknown var";
}

void AST::Assign::codegenTranslation( ) {
	Value * var_ref = this->variable->codegenAddress();
	MilaBuilder->CreateStore(this->value->codegenValue(), var_ref);
	BreakedInBlock = false;
}

void AST::If::codegenTranslation( ) {
	Value * cond = condition->codegenValue();
	cond = MilaBuilder->CreateICmpNE(cond , ConstantInt::get(*MilaContext, APInt(32, 0, true)));
	Function *f = MilaBuilder->GetInsertBlock()->getParent();
	BasicBlock *ThenBB =  BasicBlock::Create(*MilaContext, "then", f);
	BasicBlock *ElseBB =  BasicBlock::Create(*MilaContext, "else");
	BasicBlock *MergeBB = BasicBlock::Create(*MilaContext, "mergeIf");
	MilaBuilder->CreateCondBr(cond, ThenBB, ElseBB);
	MilaBuilder->SetInsertPoint(ThenBB);
	BreakedInBlock= false;
	then->codegen();
	if (!BreakedInBlock) MilaBuilder->CreateBr(MergeBB);
	f->getBasicBlockList().push_back(ElseBB);
	MilaBuilder->SetInsertPoint(ElseBB);
	BreakedInBlock = false;
	if (elseBody)
		elseBody->codegen();
	if (!BreakedInBlock)
		MilaBuilder->CreateBr(MergeBB);
	f->getBasicBlockList().push_back(MergeBB);
	MilaBuilder->SetInsertPoint(MergeBB);
	BreakedInBlock = false;
	ExitedInBlock = false;
}

void AST::For::codegenTranslation( ) {
	Function *f = MilaBuilder->GetInsertBlock()->getParent();
	AllocaInst *Alloca = CreateEntryBlockAlloca(f, this->varName, Type::getInt32Ty(*MilaContext));
	Value *StartVal = this->startValue->codegenValue();
	if (!StartVal) { return;}
	// Store the value into the alloca.
	MilaBuilder->CreateStore(StartVal, Alloca);
	BasicBlock *LoopBB = BasicBlock::Create(*MilaContext, "forLoop", f);
	BasicBlock *AfterLoopBB = BasicBlock::Create(*MilaContext, "afterForLoop");
	// Insert an explicit fall through from the current block to the LoopBB.
	MilaBuilder->CreateBr(LoopBB);
	// Start insertion in LoopBB.
	MilaBuilder->SetInsertPoint(LoopBB);
	AllocaInst *OldVal = NamedValues[varName];
	NamedValues[varName] = Alloca;
	BasicBlock * oldBreakPoint = placeToBreak;
	placeToBreak = AfterLoopBB;
	this->body->codegen();
	placeToBreak = oldBreakPoint;
	Value *StepVal = nullptr;
	if (this->by) {
		StepVal = this->by->codegenValue();
		if (!StepVal) return;
	} else { StepVal = ConstantInt::get(*MilaContext, APInt(32, 1, true));}
	Value *EndCond = this->endValue->codegenValue();
	if (!EndCond)
		return;
	Value *CurVar = MilaBuilder->CreateLoad(Alloca, varName.c_str());
	Value *NextVar;
	if (ascending)
	NextVar = MilaBuilder->CreateAdd(CurVar, StepVal, "nextvar");
	else NextVar = MilaBuilder->CreateSub(CurVar, StepVal, "nextvar");
	MilaBuilder->CreateStore(NextVar, Alloca);
	EndCond = MilaBuilder->CreateICmpNE(EndCond , CurVar);
	MilaBuilder->CreateCondBr(EndCond, LoopBB, AfterLoopBB);
	f->getBasicBlockList().push_back(AfterLoopBB);
	MilaBuilder->SetInsertPoint(AfterLoopBB);
	BreakedInBlock = false;
	ExitedInBlock = false;
	if (OldVal)  NamedValues[varName] = OldVal;
	else  NamedValues.erase(varName);
}

void AST::While::codegenTranslation( ) {
	Function* f = MilaBuilder->GetInsertBlock()->getParent();
	BasicBlock* loopBB = BasicBlock::Create(*MilaContext, "whileLoop");
	BasicBlock* loopCondBB = BasicBlock::Create(*MilaContext, "whileCond", f);
	BasicBlock* AfterLoopBB = BasicBlock::Create(*MilaContext, "afterWhileLoop");
	MilaBuilder->CreateBr(loopCondBB);
	MilaBuilder->SetInsertPoint(loopCondBB);
	Value* cond = condition->codegenValue();
	cond = MilaBuilder->CreateICmpNE(cond, ConstantInt::get(*MilaContext, APInt(32, 0, true)));
	MilaBuilder->CreateCondBr(cond, loopBB, AfterLoopBB);
	f->getBasicBlockList().push_back(loopBB);
	MilaBuilder->SetInsertPoint(loopBB);
	BasicBlock *oldBreakPoint = placeToBreak;
	placeToBreak = AfterLoopBB;
	BreakedInBlock = false;
	this->body->codegen();
	placeToBreak = oldBreakPoint;
	if (!BreakedInBlock) MilaBuilder->CreateBr(loopCondBB);
	f->getBasicBlockList().push_back(AfterLoopBB);
	MilaBuilder->SetInsertPoint(AfterLoopBB);
	BreakedInBlock = false;
	ExitedInBlock = false;
}

Value *AST::BinOp::codegenValue( ) {
	Value *l = LHS->codegenValue(), *r = RHS->codegenValue();
	if (!l || !r) return NULL;
	Value * retResult = NULL;
	switch (op) {
		case bo_plus:
			retResult = MilaBuilder->CreateAdd(l, r);  break;
		case bo_minus:
			retResult = MilaBuilder->CreateSub(l, r);  break;			
		case bo_div:
			retResult = MilaBuilder->CreateSDiv(l, r); break;
		case bo_multiply:
			retResult = MilaBuilder->CreateMul(l, r);  break;
		case bo_mod:
			retResult = MilaBuilder->CreateSRem(l, r); break;
		case bo_equal:
			retResult = MilaBuilder->CreateICmpEQ(l, r); break;
		case bo_notequal:
			retResult = MilaBuilder->CreateICmpNE(l, r); break;
		case bo_less:
			retResult = MilaBuilder->CreateICmpSLT(l, r); break;
		case bo_lessequal:
			retResult = MilaBuilder->CreateICmpSLE(l, r); break;
		case bo_greater:
			retResult = MilaBuilder->CreateICmpSGT(l, r); break;
		case bo_greaterequal:
			retResult = MilaBuilder->CreateICmpSGE(l, r); break;
		case bo_and:
			retResult = MilaBuilder->CreateAnd(l, r); break;
		case bo_or:
			retResult = MilaBuilder->CreateOr(l, r); break; }
	return MilaBuilder->CreateIntCast(retResult, Type::getInt32Ty(*MilaContext), true);
}

void AST::Exit::codegenTranslation( ) {
	Function * f = MilaBuilder->GetInsertBlock()->getParent();
	if (f->getReturnType() != Type::getVoidTy(*MilaContext)) {
		StringRef fName = MilaBuilder->GetInsertBlock()->getParent()->getName();
		MilaBuilder->CreateRet(MilaBuilder->CreateLoad(NamedValues[(std::string)fName]));
	} else MilaBuilder->CreateRetVoid();
	BreakedInBlock = true;
	ExitedInBlock = true;
}

void AST::Break::codegenTranslation( ) {
	MilaBuilder->CreateBr(placeToBreak);
	BreakedInBlock = true;
	ExitedInBlock = false;
}

Value *AST::FunctionCall::codegenValue( ) {
	Function *f =MilaModule->getFunction(name);
	if (!f) return NULL;
	if (f->arg_size() != parameters.size()) return NULL;
	vector<Value *> ArgsV;
	for (size_t i = 0; i < parameters.size(); i++)
		ArgsV.push_back(parameters[i]->codegenValue());

	return MilaBuilder->CreateCall(f, ArgsV);
}

void AST::BuiltinFunctions::codegenTranslation( ) {
	if (name == "write" || name == "writeln") {
		auto val = parameters[0]->codegenValue();
		if (val->getType() == Type::getInt32Ty(*MilaContext)) {
			MilaBuilder->CreateCall(MilaModule->getFunction("printf"), {globalNumberPrintFormat, val});
			if (name == "writeln") MilaBuilder->CreateCall(MilaModule->getFunction("printf"), {globalPrintfNewLineFormat});
		}else {
			GlobalVariable *var =
			new GlobalVariable( *MilaModule, ArrayType::get(IntegerType::get(*MilaContext, 8), val->getType()->getArrayNumElements()),
			true, GlobalValue::PrivateLinkage, (Constant*)val, ".str");
			Constant *zero = Constant::getNullValue(IntegerType::getInt32Ty(*MilaContext));
			std::vector<Constant*> indices;
			indices.push_back(zero);
			indices.push_back(zero);
			Constant *var_ref = ConstantExpr::getGetElementPtr(var->getValueType(), var, indices);
			MilaBuilder->CreateCall(MilaModule->getFunction("printf"), {var_ref});
			if (name == "writeln") MilaBuilder->CreateCall(MilaModule->getFunction("printf"), {globalPrintfNewLineFormat});
		}
	} else if (name == "readln"){
		Value * paramAddress = ((Variable *) (parameters[0].get()))->codegenAddress();
		MilaBuilder->CreateCall( MilaModule->getFunction("scanf"), {globalNumberPrintFormat, paramAddress});
	} else if (name == "dec"){
		Value * paramAddress = ((Variable *) (parameters[0].get()))->codegenAddress();
		Value * currVal = parameters[0]->codegenValue();
		MilaBuilder->CreateStore(MilaBuilder->CreateSub(currVal, ConstantInt::get(Type::getInt32Ty(*MilaContext), 1, true)), paramAddress);
	}else { Function *f =MilaModule->getFunction(name);
		if (!f) return;
		if (f->arg_size() != parameters.size()) return;
		vector<Value *> ArgsV;
		for (size_t i = 0; i < parameters.size(); i++)
			ArgsV.push_back(parameters[i]->codegenValue());
		MilaBuilder->CreateCall(f, ArgsV);
	}
	BreakedInBlock = false;
	ExitedInBlock = false;
}

void AST::Program::codegenTranslation( ) {
	Function *mprintf = Function::Create(FunctionType::get(
	Type::getInt32Ty(*MilaContext), {Type::getInt8PtrTy(*MilaContext)}, true),
													 Function::ExternalLinkage, Twine("printf"),
													MilaModule.get());
	mprintf->setCallingConv(CallingConv::C);

	Function *mscanf = Function::Create(FunctionType::get(Type::getInt32Ty(*MilaContext), {Type::getInt8PtrTy(*MilaContext)}, true), Function::ExternalLinkage,
													Twine("scanf"),MilaModule.get());
	mscanf->setCallingConv(CallingConv::C);

	Function *main = Function::Create(FunctionType::get(IntegerType::getInt32Ty(*MilaContext), {}, false), 
	GlobalValue::ExternalLinkage, "main",MilaModule.get()); main->setCallingConv(CallingConv::C);
	BasicBlock *mainBlock = BasicBlock::Create(*MilaContext, "mainBlock", main);
	MilaBuilder->SetInsertPoint(mainBlock);
	globalNumberPrintFormat = MilaBuilder->CreateGlobalStringPtr("%d");
	globalPrintfNewLineFormat = MilaBuilder->CreateGlobalStringPtr("\n");
	for (auto &it : declarations) {
		it->codegenTranslation(true);
	}
	this->body->codegen();
	MilaBuilder->CreateRet(ConstantInt::get(*MilaContext, APInt(32, 0)));
}
void AST::Program::codegen( ) {	
	MilaContext = std::make_unique <LLVMContext>();	
	MilaModule = std::make_unique <Module>("myMila", *MilaContext);
	MilaBuilder = std::make_unique <IRBuilder<> >(*MilaContext);
	this->codegenTranslation();
}
void AST::Program::printModule( ) {
	MilaModule->print(outs(), nullptr);
}
