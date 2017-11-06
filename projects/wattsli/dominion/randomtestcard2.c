/*
* randomtestcard2.c
* Include the following lines in your makefile:
*
* randomtestcard2: randomtestcard2.c dominion.o rngs.o
*      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
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
* Random testing smithy card
* REQUIREMENTS:
*   - STATE: Game with smithy card in kingdom cards
*       - Random deck size (0 - 50)
*       - Random hand size (1 - 10) with at least one smithy
*   - ORACLE:
*       - deck should decrease by three
*       - hand should increase by three
*/

void makeDeck(struct gameState *game, int *cards){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    game->deckCount[p] = rand() % 50;
    for (i; i < game->deckCount[p]; i++){
        r = rand() % 10;
        game->deck[p][i] = cards[r];
    }
}

int makeHand(struct gameState *game, int *cards){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    game->handCount[p] = rand() % 10 + 1;
    for (i; i < game->handCount[p]; i++){
        r = rand() % 10;
        game->hand[p][i] = cards[r];
    }
    int num = (rand()%game->handCount[p]);
    game->deck[p][num] = smithy; //making sure there is a smithy
    return num; //returns position of smithy card for discard purposes   
}

void runTests(struct gameState *game, int cards){
    //test prep
    makeDeck(game, cards);
    int cardPos = makeHand(game, cards);
    game->numActions = rand() % 30;
    struct gameState before = *game;
    int player = game->whoseTurn;

    //run smithy card
    smithyCard(player, cardPos, game);

    //TESTS FOR VILLAGE
    printf("\nSTATE FOR CARD 2, SMITHY: DECK=%d HAND=%d\n", before.deckCount[player], before.handCount[player]);
    //TEST1 - Deck should have one fewer card
    printf("    TEST 1: Deck decreased by three: ");
    if (game->deckCount[player] == before.deckCount[player] - 3 )
        printf("PASSED\n");
    else
        printf("FAILED\n");

    //TEST2 - Hand should have one more card
    printf("    TEST 2: Hand increased by three: ");
    if (game->handCount[player] == before.handCount[player] + 3 )
        printf("PASSED\n");
    else
        printf("FAILED\n");
}

int main(){
    srand(time(NULL));
    int kingdomCards[10] = {adventurer, smithy, sea_hag, cutpurse, village, feast, council_room, gardens, mine, steward};
    struct gameState game;
    initializeGame(2,kingdomCards, 1, &game);
    int player = game.whoseTurn;
    //run tests
    int i = 0;
    for(i ; i < 100; i ++){
        runTest(&game, kingdomCards);
        initializeGame(2, kingdomCards, 1, &game);
        player = game.whoseTurn;
    }

}