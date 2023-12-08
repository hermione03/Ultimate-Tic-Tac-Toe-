#ifndef AI_H
#define AI_H

#include "game.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
// Prototypes de fonctions

// Donne une valeur spécifique à un joueur
int giveValue(enum player p);
// Vérifie si l'état actuel de la grille est une condition de victoire
int check_win_condition(LocalGrid *lcState);
// Évalue l'état actuel d'une grille locale dans l'arbre du jeu
int evaluateLG(LocalGrid *lcState);
// Fonction de teste
void EvaluateMove(Node *state);
// Trouve les prochains mouvements possibles pour un état de jeu donné
Move *get_possible_moves(GlobalGrid game);
// Applique un mouvement à l'état actuel du jeu et renvoie le nouvel état
GlobalGrid apply_move(GlobalGrid game, Pos pos);

#endif /* AI_H */
