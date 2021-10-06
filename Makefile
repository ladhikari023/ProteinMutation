CC=gcc
CFLAGS=-pedantic -ansi -Wall
B117 = B.1.1.7 d69 d70 d144 N501Y A570D P681H T716I S982A D1118H

all: b117

b117: protein
	./protein $(B117) < spike.in > mutated.out

protein: protein.o
	$(CC) $(CFLAGS) -o protein protein.o

protein.o:
	$(CC) $(CFLAGS) -g -c protein.c

valgrind: protein
	valgrind --tool=memcheck --leak-check=yes ./protein $(B117) < spike.in > mutated.out

clean:
	rm protein protein.o
