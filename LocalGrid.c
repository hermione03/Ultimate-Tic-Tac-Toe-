

#include <string.h>
#include <stdio.h>

#include "LocalGrid.h"

void initialize_local_grid(LocalGrid *grid)
{
    memset(grid->board, '-', sizeof(grid->board));
    grid->winner = ' ';
    // return *grid;
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
                return 0; // Il y a une case vide, donc la grille n'est pas pleine
            }
        }
    }

    return 1; // Aucune case vide, la grille est pleine
}




