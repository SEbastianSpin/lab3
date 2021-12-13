CC=gcc
CFLAGS=-Wall -fsanitize=address,undefined -g -Og -pthread
LDFLAGS=-fsanitize=address,undefined

all: prog1

prog1:
	$(CC) $(CFLAGS) -o prog17 prog17.c
	

zip:
	tar -cjf espins.tar.bz2 simple.c
	tar -tjf espins.tar.bz2
upload:
	cp espins.tar.bz2 /home2/samba/sobotkap/unix



#all: prog17
#prog17: prog17.c	
#	$(CC) $(CFLAGS) -o prog17 prog17.c
#.PHONY: clean all
#clean:
#	rm prog17
