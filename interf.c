#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter une grille locale

typedef struct
{
    char board[3][3];
    char winner;
} LocalGrid;

// Structure pour représenter la grille globale
typedef struct
{
    LocalGrid localboard[3][3];
    char current_player;
    char relative_grid;
    char winner;
} GlobalGrid;



struct Node
{
    GlobalGrid game;
    int val;
    int num_successors;
    int capacity;
    struct Node** successors;
};
typedef struct Node Node ;

void initialize_local_grid(LocalGrid *grid)
{
    memset(grid->board, '-', sizeof(grid->board));
    grid->winner = ' ';
    // return *grid;
}

GlobalGrid initialize_global_grid()
{
    GlobalGrid game;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            initialize_local_grid(&game.localboard[i][j]);
        }
    }
    game.localboard[1][1].board[1][1] = 'X';
    game.localboard[0][1].board[0][0] = 'X';
    game.localboard[0][1].board[0][1] = 'X';
    game.localboard[2][1].board[0][1] = 'O';
    game.localboard[2][1].board[2][1] = 'O';
    game.localboard[2][2].board[0][2] = 'O';
    game.localboard[2][0].board[0][1] = 'O';
    game.localboard[2][0].board[0][2] = 'O';
    game.winner = ' ';
    game.relative_grid = -1;
    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}
GlobalGrid initialize_global_grid2()
{
    GlobalGrid game;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            initialize_local_grid(&game.localboard[i][j]);
        }
    }
    game.localboard[1][1].board[1][1] = '0';
    game.localboard[0][1].board[0][0] = '0';
    game.localboard[0][1].board[0][1] = 'X';
    game.localboard[2][1].board[0][1] = 'O';
    game.localboard[2][1].board[2][1] = 'O';
    game.localboard[2][2].board[0][2] = 'X';
    game.localboard[2][0].board[0][1] = 'X';
    game.localboard[2][0].board[0][2] = 'X';
    game.localboard[1][1].board[0][2] = 'X';
    game.localboard[0][0].board[0][2] = 'X';
    game.winner = ' ';
    game.relative_grid = -1;
    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}
GlobalGrid initialize_global_grid3()
{
    GlobalGrid game;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            initialize_local_grid(&game.localboard[i][j]);
        }
    }
    game.localboard[1][1].board[1][1] = '0';
    game.localboard[0][1].board[0][0] = '0';
    game.localboard[0][1].board[0][1] = 'X';
    game.localboard[1][1].board[0][2] = 'X';
    game.localboard[0][0].board[0][2] = 'X';
    game.winner = ' ';
    game.relative_grid = -1;
    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}

void Display_game(GlobalGrid *game)
{
    int global, acc = 0;
    char str[256];
    for (int i = 0; i < 3; i++)
    {
        if (i > 0)
        {
            printf("___________________________| |__________________________| |__________________________| |\n");
        }
        for (int row = 0; row < 3; row++)
        {
            printf("| ");
            for (int j = 0; j < 3; j++)
            {

                global = i + j + acc;

                for (int col = 0; col < 3; col++)
                {

                    if (game->localboard[i][j].winner == ' ')
                    {
                        if (game->localboard[i][j].board[row][col] == '-')
                        {
                            sprintf(str, "(%d,%d)", row, col + (global * 3));
                            printf("%-6s | ", str);
                        }
                        else
                        {
                            printf(game->localboard[i][j].board[row][col] == 'O' ? "  \033[34m%c\033[0m    | " : "  \033[35m%c\033[0m    | ", game->localboard[i][j].board[row][col]);
                        }
                    }
                    else
                    {
                        printf(game->localboard[i][j].winner == 'O' ? "  \033[34m%c\033[0m    | " : "  \033[35m%c\033[0m    | ", game->localboard[i][j].board[row][col]);
                    }
                }
                printf("| ");
            }

            printf("\n");
        }
        acc += 2;
    }
    printf("\n");
}


Node* createNode(GlobalGrid game) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->val = 0;
        newNode->game = game;
        newNode->num_successors = 0;
        newNode->capacity = 0;
        newNode->successors = NULL;
    }
    return newNode;
}

void addSuccessor(Node* node, Node* successor) {
    if (node->num_successors >= node->capacity) {
        node->capacity = (node->capacity == 0) ? 1 : node->capacity * 2;
        node->successors = realloc(node->successors, node->capacity * sizeof(Node*));
        if (node->successors == NULL) {
            printf("Allocation mémoire échouée pour les successeurs.\n");
            exit(1);
        }
    }
    node->successors[node->num_successors++] = successor;
}

void displayNode(Node* node) {
    printf("Node details here...\n");

    Display_game(&node->game);

    printf("Node Successors: ");
    for (int i = 0; i < node->num_successors; i++) {
        printf("Successor %d, ", i + 1);
    }
    printf("\n");
}

void displayTree(Node* node) {
    if (node == NULL) {
        return;
    }

    displayNode(node);

    for (int i = 0; i < node->num_successors; i++) {
        displayTree(node->successors[i]);
    }
}


void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->num_successors; i++) {
        freeTree(root->successors[i]); // Appel récursif pour libérer les enfants
    }

    free(root->successors); // Libération du tableau de successeurs
    free(root); // Libération du nœud actuel
}


int main() {
     // Initialize the global grid
    GlobalGrid game = initialize_global_grid();
    GlobalGrid game2 = initialize_global_grid2();
    GlobalGrid game3 = initialize_global_grid3();
    Node* root = createNode(game);

    Node* child1 = createNode(game2);
    Node* child2 = createNode(game3);
    addSuccessor(root, child1);
    addSuccessor(root, child2);

    // Add more successors if needed
    // ...

    displayTree(root);

    free(root);

    return 0;
}
