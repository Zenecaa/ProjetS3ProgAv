#include<stdlib.h>
#include<stdio.h>
#include"fonction_personnage.h"

 Personnage cons(SDL_Rect r, int v, int f){
     Personnage res;
     res.DestR = r;
     res.vie = v;
     res.force = f;
     return res;
 }


 bool estMort(Personnage p){
     bool res = false;
     if (p.vie<=0)
     {
         res=true;
     }
     return res;
 }

 void attaquer(Personnage agresseur, Personnage *cible){
     if (!estMort(agresseur)&&!estMort(*cible))
     {
         cible->vie= cible->vie - agresseur.force;
     }
 }