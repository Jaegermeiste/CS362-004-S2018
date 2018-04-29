/*********************************************************************
** Program name: Card Test 3
** Author: Jason George
** Date: 20180428
** Description: cardtest3.c - implementation of test for village
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

	struct gameState state, testState;
	memset(&state, 0, sizeof(struct gameState));
	memset(&testState, 0, sizeof(struct gameState));

	// Set up game
	int retVal = initializeGame(numPlayers, cards, randomSeed, &state);
	asserttrue(errorCount, retVal == 0);

	printf(" CARD TEST: village\n");

	memcpy(&testState, &state, sizeof(struct gameState));

	const int player = testState.whoseTurn;

	// Check for a village card dealt
	for (i = 0; (i < testState.handCount[0]) && (cardFound == 0); i++)
	{
		if (testState.hand[player][i] == village)
		{
			handPos = i;
			cardFound++;
		}
	}

	// Add a village card if not found
	if (cardFound <= 0)
	{
		testState.hand[player][i] = village;
		cardFound = 1;
		handPos = 0;
	}

	const int handCount = testState.handCount[player];
	const int numActions = testState.numActions;

	retVal = cardEffect(village, choice1, choice2, choice3, &testState, handPos, &bonus);
	asserttrue(errorCount, retVal > -1);
	asserttrue(errorCount, testState.handCount[player] == (handCount - 1 + 1));		// -village, + 1 card
	asserttrue(errorCount, testState.numActions == (numActions + 2));			// using village consumes 1 action but adds 2 actions

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