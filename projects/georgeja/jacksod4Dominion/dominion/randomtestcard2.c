/*********************************************************************
** Program name: Random Card Test 2
** Author: Jason George
** Date: 20180511
** Description: randomtestcard2.c - implementation of test for village
*********************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

// To avoid making it hard to collect coverage when a test fails, use your own asserttrue function instead
// of the standard C assert(which basically crashes the code and fails to collect coverage).
#ifndef asserttrue
#define asserttrue(x, y) if ((y) != 0) { x += 0; } else { printf(" !!! TEST FAILED AT LINE: %d\n", __LINE__); x += 1; };
#endif

#ifndef asserttrueX
#define asserttrueX(x, y, z) if ((y) != 0) { x += 0; } else { printf(" !!! TEST FAILED AT LINE: %d; %s\n", __LINE__, z); x += 1; };
#endif

#ifndef string
#define string(x) #x
#endif

#ifndef asserttrueEX
#define asserttrueEX(runCount, errorNum, testVal, card, c1, c2, c3, hp, b) if ((testVal) != 0) { errorNum += 0; } \
else { printf(" !!! TEST FAILED on run %d at line %d with inputs %s %d, %s %d, %s %d, %s %d, %s %d, %s %d\n", \
runCount, __LINE__, string(card), card, string(c1), c1, string(c2), c2, string(c3), c3, string(hp), hp, string(b), b); errorNum += 1; };
#endif

#ifndef MAX_ERRORS
#define MAX_ERRORS  256
#endif

#ifndef MAX_RUNS
#define MAX_RUNS    INT_MAX - 1
#endif

#ifndef RANDOM_SEED
#define RANDOM_SEED 1
#endif

#ifndef CHOICE_MIN
#define CHOICE_MIN  -2
#endif

#ifndef CHOICE_MAX
#define CHOICE_MAX  3
#endif

#ifndef HANDPOS_MIN
#define HANDPOS_MIN   -1
#endif

#ifndef HANDPOS_MAX
#define HANDPOS_MAX   10
#endif

#ifndef BONUS_MIN
#define BONUS_MIN   -1
#endif

#ifndef BONUS_MAX
#define BONUS_MAX   10
#endif

/*********************************************************************
** Description: void randomState(struct gameState *state)
**      Returns a random gameState.
*********************************************************************/
void randomState(struct gameState *state)
{
	memset(state, 0, sizeof(struct gameState));
	unsigned i = 0, j = 0;
	int			cards[10] = { smithy, adventurer, mine, remodel, sea_hag, village, baron, curse, gardens, treasure_map };
	int numPlayers = ((rand() % (MAX_PLAYERS - 2 + 1)) + 2);;
	initializeGame(numPlayers, cards, RANDOM_SEED, state);

	state->numPlayers = numPlayers;
	for (i = 0; i <= treasure_map; i++)
	{
		state->supplyCount[i] = ((rand() % (60 - 8 + 1)) + 8);
	}

	for (i = 0; i <= treasure_map; i++)
	{
		state->embargoTokens[i] = (rand() % 2);
	}

	state->outpostPlayed = (rand() % 2);
	state->outpostTurn = (rand() % state->numPlayers);
	state->whoseTurn = (rand() % state->numPlayers);
	state->phase = (rand() % 2);
	state->numActions = ((rand() % (3 - 1 + 1)) + 1);
	state->coins = ((rand() % (60 - 0 + 1)) + 0);
	state->numBuys = ((rand() % (3 - 1 + 1)) + 1);

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		for (j = 0; j < MAX_HAND; j++)
		{
			state->hand[i][j] = ((rand() % (treasure_map - curse + 1)) + curse);
		}
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		state->handCount[i] = ((rand() % (5 - 1 + 1)) + 1);
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		for (j = 0; j < MAX_DECK; j++)
		{
			state->deck[i][j] = ((rand() % (treasure_map - curse + 1)) + curse);
		}
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		state->deckCount[i] = ((rand() % (5 - 1 + 1)) + 1);
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		for (j = 0; j < MAX_DECK; j++)
		{
			state->discard[i][j] = ((rand() % (treasure_map - curse + 1)) + curse);
		}
	}

	for (i = 0; i < MAX_PLAYERS; i++)
	{
		state->discardCount[i] = ((rand() % (5 - 1 + 1)) + 1);
	}

	state->playedCardCount = ((rand() % (60 - 0 + 1)) + 0);
}

/*********************************************************************
** Description: int validateState(gameState state1, gameState state2, <various bools>)
**      Validates the contents of two state structs, based on test flags.
**      Returns errorCount.
*********************************************************************/
int validateState(struct gameState state1,
	struct gameState state2,
	int enforceNumPlayers,
	int enforceSupplyCount,
	int enforceEmbargoTokens,
	int enforceOutpostPlayed,
	int enforceOutpostTurn,
	int enforceWhoseTurn,
	int enforcePhase,
	int enforceNumActions,
	int enforceCoins,
	int enforceNumBuys,
	int enforceHand,
	int enforceHandCount,
	int enforceDeck,
	int enforceDeckCount,
	int enforceDiscard,
	int enforceDiscardCount,
	int enforcePlayedCards,
	int enforcePlayedCardCount)
{
	int errorCount = 0;
	unsigned i = 0;
	unsigned j = 0;

	if (enforceNumPlayers > 0)
	{
		asserttrueX(errorCount, state1.numPlayers == state2.numPlayers, "numPlayers");
	}

	if (enforceSupplyCount > 0)
	{
		for (i = 0; i < (sizeof(state1.supplyCount) / sizeof(int)); i++)
		{
			asserttrueX(errorCount, state1.supplyCount[i] == state2.supplyCount[i], "supplyCount");
		}
	}

	if (enforceEmbargoTokens > 0)
	{
		for (i = 0; i < (sizeof(state1.embargoTokens) / sizeof(int)); i++)
		{
			asserttrueX(errorCount, state1.embargoTokens[i] == state2.embargoTokens[i], "embargoTokens");
		}
	}

	if (enforceOutpostPlayed > 0)
	{
		asserttrueX(errorCount, state1.outpostPlayed == state2.outpostPlayed, "outpostPlayed");
	}

	if (enforceOutpostTurn > 0)
	{
		asserttrueX(errorCount, state1.outpostTurn == state2.outpostTurn, "outpostTurn");
	}

	if (enforceWhoseTurn > 0)
	{
		asserttrueX(errorCount, state1.whoseTurn == state2.whoseTurn, "whoseTurn");
	}

	if (enforceNumActions > 0)
	{
		asserttrueX(errorCount, state1.numActions == state2.numActions, "numActions");
	}

	if (enforceCoins > 0)
	{
		asserttrueX(errorCount, state1.coins == state2.coins, "coins");
	}

	if (enforceNumBuys > 0)
	{
		asserttrueX(errorCount, state1.numBuys == state2.numBuys, "numBuys");
	}

	if (enforceHand > 0)
	{
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			for (j = 0; j < MAX_HAND; j++)
			{
				asserttrueX(errorCount, state1.hand[i][j] == state2.hand[i][j], "hand");
			}
		}
	}

	if (enforceHandCount > 0)
	{
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			asserttrueX(errorCount, state1.handCount[i] == state2.handCount[i], "handCount");
		}
	}

	if (enforceDeck > 0)
	{
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			for (j = 0; j < MAX_DECK; j++)
			{
				asserttrueX(errorCount, state1.deck[i][j] == state2.deck[i][j], "deck");
			}
		}
	}

	if (enforceDeckCount > 0)
	{
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			asserttrueX(errorCount, state1.deckCount[i] == state2.deckCount[i], "deckCount");
		}
	}

	if (enforceDiscard > 0)
	{
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			for (j = 0; j < MAX_DECK; j++)
			{
				asserttrueX(errorCount, state1.discard[i][j] == state2.discard[i][j], "discard");
			}
		}
	}

	if (enforceDiscardCount > 0)
	{
		for (i = 0; i < MAX_PLAYERS; i++)
		{
			asserttrueX(errorCount, state1.discardCount[i] == state2.discardCount[i], "discardCount");
		}
	}

	if (enforcePlayedCards > 0)
	{
		for (i = 0; i < MAX_DECK; i++)
		{
			asserttrueX(errorCount, state1.playedCards[i] == state2.playedCards[i], "playedCards");
		}
	}

	if (enforcePlayedCardCount > 0)
	{
		asserttrueX(errorCount, state1.playedCardCount == state2.playedCardCount, "playedCardCount");
	}

	return errorCount;
}

/*********************************************************************
** Description: int main(int argc, char *argv[])
**      Entry point for the program.
**      Returns 0.
*********************************************************************/
int main(int argc, char *argv[])
{
	int			cards[10] = { smithy, adventurer, mine, remodel, sea_hag, village, baron, curse, gardens, treasure_map };
	const	int			numPlayers = MAX_PLAYERS;
	unsigned	errorCount = 0;
	int			handPos = 0;
	int			choice1 = 0,
		choice2 = 0,
		choice3 = 0;
	int			bonus = 0;
	int			i = 0;
	int			cardFound = 0;
	int         runTestLoop = 1;
	unsigned    runCount = 0;
	time_t      startTime = { 0 };
	time_t      currentTime = { 0 };

	struct gameState state, testState;
	memset(&state, 0, sizeof(struct gameState));
	memset(&testState, 0, sizeof(struct gameState));

	// Set up game
	int retVal = initializeGame(numPlayers, cards, RANDOM_SEED, &state);
	asserttrue(errorCount, retVal == 0);

	printf(" RANDOM CARD TEST: village\n");

	// Method under test is cardEffect, with the card "village"

	// Card effect has the following prototype:
	// int cardEffect(int card, int choice1, int choice2, int choice3, struct gameState *state, int handPos, int *bonus)

	// Valid range for card is an enum from curse through treasure_map, inclusive
	// Valid range for choice1 is an integer from -1 to 2 - usage varies per card
	// Valid range for choice2 is an integer from -1 to 2 - usage varies per card
	// Valid range for choice3 is an integer from -1 to 2 - usage varies per card
	// Valid input for state is an initialized gameState struct
	// Valid input for handPos is an int between 0 and the size of the hand
	// Valid input for bonus is a pointer to an integer with a bonus value of 0+

	while (runTestLoop > 0)
	{
		randomState(&testState);

		const int player = state.whoseTurn;

		// Check for an village card dealt
		for (i = 0; (i < state.handCount[0]) && (cardFound == 0); i++)
		{
			if (state.hand[player][i] == village)
			{
				handPos = i;
				cardFound++;
			}
		}

		// Add an village card if not found
		if (cardFound <= 0)
		{
			state.hand[player][i] = village;
			cardFound = 1;
			handPos = 0;
		}

		memcpy(&state, &testState, sizeof(struct gameState));

		const int handCount = testState.handCount[player];
		const int numActions = testState.numActions;

		// Generate random input values in a given range
		choice1 = ((rand() % (CHOICE_MAX - CHOICE_MIN + 1)) + CHOICE_MIN);
		choice2 = ((rand() % (CHOICE_MAX - CHOICE_MIN + 1)) + CHOICE_MIN);
		choice3 = ((rand() % (CHOICE_MAX - CHOICE_MIN + 1)) + CHOICE_MIN);
		handPos = ((rand() % (HANDPOS_MAX - HANDPOS_MIN + 1)) + HANDPOS_MIN);
		const int originalBonus = ((rand() % (BONUS_MAX - BONUS_MIN + 1)) + BONUS_MIN);
		bonus = originalBonus;

		// Run
		retVal = cardEffect(village, choice1, choice2, choice3, &testState, handPos, &bonus);
		runCount++;

		// Validate function did not return an error
		asserttrueEX(runCount, errorCount, retVal > -1, village, choice1, choice2, choice3, handPos, originalBonus);

		// Validate function adjusted the hand as required by the rules of the card: -village, + 1 other
		asserttrueEX(runCount, errorCount, testState.handCount[player] == (handCount - 1 + 1), village, choice1, choice2, choice3, handPos, originalBonus);

		// using village consumes 1 action but adds 2 actions
		asserttrueEX(runCount, errorCount, testState.numActions == (numActions + 2), village, choice1, choice2, choice3, handPos, originalBonus);

		// Validate bonus did not change, because that is not an effect of village
		asserttrueEX(runCount, errorCount, bonus == originalBonus, village, choice1, choice2, choice3, handPos, originalBonus);

		// Validate gameState
		errorCount += validateState(state, testState, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0);

		// Determine loop continuation
		if (errorCount >= MAX_ERRORS)
		{
			printf(" >>> TERMINATING TEST: MAX_ERRORS MET OR EXCEEDED\n");

			runTestLoop = 0;
		}
		else if (difftime(currentTime, startTime) > 280)
		{
			printf(" >>> TERMINATING TEST: TIME LIMIT MET OR EXCEEDED\n");

			runTestLoop = 0;
		}
		else if (runCount >= MAX_RUNS)
		{
			runTestLoop = 0;
		}
	}

	if (errorCount == 0)
	{
		printf(" %d TESTS SUCCESSFULLY COMPLETED\n", runCount);
	}
	else
	{
		printf(" %d TESTS FAILED\n", errorCount);
	}

	printf("\n");

	return 0;
}