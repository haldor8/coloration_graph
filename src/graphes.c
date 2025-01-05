// #include <cstdlib>
#include "graphes.h"

/* // Vestiges
const char* colorsToString[] = {
    "VIDE", 
    "BLANC",
    "GRIS", 
    "NOIR", 
    "BLEU", 
    "ROUGE",
    "VERT", 
    "JAUNE",
    "ROSE", 
    "VIOLET",
    "MARRON",
    "ORANGE"
};
*/
// Fonction de hachage pour rendre les couleurs semi-aléatoires
uint32_t hash_function(uint32_t x) {
    x = ((x >> 16) ^ x) * 0x45d9f3b;  // Mélange le nombre
    x = ((x >> 16) ^ x) * 0x45d9f3b;  // Mélange à nouveau
    x = (x >> 16) ^ x;                // Finalise le hachage
    return x;
}

// Fonction qui retourne une couleur en format #RRGGBB
char *intToColor(int input) {
    static char output[8];                      // Chaîne pour stocker la couleur
    uint32_t hash = hash_function((uint32_t)input); // Génère un hash unique
    uint8_t r = (hash & 0xFF0000) >> 16;           // Composante rouge
    uint8_t g = (hash & 0x00FF00) >> 8;            // Composante verte
    uint8_t b = (hash & 0x0000FF);                 // Composante bleue

    // Formater la couleur dans la chaîne de sortie au format #RRGGBB
    sprintf(output, "#%02X%02X%02X", r, g, b);

    return output; // Retourner la chaîne
}

/* // Vestiges
int* initializeColorArray(){
    int* initializedArray = (int*)malloc(ENUM_SIZE * sizeof(int)); // On alloue un tableau contenant toutes les couleurs possibles
    for(int i = 0; i < ENUM_SIZE; i++){
        initializedArray[i] = i; // On cast l'integer dans sa valeur correspondante dans l'enum
    }
    return initializedArray;
}

int* reinitializeColorArray(int* array){
    free(array);
    return initializeColorArray();
}

void resetColor(int* array, int color){
    array[color] = color;
}

void removeColorFromArray(int* array, int color){
    array[color] = VIDE;
}


void freeColorArray(int* array){
    free(array);
}
*/

void freeNode(Node *node) {
    // freeColorArray(node->colorArray);
    if (node->otherNodes) {
        freeVertices(node->otherNodes, node->nbNeighbor);
        node->otherNodes = NULL;
    }
    free(node);
}

void freeVertices(struct Vertex** vertices, int arraySize){
    for(int i = 0; i < arraySize; i++){
        free(vertices[i]);
    }
    free(vertices);
}

void freeGraph(Graph *graph) {
    if (!graph)
        return;

    for (int i = 0; i < graph->numNodes; i++) {
        freeNode(graph->nodes[i]);

        // printf("Node[%d] memory freed\n", i); // Ligne de debug

        // printf("Node[%d] memory freed\n", i); // Ligne de debug
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

Vertex* addVertex(Node* finalNode, int weight, int duplicated){
    Vertex* newVertex = malloc(sizeof(Vertex));
    newVertex->otherNode = finalNode;
    newVertex->weight = weight;
    newVertex->duplicated = duplicated;
    return newVertex;
}

void addNeighbor(Graph* graph, int sourceNodeId, int finalNodeId){
    Node* sourceNode = findNode(graph->nodes, graph->numNodes, sourceNodeId);
    Node* finalNode = findNode(graph->nodes, graph->numNodes, finalNodeId);

    Vertex** newArray;
    if(sourceNode->nbNeighbor == 0){
        newArray = (Vertex**)malloc(sizeof(Vertex*));
    }else{
        newArray = (Vertex**)realloc(sourceNode->otherNodes, (sourceNode->nbNeighbor+1) * sizeof(Vertex*));
    }

    sourceNode->otherNodes = (struct Vertex**)newArray;
    sourceNode->otherNodes[sourceNode->nbNeighbor] = (struct Vertex*)addVertex(finalNode, 1, 0); // Duplicated est à 0 car c'est le vertex principal qu'on ajoute
    sourceNode->nbNeighbor += 1;

    if(!graph->directed){ // Si le graphe est non-orienté, alors on ajoute aussi l'arc dans l'autre sens
        Vertex** secondArray;
        if(finalNode->nbNeighbor == 0){
            secondArray = (Vertex**)malloc(sizeof(Vertex*));
        }else{
            secondArray = (Vertex**)realloc(finalNode->otherNodes, (finalNode->nbNeighbor+1) * sizeof(Vertex*));
        }

        finalNode->otherNodes = (struct Vertex**)secondArray;
        finalNode->otherNodes[finalNode->nbNeighbor] = (struct Vertex*)addVertex(sourceNode, 1, 1); // Duplicated est à 1, de ce fait
        finalNode->nbNeighbor += 1;
    }

    graph->numArcs += 1;
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
                addNeighbor(graph, vertex1, vertex2);
            }else{
                fprintf(stderr, "Graphe non instancie\n");
                exit(-1);
            }
        }
    }
    fclose(file);
    return graph;
}

void saveGraph(char* filename, Graph* graph){ // Format col
    FILE* file = fopen(filename, "w");
    fprintf(file, "c %s\n", filename);
    fprintf(file, "p edge %d %d", graph->numNodes, graph->numArcs);
    for(int node = 0; node < graph->numNodes; node++){
        Node* currNode = graph->nodes[node];
        for(int vertex = 0; vertex < currNode->nbNeighbor; vertex++){
            Vertex* currVertex = (Vertex *)currNode->otherNodes[vertex];
            if(currVertex->duplicated == 0){ // Si ce n'est pas un arc dupliqué car le graphe est non-orienté
                fprintf(file, "e %d %d", currNode->id, currVertex->otherNode->id);
            }
        }
    }
}

void saveColoredGraph(char* filename, Graph* graph){ // Format json

    printf("Sauvegarde du graphe : %s\n", filename);
    FILE* file = fopen(filename, "w");
    fprintf(file, "{\n");
    fprintf(file, "\"nom\" : \"%s\",\n", filename);
    fprintf(file, "\"nbArcs\" : \"%d\",\n", graph->numArcs);
    fprintf(file, "\"nbNoeuds\" : \"%d\",\n", graph->numNodes);

    fprintf(file, "\"noeuds\" : [\n");
    for(int node = 0; node < graph->numNodes; node++){
        fprintf(file, "{\n");
        Node* currNode = graph->nodes[node];

        fprintf(file, "\"nom\" : \"%d\",\n", currNode->id);
        
        fprintf(file, "\"couleur\" : \"%s\",\n", intToColor(currNode->currentColor));
        
        fprintf(file, "\"arcs\" : [\n");
        for(int vertex = 0; vertex < currNode->nbNeighbor; vertex++){
            Vertex* currVertex = (Vertex *)currNode->otherNodes[vertex];
            if(currVertex->duplicated == 0){ // Si ce n'est pas un arc dupliqué car le graphe est non-orienté
                fprintf(file, "{\n");
                fprintf(file, "\"nom\" :\"%d\",", currVertex->otherNode->id);
                fprintf(file, "\"poids\" :\"%d\"\n", currVertex->weight);
                fprintf(file, "}");

                fprintf(file, "}");

                if(vertex < currNode->nbNeighbor - 1){
                    Vertex* nextVertex = (Vertex *)currNode->otherNodes[vertex+1];
                    if(nextVertex->duplicated == 0){
                        fprintf(file, ",");
                    }
                }
                fprintf(file, "\n");
            }
        }
        fprintf(file, "]\n");

        fprintf(file, "}");
        if(node < graph->numNodes - 1){
            fprintf(file, ",");
        }
        fprintf(file, "\n");
    }
    fprintf(file, "]\n}");
}

Node** initializeNodes(int numNodes){
    Node** nodeArray = (Node **)malloc(numNodes * sizeof(Node*));

    for (int i = 0; i < numNodes; i++) {
        nodeArray[i] = (Node*)malloc(sizeof(Node));
        nodeArray[i]->id = i + 1;
        nodeArray[i]->nbNeighbor = 0;
        nodeArray[i]->otherNodes = NULL;
        // nodeArray[i]->colorArray = initializeColorArray();
        // nodeArray[i]->colorArray = initializeColorArray();
        nodeArray[i]->currentColor = VIDE;
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
    return graph;
}

void displayNode(int nodeId, Vertex** verticiesArray, int arraySize){
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

void graphToString(Graph* graph, int displayVertices){
    printf("Graphe avec %d noeuds et %d arcs.\n", graph->numNodes, graph->numArcs);
    if(displayVertices){
        for(int i = 0; i < graph->numNodes; i++){
            displayNode(graph->nodes[i]->id, (Vertex **)graph->nodes[i]->otherNodes, graph->nodes[i]->nbNeighbor);
        }
    }
}

int checkColoring(Graph* graph){ // 1 = Coloration valide, 0 = erreur
    for(int node = 0; node < graph->numNodes; node++){
        Node* currNode = graph->nodes[node];
        for(int vertex = 0; vertex < currNode->nbNeighbor; vertex++){
            Vertex* currVertex = (Vertex*)currNode->otherNodes[vertex];
            if(currNode->currentColor == currVertex->otherNode->currentColor){
                return 0;
            }
        }
    }
    return 1;
}

int biggestColor(Graph* graph){
    int currColor = -1;
    for(int node = 0; node < graph->numNodes; node++){
        Node* currNode = graph->nodes[node];
        if(currNode->currentColor > currColor){
            currColor = currNode->currentColor;
        }
    }
    return currColor;
}


void resetColoring(Graph *graph){
    for(int node = 0; node < graph->numNodes; node++){
        Node* currNode = graph->nodes[node];
        currNode->currentColor = VIDE;
    }
}
