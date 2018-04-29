CFLAGS = -Wall -fpic -coverage -fprofile-arcs -ftest-coverage -lm -enable-checking -O0 -da -Q

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to enter: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

# Assignment 3 Tests
unittest1: unittest1.c dominion.o rngs.o interface.o
	gcc -o unittest1 -g  unittest1.c dominion.o rngs.o interface.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o interface.o
	gcc -o unittest2 -g  unittest2.c dominion.o rngs.o interface.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o interface.o
	gcc -o unittest3 -g  unittest3.c dominion.o rngs.o interface.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o interface.o
	gcc -o unittest4 -g  unittest4.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o interface.o
	gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o interface.o
	gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o interface.o
	gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o interface.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o interface.o
	gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o interface.o $(CFLAGS)

testAll: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4

# Add a rule in Makefile that will generate and execute all of these tests, and append complete
# testing results (including % coverage) into a file called unittestresults.out. The rule should be
# named unittestresults.out and should depend on all your test code as well as the dominion
# code. The .out files contain the output of your running tests and coverage information. Basically
# .out file should act as a proof that your tests run correctly and you collected coverage
# information correctly. (10 points)
runtests: unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4 
	rm -f unittestresults.out
	echo "Results for running Dominion tests:" >> unittestresults.out
	echo "unittest1:" >> unittestresults.out
	./unittest1 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "unittest2:" >> unittestresults.out
	./unittest2 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "unittest3:" >> unittestresults.out
	./unittest3 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "unittest4:" >> unittestresults.out
	./unittest4 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "cardtest1:" >> unittestresults.out
	./cardtest1 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "cardtest2:" >> unittestresults.out
	./cardtest2 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "cardtest3:" >> unittestresults.out
	./cardtest3 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "cardtest4:" >> unittestresults.out
	./cardtest4 >> unittestresults.out 2>&1
	gcov -b -f dominion.c >> unittestresults.out 2>&1
	echo "gcov detail:" >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out 2>&1


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe unittest1 unittest2 unitetest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
