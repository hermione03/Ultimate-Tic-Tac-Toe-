#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

enum player
{
    COMPUTER = 'O',
    HUMAN = 'X',
};

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
    GlobalGrid state;
    int value;
    int num_successors;
    int capacity;
    struct Node **successors;
};
typedef struct Node Node;

char *playerToString(enum player p)
{
    switch (p)
    {
    case COMPUTER:
        return "COMPUTER";
    case HUMAN:
        return "HUMAN";
    default:
        return "UNKNOWN";
    }
}

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
    game.current_player = HUMAN;
    game.winner = ' ';
    game.relative_grid = 2;
    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}

GlobalGrid test_initialize_global_grid()
{
    GlobalGrid game;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            initialize_local_grid(&game.localboard[i][j]);
        }
    }
    game.localboard[0][0].winner = 'X';

    game.localboard[0][1].board[0][0] = 'O';
    game.localboard[0][1].board[0][1] = 'O';
    game.localboard[0][1].board[0][2] = 'X';
    game.localboard[0][1].board[1][0] = 'X';
    game.localboard[0][1].board[1][1] = 'X';

    game.localboard[0][2].winner = 'O';

    game.localboard[1][0].winner = 'O';

    game.localboard[1][1].board[0][0] = 'O';
    game.localboard[1][1].board[0][1] = 'X';
    game.localboard[1][1].board[0][2] = 'O';
    game.localboard[1][1].board[1][0] = 'O';

    game.localboard[1][2].board[0][2] = 'X';

    // game.localboard[2][0].board[1][1] = 'O';
    // game.localboard[2][0].winner = 'O';

    game.localboard[2][0].board[0][0] = 'O';

    game.localboard[2][2].board[0][0] = 'O';

    game.current_player = HUMAN;
    game.winner = ' ';
    game.relative_grid = 2;
    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}

void display_local_grid(LocalGrid *grid)
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", grid->board[i][j]);
        }
        printf("\n");
    }
    printf("******************************");
}

void Display_game(GlobalGrid *game)
{
    int global, acc = 0;
    char str[256];
    printf("╔══════════════════════╦══════════════════════╦══════════════════════╗\n");
    for (int i = 0; i < 3; i++)
    {
        if (i > 0)
        {
            printf("╠══════════════════════╬══════════════════════╬══════════════════════╣\n");
        }
        for (int row = 0; row < 3; row++)
        {
            printf("║ ");
            for (int j = 0; j < 3; j++)
            {

                global = i + j + acc;

                for (int col = 0; col < 3; col++)
                {

                    if (game->localboard[i][j].winner != ' ')
                    {
                        printf(game->localboard[i][j].winner == 'O' ? "  \033[34m%c\033[0m    " : "  \033[35m%c\033[0m    ", game->localboard[i][j].board[row][col]);
                    }
                    else if (game->localboard[i][j].board[row][col] == '-')
                    {
                        sprintf(str, "(%d,%d)", row, col + (global * 3));
                        printf("%-6s ", str);
                    }
                    else
                    {
                        printf(game->localboard[i][j].board[row][col] == 'O' ? "  \033[34m%c\033[0m    " : "  \033[35m%c\033[0m    ", game->localboard[i][j].board[row][col]);
                    }
                }
                printf("║ ");
            }

            printf("\n");
        }
        acc += 2;
    }
    printf("╚══════════════════════╩══════════════════════╩══════════════════════╝\n");
    printf("\n");
}

int LG_CheckIfWon(LocalGrid *grid)
{
    int i;

    // Vérification des lignes
    for (i = 0; i < 3; i++)
    {
        if (grid->board[i][0] == grid->board[i][1] &&
            grid->board[i][1] == grid->board[i][2] &&
            grid->board[i][0] != '-')
        {
            grid->winner = grid->board[i][0];
            memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
            grid->board[1][1] = grid->winner;              // Placer le symbole du gagnant au milieu
            // printf("\nelle est gagnééééé\n\n ! ");
            return 1;
        }
    }

    // Vérification des colonnes
    for (i = 0; i < 3; i++)
    {
        if (grid->board[0][i] == grid->board[1][i] &&
            grid->board[1][i] == grid->board[2][i] &&
            grid->board[0][i] != '-')
        {
            grid->winner = grid->board[0][i];
            memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
            grid->board[1][1] = grid->winner;              // Placer le symbole du gagnant au milieu
            // printf("\nelle est gagnééééé\n\n ! ");
            return 1;
        }
    }

    // Vérification des diagonales
    if (grid->board[0][0] == grid->board[1][1] && grid->board[1][1] == grid->board[2][2] &&
        grid->board[0][0] != '-')
    {
        grid->winner = grid->board[0][0];
        memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
        grid->board[1][1] = grid->winner;              // Placer le symbole du gagnant au milieu
        // printf("\nelle est gagnééééé\n\n ! ");
        return 1;
    }

    if (grid->board[0][2] == grid->board[1][1] && grid->board[1][1] == grid->board[2][0] &&
        grid->board[0][2] != '-')
    {
        grid->winner = grid->board[0][2];
        memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
        grid->board[1][1] = grid->winner;              // Placer le symbole du gagnant au milieu
        // printf("\nelle est gagnééééé\n\n ! ");
        return 1;
    }

    return 0;
}

int isLocalGridFull(LocalGrid *grid)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid->board[i][j] == '-')
            {
                // printf("elle n'est pas plaine !\n ");
                return 0; // Il y a une case vide, donc la grille n'est pas pleine
            }
        }
    }

    return 1; // Aucune case vide, la grille est pleine
}

int isGlobalGridFull(GlobalGrid game)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isLocalGridFull(&game.localboard[i][j]) == 0)
            {
                return 0; // Il y a une grille locale non pleine, donc la grille globale n'est pas pleine
            }
        }
    }
    return 1; // Toutes les grilles locales sont pleines, la grille globale est pleine
}
int game_CheckIfWon(GlobalGrid *game)
{
    int i;

    // Vérification des lignes de grilles globales
    for (i = 0; i < 3; i++)
    {
        if (game->localboard[i][0].winner == game->localboard[i][1].winner &&
            game->localboard[i][1].winner == game->localboard[i][2].winner &&
            game->localboard[i][0].winner != ' ')
        {
            game->winner = game->localboard[i][0].winner;
            printf(" %s a gagné(e) !\n", playerToString(game->winner));
            return 1;
        }
    }

    // Vérification des colonnes de grilles globales
    for (i = 0; i < 3; i++)
    {
        if (game->localboard[0][i].winner == game->localboard[1][i].winner &&
            game->localboard[1][i].winner == game->localboard[2][i].winner &&
            game->localboard[0][i].winner != ' ')
        {
            game->winner = game->localboard[0][i].winner;
            printf(" %s a gagné(e) !\n", playerToString(game->winner));
            return 1;
        }
    }

    // Vérification des diagonales de grilles globales
    if (game->localboard[0][0].winner == game->localboard[1][1].winner &&
        game->localboard[1][1].winner == game->localboard[2][2].winner &&
        game->localboard[0][0].winner != ' ')
    {
        game->winner = game->localboard[0][0].winner;
        printf(" %s a gagné(e) !\n", playerToString(game->winner));
        return 1;
    }

    if (game->localboard[0][2].winner == game->localboard[1][1].winner &&
        game->localboard[1][1].winner == game->localboard[2][0].winner &&
        game->localboard[0][2].winner != ' ')
    {
        game->winner = game->localboard[0][2].winner;
        printf(" %s a gagné(e) !\n", playerToString(game->winner));
        return 1;
    }

    return 0;
}

void updatePlayer(GlobalGrid *game)
{
    game->current_player ^= COMPUTER ^ HUMAN;
}

int possibleMove(GlobalGrid *game, int x, int y)
{
    int xg, yg, g;

    // verifier si c dans la grille globale d'abord
    if (x > 2 || y > 26)
    {
        printf("Position invalide : en dehors de la grille globale !\n");
        return 0;
    }
    else
    {
        xg = (y / 3) / 3;
        yg = (y / 3) % 3;
        g = yg + xg * 3;
        // printf("grille actuelle  = %d\n", g);
        // printf("grille relative : %d\n", game->relative_grid);
        // printf("AHHHHHHHHHHHH %c, %d, %d\n", game->localboard[xg][yg].board[x][y % 3], x, y);
        if (game->relative_grid != g && game->relative_grid > -1)
        {
            // printf("Vous n'avez pas le droit de jouer dans cette grille Locale !\n");
            // printf("Vous devez jouer dans la grille numero : %d\n",game->relative_grid);
            return 0;
        }
        if (game->localboard[xg][yg].board[x][y % 3] == '-' && game->localboard[xg][yg].winner != ' ')
        {
            // printf("Cette grille locale est déjà gagnée !\n");
            return 0;
        }
        // printf("grille plaine ou deja gagnée");
        // return 0;
        if (game->localboard[xg][yg].board[x][y % 3] != '-')
        {
            // printf("Cette case est deja prise !\n");
            return 0;
        }
    }
    return 1;
}

//********************************** AI ********************************************************************
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
    xg = (pos.y / 27);       // Récupère la grille globale à mettre à jour
    yg = ((pos.y % 27) / 3); // Récupère la position de la localboard dans la grille globale
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

int MiniMax(Node *node, int depth, int maximizingPlayer)
{
    if (depth == 0 || game_CheckIfWon(&node->state) || isGlobalGridFull(node->state))
    {
        EvaluateMove(node);
        return node->value;
    }
    Move *moves = NextMoves(node->state);

    if (maximizingPlayer == node->state.current_player)
    {
        int bestValue = INT_MIN;
        for (int i = 0; i < moves->num_moves; i++)
        {
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]));
            addSuccessor(node, child);
            int value = MiniMax(child, depth - 1, !maximizingPlayer);
            node->value = bestValue;
            bestValue = max(bestValue, value);
        }
        return bestValue;
    }
    else
    {
        int bestValue = INT_MAX;
        for (int i = 0; i < moves->num_moves; i++)
        {
            Node *child = createNode(ApplyMove(node->state, *moves->lst_moves[i]));
            addSuccessor(node, child);
            int value = MiniMax(child, depth - 1, !maximizingPlayer);
            node->value = bestValue;
            bestValue = min(bestValue, value);
        }
        return bestValue;
    }
}

Pos random_pick_move(GlobalGrid *game)
{
    Pos pos;
    Move *moves = NextMoves(*game);
    printf("Mouvements disponibles :\n");
    for (int i = 0; moves->lst_moves[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
    }
    printf("\n");

    // Initialisation de la graine pour rand()
    srand(time(0));

    // Générer un indice aléatoire dans la liste des mouvements disponibles
    int random_index = rand() % moves->num_moves;

    int x = moves->lst_moves[random_index]->x;
    int y = moves->lst_moves[random_index]->y;

    pos.x = x;
    pos.y = y;

    return pos;
}

Pos human_pick_move(GlobalGrid *game)
{
    Pos pos;
    do
    {

        printf("Choisissez une case à jouer (x, y) : ");
        // Si la case sélectionnée n'est pas valide:
        if (scanf("%d,%d", &pos.x, &pos.y) != 2)
        {

            // Afficher un message d'erreur
            printf("Entrée invalide. Veuillez entrer les coordonnées x et y séparées par une virgule (par exemple : 1,2).\n");
            // Vider le tampon d'entrée
            while (getchar() != '\n')
                ;
        }
    } while (!possibleMove(game, pos.x, pos.y));
    return pos;
}
Pos minimax_pick_move(GlobalGrid *game)
{
    Pos pos;
    Move *moves = NextMoves(*game);
    printf("Mouvements disponibles :\n");
    for (int i = 0; moves->lst_moves[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
    }
    printf("\n");

    int depth = 3; // Set your desired depth for MiniMax

    Node *root = createNode(*game);
    int bestMove = MiniMax(root, depth, game->current_player);

    printf("Le meilleur mouvement suggéré par MiniMax est : (%d,%d)\n", moves->lst_moves[bestMove]->x, moves->lst_moves[bestMove]->y);

    int x = moves->lst_moves[bestMove]->x;
    int y = moves->lst_moves[bestMove]->y;

    pos.x = x;
    pos.y = y;

    return pos;
}

int UTTT_GAME(GlobalGrid *game, Pos (*player1_pick_move)(), Pos (*player2_pick_move)())
{
    Move *moves = NextMoves(*game);

    printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    Display_game(game);

    int x, y;
    Pos chosenMove;

    if (game->current_player == HUMAN)
    {
        chosenMove = player1_pick_move(game); // Obtenir le mouvement du joueur 1
    }
    else
    {
        chosenMove = player2_pick_move(game); // Obtenir le mouvement du joueur 2
    }

    x = chosenMove.x;
    y = chosenMove.y;

    int xg = (y / 3) / 3;
    int yg = (y / 3) % 3;

    if (isLocalGridFull(&game->localboard[x][y % 3]) || game->localboard[x][y % 3].winner != ' ')
    {
        printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre ! \n");
        game->relative_grid = -1;
    }
    else
    {
        game->relative_grid = y % 3 + x * 3;
    }

    if (game->relative_grid == -1)
    {
        printf("Grille relative = Choix libre \n");
    }
    else
    {
        printf("Grille relative = %d\n", game->relative_grid);
    }

    game->localboard[xg][yg].board[x][y % 3] = game->current_player;

    if (LG_CheckIfWon(&game->localboard[xg][yg]))
    {
        printf("Grille locale gagnée par : %s\n", playerToString(game->current_player));
    }

    updatePlayer(game);

    // Nettoyage de la mémoire allouée pour les mouvements
    for (int i = 0; moves->lst_moves[i] != NULL; i++)
    {
        free(moves->lst_moves[i]);
    }
    free(moves->lst_moves);
    free(moves);

    return 1;
}

//********************************** AI ********************************************************************

int main()
{
    GlobalGrid game = initialize_global_grid();

    while (1)
    {
        UTTT_GAME(&game, random_pick_move, minimax_pick_move);

        if (game_CheckIfWon(&game) || isGlobalGridFull(game))
        {
            Display_game(&game);
            break;
        }
    }

    return 0;
}
