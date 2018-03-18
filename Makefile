CC=clang
CFLAGS=-I .

ecpri: ecpri.o main.o
	$(CC) -o ecpri ecpri.o main.o $(CFLAGS)

clean: 
	rm *.o
	rm ecpri