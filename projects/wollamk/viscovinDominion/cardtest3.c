/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest3: cardtest3.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"

int main() {
    int newCards = 2;
	int newCardsOther = 0;
    int discarded = 1;
	
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

	// ----------- TEST 1: enough cards in draw deck --------------
	printf("\nTEST 1: enough cards in draw deck\n");
	//set decks
	for (int i = 0; i < 30; i++){
		G.deck[thisPlayer][i] = 4;
	}
	G.deckCount[thisPlayer] = 30;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testCardCount == gameCardCount);
	
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
	
	// ----------- TEST 2: shuffle required --------------
	printf("\nTEST 2: not enough cards in draw pile, shuffle required\n");
	//set decks
	for (int i = 0; i < 30; i++){
		G.discard[thisPlayer][i] = 4;
	}
	
	G.discardCount[thisPlayer] = 30;
	G.deck[thisPlayer][0] = 4; 
	
	for(int i = 1; i < G.handCount[thisPlayer]; i++){
		G.hand[thisPlayer][i] = -1;
	}
	
	G.handCount[thisPlayer] = 1;
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testCardCount == gameCardCount);
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
	
	
	// ----------- TEST 3: not enough cards --------------

	printf("\nTEST 3: not enough cards in draw or discard\n");

	//set decks

	while(G.handCount[thisPlayer] > 1 ){
		G.hand[thisPlayer][G.handCount[thisPlayer]] = -1;
		G.handCount[thisPlayer]--;
	}
	while(G.discardCount[thisPlayer]> 0){
		G.discard[thisPlayer][G.discardCount[thisPlayer]] = -1;
		G.discardCount[thisPlayer]--;
	}
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
	printf("total card count = %d, expected = %d\n", testCardCount, gameCardCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);
	//assert(testCardCount == gameCardCount);

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


