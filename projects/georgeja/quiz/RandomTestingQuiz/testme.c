#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	// Generate an ASCII character between 32 and 126
	return (char)((rand() % (126 - 32 + 1)) + 32);
}

char *inputString()
{
	static unsigned startTimeSet = 0;
	static time_t startTime = {0};
	time_t currentTime = {0};
	// include only the letters used in the target statement
	static char string[7] = {'\0'};	// Use 7 characters to always ensure we are null terminated
	const char sourceBuffer[] = "rest\0\0";
	unsigned i = 0;

	memset(&string, 0, sizeof(char) * 7);

	// Set the start time, if need be
	if (!startTimeSet)
	{
		startTime = time(NULL);
		startTimeSet = 1;

		// Ensure that we test the branch before the state can increase
		string[0] = 'r';
		string[1] = 'e';
		string[2] = 's';
		string[3] = 'e';
		string[4] = 't';
		string[5] = '\0';

		return (char*)string;
	}

	// Iterate through the first 6 characters
	for (i = 0; i < 6; i++)
	{
		string[i] = sourceBuffer[rand() % 5];
	}

	// If we are approaching the time limit, force the reset
	currentTime = time(NULL);
	if (difftime(currentTime, startTime) > 280)	// 300 seconds is 5 minutes
	{
		printf(" DEBUG: Near 5 minutes\n");
		string[0] = 'r';
		string[1] = 'e';
		string[2] = 's';
		string[3] = 'e';
		string[4] = 't';
		string[5] = '\0';
	}
	else if (strncmp(string, "reset", 5) == 0) // Less than 280 seconds
	{
		// Guarantee that we don't hit the reset
		string[0] = 's';
	}

	return (char*)string;
}

void testme()
{
	int tcCount = 0;
	char *s;
	char c;
	int state = 0;
	while (1)
	{
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0) state = 1;
		if (c == '(' && state == 1) state = 2;
		if (c == '{' && state == 2) state = 3;
		if (c == ' '&& state == 3) state = 4;
		if (c == 'a' && state == 4) state = 5;
		if (c == 'x' && state == 5) state = 6;
		if (c == '}' && state == 6) state = 7;
		if (c == ')' && state == 7) state = 8;
		if (c == ']' && state == 8) state = 9;
		if (s[0] == 'r' && s[1] == 'e'
			&& s[2] == 's' && s[3] == 'e'
			&& s[4] == 't' && s[5] == '\0'
			&& state == 9)
		{
			printf("error ");
			exit(200);
		}
	}
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
	testme();
	return 0;
}
