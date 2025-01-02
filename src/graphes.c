// #include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include "graphes.h"

int* initializeColorArray(){
    int* initializedArray = (int*)malloc(ENUM_SIZE * sizeof(int)); // On alloue un tableau contenant toutes les couleurs possibles
    for(int i = 0; i < ENUM_SIZE; i++){
        initializedArray[i] = i; // On cast l'integer dans sa valeur correspondante dans l'enum
    }
    return initializedArray;
}

/*
void removeColorFromArray(enum colors* array, int index){

}
*/

void freeColorArray(int* array){
    free(array);
}


void freeNode(Node *node) {
    freeColorArray(node->colorArray);
    if (node->otherNodes) {
        freeVertices(node->otherNodes, node->nbNeighbor);
        node->otherNodes = NULL;
    }
    free(node);
}

void freeVertices(struct Vertex** verticies, int arraySize){
    for(int i = 0; i < arraySize; i++){
        free(verticies[i]);
    }
    free(verticies);
}

void freeGraph(Graph *graph) {
    if (!graph)
        return;

    for (int i = 0; i < graph->numNodes; i++) {
        freeNode(graph->nodes[i]);
        printf("Node[%d] memory freed\n", i);
    }

    free(graph->nodes);
    free(graph);
}

/*
void addArc(Graph *graph, int vertex1, int vertex2) {
    printf("Arc to add: %d -> %d\n", vertex1, vertex2);
    if(graph->numArcs == 0){
        graph->vertices = (Vertex*)malloc(sizeof(Vertex));
        graph->vertices[graph->numArcs].otherNode = vertex2;
        graph->vertices[graph->numArcs].weight = 1;
        graph->numArcs++; // On incrémente après car les index sont décalés de -1
    }else{
        Arc* reallocatedArray = realloc(graph->vertices, (graph->numArcs + 1) * sizeof(Arc));
        if(reallocatedArray){
            reallocatedArray[graph->numArcs].vertex1 = vertex1;
            reallocatedArray[graph->numArcs].vertex2 = vertex2;

            reallocatedArray[graph->numArcs].weight = 1;

            graph->arcs = reallocatedArray;
            graph->numArcs++; // On incrémente après car les index sont décalés de -1
        }else{
            fprintf(stderr, "Erreur lors de la reallocation, sortie du programme");
            exit(-1);
        }
        displayArcs(reallocatedArray, graph->numArcs);
    }
    addNeighbor(graph->nodes, graph->numNodes, vertex1, vertex2);
}
*/
Node* findNode(Node** array, int arraySize, int soughtNode){
    for(int i = 0; i < arraySize; i++){
        if(array[i]->id == soughtNode){
            return array[i];
        }
    }
    // Si on n'a pas trouvé le noeud, alors on affiche une erreur sur le flux stderr
    fprintf(stderr, "Noeud : %d non trouve", soughtNode);
    return NULL;
}

Vertex* addVertex(Node* finalNode, int weight){
    Vertex* newVertex = malloc(sizeof(Vertex));
    newVertex->otherNode = finalNode;
    newVertex->weight = weight;
    return newVertex;
}

void addNeighbor(Node** array, int arraySize, int sourceNodeId, int finalNodeId){
    Node* sourceNode = findNode(array, arraySize, sourceNodeId);
    Node* finalNode = findNode(array, arraySize, finalNodeId);

    Vertex** newArray;
    if(sourceNode->nbNeighbor == 0){
        newArray = (Vertex**)malloc(sizeof(Vertex*));
    }else{
        newArray = (Vertex**)realloc(sourceNode->otherNodes, (sourceNode->nbNeighbor+1) * sizeof(Vertex*));
    }
    sourceNode->otherNodes = (struct Vertex**)newArray;
    sourceNode->otherNodes[sourceNode->nbNeighbor] = (struct Vertex*)addVertex(finalNode, 1);
    sourceNode->nbNeighbor += 1;
}

Graph *readGraphFromFile(const char *filename, int directed) {
    int numNodes, numEdges;

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Fichier non trouve\n");
        exit(-1);
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
            if(graph != NULL){
                int vertex1, vertex2;
                sscanf(buffer, "e %d %d", &vertex1, &vertex2);
                addNeighbor(graph->nodes, graph->numNodes, vertex1, vertex2);
            }else{
                fprintf(stderr, "Graphe non instancie\n");
                exit(-1);
            }
        }
    }
    fclose(file);
    return graph;
}

Node** initializeNodes(int numNodes){
    Node** nodeArray = (Node **)malloc(numNodes * sizeof(Node*));

    for (int i = 0; i < numNodes; i++) {
        nodeArray[i] = (Node*)malloc(sizeof(Node));
        nodeArray[i]->id = i + 1;
        nodeArray[i]->nbNeighbor = 0;
        nodeArray[i]->otherNodes = NULL;
        nodeArray[i]->colorArray = initializeColorArray();
    }
    return nodeArray;
}

Graph *createGraph(int numNodes, int directed) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (!graph) {
        printf("Probleme au moment d'allouer le graph");
        exit(-1);
    }

    graph->nodes = initializeNodes(numNodes);

    graph->numNodes = numNodes;
    graph->numArcs = 0;
    graph->directed = directed;
    graph->vertices = NULL;
    return graph;
}

/*
void displayArcs(Vertex* arcList, int length){
    for(int i = 0; i < length; i++){
        printf("Vertex1 : %d, vertex2 : %d, weight : %d\n", arcList[i].vertex1, arcList[i].vertex2, arcList[i].weight);
    }
}
*/

void displayNeighbors(int nodeId, Vertex** verticiesArray, int arraySize){
    if(arraySize == 0){
        printf("Noeud numero %d : aucun voisin", nodeId);
        printf("\n");
    }
    else{
        printf("Noeud numero %d qui pointe vers les noeuds : ", nodeId);
        for(int i = 0; i < arraySize; i++){
            printf("%d (%d), ", verticiesArray[i]->otherNode->id, verticiesArray[i]->weight);
        }
        printf("\n");
    }
}

void graphToString(Graph* graph){
    printf("Graphe avec %d noeuds.\n", graph->numNodes);
    for(int i = 0; i < graph->numNodes; i++){
        displayNeighbors(graph->nodes[i]->id, (Vertex **)graph->nodes[i]->otherNodes, graph->nodes[i]->nbNeighbor);
    }
}