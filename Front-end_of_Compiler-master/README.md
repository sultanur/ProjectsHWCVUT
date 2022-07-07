Extending LLVM compliler by a new frontend able to parse a Pascal inspired language called Mila language.
 I implemented front-end part of compiler:Lexer, Parser, AST and codegen for programming language Mila

- CMakeLists.txt - CMake source file
- main.hpp - main function definition
- Lexer.hpp, Lexan.cpp - Lexan related sources
- Parser.hpp, Parser.cpp - Parser related sources
- fce.c - grue for write, writeln, read function, it is compliled together with the program
- samples - directory with samples desribing syntax
- mila - wrapper script for your compiler
- runtests - test script with compiles all samples
- AST 
- codegen 

Implemented functions:

    Main function, printing numbers (print, println), reading numbers (readln), global variables support, expressions, assignment,
    
    Number constants in hexadecimal and octal base ($ and & prefix)
    
    If, While (along with break statement)
    
    For (to and downto; along with break statement)
    
    Nested blocks
    
    Statically allocated arrays (indexed in any interval)
    
    Procedures, Functions, Local variables, exit
    
    Parameters of functions and procedures
    
    Real numbers (incuding printing and reading, explicit typecast using functions int and float)
   
