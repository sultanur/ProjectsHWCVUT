#make
#make run
#make compare

CXX = g++
CC = gcc
CFLAGS = -g
LDFLAGS = -lcrypto
MY_VER1 = input.txt  pubkey.pem  ciphertext.txt
MY_VER2 = ciphertext.txt privkey.pem  decrtext.txt
compare = diff -qs input.txt  decrtext.txt

all: ./encr.o ./decr.o 
	
run:
	./encr.o $(MY_VER1)
	./decr.o  $(MY_VER2)
	$(compare)
		
./encr.o: encr.cpp
	$(CXX) -o $@ $< $(LDFLAGS)
./decr.o: decr.cpp
	$(CXX) -o $@ $< $(LDFLAGS)

clean:
	rm -f *.o





