
#include "AI.h"



Node* createNode(GlobalGrid game) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->value = 0;
        newNode->state = game;
        newNode->num_successors = 0;
        newNode->capacity = 0;
        newNode->successors = NULL;
    }
    return newNode;
}


void EvaluateMove(Node *state){
    state->value = 0;
}

Move **NextMoves(GlobalGrid game) {
    int x, y, i = 0;
    int capacity = 1; 
    Move **moves = (Move **)malloc(capacity * sizeof(Move *));

    if (moves == NULL) {
        printf("Memory allocation failed for moves.\n");
        return NULL;
    }

    for (x = 0; x < 3; x++) {
        for (y = 0; y < 27; y++) {
            if (possibleMove(&game, x, y)) {
                if (i >= capacity -1 ) {
                    capacity += 1;
                    moves = (Move **)realloc(moves, capacity * sizeof(Move *));
                    if (moves == NULL) {
                        printf("Memory reallocation failed for moves.\n");
                        return NULL;
                    }
                }

                moves[i] = (Move *)malloc(sizeof(Move));
                if (moves[i] == NULL) {
                    printf("Memory allocation failed for moves[%d].\n", i);
                    return NULL;
                }

                moves[i]->x = x;
                moves[i]->y = y;
                i++;
            }
        }
    }

    // Terminate the array with a null pointer
    moves[i] = NULL;

    return moves;
}






GlobalGrid ApplyMove (GlobalGrid game, Move pos) {
    int xg, yg;
    GlobalGrid next = game;
    xg = (pos.y / 27); // Récupère la grille globale à mettre à jour
    yg = ((pos.y % 27) / 3); // Récupère la position de la localboard dans la grille globale
    int x = pos.x;
    int y = (pos.y % 3);

    next.localboard[xg][yg].board[x][y] = game.current_player;

    return next;
}


void addSuccessor(Node* node, Node* successor) {
    if (node->num_successors >= node->capacity) {
        node->capacity = (node->capacity == 0) ? 1 : node->capacity * 2;
        node->successors = realloc(node->successors, node->capacity * sizeof(Node*));
        if (node->successors == NULL) {
            printf("Allocation mémoire échouée pour les successeurs.\n");
            exit(1);
        }
    }
    node->successors[node->num_successors++] = successor;
}

void displayNode(Node* node) {
    printf("Value : %d\n", node->value);
    printf("Nombre de successeurs : %d\n", node->num_successors);

    debug_display_game(&node->state);

    printf("Successeurs: ");
    for (int i = 0; i < node->num_successors; i++) {
        printf("Successeur %d, ", i + 1);
    }
    printf("\n");
}

void displayTree(Node* node) {
    if (node == NULL) {
        return;
    }

    displayNode(node);

    for (int i = 0; i < node->num_successors; i++) {
        displayTree(node->successors[i]);
    }
}


void freeTree(Node* root) {
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < root->num_successors; i++) {
        freeTree(root->successors[i]); // Appel récursif pour libérer les enfants
    }

    free(root->successors); // Libération du tableau de successeurs
    free(root); // Libération du nœud actuel
}



int MiniMax(Node* node, int depth, int maximizingPlayer) {
    if (depth == 0 || game_CheckIfWon(&node->state) || isGlobalGridFull(node->state)) {
        EvaluateMove(node);
        return node->value;
    }

    Move **moves = NextMoves(node->state);

    if (maximizingPlayer == node->state.current_player) {
        int bestValue = INT_MIN;
        for (int i = 0; i < 8; i++) {
            Node* child = createNode(ApplyMove(node->state, *moves[i]));
            addSuccessor(node, child);
            int value = MiniMax(child, depth - 1, !maximizingPlayer);
            node->value = bestValue;
            bestValue = max(bestValue, value);
        }
        return bestValue;
    } else {
        int bestValue = INT_MAX;
        for (int i = 0; i < 8; i++) {
            Node* child = createNode(ApplyMove(node->state, *moves[i]));
            addSuccessor(node, child);
            int value = MiniMax(child, depth - 1, !maximizingPlayer);
            node->value = bestValue;
            bestValue = min(bestValue, value);
        }
        return bestValue;
    }
}
