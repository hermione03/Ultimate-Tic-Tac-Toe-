#include <stdio.h>
#include "Local_grid.h"
#include "Global_grid.h"

enum player
{
    COMPUTER = 'O',
    HUMAN = 'X',
};

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

void updatePlayer(GlobalGrid *game)
{
    game->current_player ^= COMPUTER ^ HUMAN;
}


int possibleMove(GlobalGrid *game, int x, int y)
{
    int xg, yg, g;

    // verifier si c dans la grille globale d'abord
    if (x > 2 || y > 26)
    {
        printf("Position invalide : en dehors de la grille globale !\n");
        return 0;
    }
    else
    {
        xg = (y / 3) / 3;
        yg = (y / 3) % 3;
        g = yg + xg * 3;
        // printf("grille actuelle  = %d\n", g);
        // printf("grille relative : %d\n", game->relative_grid);
        // printf("AHHHHHHHHHHHH %c, %d, %d\n", game->localboard[xg][yg].board[x][y % 3], x, y);
        if (game->relative_grid != g && game->relative_grid > -1)
        {
            printf("Vous n'avez pas le droit de jouer dans cette grille Locale !\n");
            printf("Vous devez jouer dans la grille numero : %d\n",game->relative_grid);
            return 0;
        }
        // printf("grille plaine ou deja gagnée");
        // return 0;
        if (game->localboard[xg][yg].board[x][y % 3] != '-')
        {
            printf("Cette case est deja prise !\n");
            return 0;
        }
    }
    return 1;
}


int UTTT_GAME(GlobalGrid *game)
{
    int x, y, xg, yg;
    //  Afficher le joueur courant (humain ou ordinateur)
    printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    //     Afficher la grille globale
    Display_game(game);

    //     Tant que le joueur n'a pas sélectionné une case valide:

    //         Si la grille globale est pleine ou qu'il y a un gagnant:
    //             Terminer la partie --> return 0;

    //         Lire l'entrée du joueur pour la case à jouer
    // avec un scanf

    do
    {

        printf("Choisissez une case à jouer (x, y) : ");
        // Si la case sélectionnée n'est pas valide:
        if (scanf("%d,%d", &x, &y) != 2)
        {

            // Afficher un message d'erreur
            printf("Entrée invalide. Veuillez entrer les coordonnées x et y séparées par une virgule (par exemple : 1,2).\n");
            // Vider le tampon d'entrée
            while (getchar() != '\n')
                ;
        }
    } while (!possibleMove(game, x, y));

    //printf("x = %d,y = %d\n", x, y);
    xg = (y / 3) / 3;
    yg = (y / 3) % 3;
    //printf("REGAAAAARDE : %d, %d", x, y%3);
    //game->relative_grid = yg + (3 * xg);
    if (isLocalGridFull(&game->localboard[x][y % 3]) || game->localboard[x][y % 3].winner != ' ')
    {

        printf("grille relative plaine ou deja gagnée , le prochain coup est libre ! \n");
        game->relative_grid = -1;
    }
    else
    {
        game->relative_grid = y % 3 + x * 3;
    }
    if(game->relative_grid == -1){

        printf("grille relative = Choix libre \n" );
    }
    else{

        printf("grille relative =  %d\n", game->relative_grid );
    }
    // printf("Grille globale numero %d --> x = %d, y = %d\n", game->relative_grid, xg, yg);
    // printf("Grille Locale : x = %d,y = %d\n", x, y % 3);
    y = y % 3;
    //         Sinon:
    //             Si la case sélectionnée est valide dans la grille globale:
    //                 Mettre à jour la grille globale avec le coup du joueur
    // Mettre à jour la grille locale correspondante avec le coup du joueur
    game->localboard[xg][yg].board[x][y] = game->current_player;
    // Vérifier si la grille locale est gagnée
    if (LG_CheckIfWon(&game->localboard[xg][yg]))
    {
        printf("Grille locale gagnée par : %s\n", playerToString(game->current_player));
        // game->relative_grid = -1;
    }
    //     Vérifier si la grille globale est gagnée

    //     Si la grille globale est gagnée ou si elle est pleine:
    //         Terminer la partie

    //     Changer de joueur
    updatePlayer(game);
    return 1;
}