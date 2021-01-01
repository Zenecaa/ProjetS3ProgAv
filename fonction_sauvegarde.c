#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"fonction_objet.h"
#include"fonction_personnage.h"
#include"fonction_sauvegarde.h"

void sauvegarder(char nomfichier[], Personnage p, Objet o[], int nbObjets, Personnage e[], bool sens[], int nbEnnemis){
    FILE *f = fopen(nomfichier, "w+");
    //sauvegarde des donnees du personnage
    fprintf(f, "%d\n",(p.DestR.x));
    fprintf(f, "%d\n",(p.DestR.y));
    fprintf(f, "%d\n",(p.DestR.w));
    fprintf(f, "%d\n",(p.DestR.h));
    fprintf(f, "%d\n",(p.vie));
    fprintf(f, "%d\n",(p.force));
    //sauvegarde des donnees des objets
    for (int i = 0; i < nbObjets; i++)
    {
        fprintf(f, "%d\n",(o[i].DestR.x));
        fprintf(f, "%d\n",(o[i].DestR.y));
        fprintf(f, "%d\n",(o[i].DestR.w));
        fprintf(f, "%d\n",(o[i].DestR.h));
        fprintf(f, "%d\n",(o[i].recupere));
        fprintf(f, "%d\n",(o[i].soigne));
        fprintf(f, "%d\n",(o[i].soin));
        fprintf(f, "%d\n",(o[i].force));
    }
    //sauvegarde des donnes des ennemis et leur sens
    for (int i = 0; i < nbEnnemis; i++)
    {
        fprintf(f, "%d\n",(e[i].DestR.x));
        fprintf(f, "%d\n",(e[i].DestR.y));
        fprintf(f, "%d\n",(e[i].DestR.w));
        fprintf(f, "%d\n",(e[i].DestR.h));
        fprintf(f, "%d\n",(e[i].vie));
        fprintf(f, "%d\n",(e[i].force));
        fprintf(f, "%d\n",(sens[i]));
    }
    
    fclose(f);
}

