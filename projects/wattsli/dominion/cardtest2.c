/*
* cardtest2.c
* Include the following lines in your makefile:
*
* cardtest2: cardtest2.c dominion.o rngs.o
*      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"
/*
* Testing smithy card 
* REQUIREMENTS:
*    -Player recieved 3 cards
*    -Cards came from player deck
*    -OtherPlayer did not receive any cards
*    -Supply counts have not changed
*/
int main(){
    //Set up inputs and game state with 10 cards and 2 players
    int bonus = 0;
    int cards[10] = {adventurer, smithy, sea_hag, cutpurse, village, council_room, gardens, mine, gold, duchy};
    struct gameState game;
    //game with 2 players
    initializeGame(2, cards, 1, &game);
    int player = whoseTurn(&game);

    //test prep
    game.hand[player][0] = smithy;
    struct gameState beforeGame = game;



    //start running tests
    printf("\nTESTING: village card\n");
    cardEffect(smithy, 0, 0, 0, &game, 0, &bonus);

    //player received 3 cards
    printf("    TEST 1: Player hand should have 3 more cards:");
    if(game.handCount[player] == beforeGame.handCount[player] + 3)
        printf("PASSED\n");
    else
        printf("FAILED\n");

    //cards came from player's deck
    printf("    TEST 2: Player deck should have 3 fewer cards:");
    if(game.deckCount[player] == beforeGame.deckCount[player] - 3)
        printf("PASSED\n");
    else
        printf("FAILED\n");

    //OtherPlayer's hand should be the same
    printf("    TEST 3: OtherPlayer's hand should not have changed: ");
    if(game.handCount[player+1] == beforeGame.handCount[player+1])
        printf("PASSED\n");
    else
        printf("FAILED\n");

    //Supply counts should be the same for all cards
    printf("    TEST 4: supplyCounts should not have changed: ");
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