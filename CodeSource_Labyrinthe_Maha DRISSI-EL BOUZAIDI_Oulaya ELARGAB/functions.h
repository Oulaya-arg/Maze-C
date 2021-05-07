#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//#define cell_size          20   // la taille de la cellule = largeur = longueur cellule
//#define window_width      600   // la largeur de la fen�tre
//#define window_height     600   // la longueur de la fen�tre
#define MAX_CELL          6000  // le nombre maximal de cellules dans ce tableau cells

typedef struct _cellule
{
    int i; // la ligne o� se trouve la cellule
    int j; // colonne o� se trouve la cellule
    int x; // top left abscisse
    int y; // top left ordonn�e
    short int walls[4]; // tableau designant si un mur de la cellule existe (true) ou pas (false) walls[0] pour mur en haut ,
                   // walls[1] pour mur � droite , walls[2] pour mur en bas , walls[1] pour mur � gauche.
    short int visited; // c'est un boolean pour designer si une cellule a deja �t� visit�e durant le processus de g�n�ration du labyrinthe
    int distance; // distance par rapport � la cellule de sortie;
    int affected; // un boolean qui d�signe si une une cellule on lui a deja affect� la distance
    struct _cellule *next;// next voisin � visiter
    struct _cellule * previous; // previous voisin for stacking
}cell;



typedef cell* PILE; // type pile de cellules
cell cells[MAX_CELL]; // tableau qui stocke les cellules du maze
cell *cellAct; // la cellule actuellement visit�e par le programme
cell *cellSortie1; // la cellule de la premi�re sortie
cell *cellSortie2; // la cellule de la deuxi�me sortie
cell *cellEntree; // la cellule d'entr�e
int nbreCols; // nombre de colonnes du labyrinthe
int nbrLignes;// nombre de lignes du labyrinthe
int nbrCells;// nombre de cellules du labyrinthe
int cell_size;
SDL_Window *window;  //la fenetre principale
SDL_Renderer *renderer;  // le rendrere de la fenetre
SDL_Color grid_background; // la couleur du fond de la fen�tre : white


void initParametres(int width, int height, int cellsize); // initialise les param�tre globaux du programme
void initCell(cell *c,int i, int j); // initialise les param�tres initiaux de la cellule au d�but du programme
int index(int i,int j); // retourne l'index de la cellule de la i�me ligne j�me colonne dans le tableau cells
cell * checkNeighbors(int i, int j); // cette fonction teste les voiosins de la cellule dont le num�ro de ligne est i et le num�ro de colonne est j
void removeWalls(cell* a, cell* b); // supprimer les murs entre la cellule a et b
void colorVisitedCell(cell* c,SDL_Color line_color); // colorer la cellule c avec la couleur line_color
void drawCell(cell *c);// dessiner une cellule c (mur par mur)
void empiler(PILE **p, cell *c); // empiler la cellule c dans la pile de cellules p
cell* depiler(PILE **p); // d�piler de p et reourner la cellule d�pil�e
void loadMap(int lignes, int colonnes, int * cells, cell cellules[]); // dessiner la grille de d�part cellule par cellule
void defineDistance(cell * nowCell);// determine la distance qui s�pare nowCell de la cellule de sortie
cell * findNextInPath(cell* cellA); //retourner la cellule optimale qui a la plus courte distance entre cellA et la cellule de sortie
void findPath(cell * enterCell);// trouve le plus court chemin vers la sortie
void colorCellPath(cell *c,SDL_Color line_color); // colorie une cellule du chemin trouv� avec la couleur line_color
void pathTo(cell* entree,cell* sortie, SDL_Color color);//determine le plus court chemin entre entree et sortie et le dessine avec la couleur color
void generateMaze(cell* enterCell); // fonction pour g�n�rer le maze
void resolveMaze(cell* enterCell, cell* exitCell1, cell* exitCell2);// la fonction de r�solution du labyrinthe;
void createWindow(int width, int height, int cellsize); // La fen�tre o� l'on genere le labyrinth et on le r�sout

#endif // FUNCTIONS_H_INCLUDED
