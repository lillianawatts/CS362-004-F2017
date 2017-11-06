CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

unit1: dominion.o unittest1.c
	gcc -o unitTest1 unittest1.c -g dominion.o rngs.o  $(CFLAGS)

unit2: dominion.o unittest2.c
	gcc -o unitTest2 unittest2.c -g dominion.o rngs.o  $(CFLAGS)

unit3: dominion.o unittest3.c
	gcc -o unitTest3 unittest3.c -g dominion.o rngs.o  $(CFLAGS)

unit4: dominion.o unittest4.c
	gcc -o unitTest4 unittest4.c -g dominion.o rngs.o  $(CFLAGS)

card1: dominion.o cardtest1.c
	gcc -o cardTest1 cardtest1.c -g dominion.o rngs.o  $(CFLAGS)

card2: dominion.o cardtest2.c
	gcc -o cardTest2 cardtest2.c -g dominion.o rngs.o  $(CFLAGS)

card3: dominion.o cardtest3.c
	gcc -o cardTest3 cardtest3.c -g dominion.o rngs.o  $(CFLAGS)

card4: dominion.o cardtest4.c
	gcc -o cardTest4 cardtest4.c -g dominion.o rngs.o  $(CFLAGS)

allTests: unit1 unit2 unit3 unit4 card1 card2 card3 card4

unittestresults:
	./unitTest1 &> unittestresult.out
	./unitTest2 >> unittestresult.out
	./unitTest3 >> unittestresult.out
	./unitTest4 >> unittestresult.out
	./cardTest1 >> unittestresult.out
	./cardTest2 >> unittestresult.out
	./cardTest3 >> unittestresult.out
	./cardTest4 >> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestrestults.out: allTests unittestResults

randomtestadventurer.out: randomtestadventurer.c dominion.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer &> randomtestadventurer.out
randomtestcard1.out: randomtestcard1.c dominion.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 &> randomtestcard1.out
randomtestcard2.out: randomtestcard2.c dominion.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 &> randomtestcard2.out

allrand: randomtestadventurer.out randomtestcard1.out randomtestcard2.out

clean:
	rm -f *.o unitTest1 unitTest2 unitTest3 unitTest4 cardTest1 cardTest2 cardTest3 cardTest4 *.gcov *.gcda *.gcno *.so
