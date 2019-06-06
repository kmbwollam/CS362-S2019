#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

int checkRemodel(int p, int choice1, int choice2, struct gameState *post, int handPos) {
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));

  int r;
    
  r = playRemodel(p, choice1, choice2, post, handPos);

	//int newCards = 2;
	//int newCardsOther = 0;
    int discarded = 1;
	//int i;
	//int count = 0;
	int trashCost = getCost(pre.hand[p][choice1]);
	int newCost = getCost(choice2); 
	
	
	
	
	
	if(r==-1){
		discarded = 0; 		
		if( newCost - trashCost <= 2){
			printf("FAIL: playRemodel returned -1 in error\ntrashCost: %d, newCost: %d\n", trashCost, newCost);
			return 1;
		}		
	}else if (r==0){
		if(newCost - trashCost > 2){
			printf("FAIL: playRemodel returned 0 in error\ntrashCost: %d, newCost: %d\n", trashCost, newCost);
		}
	}
	
	int expectedHandCount = pre.handCount[p] - discarded;
	if( expectedHandCount != post->handCount[p]){
		printf("FAIL: playRemodel handcount error\nexpected: %d, actual: %d\n", expectedHandCount, post->handCount[p]);
		return 1; 
	}
 // assert(expectedHandCount == post.handCount[p]);
	return 0;
}

int main () {

  int i, n, p, c1, c2; //r,deckCount, discardCount, handCount, choice1, choice2;

 // int k[10] = {adventurer, council_room, feast, gardens, mine,
	//       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing playRemodel.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(10);
  PutSeed(5);
  
  int numTests = 100; 
  int numBugs = 0; 
  
//UPDATE FOR THINGS THAT NEED TO BE SET
  for (n = 0; n < numTests; n++) {
    
	//printf("a");
	for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
	//printf("b");
    G.numPlayers = floor(Random()* 3) + 2;
	//printf("c");
	p = floor(Random() * G.numPlayers);
    //printf("d");
	G.deckCount[p] = floor(Random() * MAX_DECK);
	//printf("e");
	for (i = 0; i <G.deckCount[p]; i++){
		G.deck[p][i] = floor(Random()*27);
	}
	//printf("f");
    G.discardCount[p] = floor(Random() * MAX_DECK);
	//printf("g");
	for (i = 0; i < G.discardCount[p]; i++){
		G.discard[p][i] = floor(Random() *27); 
	}
    //printf("h");
	G.handCount[p] = floor(Random() * MAX_HAND);
	//printf("i");
	for (i = 0; i < G.handCount[p]; i++){
		G.hand[p][i] = floor(Random() *27); 
	}
	//printf("j");
	int h = floor(Random() * G.handCount[p]); 
	//printf("k");
	c1 = h; 
	//printf("l");
	while(c1==h){
		c1 = floor(Random() * G.handCount[p]);
	}
	//printf("m");
	c2 = floor(Random() *27); 
	//printf("n");
	
	for(i = 0; i<=treasure_map; i++){
		G.supplyCount[i] = 5; 
	}
		
    numBugs += checkRemodel(p, c1, c2, &G, h);
	//printf("o\n");
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
