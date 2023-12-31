#include <stdlib.h>
#include "../HEADERS/random.h"
#include <assert.h>

Pos random_pick_move(GlobalGrid *game)
{
    PosList *moves = get_possible_moves(*game);
    assert(moves->length > 0);
    // printf("Mouvements disponibles :\n");
    //  for (int i = 0; moves->lst_moves[i] != NULL; i++)
    //  {
    //      printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
    //  }
    //  printf("\n");

    // Générer un indice aléatoire dans la liste des mouvements disponibles
    int random_index = rand() % moves->length;

    Pos pos;
    pos.x = moves->positions[random_index]->x;
    pos.y = moves->positions[random_index]->y;

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