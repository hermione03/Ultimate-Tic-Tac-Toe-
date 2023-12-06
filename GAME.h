
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

// Définition des structures pour les positions de jeu et les mouvements possibles
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

// Prototypes de fonctions pour la manipulation des joueurs et des mouvements
char *playerToString(enum player p);
void updatePlayer(GlobalGrid *game);
int possibleMove(GlobalGrid *game, int x, int y);
Pos random_pick_move(GlobalGrid *game);               // pour des mouvement aleatoirs
Pos human_pick_move(GlobalGrid *game);                // pour qu'un humain puisse jouer
Pos minimax_pick_move(GlobalGrid *game, int depth);   // MiniMax sans elagage
Pos alphaBeta_pick_move(GlobalGrid *game, int depth); // MiniMax AVEC elagage AlphaBeta
int UTTT_GAME(GlobalGrid *game, Pos (*player1_pick_move)(), Pos (*player2_pick_move)(), int depth);

#endif /* UTTT_H */
