#ifndef SFE_AST_HPP
#define SFE_AST_HPP

#include <memory>
#include <vector>
#include <llvm/IR/Value.h>


using namespace std;

namespace AST {

	class ASTBase {
	public:
		virtual ~ASTBase() = default;
	protected:
		ASTBase() = default;
	};
	
	class DataType  {
		public:
			virtual llvm::Type *codegenType() = 0;
			virtual llvm::Constant *getInitValue() = 0;
		protected:
			DataType() = default;
	};
	class Integer : public  DataType  {
		public:
			Integer() = default;
			llvm::Type *codegenType();
			llvm::Constant *getInitValue() final;
	};
	class Expression : public ASTBase {
		public:
			virtual ~Expression ( ) = default;
			virtual llvm::Value *codegenValue() = 0;
	};
	class Statement :  public ASTBase {
		public:
			virtual void codegenTranslation() = 0;
	 	 protected:
			Statement() = default;
	};
	class Number : public Expression  {
		public:
			Number(int val);

			llvm::Value *codegenValue() final;
			const int val;
	};	
	class Array :   public  DataType  {
		public:
			Array(unique_ptr<Number> start, unique_ptr<Number> end, shared_ptr< DataType> type);
			llvm::Type *codegenType();
			llvm::Constant *getInitValue() final;
			const unique_ptr<Number> startIndex, endIndex;
			const shared_ptr< DataType> type;
	};		
	class String : public Expression  {
		public:
			String(const string words);
			llvm::Value *codegenValue() final;
			const string words;
	};
	class Body :   public ASTBase  {
	  public:
			Body(vector<unique_ptr<Statement>> statements);
			void codegen();
			const vector<unique_ptr<Statement>> statements;
	};
	class VarType : public Expression {
		public:
			virtual llvm::Value *codegenValue() = 0;
			virtual llvm::Value * codegenAddress() = 0;
		protected:
			VarType( ) = default;
	};
	class Variable : public VarType   {
		public:
			Variable(const string &name);
			llvm::Value *codegenValue() final;
			llvm::Value * codegenAddress() final;
			
			const string name;
	};
	class ArrayVariable : public VarType {
		public:
			ArrayVariable(unique_ptr<VarType> var, unique_ptr<Expression> index);
			llvm::Value *codegenValue() final;
			llvm::Value * codegenAddress() final;
			
			const unique_ptr<VarType> var;
			const unique_ptr<Expression> index;
	};
	class Declaration :  public ASTBase  {
	  public:
			virtual ~Declaration() = default;
			virtual void codegenTranslation(bool isGlobal = false) = 0;
	  protected:
			Declaration() = default;
	};
	class VarDeclaration :   public Declaration  {
		public:
			VarDeclaration(const string &name, shared_ptr <DataType> type);
			void codegenTranslation(bool isGlobal = false) final;

			const shared_ptr< DataType> type;
			const string identifier;
	};
	class ConstDeclaration : public Declaration  {
		public:
			ConstDeclaration(const string &name, int val);
			void codegenTranslation(bool isGlobal = false) final;
			const string identifier;
			const int value;
	};
	class FunctionProto  {
		public:
			FunctionProto(	const string &name, vector<unique_ptr<VarDeclaration>> params, 
										shared_ptr< DataType> retType);
			llvm::Function *codegen();
			const string name;
			const vector<unique_ptr<VarDeclaration>> parameters;
			const shared_ptr< DataType> retType;
	};
	class ProcedureProto {
		public:
			ProcedureProto ( const string &name, vector<unique_ptr<VarDeclaration>> params);
			llvm::Function *codegen();
			const string name;
			const vector<unique_ptr<VarDeclaration>> parameters;
	};
	class FunctionDeclaration  : public Declaration {
		public:
			FunctionDeclaration(unique_ptr<FunctionProto> proto, vector<unique_ptr<Declaration>> declarations,
							unique_ptr<Body> body);
			void codegenTranslation(bool isGlobal = false) final;
			const unique_ptr<FunctionProto> proto;
			const vector<unique_ptr<Declaration>> declarations;
			const unique_ptr<Body> body;
	};
	class ProcedureDeclaration : public Declaration {
		public:
			ProcedureDeclaration(unique_ptr<ProcedureProto> proto, vector<unique_ptr<Declaration>> declarations,
							 unique_ptr<Body> body);
			void codegenTranslation(bool isGlobal = false) final;
			const unique_ptr<ProcedureProto> proto;
			const vector<unique_ptr<Declaration>> declarations;
			const unique_ptr<Body> body;
	};
	enum  binOperation {
		bo_plus,
		bo_minus,
		bo_div,
		bo_multiply,
		bo_mod,
		bo_equal,
		bo_notequal,
		bo_less,
		bo_lessequal,
		bo_greater,
		bo_greaterequal,
		bo_or,
		bo_and
	};
	class BinOp : public Expression {
		public:
			BinOp(unique_ptr<Expression> left, unique_ptr<Expression> right, binOperation op);
			llvm::Value *codegenValue() final;

			const unique_ptr<Expression> LHS,RHS;
			const binOperation op;
	};
	class BuiltinFunctions :  public Statement  {
		public:
			BuiltinFunctions(const string &name, vector<unique_ptr<Expression>> parameters);
			void codegenTranslation() final;

			const string name;
			const vector<unique_ptr<Expression>> parameters;
	};
	class FunctionCall :  public Expression {
		public:
			FunctionCall(const string &name, vector<unique_ptr<Expression>> parameters);
			llvm::Value *codegenValue() final;

			const string name;
			const vector<unique_ptr<Expression>> parameters;
	};
	class Assign :  public Statement {
		public:
			Assign(unique_ptr<VarType> var, unique_ptr<Expression> value);
			void codegenTranslation() final;
			
			const unique_ptr<VarType> variable;
			const unique_ptr<Expression> value;
	};
	class If :      public Statement {
		public:
			If(unique_ptr<Expression> condition, unique_ptr<Body> then, unique_ptr<Body> elseBody);
			void codegenTranslation() final;
			
			const unique_ptr<Expression> condition;
			const unique_ptr<Body> then;
			const unique_ptr<Body> elseBody;
	};
	class For :     public Statement {
		public:
			For(const string &varName, unique_ptr<Expression> startValue,
				unique_ptr<Expression> endValue, bool ascending, unique_ptr<Expression> by,
				unique_ptr<Body> body);
			void codegenTranslation() final;
			
			const string varName;
			const unique_ptr<Expression> startValue;
			const unique_ptr<Expression> endValue;
			const bool ascending;
			const unique_ptr<Expression> by;
			const unique_ptr<Body> body;
	};
	class While :   public Statement {
		public:
			While(unique_ptr<Expression> condition, unique_ptr<Body> doBody);
			void codegenTranslation() final;
			
			const unique_ptr<Expression> condition;
			const unique_ptr<Body> body;
	};
	class Break :   public Statement {
		void codegenTranslation() final;
	};
	class Exit :    public Statement {
		void codegenTranslation() final;
	};
	class Program : public ASTBase   {
		public:
			Program(const string &name, vector<unique_ptr<Declaration>> declarations, unique_ptr<Body> body);
			void codegenTranslation();
			void codegen();
			void printModule();
			const string name;
			const vector<unique_ptr<Declaration>> declarations;
			const unique_ptr<Body> body;
	};
}


#endif //SFE_AST_H
