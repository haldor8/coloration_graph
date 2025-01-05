#ifndef WELSHPOWELL_H
#define WELSHPOWELL_H

#include "graphes.h"
/**
 * @brief Compare le degré (nombre de voisins) de deux nœuds pour le tri
 * 
 * Cette fonction est utilisée comme comparateur pour qsort() afin de trier
 * les nœuds par ordre décroissant de leur degré. Le tri décroissant est
 * crucial pour l'algorithme de Welsh-Powell car il permet de commencer
 * la coloration par les nœuds les plus connectés.
 * 
 * @param a Pointeur vers le premier nœud à comparer (Node**)
 * @param b Pointeur vers le second nœud à comparer (Node**)
 * @return int 
 *         - Valeur positive si le degré de b est plus grand que celui de a
 *         - Valeur négative si le degré de a est plus grand que celui de b
 *         - 0 si les degrés sont égaux
 */
int compareDegree(const void* a, const void* b);

/**
 * @brief Vérifie si deux nœuds sont voisins dans le graphe
 * 
 * Parcourt la liste des voisins du premier nœud pour vérifier si le second
 * nœud y figure. Cette fonction est essentielle pour s'assurer que deux
 * nœuds adjacents ne reçoivent pas la même couleur.
 * 
 * @param node1 Premier nœud à vérifier
 * @param node2 Second nœud à vérifier
 * @return int 
 *         - 1 si les nœuds sont voisins
 *         - 0 si les nœuds ne sont pas voisins
 * @note La complexité est O(d) où d est le degré du node1
 */
int areNeighbors(Node* node1, Node* node2);

/**
 * @brief Trouve la première couleur disponible pour un nœud donné
 * 
 * Détermine la plus petite couleur qui n'est pas utilisée par les voisins
 * du nœud. La fonction considère les couleurs comme des entiers positifs,
 * où 0 ou VIDE représente l'absence de couleur.
 * 
 * @param node Le nœud à colorer
 * @param numColors Le nombre maximum de couleurs disponibles
 * @return int 
 *         - Un entier positif représentant la première couleur disponible
 *         - -1 si aucune couleur n'est disponible
 * @warning La fonction alloue dynamiquement de la mémoire qui doit être libérée
 */
int findAvailableColor_wp(Node* node, int numColors);

/**
 * @brief Implémente l'algorithme de coloration de Welsh-Powell
 * 
 * Colore les nœuds d'un graphe de manière à ce qu'aucun nœud adjacent n'ait
 * la même couleur, en utilisant un nombre minimal de couleurs. L'algorithme
 * procède comme suit :
 * 1. Trie les nœuds par degré décroissant
 * 2. Attribue la première couleur disponible au nœud non coloré de plus haut degré
 * 3. Utilise la même couleur pour tous les nœuds non adjacents possibles
 * 4. Répète jusqu'à ce que tous les nœuds soient colorés
 * 
 * @param graph Le graphe à colorer
 * @return int 
 *         - Le nombre de couleurs utilisées si la coloration est réussie
 *         - -1 si la coloration a échoué ou si le graphe est invalide
    */
int welshPowell(Graph *graph);
#endif 