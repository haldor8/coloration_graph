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

struct Vertex;

typedef struct {
        int id;
        struct Vertex **otherNodes;
        int nbNeighbor;
        int* colorArray;
        int currentColor;
}Node;

typedef struct {
        Node* otherNode;
        int weight;
}Vertex;

typedef struct {
        Node **nodes;
        int numNodes;
        int numArcs;
        int directed; // 1 si oui 0 si non
}Graph;

void freeNode(Node *node);
void freeGraph(Graph *graph);
void freeVertices(struct Vertex** vertices, int arraySize);
void freeColorArray(int* array);


Vertex* addVertex(Node* finalNode, int weight);
int* initializeColorArray();
void addNeighbor(Graph* graph, int sourceNodeId, int finalNodeId);
Node* findNode(Node** array, int arraySize, int soughtNode);

Graph *readGraphFromFile(const char *filename, int directed);
Graph *createGraph(int numNodes, int directed);


void displayNode(int nodeId, Vertex** nodeArray, int arraySize);
void graphToString(Graph* graph);
#endif