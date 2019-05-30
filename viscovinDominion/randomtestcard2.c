/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-4
	
	RANDOMTESTCARD2.C: Random testing Steward function
--------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>


int checkStewardCard() {
	srand(time(NULL));
	int c,i,j,r;
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			     remodel, smithy, village, baron, great_hall};
	struct gameState pre,G;
	int handSize = rand() %MAX_HAND;
	int controlHand[handSize];
	int p = rand() % 3 + 2;  
	int choice1, choice2, choice3;
	 
	// Random Control Hand with Steward at position 0 
	for (i=0; i<handSize; i++){
		controlHand[0]= steward;
		controlHand[i+1]= k[rand() %10 + 1];
	}
	
	for (i = 0; i < 100000; i++) {
		choice1 = rand() %3;	//Randomly make choice 0,1,2
		if (choice1 == 0){			//If choice is 0 choose 2 cards to trash.
			choice2 =  rand() %5 + 1; 
			choice3 =  rand() %5 + 1; 
			while (choice2 == choice3){
				choice2 = rand() %5 + 1; 
			}
		}
		else {
			choice2 = 0; 
			choice3 = 0; 
		}
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
		
		r = cardEffect(steward, choice1, choice2, choice3, &G, 0, NULL);
		assert (r == 0);

		// Hand increased by 2 cards  (+2 - 1 discarded = 1)
		// Deck count decreased by 2 cards.
		if (choice1 == 1){
			assert (G.handCount[0] == pre.handCount[0] + 1);
			//Deck decreased by 2 cards
			assert (G.deckCount[0] == pre.deckCount[0] - 2);
		}
		
		// Treasure in hand increased by 2.
		if (choice1 == 2){
			assert (G.coins == pre.coins + 2);
		}
		
		// 2 cards discarded plus the steward card = 3 
		if (choice1 == 0){
			assert (G.handCount[0] == pre.handCount[0] - 3);
		}
		
		//Other players hands are unaffected
		for (j=1; j<p; j++){
			assert (G.handCount[j] == pre.handCount[j]);
			assert (G.deckCount[j] == pre.deckCount[j]);
		}
	
		//Card in position 0 has been discarded after use. 
		c = handCard(0, &G);
		assert (c != 18);

	}
	
	printf("Card Effect function for Steward runs PASSED.\n");
	
	printf("CHOICE 1: +2 cards on hand PASSED.\n"); 
	printf("CHOICE 1: -2 cards on deck PASSED.\n"); 
	
	printf("CHOICE 2: +2 coins PASSED.\n"); 
	
	printf("CHOICE 3:  2 cards trashed PASSED.\n"); 
	
	printf("Other players hands unaffected. PASSED.\n");
	printf("Steward card discarded. PASSED.\n");
 
}

int main () {
	printf ("------------- Testing Steward -------------\n");
	checkStewardCard();
	return 0;
}