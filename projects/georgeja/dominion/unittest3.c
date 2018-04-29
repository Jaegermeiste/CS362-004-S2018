/*********************************************************************
** Program name: Unit Test 3
** Author: Jason George
** Date: 20180428
** Description: unittest3.c - implementation of test for fullDeckCount
*********************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

// To avoid making it hard to collect coverage when a test fails, use your own asserttrue function instead
// of the standard C assert(which basically crashes the code and fails to collect coverage).
#ifndef asserttrue
#define asserttrue(x, y) if ((y) != 0) { x += 0; } else { printf(" !!! TEST FAILED AT LINE: %d\n", __LINE__); x += 1; };
#endif

#ifndef string
#define string(x) #x
#endif

/*********************************************************************
** Description: int main(int argc, char *argv[])
**      Entry point for the program.
**      Returns 0.
*********************************************************************/
int main(int argc, char *argv[])
{
			int			cards[10] = { smithy, adventurer, mine, remodel, sea_hag, village, baron, curse, gardens, treasure_map };
	const	int			numPlayers = MAX_PLAYERS;
			int			player = 0;
	const	int			randomSeed = 1;
			int			cardNumber = 0;
			int			deckCount = 0;
	const	int			maxDeckCount = 5;
			unsigned	errorCount = 0;

	struct gameState state, testState;
	memset(&state, 0, sizeof(struct gameState));
	memset(&testState, 0, sizeof(struct gameState));

	// Set up game
	int retVal = initializeGame(numPlayers, cards, randomSeed, &state);
	asserttrue(errorCount, retVal == 0);

	printf(" UNIT TEST: fullDeckCount\n");

	// Player number -1 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(-1, 0, &testState);
	asserttrue(errorCount, retVal == 0);							// Function returned badly

	/* Causes SIGSEGV
	// Player number -2147483648 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(INT_MIN, 0, &testState);
	asserttrue(errorCount, retVal == 0);							// Function returned badly
	*/

	// Player number 4 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(MAX_PLAYERS, 0, &testState);
	asserttrue(errorCount, retVal == 0);							// Function returned badly

	// Player number 5 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(MAX_PLAYERS + 1, 0, &testState);
	asserttrue(errorCount, retVal == 0);							// Function returned badly

	/* Causes SIGSEGV
	// Player number 2147483647 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(INT_MAX, 0, &testState);
	asserttrue(errorCount, retVal == 0);							// Function returned badly
	*/

	// Card number -1 (in a valid range of curse-treasure_map)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(0, curse - 1, &testState);
	asserttrue(errorCount, retVal == 0);						// Function returned badly

	// Card number -2147483648 (in a valid range of curse-treasure_map)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(0, INT_MIN, &testState);
	asserttrue(errorCount, retVal == 0);						// Function returned badly

	// Card number 27 (in a valid range of curse-treasure_map)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(0, treasure_map + 1, &testState);
	asserttrue(errorCount, retVal == 0);						// Function returned badly

	// Card number 2147483647 (in a valid range of curse-treasure_map)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = fullDeckCount(0, INT_MAX, &testState);
	asserttrue(errorCount, retVal == 0);						// Function returned badly

	// Card Num Variable
	memcpy(&testState, &state, sizeof(struct gameState));
	for (cardNumber = curse; cardNumber <= treasure_map; cardNumber++)
	{
		retVal = fullDeckCount(0, cardNumber, &testState);
		asserttrue(errorCount, retVal > -1);						// Function returned something not an error
	}

	// Player Num Variable
	for (player = 0; player < numPlayers; player++)
	{
		// Size of hand
		for (deckCount = 1; deckCount <= maxDeckCount; deckCount++)
		{
			// Set the number of cards in the deck
			testState.handCount[player] = deckCount;
			testState.deckCount[player] = deckCount;
			testState.discardCount[player] = deckCount;

			// Test all the player's cards as copper
			for (cardNumber = 0; cardNumber < deckCount; cardNumber++)
			{
				testState.hand[player][cardNumber] = copper;
				testState.deck[player][cardNumber] = copper;
				testState.discard[player][cardNumber] = copper;
			}
			retVal = fullDeckCount(player, copper, &testState);
			asserttrue(errorCount, retVal == deckCount * 3);	// Expected coins

			// Test all the player's cards as silver
			for (cardNumber = 0; cardNumber < deckCount; cardNumber++)
			{
				testState.hand[player][cardNumber] = silver;
				testState.deck[player][cardNumber] = silver;
				testState.discard[player][cardNumber] = silver;
			}
			retVal = fullDeckCount(player, silver, &testState);
			asserttrue(errorCount, retVal == deckCount * 3);	// Expected coins

			// Test all the player's cards as gold
			for (cardNumber = 0; cardNumber < deckCount; cardNumber++)
			{
				testState.hand[player][cardNumber] = gold;
				testState.deck[player][cardNumber] = gold;
				testState.discard[player][cardNumber] = gold;
			}
			retVal = fullDeckCount(player, gold, &testState);
			asserttrue(errorCount, retVal == deckCount * 3);	// Expected coins

			// Test all the players cards as combinations of copper, silver, and gold
			int copperCount = 0, silverCount = 0, goldCount = 0;
			for (cardNumber = 0; cardNumber < deckCount; cardNumber++)
			{
				if ((cardNumber + 1) % 3 == 0)
				{
					testState.hand[player][cardNumber] = gold;
					testState.deck[player][cardNumber] = gold;
					testState.discard[player][cardNumber] = gold;
					goldCount = goldCount + 3;
				}
				else if ((cardNumber + 1) % 2 == 0)
				{
					testState.hand[player][cardNumber] = silver;
					testState.deck[player][cardNumber] = silver;
					testState.discard[player][cardNumber] = silver;
					silverCount = silverCount + 3;
				}
				else
				{
					testState.hand[player][cardNumber] = copper;
					testState.deck[player][cardNumber] = copper;
					testState.discard[player][cardNumber] = copper;
					copperCount = copperCount + 3;
				}
			}
			retVal = fullDeckCount(player, gold, &testState);
			asserttrue(errorCount, retVal == goldCount);			// Function returned proper value

			retVal = fullDeckCount(player, silver, &testState);
			asserttrue(errorCount, retVal == silverCount);			// Function returned proper value

			retVal = fullDeckCount(player, copper, &testState);
			asserttrue(errorCount, retVal == copperCount);			// Function returned proper value
		}
	}

	if (errorCount == 0)
	{
		printf(" TEST SUCCESSFULLY COMPLETED\n");
	}
	else
	{
		printf(" %d TESTS FAILED\n", errorCount);
	}

	printf("\n");

	return 0;
}