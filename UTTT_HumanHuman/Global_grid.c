#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Local_grid.h"
// #include "GAME.h"

// Structure pour représenter la grille globale
typedef struct
{
    LocalGrid localboard[3][3];
    char current_player;
    char relative_grid;
    char winner;
} GlobalGrid;


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


