/*
* cardtest1.c
* Include the following lines in your makefile:
*
* cardtest1: cardtest1.c dominion.o rngs.o
*      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "adventurer"
/*
* Testing adventurer card 
* REQUIREMENTS:
*    - There are 2 more cards in the player's hand
*    - If more than 2 cards were removed from the deck,
*        the # of cards in the discard has increased
*    -If 2 cards were removed, 
*        the discard is the same size
*    -Number of cards in OtherPlayer's hand is the same
*    -Supply counts have not changed
*/
int main(){
    //Set up inputs and game state with 10 cards and 2 players
    int bonus = 0;
    int cards[10] = {adventurer, smithy, sea_hag, cutpurse, village, council_room, gardens, mine, steward, duchy};
    struct gameState game;
    //game with 2 players
    initializeGame(2, cards, 1, &game);
    int player = whoseTurn(&game);

    //test prep
    game.hand[player][0] = adventurer;
    struct gameState beforeGame = game;
    

    
    //start running tests
    printf("\nTESTING CARD 1: adventurer card\n");
    cardEffect(adventurer, 0, 0, 0, &game, 0, &bonus);

    //Are there 2 more cards in the player's hand?
    printf("    TEST 1: Number of cards in player's hand += 2?: ");
    if(game.handCount[player] == (beforeGame.handCount[player]+2))
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //If only 2 cards were removed from the deck, 
    //discard should be the same
    printf("    TEST 2: Case: top two cards in deck are treasures: ");
    if(game.deckCount[player] == (beforeGame.deckCount[player]-2)){
        if(game.discardCount[player] == beforeGame.discardCount[player])
            printf("PASSED\n");
        else
            printf("FAILED\n");
    }
    else{
        printf("N/A\n");
    }
    //If more than 2 cards were removed from the deck, 
    //discard should have increased
    printf("    TEST 3: Case: top two cards in deck are not both treasures: ");
    if( game.deckCount[player] < (beforeGame.deckCount[player]-2) ){
        if(game.discardCount[player] > beforeGame.discardCount[player])
            printf("PASSED\n");
        else
            printf("FAILED\n");
    }
    else{
        printf("N/A\n");
    }
    //OtherPlayer's hand should be the same
    printf("    TEST 4: OtherPlayer's hand should not have changed: ");
    if(game.handCount[player+1] == beforeGame.handCount[player+1])
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //Supply counts should be the same for all cards
    printf("    TEST 5: supplyCounts should not have changed: ");
    int flag = 0; //0 if no change in supplyCount, 1 otherwise
    int supplyLen = sizeof(game.supplyCount) / sizeof(int);
    int i;
    for(i=0;i<supplyLen;i++){
        if(game.supplyCount[i] != beforeGame.supplyCount[i])
            flag = 1;
    }
    if(flag == 0)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    return 0;
}