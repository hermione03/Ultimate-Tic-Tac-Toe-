<<<<<<< HEAD
#ifndef GLOBAL_GRID_H
#define GLOBAL_GRID_H





// Structure pour représenter la grille globale
typedef struct {
    LocalGrid localboard[3][3];
    char current_player;
    char relative_grid;
    char winner;
} GlobalGrid;

// Prototypes de fonctions
GlobalGrid initialize_global_grid();
void debug_display_game(GlobalGrid *game);
int isGlobalGridFull(GlobalGrid game);
int game_CheckIfWon(GlobalGrid *game);

#endif /* GLOBAL_GRID_H */
=======
#ifndef GLOBAL_GRID_H
#define GLOBAL_GRID_H





// Structure pour représenter la grille globale
typedef struct {
    LocalGrid localboard[3][3];
    char current_player;
    char relative_grid;
    char winner;
} GlobalGrid;

// Prototypes de fonctions
GlobalGrid initialize_global_grid();
void Display_game(GlobalGrid *game);
int isGlobalGridFull(GlobalGrid game);
int game_CheckIfWon(GlobalGrid *game);

#endif /* GLOBAL_GRID_H */
>>>>>>> 05394a0 (✨ Startin AI)
