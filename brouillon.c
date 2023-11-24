#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum player
{
    COMPUTER = 'O',
    HUMAN = 'X',
};
// Structure pour représenter une grille locale

typedef struct
{
    char board[3][3];
} LocalGrid;

// Structure pour représenter la grille globale
typedef struct
{
    LocalGrid localboard[3][3];
    char current_player;
} GlobaleGrid;

void initialize_local_grid(LocalGrid *grid)
{
    memset(grid->board, '-', sizeof(grid->board));
    // return *grid;
}

GlobaleGrid initialize_global_grid()
{
    GlobaleGrid game;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            initialize_local_grid(&game.localboard[i][j]);
        }
    }

    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}

// Structure pour représenter un coup
typedef struct
{
    int row;
    int col;
} play;

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

void display_game(GlobaleGrid *game)
{
    for (int i = 0; i < 3; i++)
    {
        if (i > 0) // Pour afficher une ligne de séparation entre les lignes de grilles
        {
            printf("+ - - - + - - - + - - - +\n");
        }

        for (int row = 0; row < 3; row++)
        {
            printf("| ");
            for (int j = 0; j < 3; j++)
            {
                for (int col = 0; col < 3; col++)
                {
                    printf("%c ", game->localboard[i][row].board[col][col]);
                }
                printf("| ");
            }
            printf("\n");
        }
    }
    printf("+ - - - + - - - + - - - +\n");
}

char LG_CheckIfWon(LocalGrid *grid)
{
    int i, j;
    char winner = ' ';

    // Vérification des lignes
    for (i = 0; i < 3; i++)
    {
        if (grid->board[i][0] == grid->board[i][1] &&
            grid->board[i][1] == grid->board[i][2] &&
            grid->board[i][0] != '_')
        {
            winner = grid->board[i][0];
            grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la ligne gagnante
            memset(grid->board, '_', sizeof(grid->board)); // Vider la grille locale
            return winner;
        }
    }

    // Vérification des colonnes
    for (i = 0; i < 3; i++)
    {
        if (grid->board[0][i] == grid->board[1][i] &&
            grid->board[1][i] == grid->board[2][i] &&
            grid->board[0][i] != '_')
        {
            winner = grid->board[0][i];
            grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la colonne gagnante
            memset(grid->board, '_', sizeof(grid->board)); // Vider la grille locale

            return winner;
        }
    }

    // Vérification des diagonales
    if (grid->board[0][0] == grid->board[1][1] && grid->board[1][1] == grid->board[2][2] &&
        grid->board[0][0] != '_')
    {
        winner = grid->board[0][0];
        grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante
        memset(grid->board, '_', sizeof(grid->board)); // Vider la grille locale
        return winner;
    }

    if (grid->board[0][2] == grid->board[1][1] && grid->board[1][1] == grid->board[2][0] &&
        grid->board[0][2] != '_')
    {
        winner = grid->board[0][2];
        grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante
        memset(grid->board, '_', sizeof(grid->board)); // Vider la grille locale

        return winner;
    }

    return winner;
}

int isLocalGridFull(LocalGrid *grid)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid->board[i][j] == '_')
            {
                return 0; // Il y a une case vide, donc la grille n'est pas pleine
            }
        }
    }
    return 1; // Aucune case vide, la grille est pleine
}

int isGlobalGridFull(GlobaleGrid game)
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

char game_CheckIfWon(GlobaleGrid *game)
{
    int i, j;
    char winner = ' ';

    // Vérification des lignes
    for (i = 0; i < 3; i++)
    {
        if (game->localboard[i][0].board[1][1] == game->localboard[i][1].board[1][1] &&
            game->localboard[i][1].board[1][1] == game->localboard[i][2].board[1][1] &&
            game->localboard[i][0].board[1][1] != '_')
        {
            winner = game->localboard[i][0].board[1][1];
            // game->localboard[1][1].board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la ligne gagnante

            return winner;
        }
    }

    // Vérification des colonnes
    for (i = 0; i < 3; i++)
    {
        if (game->localboard[0][i].board[1][1] == game->localboard[1][i].board[1][1] &&
            game->localboard[1][i].board[1][1] == game->localboard[2][i].board[1][1] &&
            game->localboard[0][i].board[1][1] != '_')
        {
            winner = game->localboard[0][i].board[1][1];
            // game->localboard[1][1].board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la colonne gagnante

            return winner;
        }
    }

    // Vérification des diagonales
    if (game->localboard[0][0].board[1][1] == game->localboard[1][1].board[1][1] && game->localboard[1][1].board[1][1] == game->localboard[2][2].board[1][1] &&
        game->localboard[0][0].board[1][1] != '_')
    {
        winner = game->localboard[0][0].board[1][1];
        // game->localboard[1][1].board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante

        return winner;
    }

    if (game->localboard[0][2].board[1][1] == game->localboard[1][1].board[1][1] && game->localboard[1][1].board[1][1] == game->localboard[2][0].board[1][1] &&
        game->localboard[0][2].board[1][1] != '_')
    {
        winner = game->localboard[0][2].board[1][1];
        // game->localboard[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante

        return winner;
    }

    return winner;
}

void update_player(int *current_player)
{
    *current_player ^= COMPUTER ^ HUMAN;
}

int UTTT_GAME(GlobaleGrid game)
{
    display_game(&game);
}

int main()
{
    // LocalGrid grid = initialize_local_grid();    // Initialisation de la grille locale avec des tirets
    GlobaleGrid game = initialize_global_grid(); // Initialisation de la grille globale avec des tirets
    // display_local_grid(&grid); // Affichage de la grille locale
    UTTT_GAME(game);
    return 0;
}
