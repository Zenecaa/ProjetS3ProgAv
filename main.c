#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonction_fichiers.h"
#include "fonctions_collision.h"
#define SIZE_X 600
#define SIZE_Y 600

int main(int argc, char *argv[]){
    SDL_Window* fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());
        SDL_Quit();return EXIT_FAILURE;
    }// Créer la fenêtre
    fenetre = SDL_CreateWindow("Fenetre SDL", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, SIZE_X, SIZE_Y, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d’erreur
    {
        printf("Erreur de la creation d’une fenetre: %s",SDL_GetError());
        SDL_Quit();return EXIT_FAILURE;
    }
    // Mettre en place un contexte de rendu de l’écran
    SDL_Renderer* ecran;
    ecran = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    // Charger l’image
    SDL_Texture* fond = charger_image( "fond.bmp", ecran );

    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    
    //lecture du pavage
    int* tailleX = malloc(sizeof(int));
    int* tailleY = malloc(sizeof(int));
    taille_fichier("terrain.txt", tailleX, tailleY);
    printf("%d\n", SIZE_X/ *tailleX);
    printf("%d\n", SIZE_Y/ *tailleY);
    char** terrain = lire_fichier("terrain.txt");
    SDL_Texture* pavage = charger_image( "pavage.bmp", ecran );
    int pw, pl;
    SDL_QueryTexture(pavage, NULL, NULL, &pw, &pl);
    SDL_Rect SrcR_pavage[16][10];
    for(int i=0; i<16; i++){
        for (int j = 0; j < 10; j++)
        {
            SrcR_pavage[i][j].x = i*(pw/16);
            SrcR_pavage[i][j].y = j*(pl/10);
            SrcR_pavage[i][j].w = pw/16; // Largeur du sprite
            SrcR_pavage[i][j].h = pl/10; // Hauteur du sprite
        }
    }

    
    SDL_Rect DestR_pavage[*tailleX][*tailleY];
    for (int i = 0; i < *tailleX; i++){
        for (int j = 0; j < *tailleY; j++)
        {
            DestR_pavage[i][j].x = j*(pw/16);
            DestR_pavage[i][j].y = i*(pl/10);
            DestR_pavage[i][j].w = pl/10;
            DestR_pavage[i][j].h = pw/16;
        }
    }

    SDL_SetWindowSize(fenetre, (*tailleY)*SrcR_pavage[0][0].h, (*tailleX-1)*SrcR_pavage[0][0].w);

    SDL_Surface *surf = SDL_LoadBMP("sprites.bmp");
    Uint32 *mespixels = (Uint32*) ((Uint8*) surf->pixels);
    SDL_GetRGB(*mespixels, surf->format, &r, &g, &b); 
    SDL_Texture* sprite = charger_image_transparente("sprites.bmp", ecran,r,g,b);
    int spriteW, spriteH;
    SDL_QueryTexture(sprite, NULL, NULL, &spriteW, &spriteH);
    
    //Affichage de sprites
    SDL_Rect SrcR_sprite;
    int tailleW = spriteW/3;
    int tailleH = spriteH/2;
    SrcR_sprite.x = 0;
    SrcR_sprite.y = 0;
    SrcR_sprite.w = tailleW;
    SrcR_sprite.h = tailleH;


    SDL_Rect DestR_sprite;
    DestR_sprite.x = 0;
    DestR_sprite.y =  0;
    DestR_sprite.w = SIZE_X/ *tailleY;
    DestR_sprite.h = SIZE_Y/ *tailleY;

    printf("%d\n", check_collision(SrcR_pavage[0][0],SrcR_pavage[2][2]));
    printf("%d\n", check_collision(DestR_pavage[0][0],DestR_sprite));
    //check_terrain_col(DestR_sprite, DestR_pavage, terrain, *tailleX, *tailleY);

    // Boucle principale
    while(!terminer){
        SDL_PollEvent( &evenements );
        SDL_RenderClear(ecran);
        for (int i = 0; i < *tailleX; i++)
        {
            for (int j = 0; j < *tailleY; j++)
            {
                switch (terrain[i][j])
                {
                case '0':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[0][0], &DestR_pavage[i][j]);
                    break;
                case '1':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[1][0], &DestR_pavage[i][j]);
                    break;
                case '2':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[2][0], &DestR_pavage[i][j]);
                    break;
                case '3':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[3][0], &DestR_pavage[i][j]);
                    break;
                case '4':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[4][0], &DestR_pavage[i][j]);
                    break;
                default:
                    break;
                }
            }
            
        }
        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &DestR_sprite);
        int i=DestR_sprite.y/DestR_pavage[0][0].h;
        int j=DestR_sprite.x/DestR_pavage[0][0].w;
        switch(evenements.type){
            case SDL_QUIT:terminer = true;
            break;
            case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym){
                /*case SDLK_RIGHT:
                    
                    if(DestR_sprite.x<(*tailleY-1)*SrcR_pavage[0][0].h+3 && !(check_collision(DestR_sprite, DestR_pavage[i][j]) && terrain[i][j+1]!='0')){//check_terrain_col(DestR_sprite, DestR_pavage, terrain, *tailleX, *tailleY)==false ){
                        DestR_sprite.x += 1;  
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &DestR_sprite);
                        printf("%d\n", check_collision(DestR_pavage[0][0],DestR_sprite));
                    }
                    break;
                case SDLK_LEFT:
                    if (DestR_sprite.x>0 && j>0 && !(check_collision(DestR_sprite, DestR_pavage[i][j-1]) && terrain[i][j-1]!='0'))
                    {
                        DestR_sprite.x -= 1;  
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &DestR_sprite); 
                    }
                    break;
                case SDLK_DOWN:
                    if (DestR_sprite.y<(*tailleX-2)*SrcR_pavage[0][0].w+3 && !(check_collision(DestR_sprite, DestR_pavage[i][j]) && terrain[i+1][j]!='0'))
                    {
                        DestR_sprite.y += 1;  
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &DestR_sprite);
                    }
                    break;
                case SDLK_UP:
                    if (DestR_sprite.y>0)
                    {
                        DestR_sprite.y -= 1;  
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &DestR_sprite);
                    }*/
                    break;
                case SDLK_ESCAPE:terminer = true;  
                break;
            }
        }
        SDL_RenderPresent(ecran);
    }// Quitter SDL;
    TTF_Quit();
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(sprite);
    SDL_DestroyTexture(pavage);
    SDL_DestroyRenderer(ecran);//Quitter SDL ...
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}