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

/**
 * Structure décrivant un noeud.
 * /!\ Toujours cast [otherNodes] en (Edge**) car la structure "Edge" est inconnue dans le scope de la structure "Node" à la compilation.
 */
typedef struct
{
        int id; // L'étiquette du noeud
        struct Edge **otherNodes; // Obligé de le définir comme tel car la structure vertex n'est pas encore déclaré aux yeux du compilateur
        int nbNeighbor; // Le nombre d'arcs
        // int* colorArray; // Vestiges
        int currentColor; // Sa couleur
} Node;

/**
 * Structure représentant un arc. 
 * Elle contient un pointeur vers un noeud (noeud pointé par un autre noeud), possédant un poids et un "booléen" qui sert pour la sauvegarde.
 */
typedef struct
{
        Node *otherNode; // Le voisin
        int duplicated;  // Pour savoir si on doit l'ajouter ou non à la sauvegarde
        int weight;      // Le poids de l'arc
} Edge;

/**
 * Globalement, les structures suivent une architecture d'arbre n-aire.
 * Le graphe stocke tous les noeuds, leur quantité et la quantité d'arcs. Il y a également un paramètre de mit en place pour changer vers un graphe orienté.
 * Les noeuds pointent directement vers les autres noeuds (facilite le parcours de l'arbre) et utilise la structure Edge pour utiliser, éventuellement, des poids.
 */
typedef struct
{
        Node **nodes; // La liste des noeuds
        int numNodes; // Le nombre de noeuds
        int numArcs;  // Le nombre d'arcs
        int directed; // 1 si oui 0 si non
} Graph;

/**
 * @brief Mélange un entier pour produire un hachage unique.
 * @param x L'entier à hacher.
 * @return Le résultat du hachage.
 */
uint32_t hash_function(uint32_t x);

/**
 * @brief Convertit un entier en une couleur hexadécimale au format #RRGGBB.
 * @param input L'entier à convertir.
 * @return Une chaîne représentant la couleur.
 */
char *intToColor(int input);

/**
 * @brief Libère la mémoire allouée pour un noeud.
 * @param node Le noeud à libérer.
 */
void freeNode(Node *node);

/**
 * @brief Libère la mémoire allouée pour un tableau de sommets.
 * @param edges Tableau de sommets.
 * @param arraySize Taille du tableau.
 */
void freeEdges(struct Edge **edges, int arraySize);

/**
 * @brief Libère la mémoire allouée pour un graphe.
 * @param graph Le graphe à libérer.
 */
void freeGraph(Graph *graph);

/**
 * @brief Trouve un noeud dans un tableau de noeuds.
 * @param array Tableau de noeuds.
 * @param arraySize Taille du tableau.
 * @param soughtNode Identifiant du noeud recherché.
 * @return Un pointeur vers le noeud trouvé, ou NULL si non trouvé.
 */
Node *findNode(Node **array, int arraySize, int soughtNode);

/**
 * @brief Ajoute un sommet (vertex) reliant deux noeuds.
 * @param finalNode Le noeud cible.
 * @param weight Poids de l'arc.
 * @param duplicated Indicateur si l'arc est dupliqué.
 * @return Un pointeur vers le sommet ajouté.
 */
Edge *addEdge(Node *finalNode, int weight, int duplicated);

/**
 * @brief Ajoute un voisin à un noeud dans un graphe.
 * @param graph Le graphe.
 * @param sourceNodeId ID du noeud source.
 * @param finalNodeId ID du noeud cible.
 * @param color couleur du noeud source.
 */
void addNeighbor(Graph *graph, int sourceNodeId, int finalNodeId, int color);

/**
 * @brief Lit un graphe à partir d'un fichier.
 * @param filename Nom du fichier.
 * @param directed Indique si le graphe est orienté (1) ou non (0).
 * @return Un pointeur vers le graphe lu.
 */
Graph *readGraphFromFile(const char *filename, int directed);

/**
 * @brief Sauvegarde un graphe au format .col dans un fichier.
 * @param filename Nom du fichier de sortie.
 * @param graph Le graphe à sauvegarder.
 */
void saveGraph(char *filename, Graph *graph);

/**
 * @brief Sauvegarde un graphe coloré au format JSON dans un fichier.
 * @param filename Nom du fichier de sortie.
 * @param graph Le graphe à sauvegarder.
 */
void saveColoredGraph(char *filename, Graph *graph);

/**
 * @brief Initialise un tableau de noeuds.
 * @param numNodes Nombre de noeuds à initialiser.
 * @return Un tableau de pointeurs vers les noeuds initialisés.
 */
Node **initializeNodes(int numNodes);

/**
 * @brief Crée un graphe vide avec un certain nombre de noeuds.
 * @param numNodes Nombre de noeuds.
 * @param directed Indique si le graphe est orienté (1) ou non (0).
 * @return Un pointeur vers le graphe créé.
 */
Graph *createGraph(int numNodes, int directed);

/**
 * @brief Affiche les informations d'un noeud et ses voisins.
 * @param nodeId ID du noeud.
 * @param verticiesArray Tableau des voisins.
 * @param arraySize Taille du tableau de voisins.
 */
void displayNode(int nodeId, Edge **verticiesArray, int arraySize);

/**
 * @brief Affiche les informations d'un graphe.
 * @param graph Le graphe à afficher.
 * @param displayEdges Si on doit afficher la liste de tous les arcs ou non. 1 = oui, 0 = non.
 */
void graphToString(Graph *graph, int displayEdges);

/**
 * @brief Vérifie si une coloration est valide pour un graphe. (Aucun noeud ne possède la même couleur qu'un voisin)
 * @param graph Le graphe.
 * @return 1 si valide, 0 sinon.
 */
int checkColoring(Graph *graph);

/**
 * @brief Trouve la couleur maximale utilisée dans un graphe.
 * @param graph Le graphe.
 * @return La couleur maximale.
 */
int biggestColor(Graph *graph);

/**
 * @brief Réinitialise les couleurs d'un graphe à 0.
 * @param graph Le graphe.
 */
void resetColoring(Graph *graph);

#endif