
#ifndef LOCAL_GRID_H
#define LOCAL_GRID_H

// Structure pour représenter une grille locale
typedef struct
{
    char board[3][3]; // une matrice de char 3 * 3
    char winner;      // le gagnant de cette grille locale
} LocalGrid;

// Initialise une grille locale
void initialize_local_grid(LocalGrid *grid);

// Affiche une grille locale
void display_local_grid(LocalGrid *grid);

// Vérifie s'il y a un gagnant dans une grille locale
int is_LG_won(LocalGrid *grid);

// Vérifie si une grille locale est pleine
int is_local_grid_full(LocalGrid *grid);

#endif /* LOCAL_GRID_H */
