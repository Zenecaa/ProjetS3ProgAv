#include<stdlib.h>
#include<stdio.h>
#include"fonction_fichiers.h"

char** allouer_tab_2D(int n, int m){
    char ** tableau2d = malloc(n*m*sizeof(int));
    for(int i = 0; i < n; ++i){
        tableau2d[i] = malloc(m*sizeof(int));
    } 
    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            tableau2d[i][j]='1';
        }
    }
    return tableau2d;
}

void desallouer_tab_2D(char** tab, int n){
    for(int i = 0; i < n; ++i){
        free(tab[i]);
    }
    free(tab); 
}

void afficher_tab_2D(char** tab, int n, int m){
    for(int i = 0; i<n; i++){
       for(int j = 0; j<m; j++){
           printf("%c", tab[i][j]);
        } 
        printf("%c", '\n');
    }
}

void taille_fichier(const char* nomFichier, int* nbLig, int* nbCol){
    FILE* pFile = fopen(nomFichier, "r");
    char c; 
    int tmp = 0;
    int l = 0;
    int col = 0;
    if (pFile==NULL) {
        perror("Erroropeningfile"); 
    }
    else{ 
        do { 
            c = fgetc(pFile); 
            if(c=='\n'){
                l++;
                if(tmp>col){
                    col=tmp;
                }
                tmp=0;
            }
            else{
                if(c!='\n'){
                    tmp++;
                }
                
            }
        } 
        while(c != EOF);
    }
    *nbLig=l;
    *nbCol=col;
    /*printf("%d", *nbLig);
    printf("%c", '\n');
    printf("%d", *nbCol);
    printf("%c", '\n');*/
    fclose(pFile);
}

char** lire_fichier(const char* nomFichier){
    FILE* pFile = fopen(nomFichier, "r");
    /*char c; 
    int n = 0; 
    if (pFile==NULL) 
        perror("Erroropeningfile"); 
    else{ 
        do { 
            c = fgetc(pFile); 
            printf("%c", c);
            n++;
        } 
        while(c != EOF);
    }
    fclose(pFile);
    return NULL;*/
    char c; 
    int* l = malloc(sizeof(int));
    int* col = malloc(sizeof(int));
    taille_fichier(nomFichier, l, col);
    char** tab = allouer_tab_2D(*l, *col);
    if (pFile==NULL) 
        perror("Erroropeningfile"); 
    else{ 
        int i = 0;
        int j = 0;
        do { 
            c = fgetc(pFile); 
            if((i<*l) && (j<*col)){
                tab[i][j]=c;
                j++;
            }
            if(c=='\n'){
                i++;    
                j=0;
            }
        } 
        while(c != EOF);
        /*c = fgetc(pFile); 
        while(c != EOF){
            if(c=='\n'){
                i++;    
                j=0;
            }
            else{
                if((c!='\n') & (i<*l) & (j<*col)){
                    tab[i][j]=c;
                }
                j++;
            }
        }*/
    }
    //char** tab = allouer_tab_2D(2, 2);
    /*for(int j=0;j<*col;j++){
                if(c=='\n'){
                    for(j;j<*col;j++){
                        tab[i][j]=' ';
                    }
                }
                else{
                    tab[i][j]=c;
                }
                c = fgetc(pFile); 
            }*/
    fclose(pFile);
    return tab;
}

char** modifier_caractere(char** tab, int n, int m, char ancien, char nouveau){
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (tab[i][j]==ancien)
            {
                tab[i][j]=nouveau;
            }
            
        }
    }  
}



/*int main(int argc, char *argv[]){
    int* l = malloc(sizeof(int));
    int* col = malloc(sizeof(int));
    taille_fichier("terraintest.txt", l, col);
    printf("%d\n", *l);
    printf("%d\n", *col);
    char** tab = lire_fichier("terraintest.txt");
    afficher_tab_2D(tab, *l, *col);
    //char** tab1 = allouer_tab_2D(12, 12);
    //afficher_tab_2D(tab1, 12, 12);
    //printf("%c", l);
    //printf("%c", c);
}*/