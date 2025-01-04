from Graphe import Graphe
graph_path = "../graphes"

le_graphe = Graphe()
le_graphe.charger("test")

le_graphe.to_png("test")