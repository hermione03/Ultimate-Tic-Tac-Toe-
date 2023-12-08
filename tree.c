#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node *create_node(GlobalGrid game)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode)
    {
        newNode->value = 0;
        newNode->state = game;
        newNode->num_successors = 0;
        newNode->capacity = 0;
        newNode->successors = NULL;
    }
    return newNode;
}

void add_successor(Node *node, Node *successor)
{
    if (node->num_successors >= node->capacity)
    {
        node->capacity = (node->capacity == 0) ? 1 : node->capacity * 2;
        node->successors = realloc(node->successors, node->capacity * sizeof(Node *));
        if (node->successors == NULL)
        {
            printf("Allocation mémoire échouée pour les successeurs.\n");
            exit(1);
        }
    }
    node->successors[node->num_successors++] = successor;
}

void display_node(Node *node)
{
    printf("--------------- Node ------------------------\n");
    printf("Winner ? %c\n ", node->state.winner);
    printf("Current player ? %c\n ", node->state.current_player);
    printf("Value : %d\n", node->value);
    printf("Nombre de successeurs : %d\n", node->num_successors);

    Display_game(&node->state);

    printf("Successeurs: ");
    for (int i = 0; i < node->num_successors; i++)
    {
        printf("Successeur %d, ", i + 1);
    }
    printf("\n");
    printf("-------------------------------------------------------\n");
}

void display_tree(Node *node)
{
    printf("--------------- Tree ------------------------\n");
    if (node == NULL)
    {
        return;
    }

    display_node(node);

    for (int i = 0; i < node->num_successors; i++)
    {
        display_tree(node->successors[i]);
    }
    printf("-------------------------------------------------------\n");
}

void freeTree(Node *root)
{
    if (root == NULL)
    {
        return;
    }

    for (int i = 0; i < root->num_successors; i++)
    {
        freeTree(root->successors[i]); // Appel récursif pour libérer les enfants
    }

    free(root->successors); // Libération du tableau de successeurs
    free(root);             // Libération du nœud actuel
}
