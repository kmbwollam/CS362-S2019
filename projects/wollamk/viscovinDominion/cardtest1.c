/*
 * cardtest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "minion"
int main() {
    //int newCards = 3;
    //int discarded = 1;
	int xtraActions = 1;
	int newHandCount = 4; 
	
    //int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 1, choice3 = 0, bonus = 0;
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

	// ----------- TEST 1: enough cards to draw --------------
	printf("\nTEST 1: choice 2 & both players 5+ cards\n");
	//set decks
	
	while (G.handCount[thisPlayer] < 6){
		G.hand[thisPlayer][G.handCount[thisPlayer]] = 4;
		G.handCount[thisPlayer]++;
	}

	while (G.handCount[otherPlayer] < 6){
		G.hand[otherPlayer][G.handCount[otherPlayer]] = 4;
		G.handCount[otherPlayer]++;
	}

	while (G.deckCount[thisPlayer] < 6){
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = 4;
		G.deckCount[thisPlayer]++;
	}

	while (G.deckCount[otherPlayer] < 6){
		G.deck[otherPlayer][G.deckCount[otherPlayer]] = 4;
		G.deckCount[otherPlayer]++;
	}

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], newHandCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	
	printf("actions count = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	//assert(testG.numActions == G.numActions + xtraActions);
	
	printf("other player hand count = %d, expected <= %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	
	printf("players: %d expected: %d\n", testG.numPlayers, G.numPlayers);
	//assert(testG.numPlayers == G.numPlayers);
	printf("turn: %d expected %d\n", testG.whoseTurn, G.whoseTurn);
	//assert(testG.whoseTurn == G.whoseTurn);
	printf("phase: %d expected %d\n", testG.phase, G.phase);
	//assert(testG.phase == G.phase);
	
	
	// ----------- TEST 2: cards need to be shuffled --------------
	printf("\nTEST 2: card player 5+ cards, other player <5 cards \n");
	//set decks
	while (G.handCount[thisPlayer] < 6){
		G.hand[thisPlayer][G.handCount[thisPlayer]] = 4;
		G.handCount[thisPlayer]++;
	}
	
	while (G.handCount[otherPlayer] > 4){
		G.hand[otherPlayer][G.handCount[otherPlayer]] = -1;
		G.handCount[otherPlayer]--;
	}
	
	while (G.deckCount[thisPlayer] < 6){
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = 4;
		G.deckCount[thisPlayer]++;
	}
	
	while (G.deckCount[otherPlayer] < 6){
		G.deck[otherPlayer][G.deckCount[otherPlayer]] = 4;
		G.deckCount[otherPlayer]++;
	}
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], newHandCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	
	printf("actions count = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	//assert(testG.numActions == G.numActions + xtraActions);
	
	printf("other player hand count = %d, expected <= %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	
	printf("players: %d expected: %d\n", testG.numPlayers, G.numPlayers);
	//assert(testG.numPlayers == G.numPlayers);
	printf("turn: %d expected %d\n", testG.whoseTurn, G.whoseTurn);
	//assert(testG.whoseTurn == G.whoseTurn);
	printf("phase: %d expected %d\n", testG.phase, G.phase);
	//assert(testG.phase == G.phase);

	// ----------- TEST 3: not enough cards in deck or discard -------------

	printf("\nTEST 3: both players less than 5 cards \n");

	//set decks
	while (G.handCount[thisPlayer] > 4){
		G.hand[thisPlayer][G.handCount[thisPlayer]] = -1;
		G.handCount[thisPlayer]--;
	}
	
	while (G.handCount[otherPlayer] > 4){
		G.hand[otherPlayer][G.handCount[otherPlayer]] = -1;
		G.handCount[otherPlayer]--;
	}
	
	while (G.deckCount[thisPlayer] < 6){
		G.deck[thisPlayer][G.deckCount[thisPlayer]] = 4;
		G.deckCount[thisPlayer]++;
	}
	
	while (G.deckCount[otherPlayer] < 6){
		G.deck[otherPlayer][G.deckCount[otherPlayer]] = 4;
		G.deckCount[otherPlayer]++;
	}
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(minion, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("hand count = %d, expected = %d\n", testG.handCount[thisPlayer], newHandCount);
	//assert(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - discarded);

	
	printf("actions count = %d, expected = %d\n", testG.numActions, G.numActions + xtraActions);
	//assert(testG.numActions == G.numActions + xtraActions);
	
	printf("other player hand count = %d, expected <= %d\n", testG.handCount[otherPlayer], G.handCount[otherPlayer]);
	//assert(testG.handCount[otherPlayer] == G.handCount[otherPlayer]);
	
	printf("players: %d expected: %d\n", testG.numPlayers, G.numPlayers);
	//assert(testG.numPlayers == G.numPlayers);
	printf("turn: %d expected %d\n", testG.whoseTurn, G.whoseTurn);
	//assert(testG.whoseTurn == G.whoseTurn);
	printf("phase: %d expected %d\n", testG.phase, G.phase);
	//assert(testG.phase == G.phase);


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
}


