#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define tests 1000
#define criteria 3
#define MAX_PLAYERS 4
#define TESTCARD "adventurer"

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
    int failed = 0;

	printf("\n\n");
	printf("---------------- Random Card Test ----------------\n\n");

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

		//test criteria 1: check for drawing only 2 cards
        testCheck(afterTest.handCount[player], beforeTest.handCount[player] + 2);
		
		//test criteria 2: check for first card drawn is treasure
        int card1 = afterTest.hand[player][afterTest.handCount[player] - 2];
        if(card1 != gold && card1 != silver && card1 != copper)
		{
			failed++;
            printf("Criteria Failed: Player %d's first card isn't treasure.\n", player);
        }
		
		//test criteria 3: check for second card drawn is treasure
        int card2 = afterTest.hand[player][afterTest.handCount[player] - 1];
        if(card2 != gold && card2 != silver && card2 != copper)
		{
			failed++;
            printf("Criteria Failed: Player %d's second card isn't treasure.\n", player);
        }


    }

    printf("Test Success Rate: %d of %d\n", tests * criteria - failed, tests * criteria);
}