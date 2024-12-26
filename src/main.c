#include "main.h"
#include "graphes.h"

int main() {
    // Test 1 : Création manuelle du graphe
    printf("\n=== Test 1: Creation manuelle du graphe ===\n");
    Graph *graph = createGraph(5, 0);
    printf("graph with %d nodes \n", graph->numNodes);
    for (int i = 0; i < graph->numNodes; i++) {
        printf("Node %d, neighbor %d, color %d \n", graph->nodes[i].id,
               graph->nodes[i].nbNeighbor, graph->nodes[i].color);
    }
    freeGraph(graph);
    if (graph) {
        printf("Graph memory freed\n");
    }

    // Test 2 : Lecture depuis un fichier
    printf("\n=== Test 2: Lecture depuis un fichier ===\n");
    Graph *graphFromFile = readGraphFromFile("graph/graphTest.col", 0);
    if (graphFromFile) {
        printf("Graph from file with %d nodes\n", graphFromFile->numNodes);
        for (int i = 0; i < graphFromFile->numNodes; i++) {
            printf("Node %d, neighbor %d, color %d \n",
                   graphFromFile->nodes[i].id,
                   graphFromFile->nodes[i].nbNeighbor,
                   graphFromFile->nodes[i].color);
        }
        freeGraph(graphFromFile);
        printf("Graph from file memory freed\n");
    } else {
        printf("Failed to read graph from file\n");
    }

    return 0;
}