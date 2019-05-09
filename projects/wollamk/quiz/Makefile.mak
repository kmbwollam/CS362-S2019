CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme.o: testme.c
	gcc -c testme.c -g  $(CFLAGS)

testme: testme.o
	gcc -o testme -g testme.o $(CFLAGS)

testresults: testme
	./testme &> testresults.out
	gcov -b testme.c >> testresults.out
	cat testme.c.gcov >> testresults.out

all: testme

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out
