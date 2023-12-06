
#include "AI.h"

Node *createNode(GlobalGrid game)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode)
    {
        newNode->value = 0;
        newNode->state = game;
        newNode->num_successors = 0;
        newNode->capacity = 0;
        newNode->successors = NULL;
    }
    return newNode;
}

int giveValue(enum player p)
{
    if (p == HUMAN)
    {
        return 1;
    }
    if (p == COMPUTER)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int checkWinCondition(LocalGrid *lcState)
{
    LG_CheckIfWon(lcState);
    if (lcState->winner == COMPUTER)
    {
        return -1;
    }
    else if (lcState->winner == HUMAN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int realEvaluateSquare(LocalGrid *lcState)
{
    int evaluation = 0;
    int poids[] = {0.2, 0.17, 0.2, 0.17, 0.22, 0.17, 0.2, 0.17, 0.2};

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            evaluation -= giveValue((lcState->board[i][j])) * poids[i * 3 + j];
        }
    }

    int a = 2;
    if (giveValue(lcState->board[0][0]) + giveValue(lcState->board[0][1]) + giveValue(lcState->board[0][2]) == a || giveValue(lcState->board[1][0]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[1][2]) == a || giveValue(lcState->board[2][0]) + giveValue(lcState->board[2][1]) + giveValue(lcState->board[2][2]) == a)
    {
        evaluation -= 6;
    }
    if (giveValue(lcState->board[0][0]) + giveValue(lcState->board[1][0]) + giveValue(lcState->board[2][0]) == a || giveValue(lcState->board[0][1]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[2][1]) == a || giveValue(lcState->board[0][2]) + giveValue(lcState->board[1][2]) + giveValue(lcState->board[2][2]) == a)
    {
        evaluation -= 6;
    }
    if (giveValue(lcState->board[0][0]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[2][2]) == a || giveValue(lcState->board[0][2]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[2][0]) == a)
    {
        evaluation -= 7;
    }

    a = -1;
    if (giveValue((lcState->board[0][0]) + giveValue(lcState->board[0][1]) == 2 * a && giveValue(lcState->board[0][2]) == -a) || giveValue((lcState->board[0][1]) + giveValue(lcState->board[0][2]) == 2 * a && giveValue(lcState->board[0][0]) == -a) || giveValue((lcState->board[0][0]) + giveValue(lcState->board[0][2]) == 2 * a && giveValue(lcState->board[0][1]) == -a) ||
        giveValue((lcState->board[1][0]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[1][2]) == -a) || giveValue((lcState->board[1][0]) + giveValue(lcState->board[1][2]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[1][2]) == 2 * a && giveValue(lcState->board[1][0]) == -a) ||
        giveValue((lcState->board[2][0]) + giveValue(lcState->board[2][1]) == 2 * a && giveValue(lcState->board[2][2]) == -a) || giveValue((lcState->board[2][0]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[2][1]) == -a) || giveValue((lcState->board[2][1]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[2][0]) == -a) ||
        giveValue((lcState->board[0][0]) + giveValue(lcState->board[1][0]) == 2 * a && giveValue(lcState->board[2][0]) == -a) || giveValue((lcState->board[0][0]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[1][0]) == -a) || giveValue((lcState->board[1][0]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[0][0]) == -a) ||
        giveValue((lcState->board[0][1]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[2][1]) == -a) || giveValue((lcState->board[0][1]) + giveValue(lcState->board[2][1]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[2][1]) == 2 * a && giveValue(lcState->board[0][1]) == -a) ||
        giveValue((lcState->board[0][2]) + giveValue(lcState->board[1][2]) == 2 * a && giveValue(lcState->board[2][2]) == -a) || giveValue((lcState->board[0][2]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[1][2]) == -a) || giveValue((lcState->board[1][2]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[0][2]) == -a) ||
        giveValue((lcState->board[0][0]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[2][2]) == -a) || giveValue((lcState->board[0][0]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[0][0]) == -a) ||
        giveValue((lcState->board[0][2]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[2][0]) == -a) || giveValue((lcState->board[0][2]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[0][2]) == -a))
    {
        evaluation -= 9;
    }

    a = -2;
    if (giveValue(lcState->board[0][0]) + giveValue(lcState->board[0][1]) + giveValue(lcState->board[0][2]) == a || giveValue(lcState->board[1][0]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[1][2]) == a || giveValue(lcState->board[2][0]) + giveValue(lcState->board[2][1]) + giveValue(lcState->board[2][2]) == a)
    {
        evaluation += 6;
    }
    if (giveValue(lcState->board[0][0]) + giveValue(lcState->board[1][0]) + giveValue(lcState->board[2][0]) == a || giveValue(lcState->board[0][1]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[2][1]) == a || giveValue(lcState->board[0][2]) + giveValue(lcState->board[1][2]) + giveValue(lcState->board[2][2]) == a)
    {
        evaluation += 6;
    }
    if (giveValue(lcState->board[0][0]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[2][2]) == a || giveValue(lcState->board[0][2]) + giveValue(lcState->board[1][1]) + giveValue(lcState->board[2][0]) == a)
    {
        evaluation += 7;
    }

    a = 1;
    if (giveValue((lcState->board[0][0]) + giveValue(lcState->board[0][1]) == 2 * a && giveValue(lcState->board[0][2]) == -a) || giveValue((lcState->board[0][1]) + giveValue(lcState->board[0][2]) == 2 * a && giveValue(lcState->board[0][0]) == -a) || giveValue((lcState->board[0][0]) + giveValue(lcState->board[0][2]) == 2 * a && giveValue(lcState->board[0][1]) == -a) ||
        giveValue((lcState->board[1][0]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[1][2]) == -a) || giveValue((lcState->board[1][0]) + giveValue(lcState->board[1][2]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[1][2]) == 2 * a && giveValue(lcState->board[1][0]) == -a) ||
        giveValue((lcState->board[2][0]) + giveValue(lcState->board[2][1]) == 2 * a && giveValue(lcState->board[2][2]) == -a) || giveValue((lcState->board[2][0]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[2][1]) == -a) || giveValue((lcState->board[2][1]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[2][0]) == -a) ||
        giveValue((lcState->board[0][0]) + giveValue(lcState->board[1][0]) == 2 * a && giveValue(lcState->board[2][0]) == -a) || giveValue((lcState->board[0][0]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[1][0]) == -a) || giveValue((lcState->board[1][0]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[0][0]) == -a) ||
        giveValue((lcState->board[0][1]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[2][1]) == -a) || giveValue((lcState->board[0][1]) + giveValue(lcState->board[2][1]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[2][1]) == 2 * a && giveValue(lcState->board[0][1]) == -a) ||
        giveValue((lcState->board[0][2]) + giveValue(lcState->board[1][2]) == 2 * a && giveValue(lcState->board[2][2]) == -a) || giveValue((lcState->board[0][2]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[1][2]) == -a) || giveValue((lcState->board[1][2]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[0][2]) == -a) ||
        giveValue((lcState->board[0][0]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[2][2]) == -a) || giveValue((lcState->board[0][0]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[2][2]) == 2 * a && giveValue(lcState->board[0][0]) == -a) ||
        giveValue((lcState->board[0][2]) + giveValue(lcState->board[1][1]) == 2 * a && giveValue(lcState->board[2][0]) == -a) || giveValue((lcState->board[0][2]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[1][1]) == -a) || giveValue((lcState->board[1][1]) + giveValue(lcState->board[2][0]) == 2 * a && giveValue(lcState->board[0][2]) == -a))
    {
        evaluation += 9;
    }

    evaluation -= checkWinCondition(lcState) * 12;

    return evaluation;
}

void EvaluateMove(Node *curr)
{
    curr->value = 0;
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
            evale += realEvaluateSquare(&curr->state.localboard[row][col]) * 1.5 * evaluatorMul[currentPos];
            if (currentPos == curr->state.relative_grid && curr->state.relative_grid != -1)
            {
                evale += realEvaluateSquare(&curr->state.localboard[row][col]) * evaluatorMul[currentPos];
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
    evale += realEvaluateSquare(mainBd) * 150;
    free(mainBd);

    curr->value = evale;
}

Move *NextMoves(GlobalGrid game)
{
    int x, y, i = 0;
    int capacity = 1;
    Move *moves = (Move *)malloc(sizeof(Move));
    moves->lst_moves = (Pos **)malloc(capacity * sizeof(Pos *));

    if (moves == NULL || moves->lst_moves == NULL)
    {
        printf("Memory allocation failed for moves.\n");
        return NULL;
    }

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 27; y++)
        {
            if (possibleMove(&game, x, y))
            {
                if (i >= capacity - 1)
                {
                    capacity += 1;
                    moves->lst_moves = (Pos **)realloc(moves->lst_moves, capacity * sizeof(Pos *));
                    if (moves->lst_moves == NULL)
                    {
                        printf("Memory reallocation failed for moves->lst_moves.\n");
                        return NULL;
                    }
                }

                moves->lst_moves[i] = (Pos *)malloc(sizeof(Pos));
                if (moves->lst_moves[i] == NULL)
                {
                    printf("Memory allocation failed for moves->lst_moves[%d].\n", i);
                    return NULL;
                }

                moves->lst_moves[i]->x = x;
                moves->lst_moves[i]->y = y;
                i++;
            }
        }
    }

    moves->lst_moves[i] = NULL;
    moves->num_moves = i;

    return moves;
}

GlobalGrid ApplyMove(GlobalGrid game, Pos pos)
{
    int xg, yg;
    GlobalGrid next = game;
    xg = (pos.y / 3) / 3; // Récupère la grille globale à mettre à jour
    yg = (pos.y / 3) % 3; // Récupère la position de la localboard dans la grille globale
    int x = pos.x;
    int y = (pos.y % 3);

    next.localboard[xg][yg].board[x][y] = game.current_player;

    return next;
}

void addSuccessor(Node *node, Node *successor)
{
    if (node->num_successors >= node->capacity)
    {
        node->capacity = (node->capacity == 0) ? 1 : node->capacity * 2;
        node->successors = realloc(node->successors, node->capacity * sizeof(Node *));
        if (node->successors == NULL)
        {
            printf("Allocation mémoire échouée pour les successeurs.\n");
            exit(1);
        }
    }
    node->successors[node->num_successors++] = successor;
}

void displayNode(Node *node)
{
    printf("--------------- Node ------------------------\n");
    printf("Winner ? %c\n ", node->state.winner);
    printf("Current player ? %c\n ", node->state.current_player);
    printf("Value : %d\n", node->value);
    printf("Nombre de successeurs : %d\n", node->num_successors);

    Display_game(&node->state);

    printf("Successeurs: ");
    for (int i = 0; i < node->num_successors; i++)
    {
        printf("Successeur %d, ", i + 1);
    }
    printf("\n");
    printf("-------------------------------------------------------\n");
}

void displayTree(Node *node)
{
    printf("--------------- Tree ------------------------\n");
    if (node == NULL)
    {
        return;
    }

    displayNode(node);

    for (int i = 0; i < node->num_successors; i++)
    {
        displayTree(node->successors[i]);
    }
    printf("-------------------------------------------------------\n");
}

void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < root->num_successors; i++)
    {
        freeTree(root->successors[i]); // Appel récursif pour libérer les enfants
    }

    free(root->successors); // Libération du tableau de successeurs
    free(root);             // Libération du nœud actuel
}

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
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]));
            addSuccessor(node, child);
            Node *result = MiniMax(child, depth - 1, !maximizingPlayer);
            if (bestNode == NULL || result->value > bestNode->value)
            {
                bestNode = result;
            }
        }
        return bestNode;
    }
    else
    {
        // int bestValue = INT_MAX;
        Node *bestNode = NULL;
        for (int i = 0; i < moves->num_moves; i++)
        {
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]));
            addSuccessor(node, child);
            Node *result = MiniMax(child, depth - 1, !maximizingPlayer);
            if (bestNode == NULL || result->value < bestNode->value)
            {
                bestNode = result;
            }
        }
        return bestNode;
    }
}

Node *AlphaBeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer)
{
    if (depth == 0 || game_CheckIfWon(&node->state) || isGlobalGridFull(node->state))
    {
        evaluateGame(node);
        return node;
    }
    Move *moves = NextMoves(node->state);

    if (maximizingPlayer == node->state.current_player)
    {
        Node *bestNode = NULL;
        for (int i = 0; i < moves->num_moves; i++)
        {
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]));
            addSuccessor(node, child);
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
        return bestNode;
    }
    else
    {
        Node *bestNode = NULL;
        for (int i = 0; i < moves->num_moves; i++)
        {
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]));
            addSuccessor(node, child);
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
        return bestNode;
    }
}
