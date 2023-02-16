#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"

int main(void){
    srand(time(NULL));
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    int energie=10;

    int i;
    for(i=0;i<20;i++){
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
        ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
    }
    printf("le nombre de proie est de %d\n",compte_animal_rec(liste_proie));
    printf("le nombre de predateur est de %d\n",compte_animal_rec(liste_predateur));
    ecrire_ecosys("test.txt",liste_predateur,liste_proie);
    afficher_ecosys(liste_proie,liste_predateur);

    liste_proie = liberer_liste_animaux(liste_proie);
    liste_predateur = liberer_liste_animaux(liste_predateur);
    afficher_ecosys(liste_proie,liste_predateur);
    
    Animal *liste_proie2 = NULL;
    Animal *liste_predateur2 = NULL;
    lire_ecosys("test.txt",&liste_predateur2,&liste_proie2);
    afficher_ecosys(liste_proie2,liste_predateur2);

    return 0;
    
}
