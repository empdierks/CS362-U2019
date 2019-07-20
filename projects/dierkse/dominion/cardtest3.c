/* -----------------------------------------------------------------------
 * Unit test for endTurn()
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


int main(){

    int seed = 1000;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int currentPlayer = 0;
    int NumDiscard;

	printf ("TESTING endTurn()\n");

    	initializeGame(numPlayers, k, seed, &G); //initialize new game

    for (int turn = 0; turn <= 5; turn++){

    	NumDiscard = G.discardCount[currentPlayer];

    	printf("Player Before endTurn(): expected %d, Result: %d. ", currentPlayer,G.whoseTurn );

    	endTurn(&G);

    	//Previous Player discard count = ++5
    	printf("Previous Player %d discard count: expected value: %d, Result: %d. ", currentPlayer, NumDiscard+5, G.discardCount[currentPlayer]);
    	if(G.discardCount[currentPlayer] == NumDiscard + 5){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Previous Player hand size = 0
		printf("Previous Player %d hand size: expected value: 0, Result: %d. ", currentPlayer, G.handCount[currentPlayer]);
		if(G.handCount[currentPlayer] == 0){printf("SUCCESS\n");}
		else{ printf("FAIL\n");}

		if(currentPlayer == numPlayers-1){
			currentPlayer = 0;
		}
		else{
			currentPlayer++;
		}
		
		printf("Current Player After endTurn(): expected: %d, Result: %d. ", currentPlayer, G.whoseTurn);
		if(G.whoseTurn == currentPlayer){printf("SUCCESS\n");}
		else{ printf("FAIL\n");}

		//Current Player hand size = 5
		printf("Current Player %d hand size: expected value: 5, Result: %d. ", G.whoseTurn, G.handCount[G.whoseTurn]);
		if(G.handCount[G.whoseTurn] == 5){printf("SUCCESS\n");}
		else{ printf("FAIL\n");}

	}

	printf("**END CARD TEST 3: endTurn() **\n\n");

	return 0;
}
