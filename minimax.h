#ifndef MINIMAX_H
#define MINIMAX_H

#include "GAME.h"
#include "AI.h"

Node *MiniMax(Node *node, int depth, int maximizingPlayer);
Pos minimax_pick_move(GlobalGrid *game);


#endif // MINIMAX_H