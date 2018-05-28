/*********************************************************************
** Program name: Unit Test 2
** Author: Jason George
** Date: 20180428
** Description: unittest2.c - implementation of test for getCost
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
	const	int			values[10] = { 4, 6, 5, 4, 4, 3, 4, 0, 4, 4 };
			int			cardNumber = 0;
			unsigned	errorCount = 0;

	// Set up game
	int retVal = 0;

	printf(" UNIT TEST: getCost\n");

	// Test invalid values for card number
	// Card number -1 (in a valid range of curse-treasure_map)
	retVal = getCost(curse - 1);
	asserttrue(errorCount, retVal == -1);						// Function returned badly

	// Card number -2147483648 (in a valid range of curse-treasure_map)
	retVal = getCost(INT_MIN);
	asserttrue(errorCount, retVal == -1);						// Function returned badly

	// Card number 27 (in a valid range of curse-treasure_map)
	retVal = getCost(treasure_map + 1);
	asserttrue(errorCount, retVal == -1);						// Function returned badly

	// Card number 2147483647 (in a valid range of curse-treasure_map)
	retVal = getCost(INT_MAX);
	asserttrue(errorCount, retVal == -1);						// Function returned badly

	// Predefined (known value) testing
	for (cardNumber = 0; cardNumber < (sizeof(cards)/sizeof(int)); cardNumber++)
	{
		retVal = getCost(cards[cardNumber]);
		asserttrue(errorCount, retVal == values[cardNumber]);		// Function returned proper number
	}

	// Card Num Variable
	for (cardNumber = curse; cardNumber <= treasure_map; cardNumber++)
	{
		retVal = getCost(cardNumber);
		asserttrue(errorCount, retVal != -1);						// Function returned something not an error
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