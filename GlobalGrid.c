#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "LocalGrid.h"
#include "GAME.h"

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
    game.localboard[0][0].board[1][1] = 'X';

    game.localboard[0][1].board[0][0] = 'O';
    game.localboard[0][1].board[0][1] = 'O';
    game.localboard[0][1].board[0][2] = 'X';
    game.localboard[0][1].board[1][0] = 'X';
    game.localboard[0][1].board[1][1] = 'X';

    game.localboard[0][2].winner = 'O';
    game.localboard[0][2].board[1][1] = 'O';

    game.localboard[1][0].winner = 'O';
    game.localboard[1][0].board[1][1] = 'O';

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
    game.relative_grid = -1;
    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
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

int isGlobalGridFull(GlobalGrid game)
{
    // printf("isGlobalGridFull\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (game.localboard[i][j].winner == ' ' && !isLocalGridFull(&game.localboard[i][j]))
            {
                return 0; // Il y a une grille locale non pleine, donc la grille globale n'est pas pleine
            }
        }
    }
    return 1; // Toutes les grilles locales sont pleines, la grille globale est pleine
}

int game_CheckIfWon(GlobalGrid *game)
{
    // printf("game_CheckIfWon\n");
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
