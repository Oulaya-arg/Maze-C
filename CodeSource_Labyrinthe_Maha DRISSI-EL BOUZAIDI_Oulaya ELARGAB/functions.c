#include "functions.h"

//Fonction qui initialise les paramètres globaux du labyrinthe

void initParametres(int width, int height, int cellsize)
{
    nbreCols = (int)width/cellsize;// le nombre de colonnes en se basant sur la largeur de la fenêtre et celle de la cellule
    nbrLignes= (int)height/cellsize;// le nombre de lignes en se basant sur la longueur de la fenêtre et celle de la cellule
    nbrCells = 0;// on initialise le nombre de cellules à 0
    cell_size = cellsize; // la taille de la celllule sera entrée ar l'utilisateur
    grid_background.r = 240;
    grid_background.g = 240;
    grid_background.b = 240;
    grid_background.a = 255;
    //{241, 222, 114, 255};
}

// fonction qui initialise les paramètre d'entrée de la cellule c
void initCell(cell * c,int i, int j)
{
    c->i = i;// numero de ligne
    c->j = j;// numéro de colonne
    c->x = j*cell_size; // top left abscisse
    c->y = i*cell_size; // top left ordonnée
    c->visited = 0; // la cellule n'a pas encore été visitée. Au départ c'est le cas de toures les cellules
    c->distance = 0; // la cellule n'a pas de distance definie par rapport à la case de sortie
    c->next = NULL; // la cellule suivante pointe sur null
    for(int k=0; k<4 ; k++) c->walls[k] = 1; // tous les murs de la cellule existent
}

// Fonction qui retourne l'indice de la cellule dans le tableau global cells[] en partant de bon numero de ligne et colonne
// dans la grille de départ
int index(int i,int j)
{
    // si le numéro de ligne ou de colonne sont inferieurs à 0 ou supérieurs ou égaux respectivement à nombre de lignes
    //et nombre de colonnes on retourne -1
    if(i<0 || j<0 || i>nbrLignes-1 || j>nbreCols-1) return -1;
    return j + i*nbreCols;// on retourne l'indice
}

// Fonction qui colorie la cellule c avec la couleur line_color
// elle est utile pour colorier le rectangle qui indique les cellues d'entrée ou de sortie
void colorVisitedCell(cell *c,SDL_Color line_color)
{
    SDL_Rect rect; // le rectangle a colorier
    rect.x = c->x+cell_size/6; // on indique ses coordonnées à partir de celles de la cellules
    rect.y = c->y+cell_size/6; // on réduit les limites du rectangle pour une meilleure apparance sur le labyrinthe
    rect.w = 2*cell_size/3;
    rect.h = 2*cell_size/3;
    SDL_SetRenderDrawColor( renderer, line_color.r, line_color.g, line_color.b, line_color.a );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);
}
void colorPath(cell *c,SDL_Color line_color)
{
    SDL_Rect rect; // le rectangle a colorier
    rect.x = c->x+cell_size/20; // on indique ses coordonnées à partir de celles de la cellules
    rect.y = c->y+cell_size/20; // on réduit les limites du rectangle pour une meilleure apparance sur le labyrinthe
    rect.w = 18*cell_size/20;
    rect.h = 18*cell_size/20;
    SDL_SetRenderDrawColor( renderer, line_color.r, line_color.g, line_color.b, line_color.a );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);
}
//fonction qui colorie les rectangle des cellule du chemin de sortie
// elle prend en paramètres la cellule à colorier et la couleur de coloration
// cette fonction est dofférente de la precedente parce que les rectangles à colorier sont de tailles différentes
void colorCellPath(cell *c,SDL_Color line_color)
{
    SDL_Rect rect;
    rect.x = c->x+cell_size/4; // on reduit la taille du rectangle à colorier pour une meilleure apparence
    rect.y = c->y+cell_size/4;
    rect.w = cell_size/2;
    rect.h = cell_size/2;
    SDL_SetRenderDrawColor( renderer, line_color.r, line_color.g, line_color.b, line_color.a );
    SDL_RenderFillRect( renderer, &rect );
    SDL_RenderPresent(renderer);

}

//fonction qui dessine la cellule mur par mur
void drawCell(cell *c)
{
    SDL_Color line_color = {0, 0, 0, 255}; // Barely Black
    int x = c->j*cell_size;
    int y = c->i*cell_size;
    SDL_SetRenderDrawColor( renderer, line_color.r, line_color.g, line_color.b, line_color.a );
    SDL_RenderDrawLine(renderer, x          , y             , x+cell_size   , y          );
    SDL_RenderDrawLine(renderer, x+cell_size, y             , x+cell_size   , y+cell_size);
    SDL_RenderDrawLine(renderer, x          , y+cell_size   ,x+cell_size    , y+cell_size);
    SDL_RenderDrawLine(renderer, x          , y             , x             , y+cell_size);
}

//Fonction qui teste les voisins de la cellule caractérisée par les numéros de ligne i et numéro de colonne j
// et retourne la cellule à visiter lors de la phase de génératon du labyrinthe
cell *checkNeighbors(int i, int j)
{
    int neighbors[4]; // un tableau qui stocke les indices des voisins susceptible d'être choisi
    short int n = 0; // nombre des voisins susceptibles d'être choisi
    cell *c;
    int top, right, bottom, left; // des variables qui stocke les numéros des voisins de top, right, bottom et left
    if((top = index(i-1,j))!=-1) // si le voisin d'en haut existe
    {
        if(cells[top].visited==0) // et si ce voisin n'a pas été visité
        {
            neighbors[n] = top; // on le stocke dans le tableau des voisins parmi lesquels on peut choisir un à visiter
            n++; // et on incrémente le nombre de voisins susceptibles d'être choisis
        }
    }
    if((right = index(i,j+1)) != -1) // même traitement sur le voisin d'à droite
    {
        if(cells[right].visited==0)
        {
            neighbors[n] = right;
            n++;
        }
    }
    if((bottom = index(i+1,j)) != -1) // même traitement sur le voisin d'en bas
    {
        if(cells[bottom].visited==0)
        {
            neighbors[n] = bottom;
            n++;
        }
    }
    if((left = index(i,j-1)) != -1) // même traitement sur le voisin d'à gauche
    {
        if(cells[left].visited==0)
        {
            neighbors[n] = left;
            n++;
        }
    }

    if(n>0) // si le nombre de voisins qui réalisent les conditions précedentes est non nul
    {
        int r ;
        r= rand()%n; // on choisit un nombre au hasard entre 0 et n
        c = &cells[neighbors[r]]; // et on affecte à c la cellule d'indice stocké dans la case r du tableau neighbors[]
        return c; //et on retourne cette cellule
    }
    return NULL; // le cas écheant on retourne null; chose qui veut dire que tous les voisins de la cellule d'entrée sont visités
}

// cette fonction détruit le mur entre la cellule a et la cellule b
void removeWalls(cell* a, cell* b)
{
    int x = a->i - b->i; // pour savoir à quelle ligne se trouve b par rapport à a
    int y = a->j - b->j;// pour savoir à quelle colonne se trouve b par rapport à a
  //  SDL_Color line_color = {255, 255, 255, 255};// background color
    SDL_SetRenderDrawColor( renderer, grid_background.r, grid_background.g, grid_background.b, grid_background.a );
    if(x == -1) //si la cellule b se trouve en bas de a
    {
        a->walls[2] = 0; // detruire le mur d'en bas de a
        b->walls[0] = 0;// et le mur d'en haut de b
        SDL_RenderDrawLine(renderer, a->x , a->y+cell_size ,a->x+cell_size , a->y+cell_size); // et colorer les deux murs en blanc
        SDL_RenderDrawLine(renderer, b->x , b->y           ,b->x+cell_size , b->y          );// parce que le blanc est la couleur de l'arrier plan
    }
    else if(x == 1) // si la cellule b se trouve au dessus de a
    {
        a->walls[0] = 0; // detruire le bur de haut de a
        b->walls[2] = 0;// et le mur de bas de b
        SDL_RenderDrawLine(renderer, b->x , b->y+cell_size ,b->x+cell_size , b->y+cell_size);
        SDL_RenderDrawLine(renderer, a->x , a->y           ,a->x+cell_size , a->y          );
    }
    if(y == -1) // b à droite de a
    {
        a->walls[1] = 0; // détruire le mur de droite de a
        b->walls[3] = 0; // et le mur de gauche de b
        SDL_RenderDrawLine(renderer, a->x+cell_size, a->y   , a->x+cell_size , a->y+cell_size);
        SDL_RenderDrawLine(renderer, b->x          , b->y   , b->x           , b->y+cell_size);
    }
    else if(y == 1) // b a gauche de a
    {
        a->walls[3] = 0; // detruire le mur de gauche de a
        b->walls[1] = 0; // et le mur de droite de b
        SDL_RenderDrawLine(renderer, b->x+cell_size, b->y   , b->x+cell_size , b->y+cell_size);
        SDL_RenderDrawLine(renderer, a->x          , a->y   , a->x           , a->y+cell_size);
    }
    SDL_RenderPresent(renderer);
}

// fonction qui empile la cellule c dans la pile de cellules p lors de la génération du labyrinthe
void empiler(PILE **p, cell *c)
{
    if(*p==NULL) {*p = c;c->previous = NULL;} // au départ la pile ne contient aucun élément et par la suite elle doit pointer sur c
    else{ // sinon la nouvelle cellule à empiler c doit pointer sur la cellule en tete de la pile et la pile sur c
        c->previous = *p;
        *p=c;
    }

}

// fonction qui retourne une cellule qu'on dépile de la pile p
cell* depiler(PILE **p)
{
    cell *c;
    if(*p!=NULL) // si la pile contient au moin un élément
    {
        c=(*p); // c pointe alors sur la tete de la pile
        if(c->previous!=NULL)*p=c->previous; // s'il y a encore un élément, alors la tete de la pile pointe sur celui là
        else p=NULL; // sinon elle pointe sur null
    }
    else c=NULL; // si la pile ne contient aucune cellule on retourne null
    return c;
}

// fonction qui prend en entrée les paramètres necessaires pour dessiner la grille qui va servir de base pour
// generer le labyrinthe. On dessine cellule par cellule
void loadMap(int lignes, int colonnes, int * cells, cell cellules[])
{
    cell c;
    for(int i = 0 ; i<lignes ; i++) // en allant de 0 à nombre de lignes de la grille
    {
        for(int j = 0 ; j<colonnes ; j++) // et de 0 à nombre de colonnes
        {
            initCell(&cellules[*cells],i,j); // on initialise les paramètre la case numero (*cells) du tableau
            drawCell(&cellules[*cells]);// et on dessine cette cellule
            (*cells)++;// et on incrémente le nombre de cellules (*cells)
        }
    }
}

//Affecter une distance à chaque cellule voisine à cellNow puis à
//la suivante et ainsi de suite jusqu'à arriver à la cellule d'entrée
void defineDistance(cell * nowCell)
{
    int indice = nowCell->i*nbreCols+nowCell->j; // indice de la nowCell dans le tableau cells[]
    if(nowCell->walls[0] == 0 && cells[indice-nbreCols].affected==0)// on teste si le mur d'en haut est détruit et qu'on lui a pas encore affecté une distance par rapport à nowCell
    {
        cells[indice-nbreCols].distance=nowCell->distance+1;// on affecte à son paramètre distance la valeur de distance de nowCell + 1
        cells[indice-nbreCols].affected = 1; // on change le paramètre affected pour signaler que cette cellule a deja une distance par rapport à la cellule de sortie
        defineDistance(&cells[indice-nbreCols]); //et on on fait le meme traitement sur les cellules voisines de la cellule d'en haut
    }
    if(nowCell->walls[1] == 0 && cells[indice+1].affected==0) // Même traitement sur la cellule à droite
    {
        cells[indice+1].distance=nowCell->distance+1;
        cells[indice+1].affected = 1;
        defineDistance(&cells[indice+1]);
    }
    if(nowCell->walls[2] == 0 && cells[indice+nbreCols].affected==0) // Même traitement sur la cellule d'en bas
    {
        cells[indice+nbreCols].distance=nowCell->distance+1;
        cells[indice+nbreCols].affected = 1;
        defineDistance(&cells[indice+nbreCols]);
    }
    if(nowCell->walls[3] == 0 && cells[indice-1].affected==0)// Même traitement sur la cellule d'à gauche
    {
        cells[indice-1].distance=nowCell->distance+1;
        cells[indice-1].affected = 1;
        defineDistance(&cells[indice-1]);
    }
}

//foiction qui retourne la cellule qui a la plus petite distance par rapport à la cellule de sortie parmi les cellules
// voisines de cellA
cell * findNextInPath(cell* cellA)
{
    int min = cellA->distance; // on initialise la valeur min à la distance de cellA
    int indice = cellA->i*nbreCols+cellA->j; // on stocke l'iindice de cellA dans le tableau cells[] dans la variable indice
    cell* choosedCell; // indique la cellule élue parmi les voisines de cellA

    if(cellA->walls[0] == 0 && cells[indice-nbreCols].affected==1) //si le mur d'en haut est détruit et la cellule d'en haut a deja une distance
    {
        min = cells[indice-nbreCols].distance; // alors la valeur min deviens celle de la cellule d'en haut
        choosedCell = &cells[indice-nbreCols];// et c'est cette cellule qui sera élue
    }
    if(cellA->walls[1] == 0 && cells[indice+1].affected==1)// on fait le meme teste sur la cellule d'à droite
    {
        if (min>cells[indice+1].distance)// mnt si la distance affectée a celle ci est plus petite que celle affectée à la cellule d'en haut
        {
            min=cells[indice+1].distance; //la variable min prend la valeur de la distance de cette cellule
            choosedCell = &cells[indice+1];// et c'est cette cellule qui sera elue à la place de celle d'en haut
        }
    }
    if(cellA->walls[2] == 0 && cells[indice+nbreCols].affected==1)// Même traitement que le précédent sur la cellule d'en bas
    {
        if (min>cells[indice+nbreCols].distance)
        {
            min=cells[indice+nbreCols].distance;
            choosedCell = &cells[indice+nbreCols];
        }
    }
    if(cellA->walls[3] == 0 && cells[indice-1].affected==1)// Même traitement que le précédent sur la cellule d'à gauche
    {
        if (min>cells[indice-1].distance)
        {
            min=cells[indice-1].distance;
            choosedCell = &cells[indice-1];
        }
    }
    if(min == 0) return NULL; // si le minimum est null la fonction retourne null pouor indiquer qu'on est arrivé à destination
    return choosedCell; // retourne la cellule élue
}

//fonction qui definit la cellule suivante de chaque cellule, elue en appelant le fonction findNextInPath,
//du chemin vers la sortie, et ce à partir de la cellule d'entrée, et qui s'arrete quand la cellule élue
//pointe sur null (cad on est arrivé à la cellule de sortie). En d'autres termes elle permet de trouver le chemin
//le plus court vers la sortie
void findPath(cell * enterCell)
{
    cell *cellChoosed = (cell*)malloc(sizeof(cell));
    cellChoosed = findNextInPath(enterCell);// on choisit la cellule qui a la plus courte distance par rapport à la sortie parmi les voisines de enterCell
    if(cellChoosed == NULL) return; // si c'est la cellule de sortie on sort de la fonction
    SDL_Color line_color = {177,235,235,0};
    colorPath(cellChoosed,line_color); // colorer la cellule c avec la couleur line_color
    enterCell->next = cellChoosed; // la cellule qui suit enerCell dans le chemin de sortie est cellChoosed
    cellChoosed->next = NULL; // et cellChoosed pointe sur null en attendant de trouver la suivante
    Sleep(10);
    findPath(cellChoosed);// trouver la cellule suivante de cellChoosed
}

// fonction qui définit le plus court chemin entre la cellule entree et la cellule sortie, et colorie le chemin avec la couleur color
void pathTo(cell* entree,cell* sortie, SDL_Color color)
{
    SDL_Surface *ball=NULL;
    PILE pathES = entree; // une pile qui stocke les cellules du chemin et qui pointe au début sur la cellule d'entrée
    defineDistance(sortie); // on determine la distance de chaque cellule par rapport à la cellule sortie
    findPath(entree);// on definit les cellule du chemin à partir de la cellule entree
    SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.a );
    while(pathES!=NULL) // tant que la tete de la pile ne pointe pas encore sur la sortie
    {
      //  SDL_RenderClear(renderer);
        if(pathES!= entree) colorPath(pathES,grid_background); // on colorie la cellule sur laquelle pointe la pile
        pathES=pathES->next;// et on passe à la cellule suivante
        if(pathES!=NULL)colorCellPath(pathES,color); // on colorie la cellule sur laquelle pointe la pile
        Sleep(100);// on attend un petit moment avant de refaire la boucle, juste pour voir l'avancement du process
    }
}
// la fonction qui génère le labyrinthe
void generateMaze(cell* enterCell)
{
    PILE *p=NULL; // la pile qui sert à stocker les cellules lors de la génération du maze
    cellAct = enterCell; // cellAct c'est la cellule où le programme est positionné, et donc elle pointe sur cellEntree
    do{
        cell *next = checkNeighbors(cellAct->i,cellAct->j); // on affecte à next un des voisin de la cellule pointée par cellAct (au début cellAct =cellEntree)
        if(next!=NULL)// si on a un voisin à visiter
        {
            next->visited=1;// on le déclare visité
            removeWalls(cellAct,next);// on détruit les murs qui le sépare de cellAct
            empiler(&p,cellAct);// on l'empile dans la pile p
            cellAct = next;// et on pointe cellAct sur ce meme voisin
        }
        else// sinon si tous les voisins de cellAct sont dejà visités
        {
            if(p!= NULL)// si la pile contient au moins une cellule
            {
                cellAct=depiler(&p);// on dépile la ccellule qui se trouve en tete de la pile et on la stocke dans cellAct
            }
            else {printf("empty Pile\n"); break;} // sinon si la pile est vide, on renvoie un message et on sort de la boucle
        }
        Sleep(10); // faire une pause de 10ms entre chaque itération pour voir l'avancement de la génération du labyrinthe
    }while(cellAct!=enterCell);  // on répète juqu'à ce que cellAct revienne à la case de départ qui est la cellule d'entrée

}
// cette fonction résout le labyrinthe en trouvant le plus court chemin entre enterCell et exitCell1 et en le dessinant
// puis entre enterCell et exitCell12 et en le dessinant aussi
void resolveMaze(cell* enterCell, cell* exitCell1, cell* exitCell2)
{
    /// traitement de la cellule 1 de sotie
    SDL_Color line_color2 = {10,10,200,10}; // couleur de coloration de la cellule de sortie 1
    colorVisitedCell(exitCell1,line_color2);// on colorie cette cellule
    SDL_RenderPresent(renderer);// et on applique
    exitCell1->affected=1; // on met ce parametre à 1 pour indiquer que exitCell1 a dejà une distance et qui est égale à 0
    SDL_Color colorPath1 = {0, 0, 64, 10};// la couleur du chemin entre cellEntree et exitCell1
    pathTo(cellEntree,exitCell1,colorPath1);// on trouve le plus court chemin entre cellEntree et exitCell1 et on le dessine
    Sleep(2000);
    /// traitement de la cellule 2 de sotie
    colorVisitedCell(cellSortie2,line_color2); // on colorie la 2ème cellule de sortie
    SDL_RenderPresent(renderer);
    for(int k=0;k<nbrCells;k++){ // on remet les paramètre affected et distance de toutes les cellules à 0 pour trouver
        cells[k].affected=0; // un plus court chemin vers la 2ème sortie cette fois
        cells[k].distance=0;
    }
    cellSortie2->distance = 0; // c'est la case de sortie donc sa distance est 0
    cellSortie2->affected=1; // on lui a dejà affecté une distance
    SDL_Color colorPath2 = {255, 0, 0, 10};// couleur du 2ème chemin
    pathTo(cellEntree,cellSortie2,colorPath2); // on trouve le plus court chemin entre cellEntree et cellSortie1 et on le dessine

}
// La fonction qui crée la fenetre principale, génère le labyrinthe et le résout en générant une entrée et deux sorties
// et en trouvant les plus courts chemins qui mènent de l'entrée aux sorties
void createWindow(int width, int height, int cellsize)
{
    // on initialise le sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Initialize SDL: %s",
                     SDL_GetError());
        return EXIT_FAILURE;
    }
    // on crèe la fenêtre sdl  et on retourne un message d'erreur en cas d'erreur
    if (SDL_CreateWindowAndRenderer(width, height,SDL_WINDOW_RESIZABLE, &window,
                                    &renderer) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                     "Create window and renderer: %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_SetWindowTitle(window, "Labyrinthe"); // titre de la fenêtre
    SDL_bool quit = SDL_FALSE; // boolean initialisé à false pour ne pas quitter la fenêtre

    int mazeGenerated = 0; // un boolean qui indique si le labyrinthe est dejà généré
    while (!quit)
    {
        SDL_Event event; // déclaration d'un événement sdl
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_QUIT) { SDL_Quit();break;} // si l'évenement est la fermeture de la fenêtre alors fermer la fenêtre sdl
        }
        if(mazeGenerated==0) // si le maze est dejà généré
        {
            initParametres(width, height, cellsize); // initialiser les paramètres globaux de la grille de départ
            SDL_SetRenderDrawColor(renderer, grid_background.r, grid_background.g,
                                   grid_background.b, grid_background.a);// dessiner le fond de la fentre avec la couleur grid_background
            SDL_RenderClear(renderer); //

            loadMap(nbrLignes, nbreCols, &nbrCells, cells); // on dessine les cellules de la grille qui sert de base pour la génération du labyrinthe
            //srand(time(0));
            // initialisation de la Cellule d'entree
            int firstCell = rand()%nbrLignes; // un nombre aléatoire de 0 à nombre de lignes pour choisir une cellule d'entrée
            cellEntree = &cells[firstCell*nbreCols];// on multiplie par le nombre de colonnes pour que la cellule choisi fasse partie de la première colonne de la grille
            cellEntree->visited = 1; // La cellule est donc visitée maintenant
            SDL_Color line_color = {100,10,200,10}; // la coueur du rectangle qui indique la cellule d'entrée
            colorVisitedCell(cellEntree,line_color); // on colorie cette cellule avec la couleur spécifiée
            SDL_RenderPresent(renderer); // on applique l'instruction de coloration


            //*******************Phase de génération ****************************//
            // Maintenant on commence la génération du maze
            generateMaze(cellEntree); // on genère le maze a partir de la cellule d'entrée
            SDL_RenderPresent(renderer);
            Sleep(3000); //marquer 3s de pause avant la résolution
            //*******************Phase de résolution *******************//
            /// initialisation de cellule 1 de sotie
            int exitCell1=0; // variable pour stocker un nombre aléatoire qui servira pour choisir la cellule de sortie
            while(exitCell1 == 0) exitCell1= rand()%nbrLignes; // ce nombre doit etre different de 0; l'indice de la cellule doit etre
            cellSortie1 = &cells[exitCell1*nbreCols-1]; // égal à exitCell1*nbreCols-1 pour figurer dans la dernière colonne de la grille
            /// initialisation de cellule 2 de sotie
            int exitCell2=0;// variable pour stocker un nombre aléatoire qui servira pour choisir la cellule de sortie
            while(exitCell2 == 0 || exitCell2==exitCell1 || exitCell2==firstCell) exitCell2= rand()%nbrLignes;// ce nombre doit etre different de 0, de cell entrée et de cell sortie1;
            cellSortie2 = &cells[exitCell2];//cette fois on a pas imposé que la 2ème cellule de sortie soit sur la dernière colonne de la grille
            resolveMaze(cellEntree,cellSortie1,cellSortie2);// on résout le labyrinthe en trouvant les plus courts chemins entre cellEntree
                                                            // et cellSortie1 puis entre cellEntree et cellSortie2
            mazeGenerated = 1; //on met se paramètre à 1 pour ne pas refaire le tout et garder la fenêtre ouverte en même temps
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit(); // quitter
}
