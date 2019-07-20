/* -----------------------------------------------------------------------
 * Unit test for MinionEffect()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  Compile: gcc -std=c99 unittest2.c -lm -o unittest2
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion.c"
#include "dominion_helpers.h"
#include "rngs.h"
#include "rngs.c"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main(){

	int i;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, minion, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;
	
	printf ("\nTesting minionEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Num Actions: %d, Num Coins: %d, Hand: %d, Discard: %d\n", G.numActions, G.coins, G.handCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
	            
//Test choice1 = 1 & choice2 = 0, adds action and adds 2 coins
	printf("\n\nTest choice1= 1, Adds Action, +2 coins, Discards Minion Card\n");
	minionEffect(&testG, 1, 0, 0, testG.whoseTurn);

	//Test that Adds Action
	printf("Actions: Expected value: %d, Result: %d. ", G.numActions + 1, testG.numActions);
	if(G.numActions+1 == testG.numActions){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	//Test that Adds 2 coins
	printf("COINS: Expected value: %d, Result: %d. ", G.coins + 2, testG.coins);
	if(G.coins + 2 == testG.coins){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	//Test that discards minion card
	printf("Discard Minion from Hand: Expected value: %d, Result: %d. ", G.handCount[G.whoseTurn] - 1, testG.handCount[testG.whoseTurn]);
	if(G.handCount[G.whoseTurn] - 1 == testG.handCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }
	printf("DISCARD MINION to DISCARD PILE: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+1, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+1 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}


	memcpy(&testG, &G, sizeof(struct gameState));  //refresh game
	printf("Num Actions: %d, Num Coins: %d, Hand: %d, Discard: %d\n", testG.numActions, testG.coins, testG.handCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);


//Test choice1=0 and choice2=1, hand discarded & draws 4 cards from deck, other player (has 5 cards) discarded & redrawn 4
	printf("\n\nTest choice2=1, discard cP hand, draw 4 cards from deck, other player with 5 cards discards and redraws 4");
	minionEffect(&testG, 0, 1, 0, testG.whoseTurn);

	//Test discard pile == 5
	printf("DISCARD Curr Player Hand: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+5, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+5 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Test hand pile == 4
	printf("Redraw Hand to 4: Expected value: 4, Result: %d. ", testG.handCount[testG.whoseTurn]);
	if(testG.handCount[testG.whoseTurn] == 4){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	//Other players discard pile == 5
	printf("DISCARD Other Player's Hand: Expected value: %d, Result: %d. ", G.discardCount[1]+5, testG.discardCount[1]);
	if(G.discardCount[1]+5 == testG.discardCount[1]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Other players hand == 4
	printf("Other Player Redraws Hand to 4: Expected value: 4, Result: %d. ", testG.handCount[1]);
	if(testG.handCount[1] == 4){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }


	G.handCount[1] = 3;  //change the other player's handcount to just 4

	memcpy(&testG, &G, sizeof(struct gameState));  //refresh game
	printf("Turn: %d, Hand: %d, Discard: %d\n", testG.whoseTurn, testG.handCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);

//Test choice1-0 and choice 2=1, hand discarded & draws 4 cards from deck, other player (has 3 cards) discard and hand stay same
	printf("\n\nTest choice2=1, other player has 3 cards so doesn't discard hand and redraw 4");
	minionEffect(&testG, 0, 1, 0, testG.whoseTurn);

	//Other players discard pile doesn't change
	printf("Other Player's Discard Pile Stays Same: Expected value: %d, Result: %d. ", G.discardCount[1], testG.discardCount[1]);
	if(G.discardCount[1] == testG.discardCount[1]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Other players hand still is 3
	printf("Other Player Hand Stays Same: Expected value: %d, Result: %d. ", G.handCount[1], testG.handCount[1]);
	if(G.handCount[1] == testG.handCount[1]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	
	printf("**END UNIT TEST 2: MINION **\n\n");

	return 0;
}