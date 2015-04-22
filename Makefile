main: list.o main.o
	gcc -o main list.o main.o

list.o: list.c list.h
	gcc -g -c list.c
main.o: main.c list.h
	gcc -g -c main.c

run: main
	./main

release:
	gcc -ansi -Wall -pedantic -o main merged.c

clean:
	rm *.o