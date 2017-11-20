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
    game.hand[player][2] = gold;
    int i;
    for(i=3; i < game.handCount[player]; i++)
        game.hand[player][i] = estate;

    //start running tests
    printf("\nTESTING UNIT 1: updateCoins(int, struct gameState*, int)\n");
    printf("    STATE: COINS=%d ", game.coins);
    //Is the number of available coins correct?
    printf("    TEST 1: Number of coins should be 6: ");
    updateCoins(0,&game,0);
    if(game.coins == 6)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("    STATE: COINS=%d ", game.coins);

    //Does it return 1 if the game is over? (no provences)
    printf("    TEST 2: With bonus of 2, number of coins should be 8: ");
    updateCoins(0,&game,2);
    if(game.coins == 8)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("    STATE: COINS=%d ", game.coins);

    return 0;
}
