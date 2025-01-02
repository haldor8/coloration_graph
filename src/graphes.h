#ifndef H_GRAPH
#define H_GRAPH

enum colors{
    VIDE,
    BLANC,
    GRIS,
    NOIR,
    BLEU,
    ROUGE,
    VERT,
    JAUNE,
    ROSE,
    VIOLET,
    MARRON,
    ORANGE
};

#define ENUM_SIZE 12 // Taille = "index" du dernier élément +1

typedef struct {
        int id;
        struct Node **otherNodes;
        int nbNeighbor;
        int* colorArray;
}Node;

typedef struct {
        int vertex1;
        int vertex2;
        int weight;
}Arc;

typedef struct {
        Node **nodes;
        Arc *arcs;
        int numNodes;
        int numArcs;
        int directed; // 1 si oui 0 si non
}Graph;

void freeNode(Node *node);
void freeGraph(Graph *graph);
void addArc(Graph *graph, int vertex1, int vertex2);

int* initializeColorArray();

Graph *readGraphFromFile(const char *filename, int directed);
Graph *createGraph(int numNodes, int directed);

void displayArcs(Arc* arcList, int length);
void addNeighbor(Node** array, int arraySize, int sourceNodeId, int finalNodeId);
Node* findNode(Node** array, int arraySize, int soughtNode);

void displayNeighbors(int nodeId, Node** nodeArray, int arraySize);
void graphToString(Graph* graph);
#endif