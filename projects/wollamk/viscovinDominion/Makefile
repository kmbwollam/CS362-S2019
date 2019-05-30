CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

randomtest: randomtest.c dominion.o rngs.o      
	gcc -o randomtest -g  randomtest.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard3: randomtestcard3.c dominion.o rngs.o      
	gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)

randomtestcard1: randomtestcard1.c dominion.o rngs.o      
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard2: randomtestcard2.c dominion.o rngs.o      
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)

randomtestresults: randomtestcard3.c randomtestcard1.c randomtestcard2.c dominion.o rngs.o
	echo "Result for running Dominion Random Tests:" &> unittestresults.out
	echo "randomtestcard3.c:" &>> randomtestresults.out
	gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard3 &>> randomtestresults.out

	echo "randomtestcard1.c:" &>> randomtestresults.out
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard1 &>> randomtestresults.out

	echo "randomtestcard2.c:" &>> randomtestresults.out
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	-./randomtestcard2 &>> randomtestresults.out
	gcov dominion.c  -bf &>> randomtestresults.out
	
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)	

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)	

unittestresults: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 playdom player
	-./unittest1 &> unittestresults.out
	-./unittest2 &>> unittestresults.out
	-./unittest3 &>> unittestresults.out
	-./unittest4 &>> unittestresults.out
	-./cardtest1 &>> unittestresults.out
	-./cardtest2 &>> unittestresults.out
	-./cardtest3 &>> unittestresults.out
	-./cardtest4 &>> unittestresults.out
	gcov -f dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out randomtestadventurer randomtestcard1 randomtestcard2 
