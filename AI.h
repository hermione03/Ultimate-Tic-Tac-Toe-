#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "LocalGrid.h"
#include "GlobalGrid.h"
#include "GAME.h"

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
};
typedef struct Node Node;

// Prototypes de fonctions

// Crée un nouveau nœud dans l'arbre à partir de l'état du jeu
Node *createNode(GlobalGrid game);
// Donne une valeur spécifique à un joueur 
int giveValue(enum player p);
// Vérifie si l'état actuel de la grille est une condition de victoire
int checkWinCondition(LocalGrid *lcState);
// Évalue l'état actuel d'une grille locale dans l'arbre du jeu
int evaluateLG(LocalGrid *lcState);
// Fonction de teste 
void EvaluateMove(Node *state);
// Trouve les prochains mouvements possibles pour un état de jeu donné
Move *NextMoves(GlobalGrid game);
// Applique un mouvement à l'état actuel du jeu et renvoie le nouvel état
GlobalGrid ApplyMove(GlobalGrid game, Pos pos);
// Ajoute un successeur à un nœud spécifique dans l'arbre
void addSuccessor(Node *node, Node *successor);
// Affiche les informations d'un nœud de l'arbre de jeu
void displayNode(Node *node);
// Affiche l'arbre de jeu à partir d'un nœud donné
void displayTree(Node *node);
// Libère la mémoire utilisée par tous les nœuds de l'arbre de jeu
void freeTree(Node *root);
// Algorithme MiniMax pour la prise de décision dans le jeu
Node *MiniMax(Node *node, int depth, int maximizingPlayer);
// Algorithme Alpha-Beta pour la prise de décision améliorée
Node *AlphaBeta(Node *node, int depth, int alpha, int beta, int maximizingPlayer);

#endif /* AI_H */
