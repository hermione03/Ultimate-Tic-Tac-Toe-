#include <stdlib.h>
#include "../HEADERS/random.h"
Pos random_pick_move(GlobalGrid *game)
{
    Pos pos;
    PosList *moves = get_possible_moves(*game);
    // printf("%c HEEEEERE ON RANDOM !!\n", game->current_player);
    printf("Mouvements disponibles :\n");
    for (int i = 0; moves->positions[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->positions[i]->x, moves->positions[i]->y);
    }
    printf("\n");

    // Générer un indice aléatoire dans la liste des mouvements disponibles
    int random_index = rand() % moves->num_moves;

    int x = moves->positions[random_index]->x;
    int y = moves->positions[random_index]->y;

    pos.x = x;
    pos.y = y;

    return pos;
}

Pos human_pick_move(GlobalGrid *game)
{
    // printf("%c HEEEEERE ON HUMAN !!\n", game->current_player);
    Pos pos;
    do
    {

        printf("Choisissez une case à jouer (x, y) : ");
        // Si la case sélectionnée n'est pas valide:
        if (scanf("%d,%d", &pos.x, &pos.y) != 2)
        {

            // Afficher un message d'erreur
            printf("Entrée invalide. Veuillez entrer les coordonnées x et y séparées par une virgule (par exemple : 1,2).\n");
            // Vider le tampon d'entrée
            while (getchar() != '\n')
                ;
        }
    } while (!is_move_possible(game, pos.x, pos.y));
    return pos;
}