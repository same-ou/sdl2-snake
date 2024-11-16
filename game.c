#include <stdio.h>
#include <SDL.h>

#include "linkedlist.h"

#define WIDTH 800
#define HEIGHT 600
#define true 1
#define false 0
#define startingx 400
#define startingy 300

//variable globale
typedef struct{
 SDL_Window *window;
 SDL_Renderer* render;
 Snake* snake;
}Game;
Game game;


void initialise(void);//fonction permet d'initialiser la sdl et de creer la fenetre et la rendu
Snake* RemplirSnake(Snake *S);
void dessinerSnake(void);
void moveSnake(char direction);
int mordre(Snake* S);
void dessinerFood(SDL_Rect food);
void creerfood(SDL_Rect* food);

int isRunning;

int main(int argc, char** argv) {

    initialise();
    game.snake = initialiser_Snake();
    game.snake =RemplirSnake(game.snake);



    SDL_Rect food;//initialisation de la food
    food.x = 100;
    food.y = 100;
    food.w = 25;
    food.h = 25;




    isRunning = 1;
    int isStarting = true;//pour dire que la la jeux vient de player

    
    char direction;

    while (isRunning) {

        SDL_SetRenderDrawColor(game.render, 255, 255,255, 255);
        SDL_RenderClear(game.render);
        SDL_Event e;

        while (SDL_PollEvent(&e)) {

            switch (e.type) {
                case SDL_QUIT:
                    isRunning = 0;
                    break;

                case SDL_KEYDOWN:
                // case SDL_KEYUP:
                    switch (e.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                         isRunning = 0;
                           break;
                        case SDL_SCANCODE_UP:
                            if (direction == 'S') break;
                            direction = 'N';
                            isStarting = false;
                            break;
                        case SDL_SCANCODE_DOWN:
                            if (direction == 'N') break;
                             direction = 'S';
                            isStarting = false;
                            break;
                        case SDL_SCANCODE_LEFT:
                            if (direction == 'E' || isStarting == true) break;
                            direction = 'O';
                            break;
                        case SDL_SCANCODE_RIGHT:
                            if (direction == 'O') break;
                            direction = 'E';
                            isStarting = false;
                            break;
                            default : break;
                    }
                    break;

                default: break;
            }
        }

     dessinerFood(food);
     moveSnake(direction);
        if (game.snake->Fin->corps.x == food.x && game.snake->Fin->corps.y == food.y) {
            creerfood(&food);
            int tailx = game.snake->Debut->corps.x;
            int taily = game.snake->Debut->corps.y;
         game.snake = insererDebut(game.snake, tailx, taily);
        }

        if (mordre(game.snake)== 1){SDL_Delay(1500); break;}
        dessinerSnake();


        SDL_RenderPresent(game.render);
        SDL_Delay(150);
    }

    SDL_DestroyRenderer(game.render);
    SDL_DestroyWindow(game.window);

    SDL_Quit();

    return 0;
}
void moveSnake(char direction){
    int headx = game.snake->Fin->corps.x;
    int heady = game.snake->Fin->corps.y;
    if (direction == 'N') {
          game.snake = insererFin(game.snake, headx, heady - 25);

            if (heady  <= 0) {
                SDL_Delay(1500);
                isRunning = false;

            }

          game.snake = supprimerDebut(game.snake);
        }

        if (direction == 'S') {
          game.snake = insererFin(game.snake, headx, heady + 25);

            if ((heady + 25) >= HEIGHT) {
                SDL_Delay(1500);
                isRunning = false;

            }

           game.snake = supprimerDebut(game.snake);
        }

        if (direction=='O') {
          game.snake = insererFin(game.snake, headx - 25, heady);

            if (headx <= 0) {
                SDL_Delay(1500);
                isRunning = false;
            }

          game.snake = supprimerDebut(game.snake);
        }

        if (direction == 'E') {
          game.snake = insererFin(game.snake, headx + 25, heady);

            if ((headx + 25) >= WIDTH) {
                SDL_Delay(1500);
                isRunning = false;
            }

          game.snake = supprimerDebut(game.snake);

}
}
void initialise()
{
    SDL_Init(SDL_INIT_EVERYTHING);

    game.window = SDL_CreateWindow(
        "Snake",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        0
    );

    if (!game.window) {
        SDL_LOG("Erreur creation de la fenetre %s\n", SDL_GetError());
    }

    game.render = SDL_CreateRenderer(game.window, -1, 0);
    SDL_SetRenderDrawColor(game.render, 225, 255, 255, 255);
    SDL_RenderClear(game.render);
    SDL_RenderPresent(game.render);

    if (!game.render) {
        SDL_LOG("Erreur creation de le rendu %s\n", SDL_GetError());
    }
}

Snake* RemplirSnake(Snake *snake){
   snake = insererDebut(snake, startingx, startingy);
   snake = insererFin(snake, startingx + 25, startingy);
   snake = insererDebut(snake, startingx - 25, startingy);
   snake = insererDebut(snake, startingx - 50, startingy);
   snake = insererDebut(snake, startingx - 75, startingy);

return snake;
}

void dessinerSnake(){
     Element *tmp=NULL;
    tmp=game.snake->Debut;
    while(tmp){
            SDL_SetRenderDrawColor(game.render,66,66,232,255);
            SDL_RenderFillRect(game.render,&tmp->corps);
             SDL_SetRenderDrawColor(game.render,0,0,0,255);
             SDL_RenderDrawRect(game.render,&tmp->corps);
            tmp=tmp->suivant;
    }
}

int mordre(Snake* S){
 Element* temp = S->Debut;
 int done;
        while (temp->suivant != S->Fin) {
            if (S->Fin->corps.x == temp->corps.x && S->Fin->corps.y == temp->corps.y) {
                done = 1;
                break;
            }
            temp = temp->suivant;
        }
        if(done==1) return 1;
        return 0;
}

void dessinerFood(SDL_Rect food){
      SDL_SetRenderDrawColor(game.render, 255, 0, 0, 0);
        SDL_RenderDrawRect(game.render, &food);
        SDL_RenderFillRect(game.render, &food);
}

void creerfood(SDL_Rect* food){
            int foodx = rand() % 31;
            int foody = rand() % 23;

             food->x = foodx * 25;
             food->y = foody * 25;
             // il faut tester si la food toucher le snake
            Element *tmp=game.snake->Debut;
            while(tmp!=game.snake->Fin){
                if(tmp->corps.x==food->x && tmp->corps.y==food->y){
                    creerfood(food);
                   break;}
                   tmp=tmp->suivant;
            }
}
