#include "main.h"
#include "welshPowell.h"
#include "hillClimbing.h"

double runAlgorithm(int (*algorithm)(Graph *), Graph *graph, int times)
{
    double average = 0;
    clock_t start = 0, end = 0;

    for (int i = 0; i < times; i++)
    {
        start = clock();
        algorithm(graph);
        end = clock();
        double current_time = (double)(end - start);
        if (i == 0)
        {
            average = current_time;
        }
        else
        {
            average = (average + current_time) / 2;
        }
        if (i < times - 1)
        {
            resetColoring(graph);
        }
    }
    return average;
}

int main(int argc, char *argv[])
{
    /*
    // Test 1 : Création manuelle du graphe
    printf("\n=== Test 1: Creation manuelle du graphe ===\n");
    Graph *graph = createGraph(5, 0);
    // graphToString(graph);
    freeGraph(graph);
    if (graph) {
        printf("Graph memory freed\n");
    }
    */

    if (argc != 4 && argc != 5)
    {
        fprintf(stderr, "Nombre de parametres invalide. Utilisation : \"./color_graph.exe <dossier/fichier.extension> <dsatur | welshpowell> <nb_executions> opt : <sauvegarder>\n");
        exit(-1);
    }

    int (*algo)(Graph *);
    if (!strcmp(argv[2], "dsatur"))
    {
        algo = &colorGraphDSatur;
    }
    else if (!strcmp(argv[2], "welshpowell"))
    {
        algo = &welshPowell;
    }
    else
    {
        fprintf(stderr, "Algorithme inconnu ou mal tape. Veuillez choisir parmis ceux connus <dsatur | welshpowell>\n");
        exit(-1);
    }

    // Test 3 : Lecture depuis un fichier
    printf("\n=== Coloration de %s par l'algorithme %s ===\n", argv[1], argv[2]);
    Graph *graphFromFile = readGraphFromFile(argv[1], 0);
    if (graphFromFile)
    {
        graphToString(graphFromFile, 0);
        printf("Temps d'execution moyen : %lf ms\n", runAlgorithm(algo, graphFromFile, atoi(argv[3])));
        printf("Est-ce que la coloration est valide : %d\n", checkColoring(graphFromFile));
        printf("Nombre de couleurs utilisees : %d\n", biggestColor(graphFromFile));

        if (argc == 5)
        {
            if (!strcmp(argv[4], "sauvegarder"))
            {
                saveColoredGraph("../representation/graphes/resultat.json", graphFromFile);
            }
        }

        freeGraph(graphFromFile);
    }

    return 0;
}