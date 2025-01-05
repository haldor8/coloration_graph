#include "DSATUR.h"

int getSaturationDegree(Node* node) {
    int count = 0;
    for (int i = 0; i < node->nbNeighbor; i++) {
        Edge* neighbor = (Edge*)node->otherNodes[i];
        int neighborColor = neighbor->otherNode->currentColor;
        if (neighborColor != VIDE) {
            count++;
        }
    }
    return count;
}


// Donne le nombre de voisins déjà coloré
int getUncoloredDegree(Node* node) {
    int count = 0;
    for (int i = 0; i < node->nbNeighbor; i++) {
        Edge* neighbor = (Edge*)node->otherNodes[i];
        if (neighbor->otherNode->currentColor == VIDE) {
            count++;
        }
    }
    return count;
}


// Trouve le prochain noeud selon les critères de DSatur
Node* getNextEdge(Graph* graph) {
    Node* maxNode = NULL;
    int maxSaturation = -1;
    int maxDegree = -1;

    for (int i = 0; i < graph->numNodes; i++) {
        Node* currentNode = graph->nodes[i];
        if (currentNode->currentColor != VIDE) continue;

        int saturation = getSaturationDegree(currentNode);
        int uncoloredDegree = getUncoloredDegree(currentNode);

        // Selectionner le noeud avec le plus haut taux de saturation
        if (saturation > maxSaturation || 
            (saturation == maxSaturation && uncoloredDegree > maxDegree)) {
            maxSaturation = saturation;
            maxDegree = uncoloredDegree;
            maxNode = currentNode;
        }
    }
    return maxNode;
}

// Trouve la couleur disponible la plus petite pour un noeud
int findAvailableColor(Node* node, int numNodes) {
    // On initialise la liste des couleurs disponibles
    int* usedColors = (int*)malloc(numNodes * sizeof(int));
    if(!usedColors){
        fprintf(stderr, "Erreur lors de l'allocation de memoire.\n");
    }

    for (int i = 0; i < numNodes; i++) {
        usedColors[i] = 0;
    }

    for (int i = 0; i < node->nbNeighbor; i++) {
        Edge* neighbor = (Edge*)node->otherNodes[i];
        int neighborColor = neighbor->otherNode->currentColor;
        if (neighborColor != VIDE) {
            usedColors[neighborColor] = 1; // La couleur est utilisée
        }
    }
    
    for (int color = 1; color < numNodes; color++) {
        if (!usedColors[color]) {
            free(usedColors);
            return color;
        }
    }
    free(usedColors);
    return -1; // Aucune couleur de trouvée
}

// Fonction principale
int colorGraphDSatur(Graph* graph) {
    if (!graph || graph->numNodes == 0) return 0;
    
    int maxColorUsed = 0;
    int nodesColored = 0;
    
    // Initialiser tous les noeuds comme étant non coloré
    for (int i = 0; i < graph->numNodes; i++) {
        graph->nodes[i]->currentColor = VIDE;
    }
    
    // Colorer les noeuds un à un
    while (nodesColored < graph->numNodes) {
        Node* nextNode = getNextEdge(graph);
        if (!nextNode) break;
        
        int color = findAvailableColor(nextNode, graph->numNodes);
        if (color == -1) {
            fprintf(stderr, "No available color for node %d\n", nextNode->id);
            return -1;
        }
        
        nextNode->currentColor = color;
        maxColorUsed = (color > maxColorUsed) ? color : maxColorUsed;
        nodesColored++;
    }
    
    return maxColorUsed;
}