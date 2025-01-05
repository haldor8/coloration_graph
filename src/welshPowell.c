#include <stdio.h>
#include <stdlib.h>
#include "graphes.h"
#include "welshPowell.h"


int compareDegree(const void* a, const void* b){
    Node* node1 = *(Node**)a;
    Node* node2 = *(Node**)b;
    return node2->nbNeighbor - node1->nbNeighbor; // Inversé pour trier par ordre décroissant
}

int areNeighbors(Node* node1, Node* node2) {
    // printf("Vérification des voisins pour les nœuds %d et %d\n", node1->id, node2->id);
    
    Vertex **neighbors = (Vertex **)node1->otherNodes;  // Liste des voisins du nœud 1
    // printf("Le nœud %d a %d voisins :\n", node1->id, node1->nbNeighbor);
    
    for (int i = 0; i < node1->nbNeighbor; i++) {
        Vertex* neighbor = neighbors[i];
        if (neighbor == NULL || neighbor->otherNode == NULL) {
            // printf("Attention : voisin[%d] est NULL.\n", i);
            continue;
        }
        // printf(" - Voisin %d (nœud %d)\n", i + 1, neighbor->otherNode->id);

        if (neighbor->otherNode == node2) {
            // printf("Le nœud %d est voisin du nœud %d.\n", node1->id, node2->id);
            return 1;  // Les nœuds sont voisins
        }
    }

    // printf("Le nœud %d n'est PAS voisin du nœud %d.\n", node1->id, node2->id);
    return 0;  // Les nœuds ne sont pas voisins
}


// void welshPowell(Graph *graph){
//     // Qsort trie les noeuds par rapport a leurs nombre de voisin 
//     qsort(graph -> nodes, graph -> numNodes, sizeof(Node*), compareDegree);
//         printf("Ordre des nœuds après tri :\n");
//     for (int i = 0; i < graph->numNodes; i++) {
//         printf("Nœud %d avec %d voisins\n", graph->nodes[i]->id, graph->nodes[i]->nbNeighbor);
//     }


    
//     enum colors color  = BLANC;
//     for (int i = 0 ; i < graph -> numNodes; i++){
//         if(graph -> nodes[i] -> currentColor == VIDE){
//             graph -> nodes[i] -> currentColor = color;
//             printf("Noeud %d -> Couleur : %s\n", graph->nodes[i]->id, colorsToString[color]);

//             for(int j = i +1 ; j < graph -> numNodes; j++){
//                 if(graph -> nodes[j] -> currentColor == VIDE && !areNeighbors(graph -> nodes[i], graph -> nodes[j] )){
//                     graph -> nodes[j] -> currentColor = color;
//                     printf("Noeud %d -> Couleur : %s\n", graph->nodes[j]->id, colorsToString[color]);

//                 }
//             }


//             color = (color + 1 < ENUM_SIZE) ? color + 1 : BLANC;


//             printf("Couleur SUIVANTE ========================================================================= : %s\n", colorsToString[color]);
//         }
//     }
//     printf("Welsh Powell done ? \n");
// }



int findAvailableColor_wp(Node* node, int numColors) {
    // Marquer les couleurs utilisées par les voisins
    int* usedColors = (int*)malloc(numColors * sizeof(int));
    if (!usedColors) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire.\n");
        exit(-1);
    }

    for (int i = 0; i < numColors; i++) {
        usedColors[i] = 0;
    }

    for (int i = 0; i < node->nbNeighbor; i++) {
        Vertex* neighbor = (Vertex*)node->otherNodes[i];  // Utilisation directe sans cast
        int neighborColor = neighbor->otherNode->currentColor;
        if (neighborColor != VIDE) {
            usedColors[neighborColor] = 1;  // Marquer la couleur comme utilisée
        }
    }

    // Trouver la première couleur disponible
    for (int color = 1; color < numColors; color++) {
        if (!usedColors[color]) {
            free(usedColors);
            return color;
        }
    }

    free(usedColors);
    return -1;  // Aucune couleur disponible
}


int welshPowell(Graph *graph) {
    // Tri des nœuds par ordre décroissant du nombre de voisins
    qsort(graph->nodes, graph->numNodes, sizeof(Node*), compareDegree);
    
    /*
    printf("Ordre des nœuds après tri :\n");
    for (int i = 0; i < graph->numNodes; i++) {
        printf("Nœud %d avec %d voisins\n", graph->nodes[i]->id, graph->nodes[i]->nbNeighbor);
    }
    */
    for (int i = 0; i < graph->numNodes; i++) {
        if (graph->nodes[i]->currentColor == VIDE) {
            int chosenColor = findAvailableColor_wp(graph->nodes[i], graph->numNodes);
            if (chosenColor != -1) {
                graph->nodes[i]->currentColor = chosenColor;
                
                // Parcourir les nœuds suivants et attribuer la même couleur s'ils ne sont pas voisins
                for (int j = i + 1; j < graph->numNodes; j++) {
                    if (graph->nodes[j]->currentColor == VIDE && !areNeighbors(graph->nodes[i], graph->nodes[j])) {
                        graph->nodes[j]->currentColor = chosenColor;
                    }
                }
            }
        }
    }
    // printf("Welsh-Powell terminé !\n");
    return 0;
}