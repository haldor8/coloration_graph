// #include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "graphes.h"

void freeNode(Node *node) {
    if (node->otherNode) {
        free(node->otherNode);
        node->otherNode = NULL;
    }
}

void freeGraph(Graph *graph) {
    if (!graph)
        return;
    for (int i = 0; i < graph->numNodes; i++) {
        freeNode(&graph->nodes[i]);
        printf("Node[%d] memory freed\n", i);
    }

    free(graph->nodes);

    if (graph->arcs) {
        free(graph->arcs);
    }

    free(graph);
}

void addArc(Graph *graph, int vertex1, int vertex2) {

    // TODO
    printf("Arc to add: %d -> %d\n", vertex1, vertex2);
    /*
    if (!graph->arcs) {
        graph->numArcs = 0;
        graph->arcs = (Arcs *)malloc(sizeof(Arcs));
    } else {
        graph->numArcs += 1;
        graph->arcs =
            (Arcs *)realloc(graph->arcs, graph->numArcs * sizeof(Arcs));
    }
    */
}
Graph *readGraphFromFile(const char *filename, int directed) {
    int numNodes, numEdges;

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open file \n");
        exit(EXIT_FAILURE);
    }
    Graph *graph = NULL;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (buffer[0] == 'c') {
            continue;
        }
        if (buffer[0] == 'p') {
            sscanf(buffer, "p edge %d %d", &numNodes, &numEdges);
            graph = createGraph(numNodes, directed);
        }
        if (buffer[0] == 'e') {
            int vertex1, vertex2;
            sscanf(buffer, "e %d %d", &vertex1, &vertex2);
            addArc(graph, vertex1, vertex2);
        }
    }
    fclose(file);
    return graph;
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
