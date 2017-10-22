#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

/*
* Unit test for updateCoins(int, struct gameState*, int) function 
* REQUIREMENTS:
*    -Updates with the correct coins for treasures in player's hand
*    -Adds bonus if present
*/

int main(){
    //Set up inputs and game state with 10 cards and 2 players
    int cards[10] = {adventurer, smithy, sea_hag, cutpurse, village, 
    council_room, gardens, mine, gold, duchy};
    
    struct gameState game;
    //game with 2 players
    initializeGame(2, cards, 1, &game);
    //prepare for testing
    //struct gameState beforeGame = game;
    int player = whoseTurn(&game);
    game.hand[player][0] = copper;
    game.hand[player][1] = silver;
    game.hand[player][3] = gold;

    //start running tests
    printf("\nTESTING: updateCoins(int, struct gameState*, int)\n");
    
    //Is the number of available coins correct?
    printf("    TEST 1: Number of coins should be 6: ");
    updateCoins(0,&game,0);
    if(game.coins == 6)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Does it return 1 if the game is over? (no provences)
    printf("    TEST 2: With bonus of 2, number of coins should be 8: ");
    updateCoins(0,&game,2);
    if(game.coins == 8)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    return 0;
}
