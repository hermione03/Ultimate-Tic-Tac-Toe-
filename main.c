#include "LocalGrid.h"
#include "GlobalGrid.h"
#include "GAME.h"
#include "AI.h"

int main()
{
    // Initialisation de la graine pour rand()
    srand(time(0));
    int depth = 3;
    GlobalGrid game = initialize_global_grid();

    while (1)
    {

        if (game_CheckIfWon(&game) || isGlobalGridFull(game))
        {
            Display_game(&game);
            break;
        }
        else
        {
            UTTT_GAME(&game, random_pick_move, alphaBeta_pick_move, depth);
        }
    }

    return 0;
}
