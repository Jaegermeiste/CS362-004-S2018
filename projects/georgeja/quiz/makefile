CFLAGS = -Wall -fpic -coverage -fprofile-arcs -ftest-coverage -lm -O0 -da -Q

testme:
	gcc -o testme testme.c -g $(CFLAGS)

all: testme 

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out

rebuild: clean all

run: testme
	rm -f *.gcov
	-./testme
	gcov -b -f testme