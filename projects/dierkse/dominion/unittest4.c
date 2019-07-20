/* -----------------------------------------------------------------------
 * Unit test for tributeEffect()
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
			printf("Action Count: Expected value: %d, Result: %d. ", G->numActions + 2, G2->numActions);
			if(G->numActions + 2 == G2->numActions){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}
		//if both treasures
		else if(a == 1){
			//Check Current Players Coins
			printf("Two Treasure Cards\n");
			printf("Coin Count: Expected value: %d, Result: %d. ", G->coins + 2, G2->numActions);
			if(G->coins + 2 == G2->numActions){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }

		}
		//if both victory cards
		else{
			//Check Current Players Hand Count
			printf("Discard Tribute & Add 2 Cards to Hand: Expected value: %d, Result: %d. ", G->handCount[G->whoseTurn]+ 1, G2->handCount[G2->whoseTurn]);
			if(G->handCount[G->whoseTurn] +1 == G2->handCount[G2->whoseTurn]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n");}
			
		}
	}
	else{
		//if 1 is action card
		if(a == 0 | b == 0){
			//Check current Players Action count
			printf("One Card Action\n");
			printf("Action Count: Expected value: %d, Result: %d. ", G->numActions + 2, G2->numActions);
			if(G->numActions + 2 == G2->numActions){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		// if 1 is treasure card
		if(a == 1 | b == 1){
			//Check Current Players Coins
			printf("One Card Treasure\n");
			printf("Coin Count: Expected value: %d, Result: %d. ", G->coins + 2, G2->numActions);
			if(G->coins + 2 == G->numActions){ printf("SUCCESS\n");}
			else{ printf("FAIL\n"); }
		}
		//if 1 is victory card
		if(a==2 | b == 2){
			//Check Current Players Hand Count
			printf("One Card Victory\n");
			printf("Discard Tribute & Add 2 Cards to Hand: Expected value: %d, Result: %d. ", G->handCount[G->whoseTurn]+ 1, G2->handCount[G2->whoseTurn]);
			if(G->handCount[G->whoseTurn] +1 == G2->handCount[G2->whoseTurn]){ printf("SUCCESS\n");}
			else{ printf("FAIL\n");}

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
	int tributeRevealedCards[2] = {-1, -1};
	
	printf ("\n\nTesting AmbassadorEffect().\n");
	initializeGame(numPlayers, k, seed, &G);  //initialize new game
	memcpy(&testG, &G, sizeof(struct gameState));

	//next player's deck has 0 cards and 0 cards in discard
		//error message (card not used and nothing happens to hand and discards)
	//next player's deck has 1 card and 0 cards in discard
		// get tribute card
	//next player's deck has 0 cards and 1 card in discard
	//next player's deck has 0 cards and 2 cards in discard


//Test Next Player's deck has 2 cards with all variations
	printf("\n\nNext Player Top of Deck has 2 Actions: NP cards discarded & CP +2 Actions \n");
	setUpCards(&G, &testG, 0);
	tributeEffect(&testG, 0, 0, 1, tributeRevealedCards);
	checkTributeCard(&G, &testG, 0, 0);


	//2 Treasures
	printf("\n\nNext Player Top of Deck has 2 Treasures: NP cards discarded & CP +2 coins \n");
	setUpCards(&G, &testG, 1);
	tributeEffect(&testG, 0, 0, 1, tributeRevealedCards);
	checkTributeCard(&G, &testG, 1, 1);

	//2 Victories
	printf("\n\nNext Player Top of Deck has 2 Victories: NP cards discarded & CP +2 cards from own deck \n");
	setUpCards(&G, &testG, 2);
	tributeEffect(&testG, 0, 0, 1, tributeRevealedCards);
	checkTributeCard(&G, &testG, 2, 2);

	//1 action + 1 Treasure
	printf("\n\nNext Player Top of Deck has 1 action + 1 Treasure: NP cards discarded & CP +2 Actions & +2 coins \n");
	setUpCards(&G, &testG, 3);
	tributeEffect(&testG, 0, 0, 1, tributeRevealedCards);
	checkTributeCard(&G, &testG, 0, 1);

	//1 action + 1 Victory
	printf("\n\nNext Player Top of Deck has 1 action + 1 Victory: NP cards discarded & CP +2 Actions & +2 cards from own deck \n");
	setUpCards(&G, &testG, 4);
	tributeEffect(&testG, 0, 0, 1, tributeRevealedCards);
	checkTributeCard(&G, &testG, 0, 2);

	//1 treasure + 1 Victory
	printf("\n\nNext Player Top of Deck has 1 treasure + 1 Victory: NP cards discarded & CP +2 coins & +2 cards from own deck \n");
	setUpCards(&G, &testG, 5);
	tributeEffect(&testG, 0, 0, 1, tributeRevealedCards);
	checkTributeCard(&G, &testG, 1, 2);

	printf("**END UNIT TEST 4: TRIBUTE **\n\n");
	return 0;
}
