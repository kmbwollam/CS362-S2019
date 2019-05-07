CFLAGS= -Wall -fpic -coverage -lm -std=c99

testme: testme.c
	gcc -o testme testme.c -g $(CFLAGS)


#########

testresults: testme
	./testme &> testresults.out
	gcov -b testme.c >> testresults.out
	cat testme.c.gcov >> testresults.out

all: testme

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out
