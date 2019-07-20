/* -----------------------------------------------------------------------
 * Unit test for AmbassadorEffect()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  
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

//lowsupply = 1 then smithy supply set to 0
void setUpCards(struct gameState *G, struct gameState *G2, int lowsupply){
	//have 1 estate in hand
	if(lowsupply == 1){
		G->supplyCount[smithy] = 0;
	}
	
	//set current player's hand
	G->hand[0][0] = ambassador;
	G->hand[0][1] = smithy;
	G->hand[0][2] = smithy;
	G->hand[0][3] = feast;
	G->hand[0][4] = mine;

	memcpy(G2, G, sizeof(struct gameState));
	
}

//correctOpt = 0 if any incorrect option 
void testAmb(struct gameState *G, struct gameState *G2, int correctOpt, int amt){

	if(correctOpt == 0){
		//Test no change in Ambassador supply
		printf("Ambassador Card Supply: Expected value: %d, Result: %d. ", G->supplyCount[ambassador], G2->supplyCount[ambassador]);
		if(G->supplyCount[ambassador] == G2->supplyCount[ambassador]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Test to see if Ambassador card goes to discard pile
		printf("Ambassador Card to Discard: Expected value: %d, Result: %d. ", G->discardCount[0]+1, G2->discardCount[0]);
		if(G->discardCount[0]+ 1 == G2->discardCount[0]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }


		//Test to see if handcount decreased by 1
		printf("Ambassador Card Out of Hand: Expected value: %d, Result: %d. ", G->handCount[0]-1, G2->handCount[0]);
		if(G->handCount[0]-1 == G2->handCount[0]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Test if other player's discard piles not affected
		printf("Other Player's Discards Not Affected: ");
		for(int i =0; i < G->numPlayers; i++){
			if( i != G->whoseTurn){
				printf("Player %d Expected value: %d, Result: %d. ", i, G->discardCount[i], G2->discardCount[i]);
				if(G->discardCount[i] == G2->discardCount[i]){ printf("SUCCESS\n");}
				else{ printf("FAIL\n"); }
			}
		}


	}
	else{
		//Test change to smithy supply
		printf("Smithy Card Supply: Expected value: %d, Result: %d. ", G->supplyCount[smithy] + amt, G2->supplyCount[smithy]);
		if(G->supplyCount[smithy] + amt == G2->supplyCount[smithy]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Test to see if Ambassador card goes to discard pile
		printf("Ambassador Card to Discard: Expected value: %d, Result: %d. ", G->discardCount[0]+1, G2->discardCount[0]);
		if(G->discardCount[0]+ 1 == G2->discardCount[0]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Test to see if handcount decreased by amt + 1
		printf("Ambassador & Returned Card(s) Out of Hand: Expected value: %d, Result: %d. ", (G->handCount[0]-1)-amt, G2->handCount[0]);
		if((G->handCount[0]-1)-amt == G2->handCount[0]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Test if other player's discard piles not affected
		printf("Other Player's Discards Affected: ");
		for(int i =0; i < G->numPlayers; i++){
			if( i != G->whoseTurn){

				//if no card for next player then don't get a card
				if(G2->supplyCount[smithy] == 0){
					printf("Player %d Expected value: %d, Result: %d. ", i, G->discardCount[i], G2->discardCount[i]);
					if(G->discardCount[i] == G2->discardCount[i]){ printf("SUCCESS\n");}
					else{ printf("FAIL\n"); }
				}
				else{
					printf("Player %d Expected value: %d, Result: %d. ", i, G->discardCount[i]+1, G2->discardCount[i]);
					if(G->discardCount[i]+1 == G2->discardCount[i]){ printf("SUCCESS\n");}
					else{ printf("FAIL\n"); }
				}
				
			}
		}

	}
	

	
}

int main(){

	int i;
    int seed = 1000;
    int numPlayers = 4;
    int k[10] = {adventurer, ambassador, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;
	
	printf ("\n\nTesting AmbassadorEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));

	//choice1 = hand # (being returned to supply) & choice2= # to return to supply (0, 1, 2)

//Test choice 1 wrong (current amb card) & choice 2 wrong (>2 & < 0) 
	printf("\n\nTest choice1 & choice2 incorrect: no change in supply, or other players' discards\n");
	setUpCards(&G, &testG, 0);
	ambassadorEffect(&testG, 0, 3, 0, testG.whoseTurn);

	testAmb(&G, &testG, 0, 3);

//Test choice1 is wrong (current card) & choice2 right (0)
	printf("\n\nTest choice1 incorrect & choice2 right: no change in supply, or other players' discards\n");
	setUpCards(&G, &testG, 0);
	ambassadorEffect(&testG, 0, 0, 0, testG.whoseTurn);

	testAmb(&G, &testG, 0, 0);

//Test choice 1 right (smithy card) & choice 2 wrong (3)
	printf("\n\nTest choice1 right & choice2 incorrect: no change in supply, or other players' discards\n");
	setUpCards(&G, &testG, 0);
	ambassadorEffect(&testG, 1, 3, 0, testG.whoseTurn);

	testAmb(&G, &testG, 0, 3);

//Test choice 1 right (smithy card) & choice 2 right (2)
	printf("\n\nTest choice1 & choice2 correct: change in smithy supply, & other players' discard & enough cards to evenly distribute\n");
	setUpCards(&G, &testG, 0);
	ambassadorEffect(&testG, 1, 2, 0, testG.whoseTurn);

	testAmb(&G, &testG, 1, 2);

//Test choice 1 & 2 right but not enough smithy supply to distribute to all players
	printf("\n\nTest choice1 & choice2 correct: change in smithy supply, or other players' discard & not enough cards to evenly distribute\n");
	setUpCards(&G, &testG, 1);
	ambassadorEffect(&testG, 1, 2, 0, testG.whoseTurn);

	testAmb(&G, &testG, 1, 2);
			

	printf("**END UNIT TEST 3: AMBASSADOR **\n\n");
	return 0;
}