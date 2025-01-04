#include "main.h"
#include "graphes.h"
#include "DSATUR.h"

#include "time.h"

double runAlgorithm(int (*algorithm)(Graph*), Graph* graph, int times) {
    double average = 0;
    clock_t start = 0, end = 0;

    for(int i = 0; i < times; i++) {
        start = clock();
        algorithm(graph);
        end = clock();
        double current_time = (double)(end - start);
        if(i == 0) {
            average = current_time;
        } else {
            average = (average + current_time) / 2;
        }
        if(i < times - 1){
            resetColoring(graph);
        }
    }
    return average;
}

int main() {
    // Test 1 : Création manuelle du graphe
    printf("\n=== Test 1: Creation manuelle du graphe ===\n");
    Graph *graph = createGraph(5, 0);
    // graphToString(graph);
    freeGraph(graph);
    if (graph) {
        printf("Graph memory freed\n");
    }

    // Test 2 : Lecture depuis un fichier
    printf("\n=== Test 2: Lecture depuis un fichier ===\n");
    Graph *graphFromFile = readGraphFromFile("graph/inithx.col", 0);
    if (graphFromFile) {
        // graphToString(graphFromFile);
        graphToString(graphFromFile);
        printf("Temps d'execution moyen : %lf ms\n", runAlgorithm(&colorGraphDSatur, graphFromFile, 10));
        printf("Est-ce que la coloration est valide : %d\n", verifierColoration(graphFromFile));
        printf("Nombre de couleurs utilisees : %d\n", couleurLaPlusGrande(graphFromFile));
        //saveColoredGraph("../representation/graphes/test.json", graphFromFile);

        freeGraph(graphFromFile);
        printf("Graph from file memory freed\n");
    } else {
        printf("Failed to read graph from file\n");
    }
    
    /*
    clock_t start = clock();
    colorGraphDSatur(graphFromFile);
    clock_t end = clock();

    printf("Temps d'execution : %lf ms\n", (double)(end - start));
    printf("Est-ce que la coloration est valide : %d\n", verifierColoration(graphFromFile));
    printf("Nombre de couleurs utilisees : %d\n", couleurLaPlusGrande(graphFromFile));
    */
    return 0;
}