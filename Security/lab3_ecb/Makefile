#make
#make run


CXX = g++
CC = gcc
CFLAGS = -g
LDFLAGS = -lcrypto
compare = diff -qs homer-simpson.bmp  homer-simpson_dec.bmp

all: ./ecb.o  


./ecb.o: ecb.cpp
	$(CXX) -o $@ $< $(LDFLAGS)

	

run:
	./ecb.o 
	$(compare)
	
clean:
	rm -f *.o

