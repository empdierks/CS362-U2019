/* -----------------------------------------------------------------------
 * Unit test for mineEffect()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 * Compile:  
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


void setUpCards(struct gameState *G, struct gameState *G2){

	//Include in hand treasure, action, and victory cards
	G->hand[G->whoseTurn][0] = copper;
	G->hand[G->whoseTurn][1] = smithy;
	G->hand[G->whoseTurn][2] = estate;
	G->hand[G->whoseTurn][3] = mine;

	memcpy(G2, G, sizeof(struct gameState));

}

//correctChoices = 0 (false) if not correct combo & correctChoices = 1 if correct
//treasureChoice(choice2): 0 = copper, 1 = silver, 2= gold, 3 = not treasure
void checkMineCard(struct gameState *G, struct gameState *G2, int correctChoices, int treasureChoice){

	//incorrect choices selected
	if(correctChoices == 0){
		//Selected to Receive Copper
		if(treasureChoice == 0){
			//Test no change in copper supply
			printf("Copper Card Supply Same: Expected value: %d, Result: %d. ", G->supplyCount[copper], G2->supplyCount[copper]);
			if(G->supplyCount[copper] == G2->supplyCount[copper]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}
		//Selected to Receive Silver
		else if(treasureChoice == 1){
			printf("Silver Card Supply Same: Expected value: %d, Result: %d. ", G->supplyCount[silver], G2->supplyCount[silver]);
			if(G->supplyCount[silver] == G2->supplyCount[silver]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		//Selected to Receive Gold
		else if(treasureChoice == 2){
			printf("Gold Card Supply Same: Expected value: %d, Result: %d. ", G->supplyCount[gold], G2->supplyCount[gold]);
			if(G->supplyCount[gold] == G2->supplyCount[gold]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		//Selected to Receive a non-treasure card
		else{
			printf("Copper Card Supply Same: Expected value: %d, Result: %d. ", G->supplyCount[copper], G2->supplyCount[copper]);
			if(G->supplyCount[copper] == G2->supplyCount[copper]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
			printf("Silver Card Supply Same: Expected value: %d, Result: %d. ", G->supplyCount[silver], G2->supplyCount[silver]);
			if(G->supplyCount[silver] == G2->supplyCount[silver]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
			printf("Gold Card Supply Same: Expected value: %d, Result: %d. ", G->supplyCount[gold], G2->supplyCount[gold]);
			if(G->supplyCount[gold] == G2->supplyCount[gold]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}

		//Trash count the same
		printf("Trash Count the Same: Expected value: %d, Result: %d. ", G->playedCardCount, G2->playedCardCount);
		if(G->playedCardCount == G2->playedCardCount){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Hand count same for not using Mine correctly
		printf("Hand Count the Same (didn't use Mine): Expected value: %d, Result: %d. ", G->handCount[G->whoseTurn], G2->handCount[G->whoseTurn]);
		if(G->handCount[G->whoseTurn] == G2->handCount[G->whoseTurn]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Discard count same for not using Mine correctly
		printf("Discard Count the Same: Expected value: %d, Result: %d. ", G->discardCount[G->whoseTurn], G2->discardCount[G->whoseTurn]);
		if(G->discardCount[G->whoseTurn] == G2->discardCount[G->whoseTurn]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

	}
	//correct choices selected
	else{
		//Treasure supply decremented by 1 (choice 2 new treasure)
		//Selected to Receive Copper
		if(treasureChoice == 0){
			//Test no change in copper supply
			printf("Copper Card Supply -1: Expected value: %d, Result: %d. ", G->supplyCount[copper]-1, G2->supplyCount[copper]);
			if(G->supplyCount[copper]-1 == G2->supplyCount[copper]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}
		//Selected to Receive Silver
		else if(treasureChoice == 1){
			printf("Silver Card Supply -1: Expected value: %d, Result: %d. ", G->supplyCount[silver]-1, G2->supplyCount[silver]);
			if(G->supplyCount[silver]-1 == G2->supplyCount[silver]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		//Selected to Receive Gold
		else{
			printf("Gold Card Supply -1: Expected value: %d, Result: %d. ", G->supplyCount[gold], G2->supplyCount[gold]);
			if(G->supplyCount[gold]-1 == G2->supplyCount[gold]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		//Trash increased by 1 (choice 1 old treasure)
		printf("Trash Count +1: Expected value: %d, Result: %d. ", G->playedCardCount+1, G2->playedCardCount);
		if(G->playedCardCount+1 == G2->playedCardCount){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Hand decremented by 2 (mine + old treasure card)
		printf("Hand Count -2 (mine + old treasure): Expected value: %d, Result: %d. ", G->handCount[G->whoseTurn]-2, G2->handCount[G->whoseTurn]);
		if(G->handCount[G->whoseTurn]-2 == G2->handCount[G->whoseTurn]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		//Discard pile increased by 2 (mine + new treasure card)
		printf("Discard Count +2 (mine + new treasure): Expected value: %d, Result: %d. ", G->discardCount[G->whoseTurn]+2, G2->discardCount[G->whoseTurn]);
		if(G->discardCount[G->whoseTurn]+2 == G2->discardCount[G->whoseTurn]){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }
	}
		
		
}

int main(){
	int i;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;

	
	printf ("\nTesting mineEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));
	            

//Test 1: choice 1 not treasure & choice 2 not treasure
	printf("\nTest 1: choice 1 & not treasure cards-> no change in supply, hand, discard and Trash pile\n");
	setUpCards(&G, &testG);
	mineEffect(&testG, 1, adventurer, 3, testG.whoseTurn);

	checkMineCard(&G, &testG, 0, 3);

//Test 2: choice 1 copper & choice 2 gold (more than 3 coins difference)
	printf("\nTest 2: choice1 copper & choice2 gold (> 3 coins diff)-> no change in supply, hand, discard and Trash pile\n");
	setUpCards(&G, &testG);
	mineEffect(&testG, 0, gold, 3, testG.whoseTurn);

	checkMineCard(&G, &testG, 0, 3);

//Test 3: choice 1 not treasure & choice 2 copper
	printf("\nTest 3: choice1 not treasure & choice2 copper-> no change in supply, hand, discard and Trash pile\n");
	setUpCards(&G, &testG);
	mineEffect(&testG, 2, copper, 3, testG.whoseTurn);

	checkMineCard(&G, &testG, 0, 3);

//Test 4: choice 1 copper & choice 2 silver
	printf("\nTest 4: choice1 copper & choice2 silver-> change in supply, hand, discard and Trash pile\n");
	setUpCards(&G, &testG);
	mineEffect(&testG, 0, silver, 3, testG.whoseTurn);

	checkMineCard(&G, &testG, 1, 1);

	printf("**END UNIT TEST 5: MINE **\n\n");

	return 0;
}
