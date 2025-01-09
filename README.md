# **Graph Coloring Application**

Ce projet offre une interface interactive permettant de manipuler des graphes, de les colorer avec différents algorithmes et de vérifier la validité de leurs colorations. Voici une présentation complète des fonctionnalités, ainsi qu'un guide d'utilisation.

---

## **Sommaire**

1. [Présentation du projet](#-présentation-du-projet)
2. [Fonctionnalités](#-fonctionnalités)
3. [Prérequis](#-prérequis)
4. [Installation](#-installation)
5. [Utilisation](#-utilisation)
6. [Visualisation des graphes](#-visualisation-des-graphes)
7. [Format des fichiers de graphes](#-format-des-fichiers-de-graphes)
8. [Aperçu des algorithmes](#-aperçu-des-algorithmes)

## **Présentation du projet**

Ce projet implémente deux algorithmes de coloration de graphes :

- **DSATUR** (algorithme basé sur le degré de saturation).
- **Welsh-Powell** (algorithme de coloration par degré décroissant).

L’objectif est de permettre une analyse simple et efficace des performances des algorithmes sur différents graphes via une interface en ligne de commande.

---

## **Fonctionnalités**

### **1. Coloration d'un graphe à partir d'un fichier existant**

- Charger un graphe au format `.col` depuis le dossier `graph/`.
- Sélectionner un algorithme de coloration : **DSATUR** ou **Welsh-Powell**.
- Afficher le nombre de couleurs utilisées et le temps moyen d'exécution.
- Sauvegarder le graphe coloré aux formats `.json` ou `.col` dans le dossier `save/`.

### **2. Vérification de la validité d'une coloration**

- Vérifier si une coloration donnée (fichier `.col` ou `.json`) respecte la règle selon laquelle deux nœuds adjacents ne doivent pas partager la même couleur.

### **3. Création manuelle d'un graphe**

- Créer un graphe en entrant :
  - Le nombre de **nœuds**.
  - Le nombre d'**arcs**.
  - Appliquer un algorithme de coloration et sauvegarder le graphe créé.

---

## **Prérequis**

- **Makefile** pour la compilation du projet.
- Un compilateur C (GCC recommandé).
- **Terminal** pour exécuter le programme.
- Dossiers `graph/` (pour les fichiers d'entrée) et `save/` (pour les fichiers de sortie) créés manuellement.
- **Graphviz** pour la visualisation des graphes en `.json`

## **Installation**

1. Clonez le dépôt :
   ```bash
   git clone https://github.com/haldor8/coloration_graph.git
   cd graph-coloring-app
   ```

2. Compilez le programme :

   ```bash
   make
   ```

3. Assurez-vous que les dossiers `graph/` et `save/` existent :

   ```bash
   mkdir -p graph save
   ```

4. Installez **Graphviz** pour visualiser les graphes :
   ```bash
   pip install graphviz
   ```

---

## **Utilisation**

Exécutez le programme avec la commande suivante :

```bash
./color_graph
```

Une interface interactive s'affiche avec plusieurs options :

```
=== Menu Principal ===
1. Colorer un graphe
2. Vérifier une coloration
3. Créer un graphe à la main
Votre choix:
```

### **1. Coloration d'un graphe :**

- Entrez le nom du fichier `.col` (situé dans `graph/`).
- Sélectionnez l'algorithme (`1` pour DSATUR, `2` pour Welsh-Powell).
- Visualisez les résultats.
- Sauvegardez si vous le souhaitez.

### **2. Vérification d'une coloration :**

- Entrez le nom du fichier `.col` ou `.json` à vérifier (situé dans `graph/`).
- Le programme indique si la coloration est valide ou non.

### **3. Création d'un graphe à la main :**

- Saisissez le nombre de nœuds et d'arcs.
- Entrez les paires de nœuds pour créer les connexions.
- Choisissez un algorithme et appliquez la coloration.

## **Visualisation des graphes**

- Lorsque vous sauvegardez un graphe au format `.json`, il est stocké dans le dossier `save/`.
- Pour visualiser ce graphe :
  1. Copiez le fichier `.json` dans le dossier `representation/graphes/`.
  2. Modifiez le script `src/representation/main.py` pour spécifier le nom du fichier `.json`.
  3. Exécutez la commande :
     ```bash
     python3 src/representation/main.py
     ```
  4. Une image du graphe est générée grâce à **Graphviz** et affichée dans le dossier `representation/images/`.

---

## **Format des fichiers de graphes**

Les fichiers `.col` respectent la structure suivante :

```bash
p edge <nombre_de_nœuds> <nombre_d'arcs>
e <nœud1> <nœud2>
e <nœudX> <nœudY>
```

Les lignes `e` indiquent les arcs entre les nœuds.

## **Aperçu des algorithmes**

### **1. DSATUR**

L'algorithme choisit de colorer en priorité les nœuds ayant le plus grand nombre de voisins déjà colorés, en attribuant la couleur la plus petite possible. Cela permet une coloration optimale pour de nombreux graphes.

### **2. Welsh-Powell**

Les nœuds sont triés par ordre décroissant de degré (nombre de voisins). Le premier nœud reçoit la première couleur, et les suivants reçoivent une couleur différente si nécessaire. Cet algorithme est efficace sur des graphes denses.
