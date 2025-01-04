#ifndef H_GRAPH
#define H_GRAPH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdint.h>
#define VIDE 0
/* // Vestiges
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

extern const char* colorsToString[];

#define ENUM_SIZE 12 // Taille = "index" du dernier élément +1
*/
typedef struct {
        int id;
        struct Vertex **otherNodes;
        int nbNeighbor;
        // int* colorArray; // Vestiges
        int currentColor;
}Node;

typedef struct {
        Node* otherNode;
        int duplicated; // Pour savoir si on doit l'ajouter ou non à la sauvegarde
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

char* intToColor(int);


Vertex* addVertex(Node* finalNode, int weight, int directed);
int* initializeColorArray();
void addNeighbor(Graph* graph, int sourceNodeId, int finalNodeId);
Node* findNode(Node** array, int arraySize, int soughtNode);

Graph *readGraphFromFile(const char *filename, int directed);
Graph *createGraph(int numNodes, int directed);

void saveGraph(char* filename, Graph* graph);
void saveColoredGraph(char* filename, Graph* graph);


void displayNode(int nodeId, Vertex** nodeArray, int arraySize);
void graphToString(Graph* graph);

int verifierColoration(Graph* graph);
int couleurLaPlusGrande(Graph* graph);
void resetColoring(Graph *graph);
#endif