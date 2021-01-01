#ifndef fonctions_collision
#define fonctions_collision
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include"fonction_fichiers.h"

bool check_collision( SDL_Rect A, SDL_Rect B );

bool check_terrain_col( SDL_Rect A, SDL_Rect** tabRect, char** tab, int tailleX, int tailleY);

#endif