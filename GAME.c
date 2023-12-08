
#include "game.h"
#include "ai.h"

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
            // printf("Vous devez jouer dans la grille numero : %d\n", game->relative_grid);
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

int UTTT_GAME(GlobalGrid *game, Pos (*player1_pick_move)(), Pos (*player2_pick_move)(), int depth)
{
    Move *moves = NextMoves(*game);

    printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    Display_game(game);

    int x, y;
    Pos chosenMove;

    if (game->current_player == HUMAN)
    {
        if (player1_pick_move == minimax_pick_move || player1_pick_move == alphaBeta_pick_move)
        {
            chosenMove = player1_pick_move(game, depth); // Obtenir le mouvement du joueur 1
        }
        else
        {
            chosenMove = player1_pick_move(game); // Obtenir le mouvement du joueur 1
        }
    }
    else
    {
        if (player2_pick_move == minimax_pick_move || player2_pick_move == alphaBeta_pick_move)
        {
            chosenMove = player2_pick_move(game, depth); // Obtenir le mouvement du joueur 2
        }
        else
        {
            chosenMove = player2_pick_move(game); // Obtenir le mouvement du joueur 2
        }
    }

    x = chosenMove.x;
    y = chosenMove.y;

    int xg = (y / 3) / 3;
    int yg = (y / 3) % 3;
    // printf("NARMOOOOL LE CHOIX ETAIIIIIIIIT (%d,%d)\n", x, y);
    game->localboard[xg][yg].board[x][y % 3] = game->current_player;
    LG_CheckIfWon(&game->localboard[x][y % 3]);

    if (isLocalGridFull(&game->localboard[x][y % 3]) || game->localboard[x][y % 3].winner != ' ')
    {
        // printf("Grille etudiée : (%d,%d)\n", x, y % 3);
        // printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre !%d %d\n", isLocalGridFull(&game->localboard[x][y % 3]), LG_CheckIfWon(&game->localboard[x][y % 3]));
        game->relative_grid = -1;
    }
    else
    {
        // printf("***********Grille locale testée  : %d %d\n", x, y % 3);
        // printf("***********Winner : %c\n", game->localboard[x][y % 3].winner);
        // printf("ALORS PPK PAS : Grille relative pleine ou déjà gagnée, le prochain coup est libre !%d %d\n", isLocalGridFull(&game->localboard[x][y % 3]), LG_CheckIfWon(&game->localboard[x][y % 3]));
        game->relative_grid = y % 3 + x * 3;
        // printf("relaaaaaative : %d\n", game->relative_grid);
    }

    if (game->relative_grid == -1)
    {
        printf("Grille relative = Choix libre \n");
    }
    else
    {
        printf("Grille relative = %d\n", game->relative_grid);
    }

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