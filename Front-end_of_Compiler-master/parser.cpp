#include <algorithm>
#include <memory>
#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"

InvalidTokException::InvalidTokException ( 	const std::vector <int> & tokens, int CurTok ) :
											tokens ( tokens ), CurTok ( CurTok ) { }
std::string InvalidTokException:: ErrorMessage ( ) const {
	std::string output = "Invalid token ";
	for (auto const & token : tokens )
		output += std::to_string(token) + ",";
	if (!tokens.empty()) 
		output.erase(output.length() - 1);
	return (output + " , provided " + std::to_string( CurTok ) );
}

Parser::Parser() { }
 /* PARSERS */
int Parser::  getNextToken( ) {
	//std::cout <<"token " <<  CurTok << std::endl; 
	return CurTok = m_Lexer.gettok();
}
void Parser:: parseToken ( int token ) {
	if (CurTok != token ) {
		std::cout << CurTok << " !=  "  <<  token << std::endl;	
		throw InvalidTokException( { token }, CurTok); 	
	} 	
	IdentifierStr = m_Lexer.identifierStr( );
	NumVal = m_Lexer.numVal( );
	getNextToken( );
}
shared_ptr<DataType> Parser:: parseType( ) {
	if (CurTok == tok_array) {
		getNextToken();
		parseToken(tok_squarebracketLeft);
		unique_ptr<Number> start = parseNumber();
		parseToken(tok_dot);
		parseToken(tok_dot);
		unique_ptr<Number> last = parseNumber();
		parseToken(tok_squarebracketRight);
		parseToken(tok_of);
		return make_shared<Array>(move(start), move(last), parseType());

	} else if (CurTok == tok_integer) {
		getNextToken();
		return make_shared<Integer>();
	} else throw InvalidTokException({tok_integer, tok_array}, CurTok);
}
unique_ptr<VarType> Parser::  parseVarType (string name) {
	unique_ptr<VarType> result = make_unique<Variable>( name );
	while (CurTok == tok_squarebracketLeft) {
		result = parseArrayVarType(move(result));
	}
	return result;
}
unique_ptr<Number> Parser::   parseNumber( ) {
	if (CurTok == tok_minus) {
		getNextToken();
		parseToken(tok_number);
		return make_unique<Number>(-NumVal);
	} 
	parseToken(tok_number);
	return make_unique<Number>(NumVal);
}
unique_ptr<ArrayVariable> Parser:: parseArrayVarType(unique_ptr<VarType> base) {
	parseToken(tok_squarebracketLeft);
	unique_ptr<Expression> index_array = parseExpression();
	parseToken(tok_squarebracketRight);
	return make_unique<ArrayVariable>(move(base), move(index_array));
}
vector<unique_ptr<VarDeclaration>> Parser::   parseVarDeclaration( ) {
	vector<string> variables;
	parseToken(tok_var);
	parseToken(tok_identifier);
	variables.push_back(IdentifierStr);
	while (CurTok == tok_comma) {
		getNextToken();
		parseToken(tok_identifier);
		variables.push_back(IdentifierStr);
	}
	parseToken(tok_typedefine);
	auto type = parseType();
	parseToken(tok_semicolon);
	vector<unique_ptr<VarDeclaration>> result;
	for (auto vars : variables) {
		result.push_back(move(make_unique<VarDeclaration>(vars, type)));
	}
	while (CurTok == tok_identifier) {
		variables.clear();
		variables.push_back(m_Lexer.identifierStr());
		getNextToken();
		while (CurTok == tok_comma) {
			parseToken(tok_identifier);
			variables.push_back(IdentifierStr);
		}
		parseToken(tok_typedefine);
		type = move(parseType());
		parseToken(tok_semicolon);
		for (auto vars : variables) {
			result.push_back(move(make_unique<VarDeclaration>(vars, move(type))));
		}
	}
	return result;
}
vector<unique_ptr<ConstDeclaration>> Parser:: parseConstsDeclaration( ) {
	vector<unique_ptr<ConstDeclaration>> result;
	parseToken(tok_const);
	do {
		parseToken(tok_identifier);
		string name = IdentifierStr;
		parseToken(tok_equal);
		parseToken(tok_number);
		result.push_back(move(make_unique<ConstDeclaration>(name, NumVal)));
		parseToken(tok_semicolon);
	} while (CurTok == tok_identifier);
	return result;
}
vector<unique_ptr<VarDeclaration>> Parser:: parseParamDeclaration( ) {
	vector<unique_ptr<VarDeclaration>> result;
	string name;
	if (CurTok == tok_identifier) {
		name = m_Lexer.identifierStr();
		getNextToken();
		parseToken(tok_typedefine);
		result.push_back(move(make_unique<VarDeclaration>(name, move(parseType()))));
		while (CurTok == tok_semicolon) {
			getNextToken();
			parseToken(tok_identifier);
			name = IdentifierStr;
			parseToken(tok_typedefine);
			result.push_back(move(make_unique<VarDeclaration>(name, move(parseType()))));
		}
	}
	return result;
}
unique_ptr<FunctionProto> Parser::  parseFunctionProto( ) {
	parseToken(tok_function);
	parseToken(tok_identifier);
	string name = IdentifierStr;
	parseToken(tok_parenthesisLeft);
	auto parameters = move(parseParamDeclaration());
	parseToken(tok_parenthesisRight);
	parseToken(tok_typedefine);
	auto type = parseType();
	parseToken(tok_semicolon);
	return make_unique<FunctionProto>(name, move(parameters), type);
}
unique_ptr<ProcedureProto> Parser:: parseProcedureProto( ) {
	parseToken(tok_procedure);
	parseToken(tok_identifier);
	string name = IdentifierStr;
	parseToken(tok_parenthesisLeft);
	auto parameters = move(parseParamDeclaration());
	parseToken(tok_parenthesisRight);
	parseToken(tok_semicolon);
	return make_unique<ProcedureProto>(name, move(parameters));
}
unique_ptr<Body> Parser:: parseBody( ) {
	vector<unique_ptr<Statement>> statements;
	if (CurTok == tok_begin) {
		getNextToken();
		if (CurTok == tok_end) {
			return make_unique<Body>(move(statements));
		}
		statements.push_back(parseStatement());
		while (CurTok == tok_semicolon) {
			getNextToken();
			if (CurTok == tok_end) break;
			statements.push_back(parseStatement());
		}
		parseToken(tok_end);
		return make_unique<Body>(move(statements));
	} else {
		statements.push_back(parseStatement());
		return make_unique<Body>(move(statements));
	}
}
unique_ptr<FunctionDeclaration> Parser:: parseFunction( ) {
	unique_ptr<FunctionProto> proto = parseFunctionProto();
	vector<unique_ptr<Declaration>> declarations;
	unique_ptr<Body> body = NULL;
	if (CurTok == tok_forward){
		getNextToken();
		parseToken(tok_semicolon);
		return make_unique<FunctionDeclaration>(move(proto), move(declarations), move(body));
	}
	while (true) {
		if (CurTok == tok_var) {
			auto res = parseVarDeclaration();
			for (unsigned int i = 0; i < res.size(); i++) {
				declarations.push_back(move(res.at(i)));
			}
		} else if (CurTok == tok_const) {
			auto res = parseConstsDeclaration();
			for (unsigned int i = 0; i < res.size(); i++) {
				declarations.push_back(move(res.at(i)));
			}
		} else {
			body = parseBody();
			break;
		}
	}
	parseToken(tok_semicolon);
	return make_unique<FunctionDeclaration>(move(proto), move(declarations), move(body));
}
unique_ptr<ProcedureDeclaration> Parser::parseProcedure( ) {
	unique_ptr<ProcedureProto> proto = parseProcedureProto();
	vector<unique_ptr<Declaration>> declarations;
	unique_ptr<Body> body = NULL;
	if (CurTok == tok_forward){
		getNextToken();
		parseToken(tok_semicolon);
		return make_unique<ProcedureDeclaration>(move(proto), move(declarations), move(body));
	}
	while (true) {
		if (CurTok == tok_var) {
			auto res = parseVarDeclaration();
			for (unsigned int i = 0; i < res.size(); i++) {
				declarations.push_back(move(res.at(i)));
			}
			continue;
		} else if (CurTok == tok_const) {
			auto constdeclares = parseConstsDeclaration();
			for (unsigned int i = 0; i < constdeclares.size(); i++) {
				declarations.push_back(move(constdeclares.at(i)));
			}
			continue;
		} else {
			body = parseBody();
			break;
		}
	}
	parseToken(tok_semicolon);
	return make_unique<ProcedureDeclaration>(move(proto), move(declarations), move(body));
}
unique_ptr<Exit> Parser::   parseExit( ) {
	parseToken(tok_exit);
	return make_unique<Exit>();
}
unique_ptr<While> Parser::  parseWhile() {
	parseToken(tok_while);
	unique_ptr<Expression> condition = parseExpression();
	parseToken(tok_do);
	unique_ptr<Body> doBody = parseBody();
	return make_unique<While>(move(condition), move(doBody));
}
unique_ptr<If> Parser:: 	parseIf( ) {
	parseToken(tok_if);
	unique_ptr<Expression> condition = parseExpression();
	parseToken(tok_then);
	unique_ptr<Body> thenBody = parseBody();
	unique_ptr<Body> elseBody = nullptr;
	if (CurTok == tok_else) {
		getNextToken();
		elseBody = move(parseBody());
	}
	return make_unique<If> ( move( condition ), move ( thenBody ), move( elseBody ));
}
unique_ptr<For> Parser:: 	parseFor( ) {
	parseToken(tok_for);
	parseToken(tok_identifier);
	string varName = IdentifierStr;
	parseToken(tok_assign);
	unique_ptr<Expression> initialVal = parseExpression();
	bool ascending;
	if (CurTok == tok_to) {
		ascending = true;
		getNextToken();
	} else if (CurTok == tok_downto) {
		ascending = false;
		getNextToken();
	} else throw InvalidTokException({tok_to, tok_downto}, CurTok);
	unique_ptr<Expression> limit = parseExpression();
	unique_ptr<Expression> by = nullptr;
	parseToken(tok_do);
	unique_ptr<Body> doBody = parseBody();
	return make_unique<For>(varName, move(initialVal), move(limit), ascending, move(by), move(doBody));
}
vector<unique_ptr<Expression>> Parser::parseParameters( ) {
	vector<unique_ptr<Expression>> result;
	if (CurTok != tok_parenthesisRight) {
		result.push_back(move(parseExpression()));
	}
	while (CurTok != tok_parenthesisRight) {
		parseToken(tok_comma);
		result.push_back(move(parseExpression()));
	}
	return result;
}
unique_ptr<BuiltinFunctions> Parser::parseBuiltinFunctions(string name) { 
	parseToken(tok_parenthesisLeft);
	auto parameters = parseParameters();
	parseToken(tok_parenthesisRight);
	return make_unique<BuiltinFunctions>(name, move(parameters));
}
unique_ptr<FunctionCall> Parser::parseFunctionCall(string name) {
	parseToken(tok_parenthesisLeft);
	auto parameters = parseParameters();
	parseToken(tok_parenthesisRight);
	return make_unique<FunctionCall>(name, move(parameters));
}
unique_ptr<Expression> Parser::parseIdentifierExpression() {
	parseToken(tok_identifier);
	string name = IdentifierStr;
	if (CurTok == tok_parenthesisLeft)
		return parseFunctionCall(name);
	else return parseVarType(name);
}
unique_ptr<Expression> Parser::parseString( ) {
	parseToken(tok_string);
	return make_unique<String>( m_String);
}
unique_ptr<Expression> Parser::parseLiterals( ) {
	if (CurTok == tok_number || CurTok == tok_minus) {
		return parseNumber();
	} else if (CurTok == tok_identifier) {
		return parseIdentifierExpression();
	} else if (CurTok == tok_string) {
		return parseString();
	} else {
		parseToken(tok_parenthesisLeft);
		auto expression = parseExpression();
		parseToken(tok_parenthesisRight);
		return expression;////////////
	}
}
unique_ptr<Expression> Parser::parseNextExpression( ) {
	unique_ptr<Expression> result = parseLiterals();
	while (1) {
		if (CurTok == tok_multiply) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseLiterals(), bo_multiply);
			continue;
		} else if (CurTok == tok_div) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseLiterals(), bo_div);
			continue;
		} else if (CurTok == tok_mod) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseLiterals(), bo_mod);
			continue;
		} else break;
	}
	return result;
}
unique_ptr<Expression> Parser::parseFirstExpression( ) {
	unique_ptr<Expression> result = parseNextExpression();
	while (1) {
		if (CurTok == tok_plus) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseNextExpression(), bo_plus);
			continue;
		} else if (CurTok == tok_minus) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseNextExpression(), bo_minus);
			continue;
		} else break;
	}
	return result;
}
unique_ptr<Expression> Parser::parseExpression( ) {
	unique_ptr<Expression> result = parseFirstExpression();
	while (1) {
		if (CurTok == tok_equal) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_equal);
			continue;
		} else if (CurTok == tok_notequal) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_notequal);
			continue;
		} else if ((CurTok) == tok_less) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_less);
			continue;
		} else if ((CurTok) == tok_lessequal) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_lessequal);
			continue;
		} else if ((CurTok) == tok_greater) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_greater);
			continue;
		} else if ((CurTok) == tok_greaterequal) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_greaterequal);
			continue;
		} else if ((CurTok) == tok_and) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_and);
			continue;
		} else if ((CurTok) == tok_or) {
			getNextToken();
			result = make_unique<BinOp>(move(result), parseFirstExpression(), bo_or);
			continue;
		} else break;
	}
	return result;
}
unique_ptr<Assign> Parser:: parseAssign(string name) {
	unique_ptr<VarType> Vartype = parseVarType(name);
	parseToken(tok_assign);
	return make_unique<Assign>(move(Vartype), parseExpression());
}
unique_ptr<Assign> Parser:: parseAssign( ) {
	parseToken(tok_identifier);
	return parseAssign(IdentifierStr);
}
unique_ptr<Break>  Parser:: parseBreak( ){
	parseToken(tok_break);
	return make_unique<Break>();
}
unique_ptr<Statement> Parser::parseIdentifierStatement( ) {
	parseToken(tok_identifier);
	if (CurTok == tok_parenthesisLeft) return parseBuiltinFunctions(IdentifierStr);
	else return parseAssign(IdentifierStr);
}
unique_ptr<Statement> Parser::parseStatement( ) {
	if (CurTok == tok_if) return parseIf();
	else if (CurTok == tok_while) 	return parseWhile();
	else if (CurTok == tok_for) 		return parseFor();
	else if (CurTok == tok_exit) 		return parseExit();
	else if (CurTok == tok_break) 	return parseBreak();
	else if (CurTok == tok_identifier) 	return parseIdentifierStatement();
	else throw InvalidTokException({tok_if, tok_while, tok_for, tok_exit, tok_identifier}, CurTok);
}
unique_ptr<Program> Parser::  parseProgram() {
	parseToken(tok_program);
	parseToken(tok_identifier);
	string name = IdentifierStr;
	parseToken(tok_semicolon);
	vector<unique_ptr<Declaration>> declarations;
	unique_ptr<Body> body;
	while (true) {
		if (CurTok == tok_var) {
			auto res = parseVarDeclaration();
			for (unsigned int i = 0; i < res.size(); i++) {
				declarations.push_back(move(res.at(i)));
			} continue;
		} else if (CurTok == tok_const) {
			auto res = parseConstsDeclaration();
			for (unsigned int i = 0; i < res.size(); i++) {
				declarations.push_back(move(res.at(i)));
			} continue;
		} else if (CurTok == tok_function) {
			declarations.push_back(move(parseFunction()));
			continue;
		} else if (CurTok == tok_procedure) {
			declarations.push_back(move(parseProcedure()));
			continue;
		} else {
			body = parseBody();
			break;
		}
	}

	parseToken(tok_dot);
	return make_unique<Program>(name, move(declarations), move(body));
}
void Parser:: HandleProgram ( ) {
	auto res = parseProgram ( );
	res->codegen ( );
	res->printModule ( );  

}
void Parser:: MainLoop ( ) {
	//getNextToken();
    switch ( CurTok ) {
    	case tok_eof:
      		return;
      	case ';': // ignore top-level semicolons.
      		getNextToken();
      		break;
		case tok_program:
			HandleProgram ( );
			break;
    	}
}

