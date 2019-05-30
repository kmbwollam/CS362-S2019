/*
	Software Enginnering II 			Nadia M Viscovich
	CS-362-400							Assignment-4
	
	RANDOMTESTADVENTURER.C: Random testing Adventurer function
--------------------------------------------------------------*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>


int checkAdventurerCard() {
	srand(time(NULL));
	int c,i,j,r;
	int coppersA=0,coppersB=0;
	int passed=0, failed=0; 
	int seed = 1000;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			     remodel, smithy, village, baron, great_hall};
	int p = rand() % 3 + 2;  
	struct gameState pre,G;
	int handSize = rand() %MAX_HAND;
	int controlHand[handSize];
	int deckSize = 5;
	int controlDeck[deckSize];
	
	
	// Random Control Hand with Adventurer at position 0 
	for (i=0; i<handSize; i++){
		controlHand[0]= adventurer;
		controlHand[i+1]= k[rand() %10 + 1];
	}
	
	controlDeck[0]= estate; 
	controlDeck[1]= estate;
	controlDeck[2]= copper;
	controlDeck[3]= copper;
	controlDeck[4]= copper;
		
	for (i = 0; i < 100000; i++) {
		//Clearing state of game before initializing.
		memset(&G, 23, sizeof(struct gameState)); 
		//Trusting initialize function to do its thing
		initializeGame(p, k, seed, &G);
		memcpy(G.hand[0], controlHand, sizeof(int) * MAX_HAND); // set cards according to controlHand	
		memcpy(G.deck[0], controlDeck, sizeof(int) * MAX_DECK);
		
		//Copying state of game G to pre so we can compare pre and post results.
		memcpy(&pre, &G, sizeof(struct gameState));
	
		//Make sure it is players 0 turn
		G.whoseTurn = 0;
		pre.whoseTurn = 0;
	
		coppersA = fullDeckCount(0,4,&G); 
		// Using playcard instead of cardEffect to get more coverage
		r = playCard(0, 0, 0, 0, &G);
		assert (r == 0);

		//The number of cards in the hand increased by 2
		assert(numHandCards(&G) == numHandCards(&pre)+2);
		
		//Hand has +2 treasures
		assert (G.hand[0][5] == 4 || G.hand[0][6] == 4);
		
		//Coppers where not made up and they were already in the players cards.
		coppersB = fullDeckCount(0,4,&G); 
		assert (coppersA == coppersB); 
	
		//Deck decreased by 2 cards
		assert (G.deckCount[0] == pre.deckCount[0] - 2);
	
		//Other players hands are unaffected
		for (j=1; j<p; j++){
			assert (G.handCount[j] == pre.handCount[j]);
			assert (G.deckCount[j] == pre.deckCount[j]);
		}
		
		//Card in position 0 has been discarded after use. 		
		c = handCard(0, &G);
		if (c == 7) 
			failed++;
		else 
			passed++;
	}
	
	printf("Card Effect function for Adventurer runs PASSED.\n");
	printf("+2 cards added to hand. PASSED.\n");
	printf("+2 cards added are treasures cards. PASSED.\n");
	printf("Coppers part of players deck. PASSED.\n");
	printf("Player has 2 less cards on its deck. PASSED.\n");
	printf("Other players hands unaffected. PASSED.\n");
	
	printf("Adventurer card discarded FAILED %d times. \n", failed); 
	//printf("Adventurer card discarded PASSED %d times. \n", passed); 
}

int main () {
	printf ("------------- Testing Adventurer -------------\n");
	checkAdventurerCard();
	return 0;
}
