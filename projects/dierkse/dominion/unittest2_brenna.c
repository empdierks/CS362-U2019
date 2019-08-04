/* -----------------------------------------------------------------------
 * Unit test for Team Member's MinionEffect()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  Compile: gcc -std=c99 -lm unittest2_brenna.c dominion_brenna.c rngs.c -o unittest2bren
 * -----------------------------------------------------------------------
 */

#include "dominion_brenna.h"
#include "dominion_helpers_brenna.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


int main(){

	int i;
    int seed = 1000;
    int numPlayers = 4;
    int k[10] = {adventurer, minion, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;
	
	printf ("\nTesting minionEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	//Have other players have cards in hands
	for (int j = 1; j < numPlayers; j++) {
		if (j == 2) {
			for (int k = 0; k < 6; k++) {
				gainCard(minion, &G, 2, j);
			}
		}
		else {
			for (int k = 0; k < 3; k++) {
				gainCard(minion, &G, 2, j);
			}
		}
	}

	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Num Actions: %d, Num Coins: %d, Hand: %d, Discard: %d\n", G.numActions, G.coins, G.handCount[G.whoseTurn], G.discardCount[G.whoseTurn]);
	            
//Test choice1 = 1 & choice2 = 0, adds action and adds 2 coins
	printf("\n\nTest choice1= 1, Adds Action, +2 coins, Discards Minion Card\n");
	minionEffect(0, 2, &testG);

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
	printf("\n\nTest choice2=1, discard cP hand, draw 4 cards from deck, other player with 5 cards discards and redraws 4\n");
	minionEffect(0, 1, &testG);

	//Test discard pile == old handcount
	printf("DISCARD Curr Player Hand: Expected value: %d, Result: %d. ", G.handCount[G.whoseTurn], testG.discardCount[testG.whoseTurn]);
	if(G.handCount[G.whoseTurn] == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Test hand pile == 4
	printf("Redraw Hand to 4: Expected value: 4, Result: %d. ", testG.handCount[testG.whoseTurn]);
	if(testG.handCount[testG.whoseTurn] == 4){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	//Other players discard pile == 5
	printf("DISCARD Other Player's Hand: Expected value: %d, Result: %d. ", G.handCount[2], testG.discardCount[2]);
	if(G.handCount[2] == testG.discardCount[2]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Other players hand == 4
	printf("Other Player Redraws Hand to 4: Expected value: 4, Result: %d. ", testG.handCount[2]);
	if(testG.handCount[2] == 4){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }


	G.handCount[1] = 3;  //change the other player's handcount to just 4

	memcpy(&testG, &G, sizeof(struct gameState));  //refresh game
	printf("Turn: %d, Hand: %d, Discard: %d\n", testG.whoseTurn, testG.handCount[G.whoseTurn], testG.discardCount[G.whoseTurn]);

//Test choice1-0 and choice 2=1, hand discarded & draws 4 cards from deck, other player (has 3 cards) discard and hand stay same
	printf("\n\nTest choice2=1, other player has 3 cards so doesn't discard hand and redraw 4");
	minionEffect(0, 1, &testG);

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