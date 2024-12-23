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
        int vertex1;
        int vertex2;
        int weight;
} Arcs;

typedef struct Graph {
        Node *nodes;
        Arcs *arcs;
        int numNodes;
        int numArcs;
        int directed; // 1 si oui 0 si non

} Graph;

void freeNode(Node *node);
void freeGraph(Graph *graph);
void addArc(Graph *graph, int vertex1, int vertex2);
Graph *readGraphFromFile(const char *filename, int directed);

Graph *createGraph(int numNodes, int directed);

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
int main() {
    // Test 1 : Création manuelle du graphe
    printf("\n=== Test 1: Création manuelle du graphe ===\n");
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
    Graph *graphFromFile = readGraphFromFile("graphTest.col", 0);
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
