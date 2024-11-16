// Linked list declaration

#include <stdlib.h>
#include <SDL.h>

typedef struct element{
 SDL_Rect corps ;
 struct element * suivant ;
}Element ;

typedef struct{
 Element * Debut;
 Element *Fin ;
}Snake;

Snake* initialiser_Snake (void);
int snakeVide(Snake* S);
Element* allouerNoeud(void);
Snake* insererDebut(Snake* S,int x,int y);
Snake* insererFin(Snake* S,int x,int y);
Snake* supprimerDebut(Snake* S);


