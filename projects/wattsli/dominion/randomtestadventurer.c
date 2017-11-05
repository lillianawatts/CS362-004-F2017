/*
* randomtestadventurer.c
* Include the following lines in your makefile:
*
* randomtestadv: randomtestadventurer.c dominion.o rngs.o
*      gcc -o randomtestadv -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)
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
* Random testing adventurer card
* REQUIREMENTS:
*   - STATE: A deck of (10-35) cards, with 2 random treasures in
*       in two random indexes, the rest of the deck filled by
*       random cards
*   - ORACLE: After calling adventurerCard():
*       - Player hand should have 2 more treasure cards
*       - Player deck should have 
*/

/*
* Makes a 
*/
int makeDeck(int length, struct gameState *game, int *cards){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    for (i; i < game->deckCount[p]; i++){
        r = rand() % 10;
        game->deck[p][i] = cards[r];

    }

}


int main(){
    srand(time(NULL));
    int kingdomCards[10] = {adventurer, smithy, sea_hag, cutpurse, village, feast, council_room, gardens, mine, steward};
    struct gameState game;
    initializeGame(2, kingdomCards, 1, &game);
    //fill deck with a random number of cards
    


    return 0;
}

