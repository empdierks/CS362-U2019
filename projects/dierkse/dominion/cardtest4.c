/* -----------------------------------------------------------------------
 * Unit test for getWinners()
 * Emily Dierks
 * CS362, Summer 2019
 * 
 *  
 * -----------------------------------------------------------------------
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "dominion.c"
#include "rngs.h"
#include "rngs.c"
#include <stdio.h>
#include <string.h>

int main(){

	int seed = 1000;
    	int numPlayers = 4;
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    	struct gameState G;
    	int players[4] = {0, 0, 0, 0};
    	int numWinners = 0;
    	int winningPlayers[4] = {-1, -1, -1, -1};
	int highscore = 0;	

	printf ("TESTING getWinners()\n");

    	initializeGame(numPlayers, k, seed, &G); //initialize new game

    // 0 discard 1 to deck, 2 to hand
    // 1 winner with victory cards in discard, deck, and hand
    	gainCard(estate, &G, 0, 1);
    	gainCard(estate, &G, 1, 1);
    	gainCard(duchy, &G, 0, 1);
    	gainCard(curse, &G, 1, 1);

    	printf("Player 1 should have 4 points\n");

	//set all cards in deck & discard pile to coppers
	for(int j =0; j <20; j++){
		G.deck[2][j] = copper;
		if(j <11){
			G.discard[2][j] = copper;
		}
	} 
    	gainCard(great_hall, &G, 0, 2);  //in hand (+1 pt)
    	gainCard(duchy, &G, 1, 2); //in deck (+3 pt)
    	gainCard(duchy, &G, 0, 2); // in discard pile (+3 pt)
    	gainCard(gardens, &G, 1, 2); //in deck (+deckcount/10)

    	printf("Player 2 should have 10.5 points\n");

    	gainCard(province, &G, 0, 3);
    	gainCard(duchy, &G, 1, 3);

    	printf("Player 3 should have 10 points (duchy +3, province +6, turn after end +1)\n");

    	gainCard(estate, &G, 0, 4);
    	gainCard(estate, &G, 1, 4);
    	gainCard(duchy, &G, 0, 4);
    	gainCard(great_hall, &G, 1, 4);

    	printf("Player 4 should have 7 points (2x estate +2, duchy +3, great hall +1, turn after end +1)\n ");

    	G.whoseTurn = 2;

    	getWinners(players, &G);

    for (int i = 0; i < 4; i++){
    	if(players[i] == 1){
    		winningPlayers[numWinners] = i;
		highscore = scoreFor(i, &G);
    		numWinners++;	
    	}
    }


    //Winner should be Player 2
    if(numWinners == 1){
    	printf("Winner: expected value: Player 2, Result: Player %d. ", winningPlayers[0]);
    	if(winningPlayers[0] == 2){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

		printf("High Score: expected value = 10.5 pts, Result = %d pts. ", highscore);
    	if(highscore == 10.5){ printf("SUCCESS\n");}
		else{ printf("FAIL\n"); }

    }
    else if(numWinners == 2){
    	printf("Winner: expected value: Player 2, Result: Player %d & Player %d. FAIL\n", winningPlayers[0], winningPlayers[1]);
    }
    else if(numWinners == 3){
    	printf("Winner: expected value: Player 2, Result: Players %d, %d, & %d. FAIL\n", winningPlayers[0], winningPlayers[1], winningPlayers[2]);
    }
    else{
    	printf("Winner: expected value: Player 2, Result: Players %d, %d, %d & %d. FAIL\n", winningPlayers[0], winningPlayers[1], winningPlayers[2], winningPlayers[3]);
    }


	printf("**END CARD TEST 4: getWinners() **\n\n");

	return 0;
}