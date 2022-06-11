#ifndef PJPPROJECT_LEXER_HPP
#define PJPPROJECT_LEXER_HPP
#include <map>
#include <string>

/*
 * Lexer returns tokens [0-255] if it is an unknown character, 
 * otherwise one of these for known things.
 * Here are all valid tokens:
 */
enum Token {
    tok_eof =           -1,   //EOF

    tok_identifier =    -2, 
    tok_number =        -3,    
    // keywords
    tok_begin =         -4,     //begin
    tok_end =           -5,     //end
    tok_const =         -6,     //const 
    tok_procedure =     -7,     //procedure
    tok_forward =       -8,     //forward
    tok_function =      -9,     //function
    tok_if =            -10,    //if
    tok_then =          -11,    //then    
    tok_else =          -12,    //else    
    tok_program =       -13,    //program
    tok_while =         -14,    //while  
    tok_exit =          -15,    //exit
    tok_break =         -16,     //break    
    tok_var =           -17,    //var
    tok_integer =       -18,    //integer 
    tok_for =           -19,    //for
    tok_do =            -20,    //do
	tok_or =            -21,    //or
	tok_of =            -22,    //of
    // 1,2-character operators
    tok_notequal =            -23,   //  <>
    tok_lessequal =           -24,   //  <=
    tok_greaterequal =        -25,   //  >=
    tok_assign =              -26,   //  :=   
    tok_plus =                -27,   //  +
    tok_minus =               -28,   //  -
    tok_multiply =            -29,   //  *
    tok_equal =               -30,   //  =
    tok_parenthesisLeft =     -31,   //  (
    tok_parenthesisRight =    -32,   //  )
    tok_squarebracketLeft =   -33,   //  [
    tok_squarebracketRight =  -34,   //  ]
    tok_comma =               -35,   //  ,
    tok_semicolon =           -36,   //  ;
    tok_dot =                 -37,   //  .
    tok_greater =             -38,   //  >
    tok_typedefine =          -39,   //  :
    tok_less =                -40,   //  <
    
    // 3-character operators (keywords)
    tok_mod =           -41,    //mod
    tok_div =           -42,    //div    
    tok_not =           -43,    //not
    tok_and =           -44,    //and
    tok_xor =           -45,    //xor  

    // keywords in for loop
    tok_to =            -46,     //to
    tok_downto =        -47,    //downto
    
    // keywords for array
    tok_array  =        -48,  //array
    tok_error  =        -49,
	tok_string =		-50
  
};

class Lexer {
    public:
        Lexer( ) = default;
        ~Lexer( ) = default;
        int gettok( ); 
		std::string String();
        const std::string& identifierStr( ) const;
        int numVal( ) ;
		
    private:
        std::string m_IdentifierStr; 
        int m_NumVal;  
		std::string m_string; 
        std::map < std::string , int > m_keywordTable = {
                                        {"begin" ,       -4   },    
                                        {"end" ,         -5   },           
                                        {"const" ,       -6   },        
                                        {"procedure",    -7   },
                                        {"forward",      -8   },
                                        {"function",     -9   },
                                        {"if",           -10  },
                                        {"then" ,        -11  },          
                                        {"else",         -12  },
                                        {"program",      -13  },
                                        {"while",        -14  },
                                        {"exit" ,        -15  },
                                        {"break",        -16  },           
                                        {"var",          -17  },
                                        {"integer" ,     -18  },        
                                        {"for",          -19  },
                                        {"do",           -20  },
                                        {"or",           -21  },
                                        {"of",           -22  },
                                        {"mod",          -41  },
                                        {"div" ,         -42  }, 
                                        {"not",          -43  },
                                        {"and",          -44  },
                                        {"xor",          -45  }, 
                                        {"to",           -46  },
                                        {"downto" ,      -47  },
                                        {"array",        -48  } }; 


};

#endif //PJPPROJECT_LEXER_HPP
