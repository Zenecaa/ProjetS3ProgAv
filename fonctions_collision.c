#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include <SDL2/SDL.h>
#include"fonction_fichiers.h"
#include"fonctions_collision.h"


bool check_collision( SDL_Rect A, SDL_Rect B )
{
    //Les cotes des rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
 
    //Calcul les cotes du rectangle A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;
 
    //Calcul les cotes du rectangle B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

     //Tests de collision
    if( bottomA <= topB ){
        return false;
    }
 
    if( topA >= bottomB ){
        return false;
    }
 
    if( rightA <= leftB ){
        return false;
    }
 
    if( leftA >= rightB ){
        return false;
    }
    //Si conditions collision detectee
    return true;
}

bool check_terrain_col( SDL_Rect A, SDL_Rect** tabRect, char** tab, int tailleX, int tailleY){//Non aboutie, une autre methode est utilisée pour gestion de collision
    bool res=false;
    for (int i = 0; i < tailleX; i++){
        for (int j = 0; j < tailleY; j++){
            if (/*check_collision(A, tabRect[i][j]) && */tab[i][j]!='0'){
                res = true;
            }
            else res=false;
        }
    }
    return res;
}