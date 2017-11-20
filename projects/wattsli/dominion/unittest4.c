#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0

/*
* Unit test for gainCard(int, struct gameState*, int, int) function 
* REQUIREMENTS:
*    -Fails if pile is empty or card isn't used in game 
*        -supplyCount(card, game) < 1
*    -toFlag sends card to the right place
*    -reduces suppy count of the added card
*/

int main(){
    //Set up inputs and game state with 10 cards and 2 players
    int cards[10] = {adventurer, smithy, sea_hag, cutpurse, village, 
    council_room, gardens, mine, gold, duchy};
    int i;
    struct gameState game;
    //game with 2 players
    initializeGame(2, cards, 1, &game);
    int player = whoseTurn(&game);  

    int cardCount = game.deckCount
    int supplyCount = game.supplyCount[adventurer];

    //start running tests
    printf("\nTESTING UNIT 4: gainCard(int, struct gameState*, int, int) -using adventurer\n");
    
    //Is the card available?
    printf("    TEST 1: Card should be available (in game, in stock): ");
    if(gainCard(adventurer, &game, 1, player) > -1)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Does it add it?
    printf("    TEST 2: Number of cards in hand, discard, and deck should increase by 1 respectively: ");
    printf("\n        STATE: DISC=%d DECK=%d HAND=%d\n", game.discardCount, game.deckCount, game.handCount);
    gainCard(adventurer, &game, 0, player); //sends card to discard
    gainCard(adventurer, &game, 1, player); //sends card to deck
    gainCard(adventurer, &game, 2, player); //sends card to hand
    if(fullDeckCount(whoseTurn(&game), 0, &game) == (cardCount+3))
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("        STATE: DISC=%d DECK=%d HAND=%d\n", game.discardCount, game.deckCount, game.handCount);

    //Does it update the supply?
    printf("    TEST 3: Supply of adventurer should be decreased by 3: ");
    printf("        STATE: SUPPLY=%d\n", supplyCount);
    if(game.supplyCount[adventurer] == (supplyCount - 3))
        printf("PASSED\n");
    else
        printf("FAILED\n");
    printf("        STATE: SUPPLY=%d\n", game.supplyCount[adventurer]);

    return 0;
}