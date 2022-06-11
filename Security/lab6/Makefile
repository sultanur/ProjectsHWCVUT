CC = gcc
CFLAGS = -g
LDFLAGS = -lssl -lcrypto
MY_VER =  cert.pem out.txt

all:	lab6
run:	
	./lab6 $(MY_VER)
	
lab6:	lab6.o 
	$(CC) -o $@ $< $(LDFLAGS)
%.o:	%.c
	$(CC) -c -o $@ $< $(CFLAGS)
clean:	rm -f *.o
