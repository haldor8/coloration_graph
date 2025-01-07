#ifndef H_MAIN
#define H_MAIN
#include <stdlib.h>
#include <stdio.h>

#include "graphes.h"
#include "graphes.h"
#include "DSATUR.h"

#include "time.h"

/**
 * @brief Permet à l'utilisateur de créer un graphe à la main en définissant les nœuds et les arcs.
 * 
 * Cette fonction demande à l'utilisateur :
 * - Le nombre de nœuds du graphe.
 * - Le nombre d'arcs à créer.
 * - Les connexions entre les nœuds (paires de nœuds formant les arcs).
 * 
 * Une fois le graphe créé, l'utilisateur peut appliquer un algorithme de coloration
 * (DSATUR ou Welsh-Powell), afficher les résultats, et sauvegarder le graphe.
 */
void createGraphManually();


/**
 * @brief Exécute un algorithme de coloration de graphe plusieurs fois et calcule la durée moyenne d'exécution.
 *
 * Cette fonction exécute un algorithme de coloration de graphe passé en paramètre sur un graphe donné,
 * un nombre spécifié de fois, et calcule la durée moyenne d'exécution en utilisant la fonction `clock`.
 * Entre chaque exécution (sauf la dernière), elle réinitialise les couleurs du graphe.
 *
 * @param algorithm Pointeur vers une fonction prenant un pointeur sur un graphe (`Graph*`) 
 *                  en paramètre et retournant un entier. 
 *                  Cette fonction doit représenter un algorithme de coloration.
 * @param graph     Pointeur vers le graphe sur lequel appliquer l'algorithme.
 * @param times     Nombre de fois que l'algorithme doit être exécuté.
 *
 * @return La durée moyenne d'exécution de l'algorithme sur le graphe, en ticks (unités de `clock()`).
 *
 * @note Si `times` vaut 0, la fonction retourne 0.
 * @note La réinitialisation des couleurs entre chaque exécution est effectuée par la fonction `resetColoring`.
 */
double runAlgorithm(int (*algorithm)(Graph*), Graph* graph, int times);


/**
 * @brief Affiche le menu principal et permet de choisir l'action à effectuer.
 * 
 * @return 1 si l'utilisateur choisit de colorer un graphe, 2 pour vérifier une coloration.
 */
int mainMenu();

/**
 * @brief Affiche le choix des algorithmes de coloration disponibles.
 * 
 * @return 1 pour DSATUR, 2 pour Welsh-Powell.
 */
int selectAlgorithm();

/**
 * @brief Sauvegarde la coloration d'un graphe au format JSON ou .col dans le dossier `save/`.
 * 
 * @param graph Pointeur vers le graphe coloré.
 */
void saveResult(Graph *graph);

/**
 * @brief Vérifie la validité de la coloration d'un graphe en lisant un fichier .col ou .json depuis le dossier `graph/`.
 */
void checkColoringInput();

/**
 * @brief Effectue la coloration d'un graphe en utilisant l'algorithme choisi par l'utilisateur.
 * Lit un fichier .col depuis le dossier `graph/`, exécute la coloration, affiche le résultat et permet la sauvegarde.
 */
void colorGraph();


#endif