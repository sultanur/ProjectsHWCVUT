#include "parser.hpp"

//Use tutorials in: https://llvm.org/docs/tutorial/

int main (int argc, char *argv[]) {
    Parser parser;

    parser.getNextToken();
    parser.MainLoop( );

    

    return 0;
}
