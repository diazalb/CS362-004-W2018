#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTCARD "village"

int failCount = 0;

// function to check if two ints are equal or not
void testCheck(int a, int b) {
	if (a == b) {
		printf("PASSED\n");
	}
	else {
		printf("FAILED\n");
		failCount++;
	}
}

int main() {
	int i;
	int seed = 1000;
	int treasureAfter = 0, treasureBefore = 0;
	int numPlayers = 2;
	int card;
	int handpos = 0;
	int bonus = 0;

	// kingdom cards
	int k[10] = { adventurer, council_room, feast, gardens, mine, remodel, 
				smithy, village, baron, great_hall };

	// game states
	struct gameState G, OG;

	printf("\n\n");
	printf("---------------- Card Test 3 ----------------\n\n");

	printf("-------------- Testing Card: %s ----------------\n", TESTCARD);
	
	memset(&G, 23, sizeof(struct gameState));
	memset(&OG, 23, sizeof(struct gameState));

	//create a new game
	initializeGame(numPlayers, k, seed, &G);

	//Copy Initialized game state to 'OG'
	memcpy(&OG, &G, sizeof(struct gameState));

	//Play Card
	cardEffect(TESTCARD, 0, 0, 0, &G, handpos, &bonus);

	//TEST Player Gains 1 Card and Discards 1 village card
	printf("Player 0 Hand Count: +1 Card -1 Discard");
	testCheck(G.handCount[0], OG.handCount[0]);
	
	//TEST Player Gains +2 Actions
	printf("Check Player 0 gains +2 Action");
	testCheck(G.numActions, OG.numActions + 2);

	//TEST Player Deck -1 Card Drawn
	printf("Check Player 0 Deck -1 Drawn");
	testCheck(G.deckCount[0], OG.deckCount[0] - 1);

	//TEST Other Player Hand & Deck
	printf("\nTEST: Check Player 1 status unchanged\n");
	printf("Hand Count: ");
	testCheck(G.handCount[1], OG.handCount[1]);
	
	printf("Deck Count: ");
	testCheck(G.deckCount[1], OG.deckCount[1]);

	//TEST STATUS of Kingdom Cards
	printf("\nTEST: Check kingdom card status unchanged\n");
	for (i = 0; i < 10; i++) {
		printf("Kingdom Card %i: ", i);
		testCheck(G.supplyCount[k[i]], OG.supplyCount[k[i]]);
	}

	//TEST STATUS OF Victory Cards
	printf("\nTEST: Check victory card status unchanged\n");
	printf("Province Pile: ");
	testCheck(G.supplyCount[province], OG.supplyCount[province]);
	
	printf("Duchy Pile: ");
	testCheck(G.supplyCount[duchy], OG.supplyCount[duchy]);
	
	printf("Estate Pile: ");
	testCheck(G.supplyCount[estate], OG.supplyCount[estate]);


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