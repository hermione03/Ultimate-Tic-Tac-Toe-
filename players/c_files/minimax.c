#include <stdio.h>
#include <stdlib.h>
#include "../HEADERS/minimax.h"
#include "../../ai.h"
void evaluateGame(Node *curr);

Node *MiniMax(Node *node, int depth, int maximizingPlayer)
{
    if (depth == 0 || is_game_over(node->state))
    {
        evaluateGame(node);
        return node;
    }
    PosList *moves = get_possible_moves(node->state);

    if (maximizingPlayer == node->state.current_player)
    {
        // int bestValue = INT_MIN;
        Node *bestNode = NULL;
        for (int i = 0; i < moves->length; i++)
        {
            // printf("WAAAAAAAAAAAAAAAAAH : (%d,%d)\n", moves->positions[i]->x, moves->positions[i]->y);
            Node *child = create_node(apply_move(node->state, *moves->positions[i]), *moves->positions[i]);
            // display_node(child);
            add_successor(node, child);
            Node *result = MiniMax(child, depth - 1, !maximizingPlayer);
            if (bestNode == NULL || result->value > bestNode->value)
            {
                bestNode = result;
            }
        }
        // display_node(bestNode);
        return bestNode;
    }
    else
    {
        // int bestValue = INT_MAX;
        Node *bestNode = NULL;
        for (int i = 0; i < moves->length; i++)
        {
            Node *child = create_node(apply_move(node->state, *moves->positions[i]), *moves->positions[i]);
            add_successor(node, child);
            Node *result = MiniMax(child, depth - 1, !maximizingPlayer);
            if (bestNode == NULL || result->value < bestNode->value)
            {
                bestNode = result;
            }
        }
        // display_node(bestNode);
        return bestNode;
    }
}

Pos minimax_pick_move(GlobalGrid *game, int depth)
{
    int i, x, y, xg, yg;
    Pos pos = {-1, -1};
    // printf("%c HEEEEERE ON MINIMAX !!\n", game->current_player);
    PosList *moves = get_possible_moves(*game);
    printf("Mouvements disponibles :\n");
    for (i = 0; moves->positions[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->positions[i]->x, moves->positions[i]->y);
    }
    printf("\n");
    // int depth = 5; // Set your desired depth for MiniMax
    Node *root = create_node(*game, pos);
    // display_tree(best);
    Node *bestMove = MiniMax(root, depth, game->current_player);
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