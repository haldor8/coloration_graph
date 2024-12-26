#ifndef H_GRAPH
#define H_GRAPH

enum couleur{
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

typedef struct {
        int id;
        struct Node **otherNode;
        int nbNeighbor;
        enum couleur color;
}Node;

typedef struct {
        int vertex1;
        int vertex2;
        int weight;
}Arc;

typedef struct {
        Node *nodes;
        Arc *arcs;
        int numNodes;
        int numArcs;
        int directed; // 1 si oui 0 si non

}Graph;

void freeNode(Node *node);
void freeGraph(Graph *graph);
void addArc(Graph *graph, int vertex1, int vertex2);

Graph *readGraphFromFile(const char *filename, int directed);
Graph *createGraph(int numNodes, int directed);

#endif