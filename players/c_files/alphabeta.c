#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../HEADERS/alphabeta.h"

void evaluateGame(Node *curr);

Node *AlphaBeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer)
{
    if (depth == 0 || is_game_over(node->state))
    {
        evaluateGame(node);
        return node;
    }
    PosList *moves = get_possible_moves(node->state);

    if (maximizingPlayer == node->state.current_player)
    {
        Node *bestNode = NULL;
        for (int i = 0; i < moves->length; i++)
        {
            // printf("WAAAAAAAAAAAAAAAAAH : (%d,%d)\n", moves->positions[i]->x, moves->positions[i]->y);
            Node *child = create_node(apply_move(node->state, *moves->positions[i]), *moves->positions[i]);
            add_successor(node, child);
            Node *result = AlphaBeta(child, depth - 1, alpha, beta, !maximizingPlayer);
            if (bestNode == NULL || result->value > bestNode->value)
            {
                bestNode = result;
            }
            alpha = (alpha > result->value) ? alpha : result->value;
            if (beta <= alpha)
            {
                break; // Élagage Beta
            }
        }
        // display_node(bestNode);
        return bestNode;
    }
    else
    {
        Node *bestNode = NULL;
        for (int i = 0; i < moves->length; i++)
        {
            // printf("WAAAAAAAAAAAAAAAAAH ellllllllllssssssssseeeeeeeee: (%d,%d)\n", moves->positions[i]->x, moves->positions[i]->y);
            Node *child = create_node(apply_move(node->state, *moves->positions[i]), *moves->positions[i]);
            // display_node(child);
            add_successor(node, child);
            Node *result = AlphaBeta(child, depth - 1, alpha, beta, !maximizingPlayer);
            if (bestNode == NULL || result->value < bestNode->value)
            {
                bestNode = result;
            }
            beta = (beta < result->value) ? beta : result->value;
            if (beta <= alpha)
            {
                break; // Élagage Alpha
            }
        }
        // display_node(bestNode);
        return bestNode;
    }
}

Pos alphaBeta_pick_move(GlobalGrid *game, int depth)
{
    int i, x, y, xg, yg;
    Pos pos = {-1, -1};
    PosList *moves = get_possible_moves(*game);
    // printf("%c HEEEEERE ON ALPHABETA !!\n", game->current_player);
    printf("Mouvements disponibles :\n");
    for (i = 0; moves->positions[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->positions[i]->x, moves->positions[i]->y);
    }
    printf("\n");

    Node *root = create_node(*game, pos);
    Node *bestMove = AlphaBeta(root, depth, INT_MIN, INT_MAX, game->current_player);
    printf("Best PosList : %d\n", bestMove->value);
    printf("LAAAAAAAA POOOOOS A LA FING : (%d,%d)\n", bestMove->lastpos.x, bestMove->lastpos.y);
    return bestMove->lastpos;
}

void evaluateGame(Node *curr)
{
    int evale = 0;
    float evaluatorMul[] = {1.4, 1, 1.4, 1, 1.75, 1, 1.4, 1, 1.4};
    LocalGrid *mainBd = malloc(sizeof(LocalGrid)); // Utilisation de LocalGrid au lieu de int mainBd[9];
    initialize_local_grid(mainBd);

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            int currentPos = row * 3 + col;
            evale += evaluateLG(&curr->state.localboard[row][col]) * 1.5 * evaluatorMul[currentPos];
            if (currentPos == curr->state.relative_grid && curr->state.relative_grid != -1)
            {
                evale += evaluateLG(&curr->state.localboard[row][col]) * evaluatorMul[currentPos];
            }
            int tmpEv = check_win_condition(&curr->state.localboard[row][col]);
            evale -= tmpEv * evaluatorMul[currentPos];
        }
    }

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            mainBd->board[row][col] = curr->state.localboard[(col / 3) / 3][(col / 3) % 3].board[row][col]; // Copie des LocalGrids
        }
    }

    // Utilisation des instances LocalGrid pour les calculs
    evale -= check_win_condition(mainBd) * 5000;
    evale += evaluateLG(mainBd) * 150;
    free(mainBd);

    curr->value = evale;
}