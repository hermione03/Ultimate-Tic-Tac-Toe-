
#ifndef UTTT_H
#define UTTT_H

// Inclusions de bibliothèques
#include <stdio.h>
#include <time.h>
#include "LocalGrid.h"
#include "GlobalGrid.h"

// Enumération pour les joueurs
enum player
{
    COMPUTER = 'O',
    HUMAN = 'X',
};

typedef struct
{
    int x;
    int y;
} Pos;

typedef struct
{
    Pos **lst_moves;
    int num_moves;
} Move;

// Prototypes de fonctions
char *playerToString(enum player p);
void updatePlayer(GlobalGrid *game);
int possibleMove(GlobalGrid *game, int x, int y);
Pos random_pick_move(GlobalGrid *game);
Pos human_pick_move(GlobalGrid *game);
Pos minimax_pick_move(GlobalGrid *game);
int UTTT_GAME(GlobalGrid *game, Pos (*player1_pick_move)(), Pos (*player2_pick_move)());

#endif /* UTTT_H */
