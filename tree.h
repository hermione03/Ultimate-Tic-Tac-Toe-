#ifndef TREE_H
#define TREE_H

#include "game.h"
#include "global_grid.h"

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

// Crée un nouveau nœud dans l'arbre à partir de l'état du jeu
Node *create_node(GlobalGrid game);

// Ajoute un successeur à un nœud spécifique dans l'arbre
void add_successor(Node *node, Node *successor);
// Affiche les informations d'un nœud de l'arbre de jeu
void display_node(Node *node);
// Affiche l'arbre de jeu à partir d'un nœud donné
void display_tree(Node *node);
// Libère la mémoire utilisée par tous les nœuds de l'arbre de jeu
void freeTree(Node *root);

#endif // TREE_H