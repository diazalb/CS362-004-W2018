#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTUNIT "isGameOver()"

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
	printf("---------------- Unit Test 3 ----------------\n\n");

	printf("-------------- Testing : %s ----------------\n", TESTUNIT);

    memset(&G,23,sizeof(struct gameState));
    initializeGame(numPlayers, k, seed, &G);

	//TEST Province Cards and Supply Piles Not Empty
	printf("\nTEST Supply & Province Piles are not empty: ");
    testCheck(isGameOver(&G),0);
	
	//TEST GAME OVER BY PROVINCE CARDS
	printf("\nTEST Province cards are empty: ");
    G.supplyCount[province] = 0;
    testCheck(isGameOver(&G),1);
    G.supplyCount[province] = 1;

	//TEST GAME OVER BY 3 Supply Piles
	printf("\nTEST Three supply piles are empty: ");
    G.supplyCount[0] = 0;
    G.supplyCount[1] = 0;
    G.supplyCount[2] = 0;
    testCheck(isGameOver(&G),1);


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