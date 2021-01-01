#ifndef fonction_sauvegarde
#define fonction_sauvegarde
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"fonction_objet.h"
#include"fonction_personnage.h"
#include"fonction_sauvegarde.h"

void sauvegarde(char nomfichier[], Personnage p, Objet o[], int nbObjets, Personnage e[], bool sens[], int nbEnnemis);

#endif