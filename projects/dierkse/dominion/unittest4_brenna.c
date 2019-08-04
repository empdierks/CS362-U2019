/* -----------------------------------------------------------------------
 * Unit test for team member's tributeEffect()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  Compile: gcc -std=c99 -lm unittest4_brenna.c dominion_brenna.c rngs.c -o unittest4bren
 * -----------------------------------------------------------------------
 */

#include "dominion_brenna.h"
#include "dominion_helpers_brenna.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//type 0 = 2 actions, type 1 = 2 treasures, etc
void setUpCards(struct gameState *G, struct gameState *G2, int type){

	for (int i=0; i < G->deckCount[1]; i++){
		//last two cards should be 
		if(i == G->deckCount[1]-2){
			//set top 2 cards of deck to be 2 actions
			if(type == 0){
				G->deck[1][i] = tribute;
				G->deck[1][i+1] = tribute;
				break;
			}
			//set top 2 cards of deck to be 2 treasures
			if(type == 1){
				G->deck[1][i] = copper;
				G->deck[1][i+1] = copper;
				break;
			}
			//set top 2 cards of deck to be 2 victory
			if(type == 2){
				G->deck[1][i] = estate;
				G->deck[1][i+1] = estate;
				break;
			}
			//set top 2 cards of deck to be 1 action + 1 treasure
			if(type == 3){
				G->deck[1][i] = tribute;
				G->deck[1][i+1] = copper;
				break;
			}
			//set top 2 cards of deck to be 1 action + 1 victory
			if(type == 4){
				G->deck[1][i] = tribute;
				G->deck[1][i+1] = estate;
				break;
			}
			//set top 2 cards of deck to be 1 treasure + 1 victory
			if(type == 4){
				G->deck[1][i] = copper;
				G->deck[1][i+1] = estate;
				break;
			}
		}
	}
	G->coins = 0;
	G->numActions = 1;
	G->handCount[0] = 5;
	memcpy(G2, G, sizeof(struct gameState));

}

//0 = action, 1 = treasure, 2 = victory
void checkTributeCard(struct gameState *G, struct gameState *G2, int a, int b){

	//if double cards
	if(a == b){
		//if both action cards
		if(a == 0){

			//Check current Players Action count
			printf("Two Action Cards\n");
			printf("Action Count: Expected value: %d, Result: %d. ", G->numActions+ 2, G2->numActions);
			if(G->numActions+ 2 == G2->numActions){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}
		//if both treasures
		else if(a == 1){
			//Check Current Players Coins
			printf("Two Treasure Cards\n");
			printf("Coin Count: Expected value: %d, Result: %d. ", G->coins + 2, G2->coins);
			if(G->coins + 2 == G2->coins){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}
		//if both victory cards
		else{
			//Check Current Players Hand Count
			printf("Add 2 Cards to Hand: Expected value: %d, Result: %d. ", G->handCount[G->whoseTurn]+ 1, G2->handCount[G2->whoseTurn]);
			if(G->handCount[G->whoseTurn] +1 == G2->handCount[G2->whoseTurn]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n");}
			printf("Discard Tribute Card: Expected value: %d, Result: %d. ", G->discardCount[G->whoseTurn] + 1, G2->discardCount[G2->whoseTurn]);
			if (G->discardCount[G->whoseTurn] + 1 == G2->discardCount[G2->whoseTurn]) { printf("SUCCESS\n"); }
			else { printf("FAIL\n"); }
			
		}
	}
	else{
		//if 1 is action card
		if(a == 0 | b == 0){
			//Check current Players Action count
			printf("One Card Action\n");
			printf("Action Count: Expected value: %d, Result: %d. ", G->numActions+ 2, G2->numActions);
			if(G->numActions+ 2 == G2->numActions){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		// if 1 is treasure card
		if(a == 1 | b == 1){
			//Check Current Players Coins
			printf("One Card Treasure\n");
			printf("Coin Count: Expected value: %d, Result: %d. ", G->coins+2, G2->coins);
			if(G->coins+2 == G2->coins){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		//if 1 is victory card
		if(a==2 | b == 2){
			//Check Current Players Hand Count
			printf("One Card Victory\n");
			printf("Add 1 Card to Hand(-1 Tribute+ 2 cards= 1): Expected value: %d, Result: %d. ", G->handCount[G->whoseTurn] + 1, G2->handCount[G2->whoseTurn]);
			if (G->handCount[G->whoseTurn] + 1 == G2->handCount[G2->whoseTurn]) { printf("SUCCESS\n"); }
			else { printf("FAIL\n"); }
			printf("Discard Tribute Card: Expected value: %d, Result: %d. ", G->discardCount[G->whoseTurn] + 1, G2->discardCount[G2->whoseTurn]);
			if (G->discardCount[G->whoseTurn] + 1 == G2->discardCount[G2->whoseTurn]) { printf("SUCCESS\n"); }
			else { printf("FAIL\n"); }

		}

	}

	//Check Next Player's Discarded Pile Count
	printf("Other Player Discarded Revealed Card(s): Expected value: %d, Result: %d. ", G->discardCount[1]+2, G2->discardCount[1]);
	if(G->discardCount[1]+2 == G2->discardCount[1]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	//Check Next Player's Deck Count
	printf("Other Player Deck Count: Expected value: %d, Result: %d. ", G->deckCount[1]-2, G2->deckCount[1]);
	if(G->deckCount[1]-2 == G2->deckCount[1]){ printf("SUCCESS\n");}
	else{ printf("FAIL\n");}

	
		
}

int main(){
	int i;
    int seed = 1000;
    int numPlayers = 2;
    int k[10] = {adventurer, tribute, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	struct gameState G, testG;
	
	printf ("\n\nTesting TributeEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));


//Test Next Player's deck has 2 cards with all variations
	printf("\n\nNext Player Top of Deck has 2 Actions: NP cards discarded & CP +2 Actions \n");
	setUpCards(&G, &testG, 0);
	tributeEffect(0, &testG);
	checkTributeCard(&G, &testG, 0, 0);


	//2 Treasures
	printf("\n\nNext Player Top of Deck has 2 Treasures: NP cards discarded & CP +2 coins \n");
	setUpCards(&G, &testG, 1);
	tributeEffect(0, &testG);
	checkTributeCard(&G, &testG, 1, 1);

	//2 Victories
	printf("\n\nNext Player Top of Deck has 2 Victories: NP cards discarded & CP +2 cards from own deck \n");
	setUpCards(&G, &testG, 2);
	tributeEffect(0, &testG);
	checkTributeCard(&G, &testG, 2, 2);

	//1 action + 1 Treasure
	printf("\n\nNext Player Top of Deck has 1 action + 1 Treasure: NP cards discarded & CP +2 Actions & +2 coins \n");
	setUpCards(&G, &testG, 3);
	tributeEffect(0, &testG);
	checkTributeCard(&G, &testG, 0, 1);

	//1 action + 1 Victory
	printf("\n\nNext Player Top of Deck has 1 action + 1 Victory: NP cards discarded & CP +2 Actions & +2 cards from own deck \n");
	setUpCards(&G, &testG, 4);
	tributeEffect(0, &testG);
	checkTributeCard(&G, &testG, 0, 2);

	//1 treasure + 1 Victory
	printf("\n\nNext Player Top of Deck has 1 treasure + 1 Victory: NP cards discarded & CP +2 coins & +2 cards from own deck \n");
	setUpCards(&G, &testG, 5);
	tributeEffect(0, &testG);
	checkTributeCard(&G, &testG, 1, 2);

	printf("**END UNIT TEST 4: TRIBUTE **\n\n");
	return 0;
}