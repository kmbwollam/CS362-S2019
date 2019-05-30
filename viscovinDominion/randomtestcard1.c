/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-4
	
	RANDOMTESTCARD1.C: Testing Smithy function
--------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>


int checkSmithyCard() {
	srand(time(NULL));
	int c,i,j,r;
	int passed=0, failed=0, passed1=0, failed1=0 ; 
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			     remodel, smithy, village, baron, great_hall};
	int p = rand() % 3 + 2;  
	struct gameState pre,G;
	int handSize = rand() %MAX_HAND;
	int controlHand[handSize];
	
	// Random Control Hand with Smithy at position 0 
	for (i=0; i<handSize; i++){
		controlHand[0]= smithy;
		controlHand[i+1]= k[rand() %10 + 1];
	}
	
	for (i = 0; i < 100000; i++) {
		//Clearing state of game before initializing.
		memset(&G, 23, sizeof(struct gameState)); 
		//Trusting initialize function to do its thing
		initializeGame(p, k, seed, &G);
		memcpy(G.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
		
		//Copying state of game G to pre so we can compare pre and post results.
		memcpy(&pre, &G, sizeof(struct gameState));
	
		//Make sure it is players 0 turn
		G.whoseTurn = 0;
		pre.whoseTurn = 0;
	
		r = playCard(0, 0, 0, 0, &G);
		assert (r == 0);

		// Hand increased by 2 cards  (+3 - 1 discarded = 2)
		if (G.handCount[0] == pre.handCount[0] + 2)
			passed++;
		else
			failed++;
		
		//Deck decreased by 3 cards
		if  (G.deckCount[0] == pre.deckCount[0] - 3)
			passed1++;
		else
			failed1++;	
		
		//Other players hands are unaffected
		for (j=1; j<p; j++){
			assert (G.handCount[j] == pre.handCount[j]);
			assert (G.deckCount[j] == pre.deckCount[j]);
		}
	
		//Card in position 0 has been discarded after use. 
		c = handCard(0, &G);
		assert (c != 13);

	}
	
	printf("Card Effect function for Smithy runs PASSED.\n");
	
	printf("+3 cards on hand FAILED %d times. \n", failed); 
	//printf("+3 cards on hand PASSED %d times. \n", passed);
	printf("-3 cards on deck FAILED %d times. \n", failed1); 
	//printf("-3 cards on deck PASSED %d times. \n", passed1);
	
	printf("Other players hands unaffected. PASSED.\n");
	printf("Smithy card discarded. PASSED.\n");
 
}

int main () {
	printf ("------------- Testing Smithy -------------\n");
	checkSmithyCard();
	return 0;
}