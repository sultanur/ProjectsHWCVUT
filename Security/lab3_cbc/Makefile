#make
#make run


CXX = g++
CC = gcc
CFLAGS = -g
LDFLAGS = -lcrypto
compare = diff -qs homer-simpson.bmp  homer-simpson_dec.bmp

all: ./cbc.o  


./cbc.o: cbc.cpp
	$(CXX) -o $@ $< $(LDFLAGS)

	
run:
	./cbc.o 
	$(compare)
	
clean:
	rm -f *.o

