#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "players/HEADERS/alphabeta.h"
#include "players/HEADERS/minimax.h"
#include "players/HEADERS/random.h"
int main()
{
    int i = 2;
    // Initialisation de la graine pour rand()
    srand(time(0));
    int depth = 3;
    GlobalGrid game = initialize_global_grid();

    // while (1)
    // {

    //     if (is_game_won(&game) || is_global_grid_full(game))
    //     {
    //         Display_game(&game);
    //         break;
    //     }
    //     else
    //     {
    //         UTTT_GAME(&game, random_pick_move, alphaBeta_pick_move, depth);
    //     }
    // }
    while (i > 0)
    {
        UTTT_GAME(&game, random_pick_move, minimax_pick_move, depth);
        i--;
    }

    return 0;
}
