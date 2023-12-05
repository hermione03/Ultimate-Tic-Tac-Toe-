<<<<<<< HEAD
#include "Local_grid.h"
#include "Global_grid.h"
#include "GAME.h"
#include "AI.h"


int main() {
    GlobalGrid game = initialize_global_grid();
    Node* root = createNode(game);

    // Appliquer des mouvements à la grille (si nécessaire)

    while (1) {
        UTTT_GAME(&game); // Votre logique de jeu en boucle

        if (game_CheckIfWon(&game) || isGlobalGridFull(game)) {
            debug_display_game(&game);
            break;
        }

        Move **moves = NextMoves(game);
        printf("Mouvements disponibles :\n");
        for (int i = 0; moves[i] != NULL; i++) {
            printf("(%d,%d) ", moves[i]->x, moves[i]->y);
        }
        printf("\n");

        // Appliquer MiniMax pour évaluer le meilleur mouvement à faire
        int depth = 3; // Profondeur maximale pour l'algorithme MiniMax
        int bestMove = MiniMax(root, depth, 0); // Remplacez HUMAN par le joueur qui doit jouer ensuite

        // Ici, vous avez le meilleur mouvement calculé par MiniMax dans la variable bestMove
        printf("Le meilleur mouvement suggéré par MiniMax est : (%d,%d)\n", moves[bestMove]->x, moves[bestMove]->y);

        // Libérer la mémoire des mouvements
        for (int i = 0; moves[i] != NULL; i++) {
            free(moves[i]);
        }
        free(moves);
    }

    return 0;
}
=======
#include "Local_grid.h"
#include "Global_grid.h"
#include "GAME.h"
#include "AI.h"


int main() {
    GlobalGrid game = initialize_global_grid();
    Node* root = createNode(game);

    // Appliquer des mouvements à la grille (si nécessaire)

    while (1) {
        UTTT_GAME(&game); // Votre logique de jeu en boucle

        if (game_CheckIfWon(&game) || isGlobalGridFull(game)) {
            Display_game(&game);
            break;
        }

        Move **moves = NextMoves(game);
        printf("Mouvements disponibles :\n");
        for (int i = 0; moves[i] != NULL; i++) {
            printf("(%d,%d) ", moves[i]->x, moves[i]->y);
        }
        printf("\n");

        // Appliquer MiniMax pour évaluer le meilleur mouvement à faire
        int depth = 3; // Profondeur maximale pour l'algorithme MiniMax
        int bestMove = MiniMax(root, depth, 0); // Remplacez HUMAN par le joueur qui doit jouer ensuite

        // Ici, vous avez le meilleur mouvement calculé par MiniMax dans la variable bestMove
        printf("Le meilleur mouvement suggéré par MiniMax est : (%d,%d)\n", moves[bestMove]->x, moves[bestMove]->y);

        // Libérer la mémoire des mouvements
        for (int i = 0; moves[i] != NULL; i++) {
            free(moves[i]);
        }
        free(moves);
    }

    return 0;
}
>>>>>>> 05394a0 (✨ Startin AI)
