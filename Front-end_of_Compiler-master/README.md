#This project I did during summer semester 2021 for subject PJP. I implemented front-end part of compiler:Lexer, Parser, AST and codegen for programming language Mila ( Mila was created based on language Pascal)


# Semestral work structure

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

## Literature

LLVM supplies a set of tutorials which is available here: https://llvm.org/docs/tutorial/

These tutorials are highly recommended and contains everything from lexical analysis up to transforming AST into LLVM IR.

A nice explanation of LLVM IR can be found here: https://mukulrathi.co.uk/create-your-own-programming-language/llvm-ir-cpp-api-tutorial/

## Dependencies

LLVM including headers. Bases on your OS distribution, it would be usually packages like:
`llvm`, `llvm-dev`.

For downloading this repository and building it: `git`, `cmake`, `clang` and `zlib1g-dev`.

For Ubuntu or Debian based OS use:
```
sudo apt install llvm llvm-dev clang git cmake zlib1g-dev
```

For OpenSuse it will be most likely called `llvm-devel` and `libLLVM`, search for `*llvm*` and `*LLVM*`.

### LLVM version

Recommended version is version (9,) 10, 11 or 12 (currently latest). Older version may require changes.

To get the current LLVM version, just call:
```
clang --version
```
You should get an output similar to this:
```
Ubuntu clang version 12.0.0-++rc3-4ubuntu1
Target: x86_64-pc-linux-gnu
Thread model: posix
InstalledDir: /usr/bin
```
If you need to change version of LLVM library used modify `CMakeLists.txt` based on your needs:
```
# Change this to force specific version of LLVM
# find_package(LLVM "${MAJOR}.${MINOR}" REQUIRED CONFIG)
find_package(LLVM REQUIRED CONFIG)
```
For example to force LLVM 10:
```
find_package(LLVM 10 REQUIRED CONFIG)
```
## Building

```
mkdir build &&
cd build &&
cmake ..
make
```
**To rebuild:**
```
cd build &&
make
```
Builded compiler outputs intermediate code from which llvm can generate a binary.

## Running (on Linux)
Do not call binary `mila` inside `build` directory directly, use wrapper script `mila` inside a root directory:

```
./mila
```

Details below.

## Testing samples
Run from project root. Compiles binary for all example source codes in ``sources/`` directory
```
./runtests
```

## Compiling a program
Use supplied script to compile source code into binary.


First you need to create a source file, otherwise compilation will fail:
```
touch test.mila
```

Then you can compile it with compiler.
```
./mila test.mila -o test.out
```

**How does mila wrapper script works?**

It runs `build/mila` on the source code, then `llc` and `clang` (with the fce.c file added):

```
rm -f "$OutputFileBaseName.ir"
> "$OutputFileBaseName.ir" < "$InputFileName" ${DIR}/build/mila &&
rm -f "$OutputFileBaseName.s"
llc "$OutputFileBaseName.ir" -o "$OutputFileBaseName.s" &&
clang "$OutputFileBaseName.s" "${DIR}/fce.c" -o "$OutputFileName"
```

## How should your semestral work behave?
Compiler processes source code supplied on the stdin and produces LLVM ir on its stdout.
All errors should be written to the stderr, non zero return code should be return in case of error.
No arguments are required, but the mila wrapper is prepared for -v/--verbose, -d/--debug options which can be passed to the compiler.
Other arguments can be also added for various purposes.

## How to add your own files?

You want to add `Tree.hpp` and `Tree.cpp`, change `CMakeLists.txt` by adding into `add_executable`:
```
add_executable(mila main.cpp Lexer.hpp Lexer.cpp Parser.hpp Parser.cpp)
```
Result:
```
add_executable(mila main.cpp Lexer.hpp Lexer.cpp Parser.hpp Parser.cpp Tree.hpp Tree.cpp)
```
