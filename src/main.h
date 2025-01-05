#ifndef H_MAIN
#define H_MAIN
#include <stdlib.h>
#include <stdio.h>

#include "graphes.h"
#include "graphes.h"
#include "DSATUR.h"

#include "time.h"

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

#endif