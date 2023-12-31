#include <stdlib.h>
#include "ai.h"

Node *create_node(GlobalGrid game, Pos pos)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode)
    {
        newNode->value = 0;
        newNode->state = game;
        newNode->num_successors = 0;
        newNode->capacity = 0;
        newNode->successors = NULL;
        newNode->lastpos = pos;
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

int evaluateLG(LocalGrid *lcState)
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

    evaluation -= check_win_condition(lcState) * 12;

    return evaluation;
}

// int evaluateLG(LocalGrid *lcState) {
//     int evaluation = 0;
//     int poids[] = {0.2, 0.17, 0.2, 0.17, 0.22, 0.17, 0.2, 0.17, 0.2};

//     // Calcul de l'évaluation basée sur les valeurs du tableau et des poids
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             evaluation -= giveValue(lcState->board[i][j]) * poids[i * 3 + j];
//         }
//     }

//     // Tableau de combinaisons pour les conditions de victoire
//     int lines[8][3] = {
//         {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // lignes
//         {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // colonnes
//         {0, 4, 8}, {2, 4, 6}             // diagonales
//     };

//     // Vérification des conditions de victoire pour différentes valeurs
//     int values[] = {2, -1, -2, 1};
//     int points[] = {6, 9, -6, -9};

//     for (int k = 0; k < 4; k++) {
//         for (int i = 0; i < 8; i++) {
//             int sum = 0;
//             for (int j = 0; j < 3; j++) {
//                 sum += giveValue(lcState->board[lines[i][j] / 3][lines[i][j] % 3]);
//             }
//             if (sum == values[k] * 3) {
//                 evaluation += points[k];
//             }
//         }
//     }

//     // Réduction de l'évaluation si une condition de victoire est remplie
//     evaluation -= check_win_condition(lcState) * 12;

//     return evaluation;
// }

// Fonction de test
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

void add_successor(Node *node, Node *successor)
{
    if (node->num_successors >= node->capacity)
    {
        node->capacity = (node->capacity == 0) ? 1 : node->capacity + 1;
        node->successors = realloc(node->successors, node->capacity * sizeof(Node *));
        if (node->successors == NULL)
        {
            printf("Allocation mémoire échouée pour les successeurs.\n");
            exit(1);
        }
    }
    node->successors[node->num_successors++] = successor;
}

void display_node(Node *node)
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

void display_tree(Node *node)
{
    printf("--------------- Tree ------------------------\n");
    if (node == NULL)
    {
        return;
    }

    display_node(node);

    for (int i = 0; i < node->num_successors; i++)
    {
        display_tree(node->successors[i]);
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
