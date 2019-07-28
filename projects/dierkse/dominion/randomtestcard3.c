/* -----------------------------------------------------------------------
 * Random Test of tributeEffect()
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


int testTributeEffect(int handPos, int currentPlayer, int nextPlayer, struct gameState *post){

	struct gameState pre;
	int r, i;
	int tributeCards[2] = {-1, -1};
	
	memcpy (&pre, post, sizeof(struct gameState));

	//changed tributeEffect to return 1 if wrong
	r = tributeEffect(post, handPos, currentPlayer, nextPlayer, tributeCards);

	if(r == 0){
		
		// if nextPlayer doesn't have 2 cards in discard+deck
		if(pre.discardCount[nextPlayer] + pre.deckCount[nextPlayer] <2){
			//if 1 card in deck, nextP deckcount --, discardCount++ (tribute card)
			if(pre.deckCount[nextPlayer] == 1){
				tributeCards[0] = pre.deck[nextPlayer][0];
				pre.discard[nextPlayer][0] = pre.deck[nextPlayer][0];
				pre.deck[nextPlayer][0] = -1;
				pre.deckCount[nextPlayer]--;
				pre.discardCount[nextPlayer]++;
				
			}
			//else, no change b/c discard tribute card from discard 
			else{
				tributeCards[0] = pre.discard[nextPlayer][0];
			}
		}
		//if all cards in discard, shuffle discard then put as deck
		else if(pre.deckCount[nextPlayer] == 0){
			//nextP deckCount = discardCount - tribute cards
			pre.deckCount[nextPlayer] = pre.discardCount[nextPlayer]-2;
			//nextP discardCount = 2 (discard tribute cards)
			pre.discardCount[nextPlayer] = 2;
			//tributeCards[0] = deck[nextPlayer][] -- cannot determine what tribute Cards would be though since shuffled deck
		}
		else{
			tributeCards[0] = pre.deck[nextPlayer][pre.deckCount[nextPlayer]-1];
			tributeCards[1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer]-2];
			pre.discard[nextPlayer][pre.deckCount[nextPlayer]-2] = pre.deck[nextPlayer][pre.deckCount[nextPlayer]-1];
			pre.discard[nextPlayer][pre.deckCount[nextPlayer]-1] = pre.deck[nextPlayer][pre.deckCount[nextPlayer]-2];
			//nextP deckCount -= tribute cards
			pre.deckCount[nextPlayer] -= 2;
			//nextP discardCount +2
			pre.discardCount[nextPlayer] +=2;
		}

		//if duplicate cards, drop one
		if (tributeCards[0] == tributeCards[1]) { tributeCards[1] = -1;}
	
		for (int i = 0; i <= 2; i++) {
			if (tributeCards[i] == copper || tributeCards[i] == silver || tributeCards[i] == gold) {//Treasure cards
				pre.coins += 2;
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][handPos];
				pre.hand[currentPlayer][handPos] = -1;
				pre.handCount[currentPlayer]--;
				pre.discardCount[currentPlayer]++;
			}

			else if (tributeCards[i] == estate || tributeCards[i] == duchy || tributeCards[i] == province || tributeCards[i] == gardens || tributeCards[i] == great_hall) {//Victory Card Found
			
				pre.hand[currentPlayer][pre.handCount[currentPlayer]] = pre.deck[currentPlayer][pre.deckCount[currentPlayer]-1]; //draw card from deck
				pre.deck[currentPlayer][pre.deckCount[currentPlayer]-1] = -1; //draw hand from deck

				pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][handPos]; //discard tribute card from hand
				pre.hand[currentPlayer][handPos] = -1; //discard tribute card from hand
				//pre.handCount[currentPlayer]++;  //get card from deck & discard tribute card = no change to hand
				pre.deckCount[currentPlayer]--;
				pre.discardCount[currentPlayer]++;
			
			}
			else {//Action Card
				pre.numActions += 2;
				pre.discard[currentPlayer][pre.discardCount[currentPlayer]] = pre.hand[currentPlayer][handPos]; //discard tribute card from hand
				pre.hand[currentPlayer][handPos] = -1; //discard tribute card from hand
				pre.handCount[currentPlayer]--;
				pre.discardCount[currentPlayer]++;
			}
		}
	
		if(memcmp(&pre, post, sizeof(struct gameState))==0){ return 1; }
		else{return 0;}
	}
	else{
		return 0;
	}
	
}

int main(){
	int i, n, nextP, handPos, currP, passedCount;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
				remodel, smithy, village, baron, great_hall};
	struct gameState G;

	printf("Testing tributeEffect.\n");

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

		//currentPlayer: 0-G.numPlayers
		currP = floor(Random()*G.numPlayers);

		//nextPlayer
		if(currP == G.numPlayers-1){
			nextP = 0;
		}
		else{
			nextP= currP+1;
		}

		G.deckCount[currP] = floor(Random()*MAX_DECK);
		G.deckCount[nextP] = floor(Random()*MAX_DECK);

		G.discardCount[currP] = floor(Random()*MAX_DECK);
		G.discardCount[nextP] = floor(Random()*MAX_DECK);

		G.handCount[currP] = floor(Random()*MAX_HAND);
		G.handCount[nextP] = floor(Random()*MAX_HAND);

		//handPos: 0-handcount
		handPos = floor(Random()*G.handCount[currP]);
	
		passedCount += testTributeEffect(handPos, currP, nextP, &G);

	}
	printf("Passed Count = %d out of 2,000.", passedCount );
	printf("TESTS FINISHED!\n");

	return 0;
}
