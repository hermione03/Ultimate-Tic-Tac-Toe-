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

struct Node
{
    GlobalGrid state;
    int value;
    int num_successors;
    int capacity;
    struct Node **successors;
};
typedef struct Node Node;

// Prototypes de fonctions
Node *createNode(GlobalGrid game);
int giveValue(enum player p);
int checkWinCondition(LocalGrid *lcState);
int realEvaluateSquare(LocalGrid *lcState);
void EvaluateMove(Node *state);
void evaluateGame(Node *curr);
Move *NextMoves(GlobalGrid game);
GlobalGrid ApplyMove(GlobalGrid game, Pos pos);
void addSuccessor(Node *node, Node *successor);
void displayNode(Node *node);
void displayTree(Node *node);
void freeTree(Node *root);
Node *MiniMax(Node *node, int depth, int maximizingPlayer);

#endif /* AI_H */
