#ifndef AI_H
#define AI_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Local_grid.h"
#include "Global_grid.h"
#include "GAME.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

struct Node
{
    GlobalGrid state;
    int value;
    int num_successors;
    int capacity;
    struct Node** successors;
};
typedef struct Node Node ;

typedef struct {
    int x;
    int y;
} Move;

// Prototypes de fonctions
Node* createNode(GlobalGrid game);
void EvaluateMove(Node *state);
Move **NextMoves(GlobalGrid game);
GlobalGrid ApplyMove (GlobalGrid game, Move pos);
void addSuccessor(Node* node, Node* successor);
void displayNode(Node* node);
void displayTree(Node* node);
void freeTree(Node* root);
int MiniMax(Node* node, int depth, int maximizingPlayer);

#endif /* AI_H */
