#include<stdlib.h>
#include<stdio.h>
#include"fonction_objet.h"
#include"fonctions_collision.h"


Objet construct(SDL_Rect r, bool soi, int s, int f){
    Objet res;
    res.DestR = r;
    res.soigne = soi;
    res.recupere = false;
    res.soin=s;
    res.force=f;
    return res;
}

void appliqueEffet(Objet o, Personnage * p){
    if (o.soigne)
    {
        p->vie= p->vie + o.soin;
    }
    else
    {
        p->force = p->force + o.force;
    }
}

bool recuperer(Objet o, Personnage * p){
    bool res = false;
    if (check_collision(o.DestR, p->DestR))
    {
        appliqueEffet(o, p);
        res = true;
    }
    return res;
}