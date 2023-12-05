#include "Local_grid.h"
#include "Global_grid.h"
#include "GAME.h"


int main()
{
    // LocalGrid grid = initialize_local_grid();    // Initialisation de la grille locale avec des tirets
    GlobalGrid game = initialize_global_grid(); // Initialisation de la grille globale avec des tirets
    // display_local_grid(&grid); // Affichage de la grille locale
    game.current_player = HUMAN;
    // game.relative_grid = 1;
    while (1)
    {
        UTTT_GAME(&game);
        // count++;
        // if (count > 8)
        // {
        //     break;
        // }
        if (game_CheckIfWon(&game) || isGlobalGridFull(game))
        {
            Display_game(&game);
            break;
        }
    }

    return 0;
}