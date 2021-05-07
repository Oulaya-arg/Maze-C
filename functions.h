#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#define cell_size          20   // la taille de la cellule = largeur = longueur cellule
//#define window_width      600   // la largeur de la fenêtre
//#define window_height     600   // la longueur de la fenêtre
#define MAX_CELL          6000  // le nombre maximal de cellules dans ce tableau cells

typedef struct _cellule
{
    int i; // la ligne où se trouve la cellule
    int j; // colonne où se trouve la cellule
    int x; // top left abscisse
    int y; // top left ordonnée
    short int walls[4]; // tableau designant si un mur de la cellule existe (true) ou pas (false) walls[0] pour mur en haut ,
                   // walls[1] pour mur à droite , walls[2] pour mur en bas , walls[1] pour mur à gauche.
    short int visited; // c'est un boolean pour designer si une cellule a deja été visitée durant le processus de génération du labyrinthe
    int distance; // distance par rapport à la cellule de sortie;
    int affected; // un boolean qui désigne si une une cellule on lui a deja affecté la distance
    struct _cellule *next;// next voisin à visiter
    struct _cellule * previous; // previous voisin for stacking
}cell;



typedef cell* PILE; // type pile de cellules
cell cells[MAX_CELL]; // tableau qui stocke les cellules du maze
cell *cellAct; // la cellule actuellement visitée par le programme
cell *cellSortie1; // la cellule de la première sortie
cell *cellSortie2; // la cellule de la deuxième sortie
cell *cellEntree; // la cellule d'entrée
int nbreCols; // nombre de colonnes du labyrinthe
int nbrLignes;// nombre de lignes du labyrinthe
int nbrCells;// nombre de cellules du labyrinthe
int cell_size;
SDL_Window *window;  //la fenetre principale
SDL_Renderer *renderer;  // le rendrere de la fenetre
SDL_Color grid_background; // la couleur du fond de la fenêtre : white


void initParametres(int width, int height, int cellsize); // initialise les paramètre globaux du programme
void initCell(cell *c,int i, int j); // initialise les paramètres initiaux de la cellule au début du programme
int index(int i,int j); // retourne l'index de la cellule de la ième ligne jème colonne dans le tableau cells
cell * checkNeighbors(int i, int j); // cette fonction teste les voiosins de la cellule dont le numéro de ligne est i et le numéro de colonne est j
void removeWalls(cell* a, cell* b); // supprimer les murs entre la cellule a et b
void colorVisitedCell(cell* c,SDL_Color line_color); // colorer la cellule c avec la couleur line_color
void drawCell(cell *c);// dessiner une cellule c (mur par mur)
void empiler(PILE **p, cell *c); // empiler la cellule c dans la pile de cellules p
cell* depiler(PILE **p); // dépiler de p et reourner la cellule dépilée
void loadMap(int lignes, int colonnes, int * cells, cell cellules[]); // dessiner la grille de départ cellule par cellule
void defineDistance(cell * nowCell);// determine la distance qui sépare nowCell de la cellule de sortie
cell * findNextInPath(cell* cellA); //retourner la cellule optimale qui a la plus courte distance entre cellA et la cellule de sortie
void findPath(cell * enterCell);// trouve le plus court chemin vers la sortie
void colorCellPath(cell *c,SDL_Color line_color); // colorie une cellule du chemin trouvé avec la couleur line_color
void pathTo(cell* entree,cell* sortie, SDL_Color color);//determine le plus court chemin entre entree et sortie et le dessine avec la couleur color
void generateMaze(cell* enterCell); // fonction pour générer le maze
void resolveMaze(cell* enterCell, cell* exitCell1, cell* exitCell2);// la fonction de résolution du labyrinthe;
void createWindow(int width, int height, int cellsize); // La fenêtre où l'on genere le labyrinth et on le résout

#endif // FUNCTIONS_H_INCLUDED
