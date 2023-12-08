#ifndef ALPHA_BETA_H
#define ALPHA_BETA_H

#include "game.h"
#include "ai.h"
#include "../tree.h"

Pos alphaBeta_pick_move(GlobalGrid *game);
Node *AlphaBeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer);

#endif // ALPHA_BETA_H