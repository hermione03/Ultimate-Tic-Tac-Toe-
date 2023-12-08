#ifndef AI_H
#define AI_H

#include "game.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

// La structure utilisée pour construire mon arbre
struct Node
{
    GlobalGrid state;         // etat actuel du jeu
    int value;                // value de ce noeud
    int num_successors;       // son nombre de successeurs
    int capacity;             // utilisée pour le vecteur
    struct Node **successors; // un vecteur de ses successeurs
    Pos lastpos;
};
typedef struct Node Node;

// Prototypes de fonctions

// Crée un nouveau nœud dans l'arbre à partir de l'état du jeu
Node *create_node(GlobalGrid game, Pos pos);
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
// Ajoute un successeur à un nœud spécifique dans l'arbre
void add_successor(Node *node, Node *successor);
// Affiche les informations d'un nœud de l'arbre de jeu
void display_node(Node *node);
// Affiche l'arbre de jeu à partir d'un nœud donné
void display_tree(Node *node);
// Libère la mémoire utilisée par tous les nœuds de l'arbre de jeu
void freeTree(Node *root);

#endif /* AI_H */
