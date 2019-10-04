SHELL = /bin/bash

OBJS =  quesa.c quesb.c quesc.c quesd.c

CC = gcc 
all : demo

hello : quesa.o quesb.o quesc.o quesd.o
	$(CC) $(OBJS)  -o hello

demo : main.o
	$(CC) main.o -o demo

main.o : main.c quesc.c
	$(CC) main.c -c  
quesa.o : quesa.c
	$(CC) quesa.c -c 

quesb.o : quesb.c
	$(CC) quesb.c -c

quesc.o : quesc.c
	$(CC) quesc.c -c

quesd.o : quesd.c
	$(CC) quesd.c -c 

clean : 
	-rm *.o *.txt