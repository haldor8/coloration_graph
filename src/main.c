#include "main.h"
#include "graphes.h"

int main() {
    // Test 1 : Création manuelle du graphe
    printf("\n=== Test 1: Creation manuelle du graphe ===\n");
    Graph *graph = createGraph(5, 0);
    graphToString(graph);
    freeGraph(graph);
    if (graph) {
        printf("Graph memory freed\n");
    }

    // Test 2 : Lecture depuis un fichier
    printf("\n=== Test 2: Lecture depuis un fichier ===\n");
    Graph *graphFromFile = readGraphFromFile("graph/graphTest.col", 0);
    if (graphFromFile) {
        graphToString(graphFromFile);
        saveColoredGraph("../representation/graphes/test.json", graphFromFile);
        freeGraph(graphFromFile);
        printf("Graph from file memory freed\n");
    } else {
        printf("Failed to read graph from file\n");
    }

    return 0;
}