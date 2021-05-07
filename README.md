# Maze-C (realisé en binome)

Il s'agit d'une implémentation du jeu labyrinthe en langage C à l'aide de l'interface graphique SDL2.
Deux aspects importants de cette modélisation sont la génération automatique du labyrinthe et
sa résolution.

# La génération du layrinthe consiste à construire une grille de cellules séparées par des murs. Ce
labyrinthe peut etre généré par plusieurs méthodes, ici on utilise le DFS (Depth First Search)

# La résolution consiste à trouver le plus court chemin qui mène à la sortie du labyrinthe modélisé
mathématiquement. Il existe plusieurs algorithmes pour ce problème, ici on utilise Breadth First Search (BFS).
