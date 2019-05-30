/*
 * cardtest3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council_room"

int main() {
    int newCards = 4;
	int newCardsOther = 1;
    int discarded = 1;
    //int xtraBuys = 1;

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
	int k[10] = {council_room, remodel, village, minion, mine, cutpurse,
			sea_hag, great_hall, adventurer, smithy};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

	// ----------- TEST 1: enough cards to draw --------------
	printf("\nTEST 1: enough cards in draw deck\n");
	//set decks
	while (G.deckCount[thisPlayer] < 5){
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = 4;
		G.deckCount[thisPlayer]++;
	}
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
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
	
	
	
	//test other player states
	
	// ----------- TEST 2: shuffle required--------------
	printf("\nTEST 2: not enough cards in draw pile, shuffle required\n");
	//set decks
	while (G.deckCount[thisPlayer] < 6){
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = 4;
		G.deckCount[thisPlayer]++;
	}
	while(G.deckCount[thisPlayer] > 2){
		G.discard[thisPlayer][G.discardCount[thisPlayer]] = G.deck[thisPlayer][G.deckCount[thisPlayer]];
		G.discardCount[thisPlayer]++;
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = -1;
		G.deckCount[thisPlayer]--;
	}
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
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

	// ----------- TEST 3: not enough cards--------------

	printf("\nTEST 3: not enough cards in draw or discard\n");

	//set decks

	while(G.deckCount[thisPlayer] > 2 ){
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = -1;
		G.deckCount[thisPlayer]--;
	}
	while(G.discardCount[thisPlayer]>0){
		G.discard[thisPlayer][G.discardCount[thisPlayer]] = -1;
		G.discardCount[thisPlayer]--;
	}
	
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	testCardCount = testG.deckCount[thisPlayer] + testG.handCount[thisPlayer] + testG.discardCount[thisPlayer];
	gameCardCount = G.deckCount[thisPlayer] + G.handCount[thisPlayer] + G.discardCount[thisPlayer]; 

	printf("hand count = %d, expected < %d\n", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - discarded);
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


