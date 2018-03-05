#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTUNIT "updateCoins()"

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

    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

	struct gameState G;
	
	// kingdom cards
    int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, 
				village, baron, great_hall};
				
    // arrays full of designated treasure
    for (i = 0; i < MAX_HAND; i++) {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

	printf("\n\n");
	printf("---------------- Unit Test 2 ----------------\n\n");

	printf("-------------- Testing : %s ----------------\n", TESTUNIT);

    
    for (handCount = 0; handCount <= 5; handCount = handCount + 5) {
        printf("\n\nTreasure cards: %d\n",handCount);
        printf("Bonus: %d\n", bonus);

        memset(&G,23,sizeof(struct gameState));
        b = initializeGame(numPlayers, k, seed, &G);
        G.handCount[0] = handCount;

		//TEST HAND WITH ALL GOLD
		printf("\nTEST HAND WITH ALL GOLD: ");
        memcpy(G.hand[0],golds,sizeof(int)*handCount);
        updateCoins(0,&G,bonus);
        testCheck(G.coins, handCount*3 + bonus);
		
        //TEST HAND WITH ALL SILVER
        printf("\nTEST HAND WITH ALL SILVER: ");
		memcpy(G.hand[0], silvers, sizeof(int)*handCount);
        updateCoins(0, &G, bonus);
        testCheck(G.coins,handCount*2 + bonus);

        //TEST HAND WITH ALL COPPER
        printf("\nTEST HAND WITH ALL COPPER: ");
		memcpy(G.hand[0], coppers, sizeof(int)*handCount);
        updateCoins(0, &G, bonus);  
        testCheck(G.coins,handCount*1 + bonus);

        bonus = bonus + 2;
    }

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