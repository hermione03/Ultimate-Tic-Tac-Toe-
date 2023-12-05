#ifndef UTTT_H
#define UTTT_H

// Inclusions de bibliothèques




// Enumération pour les joueurs
enum player {
    COMPUTER = 'O',
    HUMAN = 'X',
};

// Prototypes de fonctions
char *playerToString(enum player p);
void updatePlayer(GlobalGrid *game);
int possibleMove(GlobalGrid *game, int x, int y);
int UTTT_GAME(GlobalGrid *game);

#endif /* UTTT_H */
