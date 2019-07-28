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
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

int testBaronEffect(int choice1, int handPos, int currentPlayer, struct gameState *post){

	struct gameState pre;
	int r, i;
	bool hasEstate = 0;
	int estateHandPos =0;
	int emptyPiles = 0;

	memcpy (&pre, post, sizeof(struct gameState));

	//if post has estate card
	for(i=0; i < post->handCount[currentPlayer]; i++){
		if(post->hand[currentPlayer][i] == estate){
			hasEstate == 1;
			estateHandPos = i;
		}
	}

	//check if 
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
				pre.numBuys++;
				pre.discardCount[currentPlayer]+2;
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]-2]= pre.hand[currentPlayer][handPos];
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]-1] = pre.hand[currentPlayer][estateHandPos];
				pre.hand[currentPlayer][handPos] = -1; //discard baron card
				pre.hand[currentPlayer][estateHandPos] = -1; //discard estate card 
				pre.handCount[currentPlayer]-2;
				pre.coins + 4;
			}
			//if don't have estate--> numBuys+1, supplyCount[estate]-1, discardCount+2 (estate+baron), handCount-1 (baron), same coins
			else{
				pre.numBuys++;
				pre.supplyCount[estate]-1;
				pre.discardCount[currentPlayer]+2;
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]-2] = pre.hand[currentPlayer][handPos];
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]-1] = estate;
				pre.hand[currentPlayer][handPos] = -1; //baron card discarded
				pre.handCount[currentPlayer]-1;

			}
		
		}
		//else if choice1 = 0, gain an estate
		//Two instances of nothing changes = if have estate already & if don't have estate but estate supply == 0
		else{
			//if don't have estate & supply level of estate != 0
			if(hasEstate == 0 && post->supplyCount[estate] != 0){
				pre.numBuys++;
				pre.supplyCount[estate]-1;
				pre.discardCount[currentPlayer]+2;
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]-2] = pre.hand[currentPlayer][handPos];
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]-1] = estate;
				pre.hand[currentPlayer][handPos] = -1; //baron card discarded
				pre.handCount[currentPlayer]-1;
			}		
		}

		if(memcmp(&pre, post, sizeof(struct gameState))==0){printf("Success\n"); return 0;}
		else{ return 0;}
	}
	else{
		return 0;
	}
	
}


int main(){
	int i, n, j, choice1, handPos, currP;
	int passedCount = 0;
	clock_t start, end;
	double cpu_time_used;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("Testing baronEffect.\n");

	printf("RANDOM TESTING.\n");

	SelectStream(2);
	PutSeed(3);

	start = clock();
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
	
		if(n%10 == 0){
			G.supplyCount[estate] = 0;
		}

		if(n%2 == 0){
			G.hand[currP][0] = estate;
		}
		//choice 1: 0 or 1
		choice1 = floor(Random()*2);
		//handPos: 0-4
		handPos = floor(Random()*G.handCount[currP]);
	
		passedCount += testBaronEffect(choice1, handPos, currP, &G);

	}
	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time taken = %f seconds\n", cpu_time_used);
	printf("Passed Count = %d out of 20,000.", passedCount );
	printf("TESTS FINISHED!\n");

	return 0;
}
