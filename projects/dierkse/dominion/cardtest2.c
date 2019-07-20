/* -----------------------------------------------------------------------
 * Unit test for shuffle()
 * 
 *
 * 
 *  
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion.c"
#include "dominion_helpers.h"
#include "rngs.h"
#include "rngs.c"
#include <stdlib.h>
#include <stdio.h>


int main(){

	int seed = 1000;
    int numPlayers = 4;
    int currentPlayer = 0;
    int k[10] = {adventurer, minion, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;
	int successes;

	printf ("TESTING shuffle()\n");

	memset(&G, 23, sizeof(struct gameState)); //clear the game state
    initializeGame(numPlayers, k, seed, &G); //initialize new game

	memcpy(%testG, &G, sizeof(struct gameState));

	printf("Starting Deck: ")
	for(int i = 0; i < G.deckCount; i++){
		printf("%d | ", G.deck[0][i]);
	}

	printf("\n");

	int returnValue = shuffle(0, &testG);

	
	if(returnValue == -1){
		printf("Shuffle Failed\n");
		return 0;
	}

	//if both decks do not match then a success
	printf("Shuffled Deck: ")

	for(int i = 0; i < testG.deckCount; i++){
		printf("%d | ", testG.deck[0][i]);
	}
	printf("\n");

	printf("Expected: Decks are Not the Same, Result: ");
	if(memcmp(&G.deck[0], &testG.deck[0], sizeof(int)*MAX_DECK) != 0){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	printf("**END CARD TEST 2: shuffle() **\n\n");

}