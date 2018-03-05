#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTUNIT "gainCard()"

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

	struct gameState G, OG;
	
	// kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
				village, baron, great_hall};
			

	printf("\n\n");
	printf("---------------- Unit Test 1 ----------------\n\n");

	printf("-------------- Testing : %s ----------------\n", TESTUNIT);

    memset(&G,23,sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);
	
	//Copy Initialized game state to 'OG'
	memcpy(&OG, &G, sizeof(struct gameState));

	printf("\nGold supply pile is empty\n");
    G.supplyCount[gold] = 0;
    testCheck(gainCard(gold,&G,0,0),-1);
    G.supplyCount[gold] = 30;
	OG.supplyCount[gold] = G.supplyCount[gold];
	
    printf("\nTEST add +1 card to deck: ");
    gainCard(gold,&G,1,0);
    testCheck(G.deckCount[0],OG.deckCount[0] + 1);

    printf("\nTEST add +1 card to hand: ");
    gainCard(gold,&G,2,0);
    testCheck(OG.handCount[0] + 1,G.handCount[0]);

    printf("\nTEST add +1 card to discard pile: ");
    gainCard(gold,&G,0,0);
    testCheck(OG.discardCount[0] + 1,G.discardCount[0]);

    printf("\nTEST -1 decrease in gold supply: ");
    gainCard(gold,&G,0,0);
    testCheck(OG.supplyCount[gold] - 4,G.supplyCount[gold]);

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