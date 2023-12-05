#include "LocalGrid.h"
#include "GlobalGrid.h"
#include "GAME.h"
#include "AI.h"


int main() {
    GlobalGrid game = initialize_global_grid();
    //Node* root = createNode(game);

    // Appliquer des mouvements à la grille (si nécessaire)

    while (1) {
        UTTT_GAME(&game); // Votre logique de jeu en boucle

        if (game_CheckIfWon(&game) || isGlobalGridFull(game)) {
            Display_game(&game);
            break;
        }
    }

    return 0;
}
