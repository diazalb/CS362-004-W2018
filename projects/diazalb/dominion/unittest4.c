#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTUNIT "shuffle()"

int failCount = 0;

void testCheck(int a, int b) {
	if (a == b) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		failCount++;
	}
}


int main () {
    int i, b;
	int handCount;
    int numPlayers = 2;
    int seed = 1000;
    int bonus = 1;

	struct gameState G;
	
	// kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
				village, baron, great_hall};
			

	printf("\n\n");
	printf("---------------- Unit Test 4 ----------------\n\n");

	printf("-------------- Testing : %s ----------------\n", TESTUNIT);

    memset(&G,23,sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

	printf("\nTEST Player shuffle with Zero Cards: ");
    G.deckCount[0] = 0;
    testCheck(shuffle(0,&G),-1);

    printf("\nTest Player shuffle with 10 cards in deck: ");
    G.deckCount[0] = 10;
    shuffle(0,&G);
    testCheck(G.deckCount[0],10);

	//DISPLAY TEST FINAL TEST RESULTS
	if (failCount) {
		printf("\nTEST FAILED\n");
		printf("Number of Fails: %d\n", failCount);
	}
	else {
		printf("\n100% COMPLETED TEST SUCCESSFULLY\n\n");
	}

    return 0;
}