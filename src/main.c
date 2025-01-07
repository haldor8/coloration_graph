#include "main.h"
#include "welshPowell.h"
#include "hillClimbing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void createGraphManually() {
    int numNodes, numEdges;
    printf("\nCreation d'un graphe a la main.\n");
    printf("Entrez le nombre de nœuds: ");
    scanf("%d", &numNodes);

    if (numNodes <= 0) {
        fprintf(stderr, "Le nombre de nœuds doit être superieur a 0.\n");
        exit(EXIT_FAILURE);
    }

    printf("Entrez le nombre d'arcs: ");
    scanf("%d", &numEdges);

    Graph *graph = createGraph(numNodes, 0);

    printf("\nAjoutez les arcs entre les nœuds (nœuds entre 1 et %d):\n", numNodes);
    for (int i = 0; i < numEdges; i++) {
        int node1, node2;
        printf("Arc %d: Entrez les deux nœuds connectes (ex: 1 2): ", i + 1);
        scanf("%d %d", &node1, &node2);

        if (node1 < 1 || node1 > numNodes || node2 < 1 || node2 > numNodes) {
            fprintf(stderr, "Les nœuds doivent être compris entre 1 et %d.\n", numNodes);
            i--;  // Redemande cet arc si les nœuds sont invalides
            continue;
        }

        addNeighbor(graph, node1, node2, 0);  // Ajout de l'arc entre les deux nœuds
    }

    printf("\nLe graphe a ete cree avec succès.\n");

    int choice = selectAlgorithm();
    int (*algorithm)(Graph *) = (choice == 1) ? colorGraphDSatur : welshPowell;

    int nbExecutions;
    printf("Entrez le nombre d'executions pour mesurer la performance: ");
    scanf("%d", &nbExecutions);

    printf("\nExecution de l'algorithme...\n");
    double execTime = runAlgorithm(algorithm, graph, nbExecutions);
    printf("Temps d'execution moyen: %.2f ms\n", execTime);
    printf("Nombre de couleurs utilisees: %d\n", biggestColor(graph));
    printf("Coloration valide: %s\n", checkColoring(graph) ? "Oui" : "Non");

    saveResult(graph);
    freeGraph(graph);
}


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
// Menu principal
int mainMenu() {
    int choice;
    printf("\n=== Menu Principal ===\n");
    printf("1. Colorer un graphe\n");
    printf("2. Verifier une coloration\n");
    printf("3. Creer un graphe a la main\n");
    printf("Votre choix: ");
    scanf("%d", &choice);
    if (choice < 1 || choice > 3) {
        fprintf(stderr, "Choix invalide. Veuillez selectionner 1, 2 ou 3.\n");
        exit(EXIT_FAILURE);
    }
    return choice;
}

// Selection de l'algorithme
int selectAlgorithm() {
    int choice;
    printf("\nChoisissez l'algorithme de coloration:\n");
    printf("1. DSATUR\n");
    printf("2. Welsh-Powell\n");
    printf("Votre choix: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        fprintf(stderr, "Choix invalide.\n");
        exit(EXIT_FAILURE);
    }
    return choice;
}

// Sauvegarde des resultats
void saveResult(Graph *graph) {
    int saveChoice;
    printf("\nVoulez-vous sauvegarder la coloration? (1: Oui, 0: Non): ");
    scanf("%d", &saveChoice);
    if (saveChoice) {
        char format[5];
        printf("Choisissez le format (json/col): ");
        scanf("%s", format);
        char filename[256];
        printf("Entrez le nom du fichier de sauvegarde (sans extension): ");
        scanf("%s", filename);

        // Ajout du chemin "save/" devant le nom du fichier
        char fullPath[300] = "save/";
        strcat(fullPath, filename);

        if (strcmp(format, "json") == 0) {
            strcat(fullPath, ".json");
            saveColoredGraph(fullPath, graph);
        } else if (strcmp(format, "col") == 0) {
            strcat(fullPath, ".col");
            saveGraph(fullPath, graph);
        } else {
            fprintf(stderr, "Format de fichier invalide.\n");
        }

        printf("Fichier sauvegarde dans : %s\n", fullPath);
    }
}


// Verification de la validite de la coloration
void checkColoringInput() {
    char fileName[256];
    printf("\nEntrez le nom du fichier .col a verifier (ex: bigGraph.col): ");
    scanf("%s", fileName);

    char filePath[300] = "graph/";
    strcat(filePath, fileName);

    Graph *graph = readGraphFromFile(filePath, 0);
    if (!graph) {
        fprintf(stderr, "Erreur: Impossible de lire le fichier.\n");
        exit(EXIT_FAILURE);
    }

    int valid = checkColoring(graph);
    printf("La coloration est %s.\n", valid ? "valide" : "invalide");
    freeGraph(graph);
}


// Fonction pour colorer un graphe
void colorGraph() {
    char fileName[256];
    printf("\nEntrez le nom du fichier .col a utiliser (ex: myGraph.col): ");
    scanf("%s", fileName);

    char fullPath[256] = "graph/";
    strcat(fullPath, fileName);

    Graph *graph = readGraphFromFile(fullPath, 0);
    if (!graph) {
        fprintf(stderr, "Erreur: Impossible de charger le graphe.\n");
        exit(EXIT_FAILURE);
    }

    int choice = selectAlgorithm();
    int (*algorithm)(Graph *) = (choice == 1) ? colorGraphDSatur : welshPowell;

    int nbExecutions;
    printf("Entrez le nombre d'executions pour mesurer la performance: ");
    scanf("%d", &nbExecutions);

    printf("\nExecution de l'algorithme...\n");
    double execTime = runAlgorithm(algorithm, graph, nbExecutions);
    printf("Temps d'execution moyen: %.2f ms\n", execTime);
    printf("Nombre de couleurs utilisees: %d\n", biggestColor(graph));
    printf("Coloration valide: %s\n", checkColoring(graph) ? "Oui" : "Non");

    saveResult(graph);
    freeGraph(graph);
}

int main() {
    int choice = mainMenu();

    if (choice == 1) {
        colorGraph();  // Coloration d'un graphe
    } else if (choice == 2) {
        checkColoringInput();  // Verification d'une coloration
    } else if (choice == 3) {
        createGraphManually();  // Creation d'un graphe a la main
    }

    printf("\nFin du programme.\n");
    return 0;
}