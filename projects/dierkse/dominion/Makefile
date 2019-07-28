CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittest1: dominion.o unittest1.c 
	gcc -std=c99 -lm -fpic -coverage unittest1.c dominion.c -o unittest1 

unittest2: dominion.o unittest2.c 
	gcc -std=c99 -lm -fpic -coverage unittest2.c dominion.c -o unittest2

unittest3: dominion.o unittest3.c 
	gcc -std=c99 -lm -fpic -coverage unittest3.c dominion.c -o unittest3

unittest4: dominion.o unittest4.c
	gcc -std=c99 -lm -fpic -coverage unittest4.c dominion.c -o unittest4

unittest5: dominion.o unittest5.c
	gcc -std=c99 -lm -fpic -coverage unittest5.c dominion.c -o unittest5

cardtest1: dominion.o cardtest1.c 
	gcc -std=c99 -lm -fpic -coverage cardtest1.c dominion.c -o cardtest1

cardtest2: dominion.o cardtest2.c
	gcc -std=c99 -lm -fpic -coverage cardtest2.c dominion.c -o cardtest2

cardtest3: dominion.o cardtest3.c 
	gcc -std=c99 -lm -fpic -coverage cardtest3.c dominion.c -o cardtest3

cardtest4: dominion.o cardtest4.c 
	gcc -std=c99 -lm -fpic -coverage cardtest4.c dominion.c -o cardtest4

cardtest5: dominion.o cardtest5.c
	gcc -std=c99 -lm -fpic -coverage cardtest5.c dominion.c -o cardtest5 

unittests: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o
	gcc -std=c99 -lm -fpic -coverage unittest1.c dominion.c -o unittest1
	gcc -std=c99 -lm -fpic -coverage unittest2.c dominion.c -o unittest2
	gcc -std=c99 -lm -fpic -coverage unittest3.c dominion.c -o unittest3
	gcc -std=c99 -lm -fpic -coverage unittest4.c dominion.c -o unittest4
	gcc -std=c99 -lm -fpic -coverage unittest5.c dominion.c -o unittest5
	gcc -std=c99 -lm -fpic -coverage cardtest1.c dominion.c -o cardtest1
	gcc -std=c99 -lm -fpic -coverage cardtest2.c dominion.c -o cardtest2
	gcc -std=c99 -lm -fpic -coverage cardtest3.c dominion.c -o cardtest3
	gcc -std=c99 -lm -fpic -coverage cardtest4.c dominion.c -o cardtest4
	gcc -std=c99 -lm -fpic -coverage cardtest5.c dominion.c -o cardtest5
 
unittestresults: unittest1.c unittest2.c unittest3.c unittest4.c unittest5.c cardtest1.c cardtest2.c cardtest3.c cardtest4.c cardtest5.c dominion.o
	unittest1 &> unittestresults.out
	unittest2 >> unittestresults.out
	unittest3 >> unittestresults.out
	unittest4 >> unittestresults.out
	unittest5 >> unittestresults.out
	cardtest1 >> unittestresults.out
	cardtest2 >> unittestresults.out
	cardtest3 >> unittestresults.out
	cardtest4 >> unittestresults.out
	cardtest5 >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
