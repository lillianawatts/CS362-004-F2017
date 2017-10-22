#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

/*
* Unit test for buyCard() function 
* REQUIREMENTS:
*       -supplyCount() for cards[x] updates
*       -number of buys updated
*       -coin count updated
*/

int main(){
    //Set up inputs and game state with 10 cards and 2 players
    int cards[10] = {adventurer, smithy, sea_hag, cutpurse, village, 
    council_room, gardens, mine, gold, duchy};
    
    struct gameState game;
    initializeGame(2, cards, 1, &game);
    int cardCount = game.supplyCount[adventurer];
    int buyCount = game.numBuys;
    int coinCount = game.coins;
    //start running tests
    printf("\nTESTING: buyCard(int, struct gameState)\n");
    buyCard(adventurer, &game);
    
    //Did the coint of adventurer cards decrease?
    printf("    TEST 1: Supply count for adventurer decreased?: ");
    if(supplyCount(adventurer, &game) < cardCount)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Did the number of available buys decrease?
    printf("    TEST 2: Buy count for turn decreased?: ");
    if(game.numBuys < buyCount)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Did the number of available coins decrease?
    printf("    TEST 3: Coin count for turn decreased?: ");
    if(game.coins < coinCount)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    return 0;
}

