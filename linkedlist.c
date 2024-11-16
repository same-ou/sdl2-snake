#include"linkedlist.h"
Snake* initialiser_Snake ()
{
    Snake* snake = (Snake*)malloc(sizeof(snake));
    if (snake != NULL) {
        snake->Debut = NULL;
        snake->Fin = NULL;
    }
    return snake;
}
int snakeVide(Snake* S)
{
    return(S->Debut==NULL && S->Fin==NULL);
}
//fonction pour allouer de la memoire pour un element de type Element
Element* allouerNoeud(){
 Element* ne=(Element*)malloc(sizeof(Element));
 if(!ne) exit(-1);
    ne->suivant=NULL;
    return ne;
}

Snake* insererDebut(Snake* S,int x,int y)
{
    Element* ne=allouerNoeud();
    ne->corps.x=x;
    ne->corps.y=y;
    ne->corps.h=25;
    ne->corps.w=25;
    //lelement est pret pour etre inserer
    //deux sort d'insertion
    /*si la snake est vide debut = Null && fin=Null*/
    if(snakeVide(S)){
        S->Debut=ne;
        S->Fin=ne;
    }
    else{
    ne->suivant=S->Debut;
    S->Debut=ne;
    }
    return S;
}
Snake* insererFin(Snake* S,int x,int y)
{
    Element* ne=allouerNoeud();
    ne->corps.x=x;
    ne->corps.y=y;
    ne->corps.h=25;
    ne->corps.w=25;
    if(snakeVide(S)) {
        S->Debut=ne;
        S->Fin=ne;
    }
    else{
        S->Fin->suivant=ne;
        S->Fin=ne;
    }
    return S;
}

Snake* supprimerDebut(Snake* S)
{
    if(!snakeVide(S)){
            Element* esup=S->Debut;
            if(S->Debut->suivant==NULL){
                S->Debut=NULL;
                S->Fin=NULL;}
                else{
                    S->Debut=S->Debut->suivant;
                }
                free(esup);
    }
    return S;
}
