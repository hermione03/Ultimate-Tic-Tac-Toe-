#ifndef GLOBAL_GRID_H
#define GLOBAL_GRID_H

// Structure pour représenter la grille globale
typedef struct
{
    LocalGrid localboard[3][3];
    char current_player;
    char relative_grid;
    char winner;
} GlobalGrid;

// Prototypes de fonctions
GlobalGrid initialize_global_grid();
GlobalGrid test_initialize_global_grid(); // fonction de test
void Display_game(GlobalGrid *game);
int is_global_grid_full(GlobalGrid game);
int is_game_won(GlobalGrid *game);

#endif /* GLOBAL_GRID_H */
