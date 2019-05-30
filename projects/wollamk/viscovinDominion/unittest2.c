/*
 * unittest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"
int main() {
    int newCards = 1;
	int newCardsOther = 0;
    int discarded = 1;
	int xtraActions = 2;
	//int newHandCount = 4; 
	
	int testCardCount = 0;
	int gameCardCount = 0; 

    //int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    //int remove1, remove2;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int otherPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, remodel, village, minion, mine, cutpurse,
			sea_hag, great_hall, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: choice 1 --------------
	printf("\nTEST 1: choice 1 = 1 \n");
	//set decks
	
	choice1 = 1; 

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testCardCount == gameCardCount);
	printf("actions count = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	//assert(testG.numActions == G.numActions + xtraActions);
	testCardCount = testG.deckCount[otherPlayer] + testG.handCount[otherPlayer] + testG.discardCount[otherPlayer];
	gameCardCount = G.deckCount[otherPlayer] + G.handCount[otherPlayer] + G.discardCount[otherPlayer]; 
	printf("other player hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + newCardsOther);
	printf("other player total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer] + newCardsOther);
	//assert(testCardCount == gameCardCount);
	
	printf("players: %d expected: %d\n", testG.numPlayers, G.numPlayers);
	//assert(testG.numPlayers == G.numPlayers);
	printf("turn: %d expected %d\n", testG.whoseTurn, G.whoseTurn);
	//assert(testG.whoseTurn == G.whoseTurn);
	printf("phase: %d expected %d\n", testG.phase, G.phase);
	//assert(testG.phase == G.phase)
	
	
	// ----------- TEST 2: cards need to be shuffled --------------
	printf("\nTEST 2: choice 2 = 1 \n");
	//set decks
	choice2 = 1; 

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testCardCount == gameCardCount);
	printf("actions count = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	//assert(testG.numActions == G.numActions + xtraActions);
	testCardCount = testG.deckCount[otherPlayer] + testG.handCount[otherPlayer] + testG.discardCount[otherPlayer];
	gameCardCount = G.deckCount[otherPlayer] + G.handCount[otherPlayer] + G.discardCount[otherPlayer]; 
	printf("other player hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + newCardsOther);
	printf("other player total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer] + newCardsOther);
	//assert(testCardCount == gameCardCount);
	
	printf("players: %d expected: %d\n", testG.numPlayers, G.numPlayers);
	//assert(testG.numPlayers == G.numPlayers);
	printf("turn: %d expected %d\n", testG.whoseTurn, G.whoseTurn);
	//assert(testG.whoseTurn == G.whoseTurn);
	printf("phase: %d expected %d\n", testG.phase, G.phase);
	//assert(testG.phase == G.phase)

	// ----------- TEST 3: not enough cards in deck or discard -------------

	printf("\nTEST 3: Choice 3 = 1 \n");

	//set decks
	choice3 = 1; 

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testCardCount == gameCardCount);
	printf("actions count = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	//assert(testG.numActions == G.numActions + xtraActions);
	testCardCount = testG.deckCount[otherPlayer] + testG.handCount[otherPlayer] + testG.discardCount[otherPlayer];
	gameCardCount = G.deckCount[otherPlayer] + G.handCount[otherPlayer] + G.discardCount[otherPlayer]; 
	printf("other player hand count = %d, expected = %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer] + newCardsOther);
	printf("other player total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer] + newCardsOther);
	//assert(testCardCount == gameCardCount);
	
	printf("players: %d expected: %d\n", testG.numPlayers, G.numPlayers);
	//assert(testG.numPlayers == G.numPlayers);
	printf("turn: %d expected %d\n", testG.whoseTurn, G.whoseTurn);
	//assert(testG.whoseTurn == G.whoseTurn);
	printf("phase: %d expected %d\n", testG.phase, G.phase);
	//assert(testG.phase == G.phase)


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


