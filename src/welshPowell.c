#include <stdio.h>
#include <stdlib.h>
#include "graphes.h"
#include "welshPowell.h"


int compareDegree(const void* a, const void* b){
    Node* node1 = *(Node**)a;
    Node* node2 = *(Node**)b;
    return node2->nbNeighbor - node1->nbNeighbor; 
}

int areNeighbors(Node* node1, Node* node2) {
    for (int i = 0; i < node1->nbNeighbor; i++) {
        Edge* neighbor = (Edge*)node1->otherNodes[i];
        if (neighbor && neighbor->otherNode && neighbor->otherNode->id == node2->id) {
            return 1;
        }
    }
    return 0;
}


int findAvailableColor_wp(Node* node, int maxColors) {
    int* usedColors = (int*)calloc(maxColors + 1, sizeof(int));
    if (!usedColors) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(-1);
    }

    // Marquer les couleurs utilisées par les voisins
    for (int i = 0; i < node->nbNeighbor; i++) {
        Edge* neighbor = (Edge*)node->otherNodes[i];
        if (neighbor && neighbor->otherNode) {
            int neighborColor = neighbor->otherNode->currentColor;
            if (neighborColor > 0) {  // Ignorer les nœuds non colorés
                usedColors[neighborColor] = 1;
            }
        }
    }

    // Trouver la première couleur disponible
    int color;
    for (color = 1; color <= maxColors; color++) {
        if (!usedColors[color]) {
            free(usedColors);
            return color;
        }
    }

    free(usedColors);
    return -1;
}


int welshPowell(Graph* graph) {
    if (!graph || !graph->nodes || graph->numNodes <= 0) {
        return -1;
    }


    // Trier les nœuds par degré décroissant
    qsort(graph->nodes, graph->numNodes, sizeof(Node*), compareDegree);

    int maxColors = graph->numNodes;  // Nombre maximum de couleurs possibles
    int highestColorUsed = 0;

    // Coloration principale
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->currentColor == VIDE) {
            int color = findAvailableColor_wp(graph->nodes[i], maxColors);
            if (color == -1) {
                fprintf(stderr, "Erreur: Impossible de trouver une couleur valide\n");
                return -1;
            }
            
            graph->nodes[i]->currentColor = color;
            if (color > highestColorUsed) highestColorUsed = color;

            for (int j = i + 1; j < graph->numNodes; j++) {
                if (graph->nodes[j]->currentColor == VIDE) {
                    int canUseColor = 1;
                    
                    for (int k = 0; k < j; k++) {
                        if (graph->nodes[k]->currentColor == color && 
                            areNeighbors(graph->nodes[j], graph->nodes[k])) {
                            canUseColor = 0;
                            break;
                        }
                    }
                    
                    if (canUseColor) {
                        graph->nodes[j]->currentColor = color;
                    }
                }
            }
        }
    }


    return highestColorUsed;  
}