CXX=g++
LD=g++


CXXFLAGS=-std=c++17
LDFLAGS=
SRC=src
OBJ=obj


$(shell g++ -MM src/*cpp | sed 's/^/obj\//g' > makefile.d)

all:	compile
doc:
compile: sultanur
sultanur:	$(OBJ)/main.o $(OBJ)/CCalendar.o  $(OBJ)/CDate.o $(OBJ)/Event.o  $(OBJ)/CEventTypes.o $(OBJ)/ExportEvents.o $(OBJ)/Register.o  $(OBJ)/Menu.o $(OBJ)/Time.o
	$(LD) $(LDFLAGS)  -o  $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o   $@ $<

clean:
	rm -f obj/*
	rm -f calc
	rm makefile.d
	rm sultanur

include makefile.d

run:
	./sultanur



