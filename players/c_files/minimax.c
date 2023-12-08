#include "minimax.h"

void evaluateGame(Node *curr);

Node *MiniMax(Node *node, int depth, int maximizingPlayer)
{
    if (depth == 0 || game_CheckIfWon(&node->state) || isGlobalGridFull(node->state))
    {
        evaluateGame(node);
        return node;
    }
    Move *moves = NextMoves(node->state);

    if (maximizingPlayer == node->state.current_player)
    {
        // int bestValue = INT_MIN;
        Node *bestNode = NULL;
        for (int i = 0; i < moves->num_moves; i++)
        {
            // printf("WAAAAAAAAAAAAAAAAAH : (%d,%d)\n", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]), *moves->lst_moves[i]);
            // displayNode(child);
            addSuccessor(node, child);
            Node *result = MiniMax(child, depth - 1, !maximizingPlayer);
            if (bestNode == NULL || result->value > bestNode->value)
            {
                bestNode = result;
            }
        }
        // displayNode(bestNode);
        return bestNode;
    }
    else
    {
        // int bestValue = INT_MAX;
        Node *bestNode = NULL;
        for (int i = 0; i < moves->num_moves; i++)
        {
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]), *moves->lst_moves[i]);
            addSuccessor(node, child);
            Node *result = MiniMax(child, depth - 1, !maximizingPlayer);
            if (bestNode == NULL || result->value < bestNode->value)
            {
                bestNode = result;
            }
        }
        // displayNode(bestNode);
        return bestNode;
    }
}

Pos minimax_pick_move(GlobalGrid *game, int depth)
{
    int i, x, y, xg, yg;
    Pos pos = {-1, -1};
    // printf("%c HEEEEERE ON MINIMAX !!\n", game->current_player);
    Move *moves = NextMoves(*game);
    printf("Mouvements disponibles :\n");
    for (i = 0; moves->lst_moves[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
    }
    printf("\n");
    // int depth = 5; // Set your desired depth for MiniMax
    Node *root = createNode(*game, pos);
    // displayTree(best);
    Node *bestMove = MiniMax(root, depth, game->current_player);
    printf("Best Move : %d\n", bestMove->value);
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
            int tmpEv = checkWinCondition(&curr->state.localboard[row][col]);
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
    evale -= checkWinCondition(mainBd) * 5000;
    evale += evaluateLG(mainBd) * 150;
    free(mainBd);

    curr->value = evale;
}