/*********************************************************************
** Program name: Unit Test 4
** Author: Jason George
** Date: 20180428
** Description: unittest4.c - implementation of test for isGameOver
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
			int			i			= 0;

	struct gameState state, testState;
	memset(&state, 0, sizeof(struct gameState));
	memset(&testState, 0, sizeof(struct gameState));

	// Set up game
	int retVal = initializeGame(numPlayers, cards, randomSeed, &state);
	asserttrue(errorCount, retVal == 0);

	for (i = 0; i <= 1; i++)
	{
		if (i == 1)
		{
			printf(" UNIT TEST: isGameOver (pass 2, both rules combined)\n");

			// Set all supplies to 0 before testing province rule again (combination)
			memset(&state.supplyCount, 0, sizeof(int) * 27);
		}
		else
		{
			printf(" UNIT TEST: isGameOver (pass 1, both rules individually)\n");

			// Test supply rules
			memcpy(&testState, &state, sizeof(struct gameState));
			retVal = isGameOver(&testState);				// No changes
			asserttrue(errorCount, retVal == 0);			// Should return false

			memcpy(&testState, &state, sizeof(struct gameState));
			testState.supplyCount[0] = 0;					// Zero supply 0
			retVal = isGameOver(&testState);
			asserttrue(errorCount, retVal == 0);			// Should return false

			memcpy(&testState, &state, sizeof(struct gameState));
			testState.supplyCount[0] = 0;					// Zero supply 0
			testState.supplyCount[1] = 0;					// Zero supply 1
			retVal = isGameOver(&testState);
			asserttrue(errorCount, retVal == 0);			// Should return false

			memcpy(&testState, &state, sizeof(struct gameState));
			testState.supplyCount[0] = 0;					// Zero supply 0
			testState.supplyCount[1] = 0;					// Zero supply 1
			testState.supplyCount[2] = 0;					// Zero supply 2
			retVal = isGameOver(&testState);
			asserttrue(errorCount, retVal == 1);			// Should return true
		}

		// Province rule for game end
		memcpy(&testState, &state, sizeof(struct gameState));
		retVal = isGameOver(&testState);				// No changes
		asserttrue(errorCount, retVal == i);			// Return varies based on state of other rule

		memcpy(&testState, &state, sizeof(struct gameState));
		testState.supplyCount[province] = 0;			// Zero supply
		retVal = isGameOver(&testState);
		asserttrue(errorCount, retVal == 1);			// Should always return true

		memcpy(&testState, &state, sizeof(struct gameState));
		testState.supplyCount[province] = -1;			// Negative supply
		retVal = isGameOver(&testState);
		asserttrue(errorCount, retVal == 1);			// Should always return true

		memcpy(&testState, &state, sizeof(struct gameState));
		testState.supplyCount[province] = INT_MIN;		// Extreme negative supply
		retVal = isGameOver(&testState);
		asserttrue(errorCount, retVal == 1);			// Should always return true

		memcpy(&testState, &state, sizeof(struct gameState));
		testState.supplyCount[province] = 1;			// One card
		retVal = isGameOver(&testState);
		asserttrue(errorCount, retVal == i);			// Return varies based on state of other rule

		memcpy(&testState, &state, sizeof(struct gameState));
		testState.supplyCount[province] = INT_MAX;		// Extreme maximum supply
		retVal = isGameOver(&testState);
		asserttrue(errorCount, retVal == i);			// Return varies based on state of other rule
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