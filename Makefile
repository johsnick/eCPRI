CC=clang
CFLAGS=-I .

ecpri: ecpri.o main.o
	$(CC) -o ecpri ecpri.o main.o $(CFLAGS)

recieve: ecpri.o reciever.o
	$(CC) -o recieve ecpri.o reciever.o $(CFLAGS)

clean: 
	rm *.o
	rm ecpri