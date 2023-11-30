#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

enum player
{
    COMPUTER = 'O',
    HUMAN = 'X',
};
// Structure pour représenter une grille locale

typedef struct
{
    char board[3][3];
    char winner;
} LocalGrid;

// Structure pour représenter la grille globale
typedef struct
{
    LocalGrid localboard[3][3];
    char current_player;
    char free_choice;
    char winner;
} GlobaleGrid;

void initialize_local_grid(LocalGrid *grid)
{
    memset(grid->board, '-', sizeof(grid->board));
    grid->winner = ' ';
    // return *grid;
}

GlobaleGrid initialize_global_grid()
{
    GlobaleGrid game;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            initialize_local_grid(&game.localboard[i][j]);
        }
    }
    game.localboard[1][1].board[1][1] = 'X';
    game.localboard[0][1].board[0][0] = 'X';
    game.localboard[0][1].board[0][1] = 'X';
    game.localboard[2][1].board[0][1] = 'O';
    game.localboard[2][1].board[2][1] = 'O';
    game.localboard[2][2].board[0][2] = 'O';
    game.localboard[2][0].board[0][1] = 'O';
    game.localboard[2][0].board[0][2] = 'O';
    game.winner = ' ';

    // memset(game.localboard, '-', sizeof(game.localboard));
    return game;
}

// Structure pour représenter un coup
typedef struct
{
    int row;
    int col;
} move;



void display_local_grid(LocalGrid *grid)
{
    for (int i = 0; i < 3; i++)
    {
        printf("\n");
        for (int j = 0; j < 3; j++)
        {
            printf("%c ", grid->board[i][j]);
        }
        printf("\n");
    }
    printf("******************************");
}

void debug_display_game(GlobaleGrid *game)
{
    int global,acc = 0;
    for (int i = 0; i < 3; i++)
    {
        if (i > 0) // Pour afficher une ligne de séparation entre les lignes de grilles
        {
            //printf("_________________________________| |________________________________| |________________________________| |\n");
            printf("________________________| |_______________________| |_______________________| |\n");
        }

        for (int row = 0; row < 3; row++)
        {   
            printf("| ");
            for (int j = 0; j < 3; j++)
            {

                global = i + j + acc;
                
                for (int col = 0; col < 3; col++)
                {
                    //printf("%c ", game->localboard[i][row].board[col][col]);
                    if (game->localboard[i][j].winner == ' ')
                    {
                        if(game->localboard[i][j].board[row][col] == '-'){
                            printf("(%d,%d) | ",row,col+(global*3));
                        //printf("(%d)(%d,%d) | ",global,row,col+(global*3));
                        }
                        else{
                            
                            printf(game->localboard[i][j].board[row][col] == 'O'?"  \033[34m%c\033[0m   |":"   \033[35m%c\033[0m   |" , game->localboard[i][j].board[row][col]);
                        }
                    }
                    else{
                        printf(game->localboard[i][j].winner== 'O'?"  \033[34m%c\033[0m   |":"   \033[35m%c\033[0m   |" , game->localboard[i][j].board[row][col]);
                        //printf("%c ", game->localboard[i][j].board[row][col]);
                    }
                    //printf("(%d,%d) | ",row,col+(global*3));
                }
                printf("| ");
            }
            
            printf("\n");
        }
    acc+=2;
    }
    //printf("_________________________________| |________________________________| |________________________________| |\n");
    printf("\n");
}
            

int LG_CheckIfWon(LocalGrid *grid)
{
    int i, j;
    char winner = ' ';

    // Vérification des lignes
    for (i = 0; i < 3; i++)
    {
        if (grid->board[i][0] == grid->board[i][1] &&
            grid->board[i][1] == grid->board[i][2] &&
            grid->board[i][0] != '-')
        {
            winner = grid->board[i][0];
            printf("Lignes %d gagnant %s\n" ,i,winner);
            memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
            grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la ligne gagnante
            grid->winner = winner;
            return 1;
        }
    }

    // Vérification des colonnes
    for (i = 0; i < 3; i++)
    {
        if (grid->board[0][i] == grid->board[1][i] &&
            grid->board[1][i] == grid->board[2][i] &&
            grid->board[0][i] != '-')
        {
            winner = grid->board[0][i];
            printf("Colonnes %d gagnant %s\n" ,i,winner);
            memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
            grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la colonne gagnante
            grid->winner = winner;
            return 1;
        }
    }

    // Vérification des diagonales
    if (grid->board[0][0] == grid->board[1][1] && grid->board[1][1] == grid->board[2][2] &&
        grid->board[0][0] != '-')
    {
        winner = grid->board[0][0];
        printf("Diag %d gagnant %s\n" ,i,winner);
        memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
        grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante
        grid->winner = winner;
        return 1;
    }

    if (grid->board[0][2] == grid->board[1][1] && grid->board[1][1] == grid->board[2][0] &&
        grid->board[0][2] != '-')
    {
        winner = grid->board[0][2];
        printf("Diag2 %d gagnant %s\n" ,i,winner);
        memset(grid->board, '-', sizeof(grid->board)); // Vider la grille locale
        grid->board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante
        grid->winner = winner;
        return 1;
    }

    return 0;
}

int isLocalGridFull(LocalGrid *grid)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (grid->board[i][j] == '-')
            {
                return 0; // Il y a une case vide, donc la grille n'est pas pleine
            }
        }
    }
    return 1; // Aucune case vide, la grille est pleine
}

int isGlobalGridFull(GlobaleGrid game)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (isLocalGridFull(&game.localboard[i][j]) == 0)
            {
                return 0; // Il y a une grille locale non pleine, donc la grille globale n'est pas pleine
            }
        }
    }
    return 1; // Toutes les grilles locales sont pleines, la grille globale est pleine
}



int game_CheckIfWon(GlobaleGrid *game)
{
    int i, j;
    //char winner = ' ';

    // Vérification des lignes
    for (i = 0; i < 3; i++)
    {
        if (game->localboard[i][0].board[1][1] == game->localboard[i][1].board[1][1] &&
            game->localboard[i][1].board[1][1] == game->localboard[i][2].board[1][1] &&
            game->localboard[i][0].board[1][1] != '-')
        {
            
            // game->localboard[1][1].board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la ligne gagnante
            game->winner = game->localboard[0][i].board[1][1];
            return 1;
        }
    }

    // Vérification des colonnes
    for (i = 0; i < 3; i++)
    {
        if (game->localboard[0][i].board[1][1] == game->localboard[1][i].board[1][1] &&
            game->localboard[1][i].board[1][1] == game->localboard[2][i].board[1][1] &&
            game->localboard[0][i].board[1][1] != '-')
        {
            
            // game->localboard[1][1].board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la colonne gagnante
            game->winner = game->localboard[0][i].board[1][1];
            return 1;
        }
    }

    // Vérification des diagonales
    if (game->localboard[0][0].board[1][1] == game->localboard[1][1].board[1][1] && game->localboard[1][1].board[1][1] == game->localboard[2][2].board[1][1] &&
        game->localboard[0][0].board[1][1] != '-')
    {
        
        // game->localboard[1][1].board[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante
            game->winner = game->localboard[0][i].board[1][1];
        return 1;
    }

    if (game->localboard[0][2].board[1][1] == game->localboard[1][1].board[1][1] && game->localboard[1][1].board[1][1] == game->localboard[2][0].board[1][1] &&
        game->localboard[0][2].board[1][1] != '-')
    {
        
        // game->localboard[1][1] = winner;                    // Placer le symbole du gagnant au milieu de la diagonale gagnante
        game->winner = game->localboard[0][i].board[1][1];
        return 1;
    }

    return 0;
}

void updatePlayer(GlobaleGrid *game)
{
    game->current_player ^= COMPUTER ^ HUMAN;
}

int possibleMove(GlobaleGrid *game, int prev, int x, int y)
{
    // prev doit etre calculée --> c'est le g 
    int xg,yg,g;
    //verifier si c dans la grille globale d'abord 
    if (x > 2 || y > 26){
        printf("Position invalide : en dehors de la grille globale !\n");
        return 0;
    }
    // else{
    //     xg = (y/3) / 3;
    //     yg = (y/3) % 3;
    //     g = yg +(3*xg);
    //     if(prev!= g){
    //         printf("Vous n'avez pas le droit de jouer dans cette grille Locale !\n");
    //         return 0;
    //     }
    // }
    return 1;
}

// void play(GlobaleGrid game)
// {
//     // determiner les cases possibles à jouer
// }

char *playerToString(enum player p)
{
    switch (p)
    {
    case COMPUTER:
        return "COMPUTER";
    case HUMAN:
        return "HUMAN";
    default:
        return "UNKNOWN";
    }
}

int UTTT_GAME(GlobaleGrid *game)
{
    int x,y,xg,yg,g;
    // printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    // printf("Choisisser une case à jouer :\n");
    // display_game(game);
    // updatePlayer(game);
    //  Afficher le joueur courant (humain ou ordinateur)
    printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    //     Afficher la grille globale
    debug_display_game(game);

    //     Tant que le joueur n'a pas sélectionné une case valide:


    //         Si la grille globale est pleine ou qu'il y a un gagnant:
    //             Terminer la partie --> return 0;

    //         Lire l'entrée du joueur pour la case à jouer
    // avec un scanf
    
    do {

        printf("Choisissez une case à jouer (x, y) : ");
            if (scanf("%d,%d", &x, &y) != 2) {
    //         Si la case sélectionnée n'est pas valide:
    //             Afficher un message d'erreur
                printf("Entrée invalide. Veuillez entrer les coordonnées x et y séparées par une virgule (par exemple : 1,2).\n");
                while (getchar() != '\n'); // Vider le tampon d'entrée
            }
    } while (!possibleMove(game,0,x,y));

    
    printf("x = %d,y = %d\n",x,y);
    xg = (y/3) / 3;
    yg = (y/3) % 3;
    g = yg +(3*xg);
    printf("Grille globale numero %d --> x = %d, y = %d\n", g, xg, yg);
    printf("Grille Locale : x = %d,y = %d\n",x,y%3);
    y = y%3;
    
    //debug_display_game(game);

    //         Sinon:
    //             Si la case sélectionnée est valide dans la grille globale:
    //                 Mettre à jour la grille globale avec le coup du joueur
    //     Mettre à jour la grille locale correspondante avec le coup du joueur
    game->localboard[xg][yg].board[x][y] = game->current_player;
    //     Vérifier si la grille locale est gagnée
    // LG_CheckIfWon(game->localboard[xg][yg].board[x][y]);
    if (LG_CheckIfWon(&game->localboard[xg][yg])){
        printf("Grille locale gagnée par : %s\n", &game->localboard[xg][yg].winner);
    }


    //     Si la grille locale est gagnée:
    //         Placer le symbole du gagnant au milieu de la grille globale

    //     Vérifier si la grille globale est gagnée
    //     Si la grille globale est gagnée ou si elle est pleine:
    //         Terminer la partie

    //     Changer de joueur
    updatePlayer(game);
    return 1;
}

int main()
{
    // LocalGrid grid = initialize_local_grid();    // Initialisation de la grille locale avec des tirets
    GlobaleGrid game = initialize_global_grid(); // Initialisation de la grille globale avec des tirets
    // display_local_grid(&grid); // Affichage de la grille locale
    game.current_player = HUMAN;
    game.free_choice = 1;
    int count = 0;
    while (1)
    {
        UTTT_GAME(&game);
        // if (game_CheckIfWon(&game) || isGlobalGridFull(game))
        // {
        //     break;
        // }
        count++;
        if (count > 8)
        {
            break;
        }
    }

    return 0;
}
