#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define tests 10000
#define criteria 3
#define MAX_PLAYERS 4
#define TESTCARD "smithy"

int failed = 0;

// function to check if two ints are equal or not
void testCheck(int a, int b) {
	if (a == b) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		failed++;
	}
}

int main()
{
    srand(time(NULL));
	int i;

	printf("\n\n");
	printf("---------------- Random Card Test 2 ----------------\n\n");

	printf("-------------- Testing Card: %s ----------------\n", TESTCARD);
	
    for(i = 0; i < tests; i++)
	{

        struct gameState afterTest;
		
        int k[10] = {adventurer, gardens, embargo, village, steward, 
					mine, cutpurse, sea_hag, tribute, smithy};

		//establish game settings into afterTest
        initializeGame(MAX_PLAYERS, k, rand(), &afterTest);

        int player = rand() % 4;
        afterTest.whoseTurn = player;
        
        int choice1 = rand() % 50;
        int choice2 = rand() % 50;
        int choice3 = rand() % 50;
        int handPos = rand() % MAX_HAND;
		int bonus = rand() % 50;
		
		//create a copy of the initialized game before using cardEffect
        struct gameState beforeTest;
        memcpy(&beforeTest, &afterTest, sizeof(struct gameState));

		//use the adventurer card
        cardEffect(TESTCARD, choice1, choice2, choice3, &afterTest, handPos, &bonus);

	//TEST Deck goes down by -3 Cards
	printf("\nPlayer 0 Deck Count: -3 Cards Drawn\n");
	testCheck(afterTest.deckCount[0], beforeTest.deckCount[0] - 3);
	
	//TEST Hand goes up by +2 Cards
	printf("\nPlayer 0 Hand Count: +2 cards (Draw 3, Discard 1)\n");
	testCheck(afterTest.handCount[0], beforeTest.handCount[0] + 2);
    
	}

    printf("Test Success Rate: %d of %d\n", tests * criteria - failed, tests * criteria);
}