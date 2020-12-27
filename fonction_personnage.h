#ifndef fonction_personnage
#define fonction_personnage
#include <SDL2/SDL.h>
#include<stdbool.h>

typedef struct Personnage { 
    SDL_Rect DestR;
    int vie, force;
  } Personnage;

  Personnage cons(SDL_Rect r, int v, int f);

  bool estMort(Personnage p);

  void attaquer(Personnage agresseur, Personnage cible);

#endif