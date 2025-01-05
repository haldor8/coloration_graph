#ifndef DSATUR_HD
#define DSATUR_HD

#include "graphes.h"

/**
 * @brief Calcule le degré de saturation d'un noeud.
 * Le degré de saturation est défini comme le nombre de couleurs uniques utilisées 
 * par les voisins du noeud.
 * 
 * @param node Pointeur vers le noeud.
 * @return int Degré de saturation du noeud.
 */
int getSaturationDegree(Node* node);

/**
 * @brief Compte le nombre de voisins non colorés d'un noeud.
 * 
 * @param node Pointeur vers le noeud.
 * @return int Nombre de voisins non colorés.
 */
int getUncoloredDegree(Node* node);

/**
 * @brief Sélectionne le prochain noeud à colorer selon les critères de DSATUR.
 * La fonction sélectionne le noeud ayant le degré de saturation le plus élevé.
 * En cas d'égalité, elle choisit celui avec le plus grand nombre de voisins non colorés.
 * 
 * @param graph Pointeur vers le graphe.
 * @return Node* Pointeur vers le noeud à colorer. Retourne NULL si tous les noeuds sont colorés.
 */
Node* getNextVertex(Graph* graph);

/**
 * @brief Trouve la plus petite couleur disponible pour un noeud.
 * Cette fonction recherche une couleur non utilisée par les voisins du noeud.
 * 
 * @param node Pointeur vers le noeud.
 * @param numNodes Nombre total de noeuds dans le graphe (limite des couleurs possibles).
 * @return int La plus petite couleur disponible. Retourne -1 si aucune couleur n'est disponible.
 */
int findAvailableColor(Node* node, int numNodes);

/**
 * @brief Colore un graphe en utilisant l'algorithme DSATUR.
 * Cet algorithme attribue des couleurs aux noeuds d'un graphe en minimisant le nombre 
 * total de couleurs utilisées tout en respectant la contrainte que deux noeuds adjacents 
 * ne peuvent pas avoir la même couleur.
 * 
 * @param graph Pointeur vers le graphe à colorer.
 * @return int Le nombre maximal de couleurs utilisées. Retourne -1 en cas d'erreur.
 */
int colorGraphDSatur(Graph* graph);


#endif