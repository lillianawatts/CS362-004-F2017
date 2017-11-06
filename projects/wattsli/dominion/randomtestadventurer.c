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
*   - STATE: A deck of (2-50) cards, with 2 random treasures in
*       in two random indexes, the rest of the deck filled by
*       random cards
*       - a hand of size (1 - 10) with at least one adventurer card
*   - ORACLE: After calling adventurerCard():
*       - Player hand should have 2 more treasure cards
*       - Cards up until the second treasure card should have been discarded
            - Player deck should be reduced by this amount
*/

/*
* Makes a randomly constructed deck with 2 random treasures
* in it
*/
void makeHand(struct gameState *game, int *cards){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    game->handCount[p] = rand() % 10 + 1;
    for (i = 0; i < game->handCount[p]; i++){
        r = rand() % 10;
        game->hand[p][i] = cards[r];
    }
    int num = (rand()%game->handCount[p]);
    game->deck[p][num] = adventurer; //making sure there is a adventurer
}


void makeDeck(struct gameState *game, int *cards, int *loc){
    int i = 0;
    int r = 0;
    int p = game->whoseTurn;
    int treasures[3] = {gold, silver, copper};
    game->deckCount[p] = rand() % 50 +2;
    for (i = 0; i < game->deckCount[p]; i++){
        r = rand() % 10;
        game->deck[p][i] = cards[r];
    }
    loc[0] = (rand()%game->deckCount[p]);
    loc[1] = (rand()%game->deckCount[p]);
    game->deck[p][ loc[0] ] = treasures[rand()%3];
    game->deck[p][ loc[1] ] = treasures[rand()%3];
    makeHand(game, cards);
}

int getNumTreasures(struct gameState* game){
    int num = 0;
    int i;
    for(i = 0; i<game->handCount[game->whoseTurn];i++){
        if (game->hand[game->whoseTurn][i] || game->hand[game->whoseTurn][i] == silver || game->hand[game->whoseTurn][i] == gold)
            num++;
    }
    return num;
}

//gets the expected difference in the size of the deck 
//after the adventurer card has been used
int getDeckDiff(struct gameState* game, int *loc){
    int lowerIndex;
    if(loc[0] < loc[1])
        lowerIndex = loc[0];
    else    
        lowerIndex = loc[1];
    int i = 0;
    int num = game->deckCount[game->whoseTurn] - lowerIndex;
    return num;
}

//function to set up and run the tests in question
void runTest(int player, struct gameState* game, int *kingdomCards){
    int loc[2] = {-1, -1};
    makeDeck(game, kingdomCards, loc);

    //get before stats
    int deckCount = game->deckCount[player];
    int discardCount = game->discardCount[player];
    int handTreasures = getNumTreasures(game);
    printf("\nSTATE FOR ADVENTURER: DECK=%d TREASURE POS:[%d, %d]\n",game->deckCount[player],loc[0],loc[1]);

    //run adventure card
    int drawnTreasures = 0;
    int temphand[MAX_HAND];
    int z = 0; //counter for temphand
    adventurerCard(drawnTreasures, player, game, temphand, &z);

    //TESTS FOR ADVENTURE CARD
    
    //TEST1 - Hand should have 2 more treasure cards
    printf("    TEST 1: 2 more treasures in hand: ");
    if (getNumTreasures(game) == handTreasures + 2)
        printf("PASSED\n");
    else
        printf("FAILED\n");
    
    //TEST2 - deck should have been reduced by correct amount
    printf("    TEST 2: Deck decreased by the correct amount: ");
    printf("         current val=%d, dC %d - diff %d = %d", game->deckCount[player], deckCount, getDeckDiff(game, loc), (deckCount - getDeckDiff(game, loc)));
    if ((deckCount - getDeckDiff(game, loc)) == game->deckCount[player])
        printf("PASSED\n");
    else
        printf("FAILED\n");   

    //TEST3 - deck should have been reduced by correct amount
    printf("    TEST 3: Discard increased by the correct amount: ");
    if ((discardCount + getDeckDiff(game, loc)) == game->discardCount[player])
        printf("PASSED\n");
    else
        printf("FAILED\n"); 
}

int main(){
    srand(time(NULL));
    int kingdomCards[10] = {adventurer, smithy, sea_hag, cutpurse, village, feast, council_room, gardens, mine, steward};
    struct gameState game;
    initializeGame(2, kingdomCards, 1, &game);
    int player = game.whoseTurn;
    //run tests
    int i = 0;
    for(i = 0; i < 100; i ++){
        runTest(player, &game, kingdomCards);
        initializeGame(2, kingdomCards, 1, &game);
        player = game.whoseTurn;
    }
    

    return 0;
}

