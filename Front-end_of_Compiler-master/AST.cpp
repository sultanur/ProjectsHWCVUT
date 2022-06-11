#include <memory>
#include <vector>
#include "AST.hpp"
using namespace std;
using namespace AST;

//*********CONSTRUCTORS OF AST NODES************//
AST::Number::Number (int val) : val(val) { }

AST::String::String ( const string words ) : words ( words ) { }

AST::Array:: Array ( unique_ptr<Number> start, unique_ptr<Number> end, shared_ptr< DataType> type) :
                    startIndex(move(start)), endIndex(move(end)), type(type) { }

AST::Variable:: Variable ( const string &name ) : name(name) { }

AST::ArrayVariable:: ArrayVariable ( unique_ptr<VarType> var, unique_ptr<AST::Expression> index) :
											                        var(move(var)), index(move(index)) { }

AST::BinOp:: BinOp ( unique_ptr<AST::Expression> left, unique_ptr<AST::Expression> right , AST::binOperation op ):
					          LHS(move(left)), RHS(move(right)), op(op) { }

AST::VarDeclaration:: VarDeclaration(const string &name, shared_ptr<AST:: DataType> type) : 
                                    identifier(name), type(type)  { }

AST::ConstDeclaration::ConstDeclaration(const string &name, int val) : identifier(name), value(val)  { }
                                       
AST::FunctionProto:: FunctionProto(const string &name, vector<unique_ptr<AST::VarDeclaration>> params,
                                  shared_ptr<DataType> retType) :name(name), parameters(move(params)),retType(retType) { }
                                                         
AST::ProcedureProto::ProcedureProto(  const string &name, vector<unique_ptr<AST::VarDeclaration>> params):name(name), parameters(move(params)) { }  
                                                                                                               
AST::FunctionDeclaration::FunctionDeclaration ( unique_ptr<AST::FunctionProto> proto, 
                                                vector<unique_ptr<Declaration>> declarations, unique_ptr<AST::Body> body) :
                                                proto(move(proto)), declarations(move(declarations)), body(move(body)) { }

AST::ProcedureDeclaration::ProcedureDeclaration ( unique_ptr<AST::ProcedureProto> proto, 
                                                  vector<unique_ptr<Declaration>> declarations, unique_ptr<AST::Body> body) :
                                                  proto(move(proto)), declarations(move(declarations)), body(move(body)) { }

AST::Body::Body ( vector<unique_ptr<AST::Statement>> statements) : statements(move(statements)) { }

AST::Assign::Assign ( unique_ptr<AST::VarType> var, unique_ptr<AST::Expression> value) :
                      variable (move(var)), value(move(value)) { }
AST::If::If ( unique_ptr<AST::Expression> condition, unique_ptr<AST::Body> then, unique_ptr<AST::Body> elseBody) :
			        condition(move(condition)), then(move(then)), elseBody(move(elseBody)) { }

AST::For::For ( const string &varName, unique_ptr<AST::Expression> startValue,unique_ptr<AST::Expression> endValue,
				        bool ascending, unique_ptr<AST::Expression> by, unique_ptr<AST::Body> body) : 
                varName(varName), startValue(move(startValue)), endValue(move(endValue)), ascending(ascending), 
                by(move(by)), body(move(body)) {}

AST::While::While(  unique_ptr<AST::Expression> condition, unique_ptr<AST::Body> doBody) : 
                    condition( move(condition)), body(move(doBody)) { }

AST::BuiltinFunctions::BuiltinFunctions ( const string &name, vector<unique_ptr<AST::Expression>> parameters) : 
                                          name( name), parameters(move(parameters)) {}
                        
AST::FunctionCall::FunctionCall ( const string &name, vector<unique_ptr<AST::Expression>> parameters) : 
																  name(name),parameters(move(parameters)) { }
																											  																								
AST::Program::Program ( const string &name, vector<unique_ptr<Declaration>> declarations, unique_ptr<AST::Body> body) :
                        name(name), declarations(move(declarations)), body(move(body)) {}
