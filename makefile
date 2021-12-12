all: prog1

prog1:
	gcc -Wall -fsanitize=address,undefined -o task3 task3.c -lm
	 #CFLAGS=-std=gnu99 -Wall -fsanitize=thread,undefined
	# LDFLAGS=-fsanitize=thread,undefined
	# LDLIBS=-lpthread -lm

zip:
	tar -cjf espins.tar.bz2 simple.c
	tar -tjf espins.tar.bz2
upload:
	cp espins.tar.bz2 /home2/samba/sobotkap/unix
