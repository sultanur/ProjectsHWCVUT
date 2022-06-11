#include <iostream>
#include "lexer.hpp"
/*
 * Function to return the next token from standard input
 * the variable 'm_IdentifierStr' is set there in case of an identifier,
 * the variable 'm_NumVal' is set there in case of a number.
 */
const std::string& Lexer:: identifierStr( ) const { return m_IdentifierStr; }
int Lexer:: numVal( ) { return m_NumVal; }
std::string Lexer::String( ) { return m_string;}

int Lexer::gettok()  {
	static int LastChar = ' ';

	// Skip any whitespace.
	while (isspace(LastChar))
		LastChar = getchar();

	if (isalpha(LastChar))  // identifier: [a-zA-Z][a-zA-Z0-9\_]*
	{ 
		m_IdentifierStr = LastChar;
		while (isalnum((LastChar = getchar() )) || LastChar == '_')
			m_IdentifierStr += LastChar;
		auto foundkeyword = m_keywordTable.find( m_IdentifierStr );
		if (foundkeyword != m_keywordTable.end( ) ) {
			return foundkeyword->second;
		}
		return tok_identifier;
	}

	if (isdigit(LastChar)) { // Decimal number: [0-9]+
		std::string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();
		} while (isdigit(LastChar));

		m_NumVal = strtol(NumStr.c_str(), nullptr, 10);
		return tok_number;
	}
	// Comment until end of line.
	if (LastChar == '#') {		
		do
			LastChar = getchar();
		while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

		if (LastChar != EOF)
			return gettok();
		else return tok_eof;
	}

	if (LastChar == '$') { // Hex number: $[0-9]+
		std::string NumStr;
		LastChar = getchar();
		while (isxdigit(LastChar)) {
			NumStr += LastChar;
			LastChar = getchar();
		}
		m_NumVal = strtol(NumStr.c_str(), nullptr, 16);
		return tok_number;
	}

	if (LastChar == '&') { // Octal number: &[0-7]+
		std::string NumStr;
		LastChar = getchar();
		while (isdigit(LastChar) && LastChar < '8') {
			NumStr += LastChar;
			LastChar = getchar();
		}
		m_NumVal = strtol(NumStr.c_str(), nullptr, 8);
		return tok_number;
	}

	if (LastChar == '\'') {
		m_string = "";
		while ((LastChar = getchar()) != '\'') {
			if (LastChar == EOF) return tok_eof;
			if (LastChar == '\\') {
				if ((LastChar = getchar()) == '\'') {
					m_string += '\'';
					continue;
				} else m_string += '\\';
			}
			m_string += LastChar;
		}
		LastChar = getchar();
		return tok_string;
	}

	if (LastChar == '/') {
		if ((LastChar = getchar()) == '*') {
			bool end = false;
			do {
				LastChar = getchar();
				if (!end) {
					if (LastChar == '*') end = true;
				}
				else
					if (LastChar == '/') break;
					else end = false;
			}
			while (LastChar != EOF);
			if (LastChar == EOF) return tok_eof;
			LastChar = getchar();
			return gettok();
		}
		else return tok_error;
	}

	int token = tok_error;
	if (LastChar == '+') token = tok_plus;
	else if (LastChar == '-')  token = tok_minus;
	else if (LastChar == '*')  token = tok_multiply;
	else if (LastChar == '=')  token = tok_equal;
	else if (LastChar == ':') {
		LastChar = getchar();
		if (LastChar == '=')   token = tok_assign;
		else return tok_typedefine;
	} else if (LastChar == '<') {
		LastChar = getchar();
		if (LastChar == '=') token = tok_lessequal;
		else if (LastChar == '>') token = tok_notequal;
		else return tok_less;
	} else if (LastChar == '>') {
		LastChar = getchar();
		if (LastChar == '=') token = tok_greaterequal;
		else return tok_greater;
	} else if (LastChar == '(') token = tok_parenthesisLeft;
	else if (LastChar == ')') 	token = tok_parenthesisRight;
	else if (LastChar == '[') 	token = tok_squarebracketLeft;
	else if (LastChar == ']') 	token = tok_squarebracketRight;
	else if (LastChar == ',') 	token = tok_comma;
	else if (LastChar == ';') 	token = tok_semicolon;
	else if (LastChar == '.') 	token = tok_dot;

	if (LastChar == EOF)
		return tok_eof;
	LastChar = getchar();
	return token;
}


