CFLAGS = -Wall -fpic -coverage -fprofile-arcs -ftest-coverage -lm -enable-checking -O0 -da -Q

testme:
	gcc -o testme testme.c -g $(CFLAGS)

all: testme 

clean:
	rm -f *.o testme.exe testme *.gcov *.gcda *.gcno *.so *.out

rebuild: clean all

run: testme
	./testme
	gcov -b -f testme