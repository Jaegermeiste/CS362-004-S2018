/*********************************************************************
** Program name: Unit Test 1
** Author: Jason George
** Date: 20180428
** Description: unittest1.c - implementation of test for updateCoins
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

/*********************************************************************
** Description: int main(int argc, char *argv[])
**      Entry point for the program.
**      Returns 0.
*********************************************************************/
int main(int argc, char *argv[])
{
			int			cards[10]		= { smithy, adventurer, mine, remodel, sea_hag, village, baron, great_hall, curse, gardens };
	const	int			numPlayers		= MAX_PLAYERS;
			int			player			= 0;
	const	int			randomSeed		= 1;
			int			bonus			= 0;
	const	int			minBonus		= -10;
	const	int			maxBonus		= 10;
			int			handCount		= 0;
	const	int			maxHandCount	= 5;
			int			cardNumber		= 0;
			unsigned	errorCount		= 0;

	struct gameState state, testState;
	memset(&state, 0, sizeof(struct gameState));
	memset(&testState, 0, sizeof(struct gameState));

	// Set up game
	int retVal = initializeGame(numPlayers, cards, randomSeed, &state);
	asserttrue(errorCount, retVal == 0);

	printf(" UNIT TEST: updateCoins\n");

	// Test the null state - no changes
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = updateCoins(0, &testState, 0);
	asserttrue(errorCount, retVal == 0);
	asserttrue(errorCount, testState.coins == state.coins);

	// Test invalid values for player number
	if (state.coins == 0)
	{
		state.coins++;	// Make sure we start with a non-zero coin value
	}

	// Player number -1 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = updateCoins(-1, &testState, 0);
	asserttrue(errorCount, retVal != 0);						// Function returned badly
	asserttrue(errorCount, testState.coins == 0);				// Expected coins are 0
	asserttrue(errorCount, testState.coins != state.coins);		// The value changed from the original

	/* // Causes SIGSEGV
	// Player number -2147483648 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = updateCoins(INT_MIN, &testState, 0);
	asserttrue(errorCount, retVal != 0);						// Function returned badly
	asserttrue(errorCount, testState.coins == 0);				// Expected coins are 0
	asserttrue(errorCount, testState.coins != state.coins);		// The value changed from the original
	*/

	// Player number 4 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	//makeprintf("%d %d\n", testState.coins, state.coins);
	retVal = updateCoins(MAX_PLAYERS, &testState, 0);
	asserttrue(errorCount, retVal != 0);						// Function returned badly
	asserttrue(errorCount, testState.coins == 0);				// Expected coins are 0
	//printf("%d %d\n", testState.coins, state.coins);
	asserttrue(errorCount, testState.coins != state.coins);		// The value changed from the original

	// Player number 5 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = updateCoins(MAX_PLAYERS + 1, &testState, 0);
	asserttrue(errorCount, retVal != 0);						// Function returned badly
	asserttrue(errorCount, testState.coins == 0);				// Expected coins are 0
	asserttrue(errorCount, testState.coins != state.coins);		// The value changed from the original

	/* // Causes SIGSEGV
	// Player number 2147483647 (in a valid range of 0-3)
	memcpy(&testState, &state, sizeof(struct gameState));
	retVal = updateCoins(INT_MAX, &testState, 0);
	asserttrue(errorCount, retVal != 0);						// Function returned badly
	asserttrue(errorCount, testState.coins == 0);				// Expected coins are 0
	asserttrue(errorCount, testState.coins != state.coins);		// The value changed from the original
	*/

	// Player Num Variable
	for (player = 0; player < numPlayers; player++)
	{
		// Size of hand
		for (handCount = 1; handCount <= maxHandCount; handCount++)
		{
			// Bonuses
			for (bonus = minBonus; bonus <= maxBonus; bonus++)
			{
				// Re-set up game
				memset(&testState, 0, sizeof(struct gameState));
				retVal = initializeGame(numPlayers, cards, randomSeed, &testState);
				asserttrue(errorCount, retVal == 0);

				// Set the number of cards in the hand
				testState.handCount[player] = handCount;

				// Test all the player's cards as copper
				for (cardNumber = 0; cardNumber < handCount; cardNumber++)
				{
					testState.hand[player][cardNumber] = copper;
				}
				retVal = updateCoins(player, &testState, bonus);
				asserttrue(errorCount, retVal == 0);								// Function returned cleanly
				asserttrue(errorCount, testState.coins == handCount * 1 + bonus);	// Expected coins

				// Test all the player's cards as silver
				for (cardNumber = 0; cardNumber < handCount; cardNumber++)
				{
					testState.hand[player][cardNumber] = silver;
				}
				retVal = updateCoins(player, &testState, bonus);
				asserttrue(errorCount, retVal == 0);								// Function returned cleanly
				asserttrue(errorCount, testState.coins == handCount * 2 + bonus);	// Expected coins

				// Test all the player's cards as gold
				for (cardNumber = 0; cardNumber < handCount; cardNumber++)
				{
					testState.hand[player][cardNumber] = gold;
				}
				retVal = updateCoins(player, &testState, bonus);
				asserttrue(errorCount, retVal == 0);								// Function returned cleanly
				asserttrue(errorCount, testState.coins == handCount * 3 + bonus);	// Expected coins

				// Test all the players cards as combinations of copper, silver, and gold
				int copperCount = 0, silverCount = 0, goldCount = 0;
				for (cardNumber = 0; cardNumber < handCount; cardNumber++)
				{
					if ((cardNumber + 1) % 3 == 0)
					{
						testState.hand[player][cardNumber] = gold;
						goldCount++;
					}
					else if ((cardNumber + 1) % 2 == 0)
					{
						testState.hand[player][cardNumber] = silver;
						silverCount++;
					}
					else
					{
						testState.hand[player][cardNumber] = copper;
						copperCount++;
					}
				}
				retVal = updateCoins(player, &testState, bonus);
				asserttrue(errorCount, retVal == 0);								// Function returned cleanly
				asserttrue(errorCount, testState.coins == ((goldCount * 3) + (silverCount * 2) + (copperCount * 1) + bonus));	// Expected coins
			}
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