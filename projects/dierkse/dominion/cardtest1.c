/* -----------------------------------------------------------------------
 * Unit test for initializeGame()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>


// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main(){
	int i, returnValue, success;
    int seed = 1000;
    int numPlayers = 4;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;

	printf ("TESTING initializeGame()\n");

    for (int p = 2; p <= numPlayers; p++)
    {

    #if (NOISY_TEST == 1)
    	printf("%d player Dominion game with non-duplicating kingdom cards.\n", p);
	#endif
    	memset(&G, 23, sizeof(struct gameState)); //clear the game state
    	returnValue = initializeGame(p, k, seed, &G); //initialize new game

    	if(returnValue == -1){
    		printf("Error: InitializeGame() didn't process");
    		break;
    			
    	}

    	if(p == 2){
    		printf("G.supplyCount[curse] = %d, expected = 10. ", G.supplyCount[curse]);
    		if(G.supplyCount[curse] == 10){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[estate] = %d, expected = 8. ", G.supplyCount[estate]);
    		if(G.supplyCount[estate] == 8){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[duchy] = %d, expected = 8. ", G.supplyCount[duchy]);
    		if(G.supplyCount[duchy] == 8){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[province] = %d, expected = 8. ", G.supplyCount[province]);
    		if(G.supplyCount[province] == 8){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    	}
    	else if(p == 3){
    		printf("G.supplyCount[curse] = %d, expected = 20. ", G.supplyCount[curse]);
    		if(G.supplyCount[curse] == 20){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[estate] = %d, expected = 12. ", G.supplyCount[estate]);
    		if(G.supplyCount[estate] == 12){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[duchy] = %d, expected = 12. ", G.supplyCount[duchy]);
    		if(G.supplyCount[duchy] == 12){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[province] = %d, expected = 12. ", G.supplyCount[province]);
    		if(G.supplyCount[province] == 12){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    	}
    	else{
    		printf("G.supplyCount[curse] = %d, expected = 30. ", G.supplyCount[curse]);
    		if(G.supplyCount[curse] == 30){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[estate] = %d, expected = 12. ", G.supplyCount[estate]);
    		if(G.supplyCount[estate] == 12){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[duchy] = %d, expected = 12. ", G.supplyCount[duchy]);
    		if(G.supplyCount[duchy] == 12){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    		printf("G.supplyCount[province] = %d, expected = 12. ", G.supplyCount[province]);
    		if(G.supplyCount[province] == 12){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

    	}

    	printf("G.supplyCount[copper] = %d, expected = %d. ", G.supplyCount[copper], 60-(7*p));
    	if(G.supplyCount[copper] == 60-(7*p)){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }
    	printf("G.supplyCount[silver] = %d, expected = 40\n", G.supplyCount[silver]);
    	if(G.supplyCount[silver] == 40){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }
    	printf("G.supplyCount[gold] = %d, expected = 30\n", G.supplyCount[gold]);
    	if(G.supplyCount[gold] == 30){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

    	//Show Kingdom cards
    	for(int a=0; a <10; a++){ printf("\nKingdom Card %d: %i\n", a, k[a]);}

    	//Check right supply levels for Kingdom Cards
    	for(int j = 0; j < 10; j++){
    		//if Victory Kingdom card
    		if(k[j] == great_hall || k[j] == gardens){
    			if(p == 2){
    				printf("G.supplyCount[%d] = %d, expected = 8. ", k[j], G.supplyCount[k[j]]);
    				if(G.supplyCount[k[j]] == 8){ printf("SUCCESS\n");}
					else{ printf("FAIL\n"); }
    			}
    			else{
    				printf("G.supplyCount[%d] = %d, expected = 12. ", k[j], G.supplyCount[k[j]]);
    				if(G.supplyCount[k[j]] == 12){ printf("SUCCESS\n");}
					else{ printf("FAIL\n"); }
    			}
    		}

    		else{ 
    			printf("G.supplyCount[%d] = %d, expected = 10. ", k[j], G.supplyCount[k[j]]);
    			if(G.supplyCount[k[j]] == 10){ printf("SUCCESS\n");}
				else{ printf("FAIL\n"); }
    		}
    	}

    	for(int i=0; i < p; i++){
    		if(i == 0){
    			printf("\nPlayer 0: Hand Count = %d, expected = 5. ", G.handCount[i]);
    			if(G.handCount[i] == 5){ printf("SUCCESS\n");}
				else{ printf("FAIL\n"); }
				printf("Player 1: Total Cards = %d, expected = 13. ", G.handCount[i]+G.deckCount[i]);
				if(G.handCount[i]+G.deckCount[i] == 13){ printf("SUCCESS\n");}
				else{ printf("FAIL\n"); }
    		}
    		else{
    			printf("\nPlayer %d: Hand Count = %d, expected = 0. ", i, G.handCount[i]);
    			if(G.handCount[i] == 0){ printf("SUCCESS\n");}
				else{ printf("FAIL\n"); }
				printf("Player %d: Total Cards = %d, expected = 13. ", i, G.deckCount[i]);
				if(G.deckCount[i] == 13){ printf("SUCCESS\n");}
				else{ printf("FAIL\n"); }
    		}
    		printf("Player %d: Discard Count = %d, expected = 0. ", i, G.discardCount[i]);
    		if(G.discardCount[i] == 0){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
    	}
    		
    	printf("\nNumActions = %d, expected = 1. ", G.numActions);
    	if(G.numActions == 1){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		printf("Num Buys = %d, expected = 1. ", G.numBuys);
    	if(G.numBuys == 1){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		printf("Whose Turn = %d, expected = 0. ", G.whoseTurn);
    	if(G.whoseTurn == 0){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }
    		
	}		//Instance of kingdom cards having duplicates
			
	return 0;
}
