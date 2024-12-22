// #include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
        int id;
        struct Node **otherNode;
        int nbNeighbor;
        char color;
} Node;

typedef struct Arcs {
        int vertices1;
        int vertices2;
        int weight;
} Arcs;

typedef struct Graph {
        Node *nodes;
        Arcs *arcs;
        int numNodes;
        int numArcs;
        int directed; // 1 si oui 0 si non

} Graph;

void freeNode(Node *node) {
    if (node->otherNode) { // Libère le tableau des voisins, s'il existe
        free(node->otherNode);
        node->otherNode = NULL;
    }
}

void freeGraph(Graph *graph) {
    if (!graph)
        return; // Ne rien faire si le graphe est NULL

    // Libérer les ressources de chaque nœud
    for (int i = 0; i < graph->numNodes; i++) {
        freeNode(&graph->nodes[i]);
        printf("Node[%d] memory freed\n", i);
    }

    // Libérer le tableau des nœuds
    free(graph->nodes);

    // Libérer le tableau des arcs, s'il existe
    if (graph->arcs) {
        free(graph->arcs);
    }

    // Libérer la structure Graph elle-même
    free(graph);
}

Graph *createGraph(int numNodes, int directed) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph) {
        printf("Failed to allocate memory for Graph");
        exit(EXIT_FAILURE);
    }

    graph->nodes = (Node *)malloc(numNodes * sizeof(Node));
    for (int i = 0; i < numNodes; i++) {
        graph->nodes[i].id = i + 1;
        graph->nodes[i].nbNeighbor = 0;
        graph->nodes[i].otherNode = NULL;
        graph->nodes[i].color = 0;
    }
    graph->numNodes = numNodes;
    graph->directed = directed;
    graph->arcs = NULL;
    return graph;
}

int main() {

    Graph *graph = createGraph(5, 0);
    printf("graph with %d nodes \n", graph->numNodes);
    for (int i = 0; i < graph->numNodes; i++) {
        printf("Node %d, neighbor %d, color %d \n", graph->nodes[i].id,
               graph->nodes[i].nbNeighbor, graph->nodes[i].color);
    }

    freeGraph(graph);
    if (graph) {
        printf("Graph memory free");
    }
    return 0;
}
