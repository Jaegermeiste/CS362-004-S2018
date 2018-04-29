/*********************************************************************
** Program name: Card Test 4
** Author: Jason George
** Date: 20180428
** Description: cardtest4.c - implementation of test for treasure_map
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
			int			cards[10]	= { smithy, adventurer, mine, remodel, sea_hag, village, baron, curse, gardens, treasure_map };
	const	int			numPlayers	= MAX_PLAYERS;
	const	int			randomSeed	= 1;
			unsigned	errorCount	= 0;
			int			handPos		= 0;
	const	int			choice1		= 0,
						choice2		= 0,
						choice3		= 0;
			int			bonus		= 0;
			int			i			= 0;
			int			cardFound	= 0;
			int			maps		= 0;

	struct gameState state, testState;
	memset(&state, 0, sizeof(struct gameState));
	memset(&testState, 0, sizeof(struct gameState));

	// Set up game
	int retVal = initializeGame(numPlayers, cards, randomSeed, &state);
	asserttrue(errorCount, retVal == 0);

	for (maps = 1; maps <= 2; maps++)
	{
		printf(" CARD TEST: treasure_map, count = %d\n", maps);

		memcpy(&testState, &state, sizeof(struct gameState));
		cardFound = 0;

		const int player = testState.whoseTurn;

		// Check for a treasure_map card dealt
		for (i = 0; i < testState.handCount[player]; i++)
		{
			if (testState.hand[player][i] == treasure_map)
			{
				handPos = i;
				cardFound++;
			}
		}

		// Add the appropriate number of treasure_map cards if not found
		for (i = 0; (i < testState.handCount[player]) && (cardFound < maps); i++)
		{
			if (testState.hand[player][i] != treasure_map)
			{
				testState.hand[player][i] = treasure_map;
				cardFound++;
				handPos = i;
			}
		}

		const int handCount = testState.handCount[player];
		const int numActions = testState.numActions;

		// Count existing golds in deck
		int goldCount = 0;
		for (i = 0; i < testState.deckCount[player]; i++)
		{
			if (testState.deck[player][i] == gold)
			{
				goldCount++;
			}
		}

		retVal = cardEffect(treasure_map, choice1, choice2, choice3, &testState, handPos, &bonus);
		asserttrue(errorCount, retVal > -1);
		asserttrue(errorCount, testState.handCount[player] == (handCount - cardFound));			// -treasure_map(s)
		asserttrue(errorCount, testState.numActions <= numActions);								// treasure_map is terminal, actions should not increase

		// Count existing golds in deck
		int newGoldCount = 0;
		for (i = 0; i < testState.deckCount[player]; i++)
		{
			if (testState.deck[player][i] == gold)
			{
				newGoldCount++;
			}
		}

		if (maps == 1)
		{
			asserttrue(errorCount, newGoldCount == goldCount);				// discarding single adds no golds
		}
		else if (maps >= 2)
		{
			asserttrue(errorCount, newGoldCount == (goldCount + 4));				// discarding two adds 4 golds
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