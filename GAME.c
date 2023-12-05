#include <stdio.h>
#include "LocalGrid.h"
#include "GlobalGrid.h"
#include "GAME.h"
#include "AI.h"


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


int UTTT_GAME(GlobalGrid *game) {
    Move *moves = NextMoves(*game);

    printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    Display_game(game);

    if (game->current_player == HUMAN) {
        int x, y, xg, yg;

        do {
            printf("Choisissez une case à jouer (x, y) : ");
            if (scanf("%d,%d", &x, &y) != 2) {
                printf("Entrée invalide. Veuillez entrer les coordonnées x et y séparées par une virgule (par exemple : 1,2).\n");
                while (getchar() != '\n');
            }
        } while (!possibleMove(game, x, y));

        xg = (y / 3) / 3;
        yg = (y / 3) % 3;

        if (isLocalGridFull(&game->localboard[x][y % 3]) || game->localboard[x][y % 3].winner != ' ') {
            printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre ! \n");
            game->relative_grid = -1;
        } else {
            game->relative_grid = y % 3 + x * 3;
        }

        if (game->relative_grid == -1) {
            printf("Grille relative = Choix libre \n");
        } else {
            printf("Grille relative = %d\n", game->relative_grid);
        }

        game->localboard[xg][yg].board[x][y % 3] = game->current_player;

        if (LG_CheckIfWon(&game->localboard[xg][yg])) {
            printf("Grille locale gagnée par : %s\n", playerToString(game->current_player));
        }

        updatePlayer(game);
    } else {
        printf("Mouvements disponibles :\n");
        for (int i = 0; moves->lst_moves[i] != NULL; i++) {
            printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
        }
        printf("\n");

        int depth = 3; // Set your desired depth for MiniMax

        Node* root = createNode(*game);
        int bestMove = MiniMax(root, depth, game->current_player);

        printf("Le meilleur mouvement suggéré par MiniMax est : (%d,%d)\n", moves->lst_moves[bestMove]->x, moves->lst_moves[bestMove]->y);

        int x = moves->lst_moves[bestMove]->x;
        int y = moves->lst_moves[bestMove]->y;

        int xg = (y / 3) / 3;
        int yg = (y / 3) % 3;

        if (isLocalGridFull(&game->localboard[x][y % 3]) || game->localboard[x][y % 3].winner != ' ') {
            printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre ! \n");
            game->relative_grid = -1;
        } else {
            game->relative_grid = y % 3 + x * 3;
        }

        if (game->relative_grid == -1) {
            printf("Grille relative = Choix libre \n");
        } else {
            printf("Grille relative = %d\n", game->relative_grid);
        }

        game->localboard[xg][yg].board[x][y % 3] = game->current_player;

        if (LG_CheckIfWon(&game->localboard[xg][yg])) {
            printf("Grille locale gagnée par : %s\n", playerToString(game->current_player));
        }

        updatePlayer(game);
    }

    // Clean up allocated memory for moves
    for (int i = 0; moves->lst_moves[i] != NULL; i++) {
        free(moves->lst_moves[i]);
    }
    free(moves->lst_moves);
    free(moves);

    return 1;
}