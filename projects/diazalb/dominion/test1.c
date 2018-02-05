/*
 *
 *
 * Include the following lines in your makefile:
 *
 * test1.c: test1.c dominion.o rngs.open
 *		gcc -o test1 -g test1.c dominion.o rngs.o $(CFLAGS)
 *
 *
 */
 
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include "rngs.h"
 #include <string.h>
 #include <stdio.h>
 #include <assert.h>
 #include <stdlib.h>
 
 #define TESTCARD "adventurer"
 
 int main(int argc, char** argv)
 {
	 int i;
	 int handPos = 0;
	 int seed = 1000;
	 int numPlayers = 2;
	 int player = 0;
	 int numBefore;
	 int numAfter;
	 int coinsBefore;
	 int coinsAfter;
	 int deckCount = 0;
	 int card = 0;
	 int bonus = 0;

	 struct gameState G, testG, oldG;

	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag,
		tribute, smithy, council_room};

	initializeGame(numPlayers, k, seed, &G);

	printf("\n\n---------------- Card Test 1 ----------------\n\n");

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);


	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// make sure the player has treasure cards
	gainCard(copper, &testG, 1, player);
	gainCard(silver, &testG, 1, player);
	gainCard(gold, &testG, 1, player);

	// record coin amount before card is played
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
		gainCard(gardens, &testG, 1, player);
	}

	// give player an adventurer card and play it
	gainCard(adventurer, &testG, 2, player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);


	// this will fail due to the altered dominion.c code
	if (coinsAfter == 5)
	{
		printf("PASS: Two treasure cards are revealed\n\n\n");

	}
	else
	{
		printf("FAIL: Two treasure cards are revealed\n\n\n");
	}


	/*************** TEST 2: No treasure cards in deck ***********/
	printf("*******TEST 2: No treasure cards in deck *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// record coin amount before card is played
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
		gainCard(gardens, &testG, 1, player);
	}

	// give player an adventurer card and play it
	gainCard(adventurer, &testG, 2, player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test passes if player gains no coins from playing the adventurer card	
	if (coinsAfter == 0)
	{
		printf("PASS: No treasure cards in deck\n\n\n");

	}
	else
	{
		printf("FAIL: No treasure cards in deck\n\n\n");
	}



	/*************** TEST 3: One treasure card in deck ***********/
	printf("*******TEST 3: One treasure card in deck *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// record coin amount before card is played
	gainCard(silver, &testG, 1, player);
	updateCoins(player, &testG, 0);
	coinsBefore = testG.coins;

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
		gainCard(gardens, &testG, 1, player);
	}

	// give player an adventurer card and play it
	gainCard(adventurer, &testG, 2, player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get coin amounts after card is played
	updateCoins(player, &testG, 0);
	coinsAfter = testG.coins;

	endTurn(&testG);

	// test passes if player gains no coins from playing the adventurer card
	if (coinsAfter == 0)
	{
		printf("PASS: One treasure card in deck\n\n\n");

	}
	else
	{
		printf("FAIL: One treasure card in deck\n\n\n");
	}

	/*************** TEST 4: All revealed non-treasure cards are discarded ***********/
	printf("*******TEST 4: All revealed non-treasure cards are discarded *******\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	player = testG.whoseTurn;

	// give player treasure cards and record card amounts before card is played
	gainCard(silver, &testG, 1, player);
	gainCard(silver, &testG, 1, player);
	gainCard(silver, &testG, 1, player);
	numBefore = numHandCards(&testG);

	// fill players deck with gardens cards
	for (i = deckCount; i < (deckCount + 5); i++)
	{
		gainCard(gardens, &testG, 1, player);
	}

	// give player an adventurer card and play it
	gainCard(adventurer, &testG, 2, player);
	cardEffect(card, 0, 0, 0, &testG, handPos, &bonus);

	// get card amounts after card is played
	oldG = testG;
	endTurn(&testG);
	numAfter = numHandCards(&oldG);


	// test passes if player's hand cointains only the adventurer card 
	if (numAfter == (numBefore + 1))
	{
		printf("PASS: All revealed non-treasure cards are discarded\n\n\n");

	}
	else
	{
		printf("FAIL: All revealed non-treasure cards are discarded\n\n\n");
	}

	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


	return 0;
 }