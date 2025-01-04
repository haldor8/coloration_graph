import graphviz
import os
os.environ["PATH"] += os.pathsep + '../bin'

class Graphe:
    def __init__(self):
        self.liste = []

    def to_dot(self):
        """
        #Retourne la description du graphe au format dot
        """
        dot = graphviz.Graph()
        dot.attr(rankdir="LR")
        for noeud in self.liste["noeuds"]:
            nom = noeud["nom"]
            if noeud["couleur"] in ("NOIR", "BLEU"):
                couleur = "white"
            else:
                couleur = "black"
            dot.node(name=nom, label = nom, shape="circle", fontcolor=couleur, style="filled", fillcolor=noeud["couleur"])
            for arc in noeud["arcs"]:
                dot.edge(tail_name=nom, head_name=arc["nom"], label=arc["poids"])
            
        return dot
    
    def to_png(self, filename):
        """
        Génère l'image dans le fichier filename
        """
        dot = self.to_dot()
        dot.render(filename="../images/"+filename, format="png")

    #---------------------------------Sauvegarde et chargement-----------------------------------

    def charger(self, filename):
        import json

        fichier = open("../graphes/"+filename+".json", "r")

        self.liste = json.load(fichier)
        
        fichier.close()