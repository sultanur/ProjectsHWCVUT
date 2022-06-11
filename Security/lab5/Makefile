CC = gcc
CFLAGS = -g
LDFLAGS = -lssl -lcrypto
MY_VER =  cert.pem out.txt

all:	lab5
run:	
	./lab5 $(MY_VER)
	
lab5:	lab5.o 
	$(CC) -o $@ $< $(LDFLAGS)
%.o:	%.c
	$(CC) -c -o $@ $< $(CFLAGS)
clean:	rm -f *.o
