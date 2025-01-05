#include "main.h"
#include "welshPowell.h"
#include "hillClimbing.h"

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

    /*
    // Test 2 : Lecture depuis un fichier
    printf("\n=== Test 2: Lecture depuis un fichier ===\n");
    Graph *graphFromFile = readGraphFromFile("graph/DSJC1000.9.col", 0);
    if (graphFromFile) {
        graphToString(graphFromFile, 0);
        printf("Temps d'execution moyen : %lf ms\n", runAlgorithm(&colorGraphDSatur, graphFromFile, 10));
        printf("Est-ce que la coloration est valide : %d\n", checkColoring(graphFromFile));
        printf("Nombre de couleurs utilisees : %d\n", biggestColor(graphFromFile));
        //saveColoredGraph("../representation/graphes/test.json", graphFromFile);

        freeGraph(graphFromFile);
        printf("Graph from file memory freed\n");
    } else {
        printf("Failed to read graph from file\n");
    }
    */

    // Test 3 : Lecture depuis un fichier
    printf("\n=== Test 3: Lecture depuis un fichier algorithme WELSH-POWELL ===\n");
    Graph *graphFromFile2 = readGraphFromFile("graph/DSJC1000.9.col", 0);
    if (graphFromFile2) {
        graphToString(graphFromFile2, 0);
        printf("Temps d'execution moyen : %lf ms\n", runAlgorithm(&welshPowell, graphFromFile2, 10));
        printf("Est-ce que la coloration est valide : %d\n", checkColoring(graphFromFile2));
        printf("Nombre de couleurs utilisees : %d\n", biggestColor(graphFromFile2));
        //saveColoredGraph("../representation/graphes/test.json", graphFromFile);

        freeGraph(graphFromFile2);
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