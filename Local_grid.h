<<<<<<< HEAD
#ifndef LOCAL_GRID_H
#define LOCAL_GRID_H

// Structure pour représenter une grille locale
typedef struct {
    char board[3][3];
    char winner;
} LocalGrid;

// Initialise une grille locale
void initialize_local_grid(LocalGrid *grid);

// Affiche une grille locale
void display_local_grid(LocalGrid *grid);

// Vérifie s'il y a un gagnant dans une grille locale
int LG_CheckIfWon(LocalGrid *grid);

// Vérifie si une grille locale est pleine
int isLocalGridFull(LocalGrid *grid);

#endif /* LOCAL_GRID_H */
=======
#ifndef LOCAL_GRID_H
#define LOCAL_GRID_H

// Structure pour représenter une grille locale
typedef struct {
    char board[3][3];
    char winner;
} LocalGrid;

// Initialise une grille locale
void initialize_local_grid(LocalGrid *grid);

// Affiche une grille locale
void display_local_grid(LocalGrid *grid);

// Vérifie s'il y a un gagnant dans une grille locale
int LG_CheckIfWon(LocalGrid *grid);

// Vérifie si une grille locale est pleine
int isLocalGridFull(LocalGrid *grid);

#endif /* LOCAL_GRID_H */
>>>>>>> 05394a0 (✨ Startin AI)
