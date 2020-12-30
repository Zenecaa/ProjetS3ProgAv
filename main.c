#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "fonctions_SDL.h"
#include "fonction_fichiers.h"
#include "fonctions_collision.h"
#include "fonction_objet.h"
#include "fonction_personnage.h"
#define SIZE_X 600
#define SIZE_Y 600
#define START_HEALTH 3
#define START_STRENGTH 1

int main(int argc, char *argv[]){
    SDL_Window* fenetre;  // Déclaration de la fenêtre
    SDL_Event evenements; // Événements liés à la fenêtre
    bool continuer = false;
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
    //SDL_Texture* fond = charger_image( "fond.bmp", ecran );

    // Charger l’image avec la transparence
    Uint8 r = 255, g = 255, b = 255;
    
    //lecture du pavage
    int* tailleX = malloc(sizeof(int));
    int* tailleY = malloc(sizeof(int));
    taille_fichier("terrain.txt", tailleX, tailleY);
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
    
    int height = (*tailleX)*SrcR_pavage[0][0].w;
    int width = (*tailleY)*SrcR_pavage[0][0].h;
    SDL_SetWindowSize(fenetre, width, height);

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
    DestR_sprite.x = 3;
    DestR_sprite.y = 3;
    DestR_sprite.w = SIZE_X/ *tailleY;
    DestR_sprite.h = SIZE_Y/ *tailleY;

    //Menu de départ
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("./arial.ttf",28);
    SDL_Color color = {0,0,0,0};
    char msg[] = "Jouer";
    SDL_Texture* jouer = charger_texte(msg,ecran,font,color);
    SDL_Rect text_pos; // Position du texte
    text_pos.x = width/3;
    text_pos.y = height/7;
    text_pos.w = width/3;
    text_pos.h = height/7;

    char msg2[] = "Charger";
    SDL_Texture* charger = charger_texte(msg2,ecran,font,color);
    SDL_Rect text1;
    text1.x = width/3;
    text1.y = 3*(height/7);
    text1.w = width/3;
    text1.h = height/7;

    char msg3[] = "Quitter";
    SDL_Texture* quitter = charger_texte(msg3,ecran,font,color);
    SDL_Rect text2;
    text2.x = width/3;
    text2.y = 5*(height/7);
    text2.w = width/3;
    text2.h = height/7;

    //Menu pause
    char msgCont[] = "Continuer";
    SDL_Texture* t_continuer = charger_texte(msgCont,ecran,font,color);
    SDL_Rect t_cont_pos; // Position du texte
    t_cont_pos.x = width/3;
    t_cont_pos.y = (height/9);
    t_cont_pos.w = width/3;
    t_cont_pos.h = height/9;

    char msgSauv[] = "Sauvegarder";
    SDL_Texture* t_sauv = charger_texte(msgSauv,ecran,font,color);
    SDL_Rect t_sauv_pos; // Position du texte
    t_sauv_pos.x = width/3;
    t_sauv_pos.y = 3*(height/9);
    t_sauv_pos.w = width/3;
    t_sauv_pos.h = height/9;

    char msgCharg[] = "Charger";
    SDL_Texture* t_charger = charger_texte(msgCharg,ecran,font,color);
    SDL_Rect t_charg_pos; // Position du texte
    t_charg_pos.x = width/3;
    t_charg_pos.y = 5*(height/9);
    t_charg_pos.w = width/3;
    t_charg_pos.h = height/9;

    char msgQuit[] = "Quitter";
    SDL_Texture* t_quitter = charger_texte(msgQuit,ecran,font,color);
    SDL_Rect t_quit_pos; // Position du texte
    t_quit_pos.x = width/3;
    t_quit_pos.y = 7*(height/9);
    t_quit_pos.w = width/3;
    t_quit_pos.h = height/9;


    //Menu Fin 

    //Menu Mort
    char msgMort[] = "Vous etes mort";
    SDL_Texture* fin = charger_texte(msgMort,ecran,font,color);
    SDL_Rect textFin;
    textFin.x = width/4;
    textFin.y = 2*(height/7);
    textFin.w = width/2;
    textFin.h = height/7;


    Personnage p =cons(DestR_sprite, START_HEALTH, START_STRENGTH);
    
    int nbObjet = 0;
    int nbEnnemi = 0;
    for (int i = 0; i < *tailleX; i++)
        {
            for (int j = 0; j < *tailleY; j++)
            {
                if (terrain[i][j]=='5')
                {
                    nbObjet++;
                }
                if (terrain[i][j]=='6')
                {
                    nbEnnemi++;
                }
            }
        }
    Objet o[nbObjet];
    Personnage e[nbEnnemi];
    bool sens[nbEnnemi];
    nbObjet=0;
    nbEnnemi=0;
    for (int i = 0; i < *tailleX; i++)
        {
            for (int j = 0; j < *tailleY; j++)
            {
                if (terrain[i][j]=='5')
                {
                    Objet tmp = construct(DestR_pavage[i][j], true, 20, 0);
                    o[nbObjet] = tmp;
                    nbObjet++;
                }
                if (terrain[i][j]=='6')
                {
                    Personnage tmp = cons(DestR_pavage[i][j], 5, 1);
                    e[nbEnnemi] = tmp;
                    nbEnnemi++;
                    sens[nbEnnemi]=true;
                }
            }
        }

    SDL_Texture * fond = charger_image("fond.bmp", ecran);
    while (!continuer)
    {
        //SDL_PollEvent( &evenements );
        SDL_RenderClear(ecran);
        SDL_RenderCopy(ecran, fond, NULL, NULL);
        SDL_WaitEvent(&evenements);
        SDL_RenderCopy(ecran,jouer,NULL,&text_pos);
        SDL_RenderCopy(ecran,charger,NULL,&text1);
        SDL_RenderCopy(ecran,quitter,NULL,&text2);
        switch(evenements.type){
            case SDL_QUIT:continuer = true;
            break;
            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym){
                    case SDLK_SPACE:continuer = true;
                    break;
                }
            case SDL_MOUSEBUTTONUP: 
                if (evenements.button.y<(text_pos.y+text_pos.h) && evenements.button.y>(text_pos.y) && evenements.button.x<(text_pos.x+text_pos.w) && evenements.button.x>(text_pos.x))
                {
                    continuer = true;
                }
                if (evenements.button.y<(text2.y+text2.h) && evenements.button.y>(text2.y))
                {
                    continuer = true;
                    terminer = true;
                }
           break;
        }
        SDL_RenderPresent(ecran);
    }
    // Boucle principale
    while(!terminer){
        SDL_PollEvent( &evenements );
        SDL_RenderClear(ecran);
        if (!estMort(p))
        {
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
                case '5':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[0][0], &DestR_pavage[i][j]);
                    break;
                case '6':
                    SDL_RenderCopy(ecran, pavage, &SrcR_pavage[0][0], &DestR_pavage[i][j]);
                    break;
                default:
                    break;
                }
            }
            
        }
        //if (!estMort(p))
        //{
            SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &p.DestR);
        //}
        int pPosx=p.DestR.y/DestR_pavage[0][0].h;
        int pPosy=p.DestR.x/DestR_pavage[0][0].w;
        for (int i = 0; i < nbObjet; i++)
            {
                if (!o[i].recupere)
                {
                    //SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &o[i].DestR);
                }
            }
        for (int i = 0; i < nbEnnemi; i++)
            {
                if (!estMort(e[i]))
                {
                    int posx=e[i].DestR.y/DestR_pavage[0][0].h;
                    int posy=e[i].DestR.x/DestR_pavage[0][0].w;
                    /*switch (sens[i])
                    {
                    case true:
                            if (e[i].DestR.x<(*tailleY-1)*SrcR_pavage[0][0].h+3 && !estMort(e[i]) && !(check_collision(e[i].DestR, DestR_pavage[posx][posy]) && !(terrain[posx][posy+1]=='0' || terrain[posx][posy+1]=='5' || terrain[posx][posy+1]=='6')))
                            {
                                if (sens[i])
                                {
                                    e[i].DestR.x +=1;
                                }
                                else
                                    sens[i] = !sens[i]; 
                            }
                            SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &e[i].DestR);
                            break;
                        case false:
                            if (e[i].DestR.x>0 && !estMort(e[i]) && !(check_collision(e[i].DestR, DestR_pavage[pPosx][pPosy]) && !(terrain[pPosx][pPosy]=='0' || terrain[pPosx][pPosy]=='5' || terrain[pPosx][pPosy]=='6')))
                            {
                                if (!sens[i])
                                {
                                    e[i].DestR.x -=1;
                                }
                                else
                                    sens[i] = !sens[i];
                            }
                            else
                            {
                                sens[i] = true;
                            }
                            SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &e[i].DestR);
                            break;
                    default:
                        break;
                    }*/
                    //printf("%d", sens[i]);
                    if (e[i].DestR.x<(*tailleY-1)*SrcR_pavage[0][0].h+3 && !estMort(e[i]) && !(check_collision(e[i].DestR, DestR_pavage[posx][posy]) && !(terrain[posx][posy+1]=='0' || terrain[posx][posy+1]=='5' || terrain[posx][posy+1]=='6')))
                        {
                            if (sens[i])
                            {
                                e[i].DestR.x +=1;
                            }
                            else
                                
                                sens[i] = !sens[i]; 
                        }
                    else if (e[i].DestR.x>0 && !estMort(e[i]) && !(check_collision(e[i].DestR, DestR_pavage[pPosx][pPosy]) && !(terrain[pPosx][pPosy]=='0' || terrain[pPosx][pPosy]=='5' || terrain[pPosx][pPosy]=='6')))
                        {
                            if (!sens[i])
                            {
                                e[i].DestR.x -=1;
                            }
                            else
                                sens[i] = !sens[i];
                        }
                        else
                            sens[i] = true;
                            SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &e[i].DestR);
                }
            }
        switch(evenements.type){
            case SDL_QUIT:terminer = true;
            break;
            case SDL_KEYDOWN:
            switch(evenements.key.keysym.sym){
                case SDLK_RIGHT:
                    
                    if(p.DestR.x<(*tailleY-1)*SrcR_pavage[0][0].h+3 && !estMort(p) && !(check_collision(p.DestR, DestR_pavage[pPosx][pPosy]) && !(terrain[pPosx][pPosy+1]=='0' || terrain[pPosx][pPosy+1]=='5' || terrain[pPosx][pPosy+1]=='6'))){
                        p.DestR.x += 1;
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &p.DestR);
                        for (int i = 0; i < nbObjet; i++)
                        {
                            if ((check_collision(o[i].DestR, p.DestR) && !o[i].recupere))
                            {
                                o[i].recupere = recuperer(o[i], &p);
                            }
                        }
                    }
                    break;
                case SDLK_LEFT:
                    if (p.DestR.x>0 && !estMort(p) && !(check_collision(p.DestR, DestR_pavage[pPosx][pPosy]) && !(terrain[pPosx][pPosy]=='0' || terrain[pPosx][pPosy]=='5' || terrain[pPosx][pPosy]=='6')))
                    {
                        p.DestR.x -= 1;  
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &p.DestR); 
                        for (int i = 0; i < nbObjet; i++)
                        {
                            if ((check_collision(o[i].DestR, p.DestR) && !o[i].recupere))
                            {
                                o[i].recupere = recuperer(o[i], &p);
                            }
                        }
                    }
                    break;
                case SDLK_DOWN:
                    if (p.DestR.y<(*tailleX-2)*SrcR_pavage[0][0].w+3 && !estMort(p) && (pPosx<(*tailleX-1) && !(check_collision(p.DestR, DestR_pavage[pPosx+1][pPosy]) && !(terrain[pPosx+1][pPosy]=='0' || terrain[pPosx+1][pPosy]=='5' || terrain[pPosx+1][pPosy]=='6')) && pPosx<(*tailleX-1)) )//|| (i<tailleX-1 && terrain[i+1][j]=='0'))
                    {
                        p.DestR.y += 1;  
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &p.DestR);
                        for (int i = 0; i < nbObjet; i++)
                        {
                            if ((check_collision(o[i].DestR, p.DestR) && !o[i].recupere))
                            {
                                o[i].recupere = recuperer(o[i], &p);
                            }
                        }
                    }
                    break;
                case SDLK_UP:
                    if (p.DestR.y>0 && !estMort(p) && !(check_collision(p.DestR, DestR_pavage[pPosx][pPosy]) && !(terrain[pPosx][pPosy]=='0' || terrain[pPosx][pPosy]=='5' || terrain[pPosx][pPosy]=='6')))
                    {
                        p.DestR.y -= 1;
                        SDL_RenderCopy(ecran, sprite, &SrcR_sprite, &p.DestR);
                        for (int i = 0; i < nbObjet; i++)
                        {
                            if ((check_collision(o[i].DestR, p.DestR) && !o[i].recupere))
                            {
                                o[i].recupere = recuperer(o[i], &p);
                            }
                        }
                    }
                    break;
                case SDLK_SPACE:
                    for (int i = 0; i < nbEnnemi; i++)
                    {
                        if (check_collision(p.DestR, e[i].DestR))
                        {
                            attaquer(p,&e[i]);
                            attaquer(e[i],&p);
                        }
                    }
                    break;
                case SDLK_ESCAPE:
                    continuer = false;
                    while (!continuer)
                    {
                        SDL_WaitEvent(&evenements);
                        SDL_RenderClear(ecran);
                        SDL_RenderCopy(ecran, fond, NULL, NULL);
                        SDL_RenderCopy(ecran,t_continuer,NULL,&t_cont_pos);
                        SDL_RenderCopy(ecran,t_sauv,NULL,&t_sauv_pos);
                        SDL_RenderCopy(ecran,t_charger,NULL,&t_charg_pos);
                        SDL_RenderCopy(ecran,t_quitter,NULL,&t_quit_pos);
                        switch(evenements.type){
                            case SDL_QUIT:continuer = true;
                            break;
                            case SDL_KEYDOWN:
                                switch(evenements.key.keysym.sym){
                                    case SDLK_SPACE:continuer = true;
                                    break;
                                }
                            case SDL_MOUSEBUTTONUP: 
                                if (evenements.button.y<(t_cont_pos.y+t_cont_pos.h) && evenements.button.y>(t_cont_pos.y) && evenements.button.x<(t_cont_pos.x+t_cont_pos.w) && evenements.button.x>(t_cont_pos.x))
                                {
                                    continuer = true;
                                }
                                if (evenements.button.y<(t_quit_pos.y+t_quit_pos.h) && evenements.button.y>(t_quit_pos.y) && evenements.button.x<(t_quit_pos.x+t_quit_pos.w) && evenements.button.x>(t_quit_pos.x))
                                {
                                    continuer = true;
                                    terminer = true;
                                }
                            break;
                        }
                        SDL_RenderPresent(ecran);
                    }
                    break;
            }
        }
        }
        else
        {
            while (!terminer)
            {
                SDL_RenderClear(ecran);
                SDL_RenderCopy(ecran, fond, NULL, NULL);
                SDL_WaitEvent(&evenements);
                SDL_RenderCopy(ecran,fin,NULL,&textFin);
                SDL_RenderCopy(ecran,charger,NULL,&text1);
                SDL_RenderCopy(ecran,quitter,NULL,&text2);
                switch(evenements.type){
                    case SDL_QUIT:continuer = true;
                    break;
                    case SDL_KEYDOWN:
                        switch(evenements.key.keysym.sym){
                            case SDLK_SPACE:continuer = true;
                            break;
                        }
                    case SDL_MOUSEBUTTONUP: 
                        if (evenements.button.y<(text2.y+text2.h) && evenements.button.y>(text2.y))
                        {
                            
                            terminer = true;
                        }
                    break;
                }
                SDL_RenderPresent(ecran);
            }
        }
        SDL_RenderPresent(ecran);
    }// Quitter SDL;
    TTF_Quit();
    SDL_DestroyTexture(fin);
    SDL_DestroyTexture(fond);
    SDL_DestroyTexture(jouer);
    SDL_DestroyTexture(charger);
    SDL_DestroyTexture(quitter);
    SDL_DestroyTexture(t_continuer);
    SDL_DestroyTexture(t_sauv);
    SDL_DestroyTexture(t_charger);
    SDL_DestroyTexture(t_quitter);
    SDL_DestroyTexture(sprite);
    SDL_DestroyTexture(pavage);
    SDL_DestroyRenderer(ecran);//Quitter SDL ...
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}