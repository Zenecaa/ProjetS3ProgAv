#include<stdbool.h>
#include <SDL2/SDL.h>
#include"fonction_personnage.h"

typedef struct Objet{
    SDL_Rect DestR; 
    bool soigne, recupere;
    int soin, force;
  } Objet;

  Objet construct(SDL_Rect r, bool soi, int s, int f);

  void appliqueEffet(Objet o, Personnage * p);

  bool recuperer(Objet o, Personnage * p);