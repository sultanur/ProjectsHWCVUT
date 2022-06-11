#ifndef PJPPROJECT_PARSER_HPP
#define PJPPROJECT_PARSER_HPP

#include <string>
#include <vector>
#include "lexer.hpp"
#include "AST.hpp"
using namespace std;
using namespace AST;

class Parser {
public:

	Lexer m_Lexer; // lexer is used to read tokens
	int NumVal;   
    int CurTok;   // to keep the current token
	string m_String;
	std::string IdentifierStr;
    const std::vector <int> token;
    
	int getNextToken();
	void parseToken(int token);
	Parser( ); //const Module& Generate(); // generate
    ~Parser() = default;

	void HandleProgram();
	void MainLoop();	

	shared_ptr<DataType> parseType();
	vector<unique_ptr<VarDeclaration>> parseVarDeclaration();
	vector<unique_ptr<ConstDeclaration>> parseConstsDeclaration();
	vector<unique_ptr<VarDeclaration>> parseParamDeclaration();
	unique_ptr<FunctionProto> parseFunctionProto();
	unique_ptr<ProcedureProto> parseProcedureProto();
	unique_ptr<Body> parseBody();
	unique_ptr<FunctionDeclaration>  parseFunction();
	unique_ptr<ProcedureDeclaration> parseProcedure();
	unique_ptr<Program> parseProgram();
	unique_ptr<Number> 	parseNumber();
	unique_ptr<Exit> 	parseExit();
	unique_ptr<If> 	parseIf();
	unique_ptr<While> parseWhile();
	unique_ptr<For>   parseFor();
	vector<unique_ptr<Expression>> parseParameters();
	unique_ptr<BuiltinFunctions> parseBuiltinFunctions(string name);
	unique_ptr<FunctionCall> parseFunctionCall(string name);
	unique_ptr<ArrayVariable> parseArrayVarType(unique_ptr<VarType> base);
	unique_ptr<VarType>  	parseVarType(string name);
	unique_ptr<Expression> 	parseIdentifierExpression();
	unique_ptr<Expression> 	parseString();
	unique_ptr<Expression> 	parseLiterals();
	unique_ptr<Expression> 	parseNextExpression();
	unique_ptr<Expression> 	parseFirstExpression();
	unique_ptr<Expression> 	parseExpression();
	unique_ptr<Assign> parseAssign(string name);
	unique_ptr<Assign> parseAssign();
	unique_ptr<Statement> 	parseIdentifierStatement();
	unique_ptr<Break> 		parseBreak();
	unique_ptr<Statement> 	parseStatement();
};

class InvalidTokException : public std::exception {
public:
	InvalidTokException(const std::vector<int> & tokens, int CurTok);

	std::string  ErrorMessage( ) const;
	const std::vector<int> tokens;
	const int CurTok;
};

#endif //PJPPROJECT_PARSER_HPP

