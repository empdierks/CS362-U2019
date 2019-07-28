/* -----------------------------------------------------------------------
 * Random Test of BaronEffect()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdlib.h>
#include <stdio.h>

int testBaronEffect(int choice1, int handPos, int currentPlayer, struct gameState *post){

	struct gameState pre;
	int r, i, j;
	bool hasEstate = 0;
	int emptyPiles = 0;

	memcpy (&pre, post, sizeof(struct gameState));

	//if post has estate card
	for(i=0; i < post->handCount[currentPlayer]; i++){
		if(post->hand[currentPlayer][i] == estate){
			hasEstate == 1;
		}
	}

	//check if 3-pile game over can occur
	//for(j =0; j < 25; j++){
		//if(post->supplyCount[j] == 0){
			//emptyPiles++;
		//}
	//}

	//need to changebaronEffect to return 1 if wrong
	r = baronEffect(post, choice1, handPos, currentPlayer);

	if(r == 0){
		//if choice 1, discard estate for +4 coins
		if(choice1 == 1){

			//if has estate -->numBuys+1, discardCount+2(estate + baron), handCount-2 (estate+baron), coins+4
			if(hasEstate == 1){
				pre->numBuys[currentPlayer]++;
				pre->discardCount[currentPlayer]+2;
				pre->handCount[currentPlayer]-2;
				pre->coins + 4;
			}
			//if don't have estate--> numBuys+1, supplyCount[estate]-1, discardCount+2 (estate+baron), handCount-1 (baron), same coins
			else{
				pre->numBuys[currentPlayer]++;
				pre->supplyCount[estate]-1;
				pre->discardCount[currentPlayer]+2;
				pre->handCount[currentPlayer]-1;

			}
		
		}
		//else if choice1 = 0, gain an estate
		//Two instances of nothing changes = if have estate already & if don't have estate but estate supply == 0
		else{
			//if don't have estate & supply level of estate != 0
			if(hasEstate == 0 && post->supplyCount[estate] != 0){
				pre->numBuys[currentPlayer]++;
				pre->supplyCount[estate]-1;
				pre->discardCount[currentPlayer]+2;
				pre->handCount[currentPlayer]-1;
			}		
		}

		if(memcmp(&pre, post, sizeof(struct gameState))==0){ return 1;}
		else{ return 0;}
	}
	else{
		return 0;
	}
	
}


int main(){
	int i, n, choice1, handPos, currP, passedCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("Testing baronEffect.\n");

	printf("RANDOM TESTING.\n");

	SelectStream(2);
	PutSeed(3);

	for (n=0; n <2000; n++){
		//fill the game with random numbers
		for(i=0; i <sizeof(struct gameState); i++){
			((char*)&G)[i]=floor(Random()*256);
		}
		//preconditions

		//Number of Players 2-4
		G.numPlayers = floor(Random()*4);
		//currentPlayer: 0-p
		currP = floor(Random()*G.numPlayers);

		G.deckCount[currP] = floor(Random()*MAX_DECK);
		G.discardCount[currP] = floor(Random()*MAX_DECK);
		G.handCount[currP] = floor(Random()*MAX_HAND);

		//size of supply decks up to 10 so can possibly have end game result
		for(j =0; j < 25; j++){
			G.supplyCount[j] = floor(Random()*10);
		}
		//choice 1: 0 or 1
		choice1 = floor(Random()*2);
		//handPos: 0-4
		handPos = floor(Random()*G.handCount[currP]);
	
		passedCount += testBaronEffect(choice1, handPos, currP, &G);

	}
	printf("Passed Count = %d out of 2,000.", passedCount );
	printf("TESTS FINISHED!\n");

	return 0;
}
