#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkVillage(int p, struct gameState *post, int handPos) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
    
  r = playVillage(p, post, handPos);


	if(r!=0) {
		printf("FAIL: playVillage returned %d\n", r);
		return 1; 
	}
  //assert (r == 0);
  
	int newCards = 1;
	int newActions = 2;
	//int newCardsOther = 0;
    int discarded = 1;
	//int i;
	int count = 0;

	
	count += pre.deckCount[p]; 
	count += pre.discardCount[p]; 
	
	if (newCards > count) newCards = count;
	
	int expectedHandCount = pre.handCount[p] + newCards - discarded;
	
	if(pre.numActions + newActions != post->numActions){
		printf("FAIL: playVillage action error\nexpected: %d, actual: %d\n", (pre.numActions + newActions), post->numActions);
		return 1;
	}
	// assert((pre.numActions + newActions) == post->numActions);

	if( expectedHandCount != post->handCount[p]){
		printf("FAIL: playVillage handcount error\nexpected: %d, actual: %d, hand + discard count: %d\n", expectedHandCount, post->handCount[p], count);
		return 1; 
	}
 // assert(expectedHandCount == post.handCount[p]);
 
	return 0;
}

int main () {

  int i, n, p; //r,deckCount, discardCount, handCount;

 // int k[10] = {adventurer, council_room, feast, gardens, mine,
	//       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing playVillage.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);
  
  int numTests = 100; 
  int numBugs = 0; 
  
//UPDATE FOR THINGS THAT NEED TO BE SET
  for (n = 0; n < numTests; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    G.numPlayers = floor(Random()* 3) + 2;
	p = floor(Random() * G.numPlayers);
    G.deckCount[p] = floor(Random() * MAX_DECK);
	for (i = 0; i <G.deckCount[p]; i++){
		G.deck[p][i] = floor(Random()*27);
	}
    G.discardCount[p] = floor(Random() * MAX_DECK);
	for (i = 0; i < G.discardCount[p]; i++){
		G.discard[p][i] = floor(Random() *27); 
	}
    G.handCount[p] = floor(Random() * MAX_HAND);
	for (i = 0; i < G.handCount[p]; i++){
		G.hand[p][i] = floor(Random() *27); 
	}
	int h = floor(Random() * G.handCount[p]); 
    G.numActions = floor(Random() * 100) + 1;
	numBugs += checkVillage(p, &G, h);
	
  }

  if (numBugs == 0){ printf ("ALL TESTS PASS\n");}
  else{ printf ("\n%d Failed tests in %d runs\n", numBugs, numTests);}

  //exit(0);
/*
  printf ("SIMPLE FIXED TESTS.\n");
  for (p = 0; p < 2; p++) {
    for (deckCount = 0; deckCount < 5; deckCount++) {
      for (discardCount = 0; discardCount < 5; discardCount++) {
	for (handCount = 0; handCount < 5; handCount++) {
	  memset(&G, 23, sizeof(struct gameState)); 
	  r = initializeGame(2, k, 1, &G);
	  G.deckCount[p] = deckCount;
	  memset(G.deck[p], 0, sizeof(int) * deckCount);
	  G.discardCount[p] = discardCount;
	  memset(G.discard[p], 0, sizeof(int) * discardCount);
	  G.handCount[p] = handCount;
	  memset(G.hand[p], 0, sizeof(int) * handCount);
	  checkDrawCard(p, &G);
	}
      }
    }
  }
*/
  return 0;
}
