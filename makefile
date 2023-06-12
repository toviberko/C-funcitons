myset: myset.o set.o
	gcc -ansi -Wall -pedantic -g myset.o set.o -o myset
set.o: set.c set.h
	gcc -c -ansi -Wall -pedantic set.c -o set.o
myset.o: myset.c set.h
	gcc -c -ansi -Wall -pedantic myset.c -o myset.o
