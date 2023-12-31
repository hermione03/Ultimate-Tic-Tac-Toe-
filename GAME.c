#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "ai.h"

char *get_player_name(enum player p)
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

void update_player(GlobalGrid *game)
{
    game->current_player ^= COMPUTER ^ HUMAN;
}

int is_move_possible(GlobalGrid *game, int x, int y)
{
    int xg, yg, g;

    // verifier si c dans la grille globale d'abord
    if (x > 2 || y > 26)
    {
        printf("Position invalide : en dehors de la grille globale !\n");
        return 0;
    }

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
    if (game->localboard[xg][yg].winner != ' ')
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

    return 1;
}

int check_win_condition(LocalGrid *lcState)
{
    is_LG_won(lcState);
    if (lcState->winner == COMPUTER)
    {
        return -1;
    }
    else if (lcState->winner == HUMAN)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
GlobalGrid apply_move(GlobalGrid game, Pos pos)
{
    int xg, yg;
    GlobalGrid next = game;
    xg = (pos.y / 3) / 3; // Récupère la grille globale à mettre à jour
    yg = (pos.y / 3) % 3; // Récupère la position de la localboard dans la grille globale
    int x = pos.x;
    int y = (pos.y % 3);
    // printf("APPLYYYYYY LE CHOIX ETAIIIIIIIIT (%d,%d)\n", x, y);
    next.localboard[xg][yg].board[x][y] = game.current_player;
    is_LG_won(&next.localboard[x][y % 3]);

    if (is_local_grid_full(&next.localboard[x][y % 3]) || next.localboard[x][y % 3].winner != ' ')
    {
        // printf("Grille etudiée : (%d,%d)\n", x, y % 3);
        // printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre !%d %d\n", is_local_grid_full(next.localboard[x][y % 3]), is_LG_won(next.localboard[x][y % 3]));
        next.relative_grid = -1;
    }
    else
    {
        // printf("***********Grille locale testée  : %d %d\n", x, y % 3);
        // printf("***********Winner : %c\n", next.localboard[x][y % 3].winner);
        // printf("ALORS PPK PAS : Grille relative pleine ou déjà gagnée, le prochain coup est libre !%d %d\n", is_local_grid_full(next.localboard[x][y % 3]), is_LG_won(&next.localboard[x][y % 3]));
        next.relative_grid = y % 3 + x * 3;
        // printf("relaaaaaative : %d\n", next->relative_grid);
    }
    // Display_game(&next);
    update_player(&next);
    return next;
}

PosList *get_possible_moves(GlobalGrid game)
{
    int x, y;
    PosList *moves = (PosList *)malloc(sizeof(*moves));
    moves->positions = NULL;
    moves->length = 0;

    if (moves == NULL)
    {
        printf("Memory allocation failed for moves.\n");
        return NULL;
    }

    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 27; y++)
        {
            if (is_move_possible(&game, x, y))
            {
                moves->length++;

                moves->positions = (Pos **)realloc(moves->positions, moves->length * sizeof(*moves->positions));
                if (moves->positions == NULL)
                {
                    printf("Memory reallocation failed for moves->lst_moves.\n");
                    return NULL;
                }

                moves->positions[moves->length - 1] = (Pos *)malloc(sizeof(Pos));
                if (moves->positions[moves->length - 1] == NULL)
                {
                    printf("Memory allocation failed for moves->lst_moves[%d].\n", moves->length - 1);
                    return NULL;
                }

                moves->positions[moves->length - 1]->x = x;
                moves->positions[moves->length - 1]->y = y;
            }
        }
    }

    return moves;
}

Pos human_pick_move(GlobalGrid *game)
{
    Pos pos;
    do
    {

        if (verbose)
            printf("Choisissez une case à jouer (x, y) : ");
        // Si la case sélectionnée n'est pas valide:
        if (scanf("%d,%d", &pos.x, &pos.y) != 2)
        {

            // Afficher un message d'erreur
            if (verbose)
                printf("Entrée invalide. Veuillez entrer les coordonnées x et y séparées par une virgule (par exemple : 1,2).\n");
            // Vider le tampon d'entrée
            while (getchar() != '\n')
                ;
        }
    } while (!is_move_possible(game, pos.x, pos.y));
    return pos;
}

int UTTT_GAME(GlobalGrid *game, Pos (*player1_pick_move)(), Pos (*player2_pick_move)(), int depth)
{

    printf("Tour de %s de placer un %c \n", get_player_name(game->current_player), game->current_player);
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
    is_LG_won(&game->localboard[x][y % 3]);

    if (is_local_grid_full(&game->localboard[x][y % 3]) || game->localboard[x][y % 3].winner != ' ')
    {
        // printf("Grille etudiée : (%d,%d)\n", x, y % 3);
        // printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre !%d %d\n", is_local_grid_full(&game->localboard[x][y % 3]), is_LG_won(&game->localboard[x][y % 3]));
        game->relative_grid = -1;
    }
    else
    {
        // printf("***********Grille locale testée  : %d %d\n", x, y % 3);
        // printf("***********Winner : %c\n", game->localboard[x][y % 3].winner);
        // printf("ALORS PPK PAS : Grille relative pleine ou déjà gagnée, le prochain coup est libre !%d %d\n", is_local_grid_full(&game->localboard[x][y % 3]), is_LG_won(&game->localboard[x][y % 3]));
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

    if (is_LG_won(&game->localboard[xg][yg]))
    {
        printf("Grille locale gagnée par : %s\n", get_player_name(game->current_player));
    }

    update_player(game);

    return 1;
}

int is_game_over(GlobalGrid *game)
{
    return is_game_won(game) || is_global_grid_full(*game);
}