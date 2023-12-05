#include "LocalGrid.h"
#include "GlobalGrid.h"
#include "GAME.h"
#include "AI.h"


int main() {
    GlobalGrid game = initialize_global_grid();

    while (1) {
        UTTT_GAME(&game, random_pick_move, minimax_pick_move);

        if (game_CheckIfWon(&game) || isGlobalGridFull(game)) {
            Display_game(&game);
            break;
        }
    }

    return 0;
}
