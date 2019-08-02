/* -----------------------------------------------------------------------
 * Unit test for BaronEffect()
 * Emily Dierks
 * CS362, Summer 2019
 *  
 * -----------------------------------------------------------------------
 */

#include "dominion_brenna.h"
#include "dominion_helpers_brenna.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "rngs.h"
#include <math.h>

//e = 1 if have estate, s = 1 then supply
void setUpCards(struct gameState *G, struct gameState *G2, int e){
	int i;	
	//have 1 estate in hand
	if(e == 1){
		for(i =0; i < 5; i++){
			if(i == 4){
				G->hand[G->whoseTurn][i] = estate;
			}
			G->hand[G->whoseTurn][i] = baron;
		}
		memcpy(G2, G, sizeof(struct gameState));
	}
	else{
		for(i =0; i < 5; i++){
			G->hand[G->whoseTurn][i] = baron;
		}
		memcpy(G2, G, sizeof(struct gameState));
	}
}


int main (){
	int i;
   	int seed = 1000;
    	int numPlayers = 2;
    	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;

	
	printf ("Testing baronEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));

	printf("Num Coins: %d, DiscardCount: %d, HandCount: %d\n", G.coins, G.discardCount[G.whoseTurn], G.handCount[G.whoseTurn]);
            
//Test choice1 = 1, player has estate --> rec 4 coins & thier estate card discarded
	printf("Test choice1=1 and player has estate card\n");
	setUpCards(&G, &testG, 1);
	baronEffect(1, 1, &testG);

	//check if number of buys increased
	printf("BUYS: Expected value: %d, Result: %d. ", G.numBuys + 1, testG.numBuys);
	if(G.numBuys+1 == testG.numBuys){ printf("SUCCESS\n");}
	else{ printf("FAIL\n"); }

	//Check if discarded estate card & Baron card
	printf("DISCARD BARON & ESTATE FROM HAND: Expected value: %d, Result: %d. ", G.handCount[G.whoseTurn] - 2, testG.handCount[testG.whoseTurn]);
	if(G.handCount[G.whoseTurn] -2 == testG.handCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}
	printf("BARON & ESTATE DISCARD PILE: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+2, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+2 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Check if received 4 coins
	printf("COINS: Expected value: %d, Result: %d. ", G.coins+4, testG.coins);
	if(G.coins+4 == testG.coins){ printf("SUCCESS\n"); }
	else{ printf("FAIL\n"); }


//Test choice1 = 1 but don't have estate, gain estate
	printf("\n\nTest choice1=1 and player does not have estate card\n");
	setUpCards(&G, &testG, 0);
	baronEffect(1, 1, &testG);

	//Check if receive estate card & Baron card & Estate card gained were discarded
	printf("ESTATE CARD SUPPLY: Expected value: %d, Result: %d. ", G.supplyCount[estate] - 1, testG.supplyCount[estate]);
	if(G.supplyCount[estate] - 1 == testG.supplyCount[estate]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}
	printf("ESTATE & BARON CARD IN DISCARD: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+2, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+2 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Check if coins didn't increase
	printf("COINS: Expected value: %d, Result: %d. ", G.coins, testG.coins);
	if(G.coins == testG.coins){ printf("SUCCESS\n"); }
	else{ printf("FAIL\n"); }

//Test choice1 = 0, player has estate card shouldn't gain estate
	printf("\n\nTest choice1=0 and player has estate card\n");
	setUpCards(&G, &testG, 1);
	baronEffect(1, 0, &testG);

	//Check if only discard Baron & don't get estate card into discard
	printf("ESTATE CARD SUPPLY: Expected value: %d, Result: %d. ", G.supplyCount[estate], testG.supplyCount[estate]);
	if(G.supplyCount[estate] == testG.supplyCount[estate]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}
	printf("ONLY BARON CARD IN DISCARD: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+1, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+1 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}


//Test choice1=0, player does not have estate card should gain estate card and decrement supply
	printf("\n\nTest choice1=0, player doesn't have estate card\n");
	setUpCards(&G, &testG, 0);
	baronEffect(1, 0, &testG);

	//Check if only discard Baron & don't get estate card into discard
	printf("ESTATE CARD SUPPLY: Expected value: %d, Result: %d. ", G.supplyCount[estate]-1, testG.supplyCount[estate]);
	if(G.supplyCount[estate]-1 == testG.supplyCount[estate]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}
	printf("BARON & ESTATE CARD IN DISCARD: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+2, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+2 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}


//Test choice1=0, player doesnt have estate but supply of estate is 0 so don't gain estate card
	printf("\n\nTest choice1=0, player doesn't have estate card but supply is 0\n");
	setUpCards(&G, &testG, 0);

	G.supplyCount[estate] = 0; //set up for estate supply empty (game not over)
	memcpy(&testG, &G, sizeof(struct gameState));

	baronEffect(1, 0, &testG);

	//Check if only discard Baron & don't get estate card into discard
	printf("ESTATE CARD SUPPLY: Expected value: %d, Result: %d. ", G.supplyCount[estate], testG.supplyCount[estate]);
	if(G.supplyCount[estate] == testG.supplyCount[estate]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}
	printf("ONLY BARON CARD IN DISCARD: Expected value: %d, Result: %d. ", G.discardCount[G.whoseTurn]+1, testG.discardCount[testG.whoseTurn]);
	if(G.discardCount[G.whoseTurn]+1 == testG.discardCount[testG.whoseTurn]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}


//Test choice1=0, player doesn't have estate and causes game over (via 3 pile ending)
	printf("\n\nTest choice1=0, player doesn't have estate card and causes game over\n");
	setUpCards(&G, &testG, 0);

	//set up for supply empty (game over)
	G.supplyCount[estate] = 1;
	G.supplyCount[adventurer] = 0;
	G.supplyCount[smithy] = 0;
	memcpy(&testG, &G, sizeof(struct gameState));

	baronEffect(1, 0, &testG);

	//Check if causes game over
	printf("GAME OVER?: Expected value: %d, Result: %d. ", 1, isGameOver(&testG));
	if(isGameOver(&testG) == 1){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	printf("**END UNIT TEST 1: BARON **\n");
	return 0;
}
