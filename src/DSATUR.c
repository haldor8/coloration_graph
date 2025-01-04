#include "DSATUR.h"

int getSaturationDegree(Node* node) {
    int count = 0;
    for (int i = 0; i < node->nbNeighbor; i++) {
        Vertex* neighbor = (Vertex*)node->otherNodes[i];
        int neighborColor = neighbor->otherNode->currentColor;
        if (neighborColor != VIDE) {
            count++;
        }
    }
    return count;
}


// Returns the number of uncolored neighbors
int getUncoloredDegree(Node* node) {
    int count = 0;
    for (int i = 0; i < node->nbNeighbor; i++) {
        Vertex* neighbor = (Vertex*)node->otherNodes[i];
        if (neighbor->otherNode->currentColor == VIDE) {
            count++;
        }
    }
    return count;
}


// Find the next vertex to color based on DSatur criteria
Node* getNextVertex(Graph* graph) {
    Node* maxNode = NULL;
    int maxSaturation = -1;
    int maxDegree = -1;

    for (int i = 0; i < graph->numNodes; i++) {
        Node* currentNode = graph->nodes[i];
        if (currentNode->currentColor != VIDE) continue;

        int saturation = getSaturationDegree(currentNode);
        int uncoloredDegree = getUncoloredDegree(currentNode);

        // Select vertex with highest saturation degree
        // If tied, select the one with highest uncolored degree
        if (saturation > maxSaturation || 
            (saturation == maxSaturation && uncoloredDegree > maxDegree)) {
            maxSaturation = saturation;
            maxDegree = uncoloredDegree;
            maxNode = currentNode;
        }
    }
    return maxNode;
}

// Find the lowest available color for a node
int findAvailableColor(Node* node, int numNodes) {
    // Mark colors that are used by neighbors
    int* usedColors = (int*)malloc(numNodes * sizeof(int));
    if(!usedColors){
        fprintf(stderr, "Erreur lors de l'allocation de memoire.\n");
    }

    for (int i = 0; i < numNodes; i++) {
        usedColors[i] = 0;
    }

    for (int i = 0; i < node->nbNeighbor; i++) {
        Vertex* neighbor = (Vertex*)node->otherNodes[i];
        int neighborColor = neighbor->otherNode->currentColor;
        if (neighborColor != VIDE) {
            usedColors[neighborColor] = 1;
        }
    }
    
    // Find the lowest available color
    for (int color = 1; color < numNodes; color++) {
        if (!usedColors[color]) {
            free(usedColors);
            return color;
        }
    }
    free(usedColors);
    return -1; // No available color found
}

// Main DSatur algorithm function
int colorGraphDSatur(Graph* graph) {
    if (!graph || graph->numNodes == 0) return 0;
    
    int maxColorUsed = 0;
    int nodesColored = 0;
    
    // Initialize all nodes as uncolored
    for (int i = 0; i < graph->numNodes; i++) {
        graph->nodes[i]->currentColor = VIDE;
    }
    
    // Color vertices one by one
    while (nodesColored < graph->numNodes) {
        Node* nextNode = getNextVertex(graph);
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