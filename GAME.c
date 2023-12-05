
#include "GAME.h"
#include "AI.h"

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
            // printf("Vous n'avez pas le droit de jouer dans cette grille Locale !\n");
            // printf("Vous devez jouer dans la grille numero : %d\n",game->relative_grid);
            return 0;
        }
        if (game->localboard[xg][yg].board[x][y % 3] == '-' && game->localboard[xg][yg].winner != ' ')
        {
            // printf("Cette grille locale est déjà gagnée !\n");
            return 0;
        }
        // printf("grille plaine ou deja gagnée");
        // return 0;
        if (game->localboard[xg][yg].board[x][y % 3] != '-')
        {
            // printf("Cette case est deja prise !\n");
            return 0;
        }
    }
    return 1;
}

Pos random_pick_move(GlobalGrid *game)
{
    Pos pos;
    Move *moves = NextMoves(*game);
    printf("Mouvements disponibles :\n");
    for (int i = 0; moves->lst_moves[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
    }
    printf("\n");

    // Générer un indice aléatoire dans la liste des mouvements disponibles
    int random_index = rand() % moves->num_moves;

    int x = moves->lst_moves[random_index]->x;
    int y = moves->lst_moves[random_index]->y;

    pos.x = x;
    pos.y = y;

    return pos;
}

Pos human_pick_move(GlobalGrid *game)
{
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
    } while (!possibleMove(game, pos.x, pos.y));
    return pos;
}

Pos minimax_pick_move(GlobalGrid *game)
{
    int i, x, y, xg, yg;
    Pos pos;
    Move *moves = NextMoves(*game);
    printf("Mouvements disponibles :\n");
    for (i = 0; moves->lst_moves[i] != NULL; i++)
    {
        printf("(%d,%d) ", moves->lst_moves[i]->x, moves->lst_moves[i]->y);
    }
    printf("\n");

    int depth = 3; // Set your desired depth for MiniMax

    Node *root = createNode(*game);
    Node *bestMove = MiniMax(root, depth, game->current_player);
    printf("Best Move : %d\n", bestMove->value);

    for (i = 0; moves->lst_moves[i] != NULL; i++)
    {
        x = moves->lst_moves[i]->x;
        y = moves->lst_moves[i]->y;
        xg = (y / 3) / 3;
        yg = (y / 3) % 3;
        if (bestMove->state.localboard[xg][yg].board[x][y % 3] == bestMove->state.current_player)
        {
            printf("Le meilleur mouvement suggéré par MiniMax est : (%d,%d)\n", x, y);
            pos.x = x;
            pos.y = y;
            return pos;
        }
    }
    // Nettoyage de la mémoire allouée pour les mouvements
    for (int i = 0; moves->lst_moves[i] != NULL; i++)
    {
        free(moves->lst_moves[i]);
    }
    free(moves->lst_moves);
    free(moves);

    // Dans le cas improbable où aucun mouvement valide n'a été trouvé, retourner une position nulle
    pos.x = -1;
    pos.y = -1;
    return pos;
}


int UTTT_GAME(GlobalGrid *game, Pos (*player1_pick_move)(), Pos (*player2_pick_move)())
{
    Move *moves = NextMoves(*game);

    printf("Tour de %s de placer un %c \n", playerToString(game->current_player), game->current_player);
    Display_game(game);

    int x, y;
    Pos chosenMove;

    if (game->current_player == HUMAN)
    {
        chosenMove = player1_pick_move(game); // Obtenir le mouvement du joueur 1
    }
    else
    {
        chosenMove = player2_pick_move(game); // Obtenir le mouvement du joueur 2
    }

    x = chosenMove.x;
    y = chosenMove.y;

    int xg = (y / 3) / 3;
    int yg = (y / 3) % 3;

    if (isLocalGridFull(&game->localboard[x][y % 3]) || !LG_CheckIfWon(&game->localboard[x][y % 3]))
    {
        printf("Grille relative pleine ou déjà gagnée, le prochain coup est libre ! \n");
        game->relative_grid = -1;
    }
    else
    {
        printf("***********Grille locale : %d %d\n", x, y % 3);
        printf("***********Winner : %c\n", game->localboard[x][y % 3].winner);
        game->relative_grid = y % 3 + x * 3;
        printf("relaaaaaative : %d\n", game->relative_grid);
    }

    if (game->relative_grid == -1)
    {
        printf("Grille relative = Choix libre \n");
    }
    else
    {
        printf("Grille relative = %d\n", game->relative_grid);
    }

    game->localboard[xg][yg].board[x][y % 3] = game->current_player;

    if (LG_CheckIfWon(&game->localboard[xg][yg]))
    {
        printf("Grille locale gagnée par : %s\n", playerToString(game->current_player));
    }

    updatePlayer(game);

    // Nettoyage de la mémoire allouée pour les mouvements
    for (int i = 0; moves->lst_moves[i] != NULL; i++)
    {
        free(moves->lst_moves[i]);
    }
    free(moves->lst_moves);
    free(moves);

    return 1;
}