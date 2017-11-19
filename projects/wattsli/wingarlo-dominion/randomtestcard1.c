/*
* randomtestcard1.c
* Include the following lines in your makefile:
*
* randomtestcard1: randomtestcard1.c dominion.o rngs.o
*      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

/*
* Random testing village card
* REQUIREMENTS:
*   - STATE: Game with village card in kingdom cards
*       - Random deck size (1 - 50) 
*       - Random hand size (1 - 10) with at least one villgae
*       - Random number of actions (0-30)
*   - ORACLE:
*       - deck should decrease by one
*       - hand should increase by one
*       - actions should increase by two
*/

void makeDeck(struct gameState *game, int *cards){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    game->deckCount[p] = rand() % 50 + 1;
    for (i = 0; i < game->deckCount[p]; i++){
        r = rand() % 10;
        game->deck[p][i] = cards[r];
    }
}

int makeHand(struct gameState *game, int *cards){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    game->handCount[p] = rand() % 10 + 1;
    for (i = 0; i < game->handCount[p]; i++){
        r = rand() % 10;
        game->hand[p][i] = cards[r];
    }
    int num = (rand()%game->handCount[p]);
    game->deck[p][num] = village; //making sure there is a village
    return num; //returns position of village card for discard purposes   
}

void runTests(struct gameState *game, int *cards){
    //test prep
    int cardPos = makeHand(game, cards);
    makeDeck(game, cards);
    game->numActions = rand() % 30;
    struct gameState before = *game;
    int player = game->whoseTurn;

    //run village card
    //villageCard(player, cardPos, game);
    vil(game, player, cardPos);

    //TESTS FOR VILLAGE
    printf("\nSTATE FOR CARD 1, VILLAGE: DECK=%d ACTIONS=%d\n", before.deckCount[player], before.numActions);
    //TEST1 - Deck should have one fewer card
    printf("    TEST 1: Deck decreased by one: ");
    if (game->deckCount[player] == before.deckCount[player] - 1 )
        printf("PASSED\n");
    else
        printf("FAILED\n");

    //TEST2 - Hand should have one more card
    printf("    TEST 2: Hand increased by one: ");
    if (game->handCount[player] == before.handCount[player] + 1 )
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //TEST3 - number of actions should increase by 2
    printf("    TEST 2: Num actions increased by 2: ");
    if (game->numActions == before.numActions + 2 )
        printf("PASSED\n");
    else
        printf("FAILED\n");

}

int main(){
    srand(time(NULL));
    int kingdomCards[10] = {adventurer, smithy, sea_hag, cutpurse, village, feast, council_room, gardens, mine, steward};
    struct gameState game;
    initializeGame(2,kingdomCards, 1, &game);
    //run tests
    int i = 0;
    for(i = 0; i < 100; i ++){
        runTests(&game, kingdomCards);
        initializeGame(2, kingdomCards, 1, &game);
    }
    return 0;
}