#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

/*
* Unit test for isGameOver(struct gameState*) function
* REQUIREMENTS:
*    -isGameOver() should return false (0)
*    -number of provence cards should be > 0
*    -number of supply piles empty should be < 3 
*/

int main(){
    //Set up inputs and game state with 10 cards and 2 players
    int cards[10] = {adventurer, smithy, sea_hag, cutpurse, village, 
    council_room, gardens, mine, gold, duchy};
    
    struct gameState game;
    //game with 2 players
    initializeGame(2, cards, 1, &game);

    //start running tests
    printf("\nTESTING UNIT 2: isGameOver(struct gameState*)\n");

    //Does it return 0 if the game isn't over?
    printf("    TEST 1: Game not over, should not end game: ");
    if(!isGameOver(&game))
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Does it return 1 if the game is over? (no provences)
    printf("    TEST 2: # of province cards < 1, should end game: ");
    game.supplyCount[province] = 0;
    if(isGameOver(&game))
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Does it return 1 if the game is over? (3 stacks empty)
    printf("    TEST 3: 3 card stacks are < 1, should end game: ");
    printf("    STATE: ADV=%d VILL=%d GARD=%d \n", game.supplyCount[adventurer], game.supplyCount[village], game.supplyCount[gardens]);
    game.supplyCount[adventurer] = 0;
    game.supplyCount[village] = 0;
    game.supplyCount[gardens] = 0;
    if(isGameOver(&game))
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("    STATE: ADV=%d VILL=%d GARD=%d \n", game.supplyCount[adventurer], game.supplyCount[village], game.supplyCount[gardens]);

    return 0;
}
