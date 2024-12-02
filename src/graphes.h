#ifndef H_GRAPH
#define H_GRAPH

typedef struct
{
    // Données
    noeud *noeuds_suivant;
} noeud;

void initialiser_graphe();
void charger_graphe(char *nom_fichier);
void creer_noeud();
void liberer_graphe();

#endif