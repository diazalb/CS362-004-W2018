#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

#define tests 10000
#define criteria 2
#define MAX_PLAYERS 4
#define TESTCARD "council_room"

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
	printf("---------------- Random Card Test 1 ----------------\n\n");

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

		//use the council_room
        cardEffect(TESTCARD, choice1, choice2, choice3, &afterTest, handPos, &bonus);


	//TEST Player Gains 1 Card and Discards 1 village card
	printf("Player 0 Hand Count: +1 Card -1 Discard");
	testCheck(afterTest.handCount[0], beforeTest.handCount[0]);
	
	//TEST Player Gains +2 Actions
	printf("Check Player 0 gains +2 Action");
	testCheck(afterTest.numActions, beforeTest.numActions + 2);

	//TEST Player Deck -1 Card Drawn
	printf("Check Player 0 Deck -1 Drawn");
	testCheck(afterTest.deckCount[0], beforeTest.deckCount[0] - 1);

	}
    printf("Test Success Rate: %d of %d \n", tests * criteria - failed, tests * criteria);
}