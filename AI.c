
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

void EvaluateMove(Node *state)
{
    state->value = 0;
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
    xg = (pos.y / 3) / 3;// Récupère la grille globale à mettre à jour
    yg = (pos.y / 3) % 3;// Récupère la position de la localboard dans la grille globale
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
    printf("Value : %d\n", node->value);
    printf("Nombre de successeurs : %d\n", node->num_successors);

    Display_game(&node->state);

    printf("Successeurs: ");
    for (int i = 0; i < node->num_successors; i++)
    {
        printf("Successeur %d, ", i + 1);
    }
    printf("\n");
}

void displayTree(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    displayNode(node);

    for (int i = 0; i < node->num_successors; i++)
    {
        displayTree(node->successors[i]);
    }
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
        EvaluateMove(node);
        return node;
    }
    Move *moves = NextMoves(node->state);

    if (maximizingPlayer == node->state.current_player)
    {
        int bestValue = INT_MIN;
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
        int bestValue = INT_MAX;
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