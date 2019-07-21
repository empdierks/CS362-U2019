/* -----------------------------------------------------------------------
 * Unit test for drawCard()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(){


	int seed = 1000;
    int numPlayers = 2;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G, testG;

    printf ("TESTING drawCard()\n");

    initializeGame(numPlayers, k, seed, &G); //initialize new game

    memcpy(&testG, &G, sizeof(struct gameState));

    printf("\n\nTest 1: Deck Not Empty so HandCount and DeckCount Change\n");

    drawCard(0, &testG);

    printf("HandCount: Expected value: %d, Result: %d. ", G.handCount[0] + 1, testG.handCount[0]);
	if(G.handCount[0] + 1 == testG.handCount[0]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	printf("DeckCount: Expected value: %d, Result: %d. ", G.deckCount[0] - 1, testG.deckCount[0]);
	if(G.deckCount[0] - 1 == testG.deckCount[0]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	printf("\n\nTest 2: Deck is Empty so HandCount, DeckCount & DiscardCount Change\n");

	 //discard all the cards in the player 0's deck
	for (int i = 0; i < testG.deckCount[0]; i++){
	 	discardCard(G.deck[0][i], 0, &G, 0);
	}

	memcpy(&testG, &G, sizeof(struct gameState));

	drawCard(0, &testG);

	printf("DiscardCount used to be %d: Now Expected value: 0, Result: %d. ", G.discardCount[0], testG.discardCount[0]);
	if(testG.discardCount[0] == 0){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	printf("HandCount: Expected value: %d, Result: %d. ", G.handCount[0] + 1, testG.handCount[0]);
	if(G.handCount[0] + 1 == testG.handCount[0]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	printf("DeckCount: Expected value: %d, Result: %d. ", G.discardCount[0] - 1, testG.deckCount[0]);
	if(G.discardCount[0] - 1 == testG.deckCount[0]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	printf("**END CARD TEST 5: drawCard() **\n\n");

	return 0;
}
