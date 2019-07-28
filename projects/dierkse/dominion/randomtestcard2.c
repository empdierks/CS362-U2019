/* -----------------------------------------------------------------------
 * Random Test of minionEffect()
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
#include <math.h>

//all cases +1 action
	//choice 1, +2 coins
	//choice 2, current Player: discard hand, +4 cards && other players >4 handCount-> discardCount += pre->handCount +4
int testMinionEffect(int choice1, int choice2, int handPos, int currentPlayer, struct gameState *post){

	struct gameState pre;
	int r, i;
	
	memcpy (&pre, post, sizeof(struct gameState));

	//changed minionEffect to return 1 if wrong
	r = minionEffect(post, choice1, choice2, handPos, currentPlayer);

	if(r == 0){
		//if choice1 = 1 & choice2 = 0
		if(choice1 == 1 && choice2 == 0){
			//+1 action, +2 coins, handCount-1, discardCount+1
			pre.numActions++;
			pre.coins+=2;
			pre.handCount[currentPlayer]-1;
			pre.discardCount[currentPlayer]+1;
		}
		//if choice1 = 0 & choice2 = 1
		else if(choice1 == 0 && choice2 == 1){
			//+1 action, current Player: handCount = 4, discardCount +=pre->handCount &
			pre.numActions++;
			pre.discardCount[currentPlayer] += pre.handCount[currentPlayer];
			pre.handCount[currentPlayer]=4;
			pre.deckCount[currentPlayer] -=4;

			//other players > 4 pre.handCount: discardCount += pre->handCount +4
			for(i=0; i < pre.numPlayers;i++){
				if(i != currentPlayer){
					if(pre.handCount[i] > 4){
						pre.discardCount[i] += pre.handCount[i];
						pre.handCount[i] = 4;
						pre.deckCount[i] -= 4;
					}
				}
			}

		}
		//if choice1 = 1 & choice2 = 1 -- nothing happens
		if(memcmp(&pre, post, sizeof(struct gameState))==0){ return 1; }
		else{ return 0;}
	}
	else{
		return 0;
	}
	
}


int main(){
	int numPlayers, i, n, choice1, choice2, currP, passedCount;
	int handPos = 0;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("Testing minionEffect.\n");

	printf("RANDOM TESTING.\n");

	SelectStream(2);
	PutSeed(3);

	for (n=0; n <200; n++){
		
		//number of Players
		numPlayers= floor(Random()*4);
		if(numPlayers == 0 || numPlayers == 1){
			numPlayers = 2;
		}

		initializeGame(numPlayers, k, 1, &G);	

		//preconditions
		//number of actions
		G.numActions = floor(Random()*10);
		
		//number of coins
		G.coins = floor(Random()*30);

		//set all players' deck, hand, and discard piles
		for(i =0; i < G.numPlayers; i++){
			G.deckCount[i] = floor(Random()*20);
			G.discardCount[i] = floor(Random()*20);
			G.handCount[i] = floor(Random()*20);
			memset(G.deck[i], 0, sizeof(int)*G.deckCount[i]);
			memset(G.discard[i], 0, sizeof(int)*G.discardCount[i]);
			memset(G.hand[i], 0, sizeof(int)*G.handCount[i]);		
		}

		
		//choice 1 & 2: 0 or 1
		choice1 = floor(Random()*2);
		if(choice1 == 1){
			choice2 = 0;
		}
		else{ choice2 = 1;}		

		if(n%2){
			 choice2= 1;
			 choice1=0;
		}

		//currentPlayer: 0-p
		currP = floor(Random()*G.numPlayers);

		//handPos: any # in current Player's hand
		handPos = floor(Random()*G.handCount[currP]);

		passedCount += testMinionEffect(choice1, choice2, handPos, currP, &G);

	}
	printf("Passed Count = %d out of 2,000.", passedCount );
	printf("TESTS FINISHED!\n");

	return 0;
}
