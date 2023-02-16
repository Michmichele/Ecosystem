#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"
#include <string.h>

float p_ch_dir = 0.5;
float p_reproduce_proie=0.5;
float p_reproduce_predateur=0.4;
int temps_repousse_herbe=-5;
float p_manger = 1;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(x>=0 && x<SIZE_X);
  assert(y>=0 && y<SIZE_Y);
  Animal* res = creer_animal(x,y,energie);
  *liste_animal = ajouter_en_tete_animal(*liste_animal,res);
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
    //On verifie que animal n'est pas null
    assert(animal);
    if (liste == NULL) return;
    Animal *tmp = NULL;
    tmp = *liste;
    //On verifie le premier element de la liste
    if (tmp == animal) {
        *liste = animal->suivant;
        free(animal);
        return;
    }
    while ( tmp->suivant != NULL ) {
        if ( tmp->suivant == animal) {
            tmp->suivant = animal->suivant;
            free(animal);
            return;
        }
        tmp = tmp->suivant;
    }
    return;
}


/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
   Animal *tmp;
   while (liste){
    tmp=liste;
    liste = liste->suivant;
    free(tmp);
   }
  return NULL;
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}


/* Part 1. Exercice 4, question 1, ATTENTION, ce code est susceptible de contenir des erreurs... */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  while(la){
      if((float)rand()/RAND_MAX <= p_ch_dir){
        la->dir[0] = (rand()%3)-1;
        la->dir[1] = (rand()%3)-1;
      }
      la->x = (la->x + SIZE_X + la->dir[0])%SIZE_X;
      la->y = (la->y + SIZE_Y + la->dir[1])%SIZE_Y;
      la = la->suivant;
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  if(liste_animal){
    Animal *ani = *liste_animal;
    while(ani){
      if (((float)rand()) / RAND_MAX <= p_reproduce){
          ajouter_animal(ani->x,ani->y,ani->energie/2,liste_animal);
          ani->energie /=2;
      }
      ani = ani->suivant;
    }    
  }
}


/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
  //On teste si liste_proie est non null
  if(liste_proie){
    Animal *ani = *liste_proie;
    bouger_animaux(ani); 
    while(ani){
      if(monde[ani->x][ani->y] >= 0){
        ani->energie += monde[ani->x][ani->y];
        monde[ani->x][ani->y] = temps_repousse_herbe;
      }
      if( --(ani->energie) < 0){
        Animal *tmp = ani;
        ani = ani->suivant;
        enlever_animal(liste_proie, tmp);
      }else {
        ani = ani->suivant;
      }
    }
    reproduce(liste_proie, p_reproduce_proie);
  }
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  while (l) {
    //On teste si il y a une proie sur la case du prédateur
    if (l->x == x && l->y == y)
      return l;
    l = l->suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  //On teste si liste prédateur est non null
  if(liste_predateur){
    Animal *ani = *liste_predateur;
    bouger_animaux(ani);
    Animal *ani2;
    while(ani){
      ani->energie -= 1;
      //On teste si la liste proie est non vide
      if(liste_proie){
        ani2 =animal_en_XY(*liste_proie, ani->x, ani->y);
        if((ani2) && rand()*1./RAND_MAX < p_manger){
          ani->energie += ani2->energie;
          enlever_animal(liste_proie, ani2);
        }  
      }
      if(ani->energie < 0){
        Animal *tmp = ani;
        ani = ani->suivant;
        enlever_animal(liste_predateur, tmp);
      }else{
        ani = ani->suivant;
      }
    }
    reproduce(liste_predateur, p_reproduce_predateur);
  }  
}


/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for (int i = 0; i < SIZE_X; i++) {
      for (int j = 0; j < SIZE_Y; j++) {
          monde[i][j] += 1;
      }
  }
}

void ecrire_ecosys(const char *nom_fichier, Animal * liste_predateur,Animal * liste_proie){
  FILE *f;
  f = fopen(nom_fichier,"w");
  assert(f);
  fprintf(f,"<proie>\n");
  while(liste_proie){
    fprintf(f,"x=%d,y=%d,dir=[%d,%d],e=%.6f\n",liste_proie->x,liste_proie->y,liste_proie->dir[0],liste_proie->dir[1],liste_proie->energie);
    liste_proie=liste_proie->suivant;
  }
  fprintf(f,"</proie>\n");
  fprintf(f,"<predateur>\n");
  while(liste_predateur){
    fprintf(f,"x=%d,y=%d,dir=[%d,%d],e=%.6f\n",liste_predateur->x,liste_predateur->y,liste_predateur->dir[0],liste_predateur->dir[1],liste_predateur->energie);
    liste_predateur=liste_predateur->suivant;
  }
  fprintf(f,"</predateur>\n");
  fclose(f);
}

void lire_ecosys(const char *nom_fichier,Animal **liste_predateur,Animal **liste_proie){
  FILE *f;
  f = fopen(nom_fichier,"r");
  //Verifie si le fichier existe
  assert(f);
  char buffer[130];
  if(fgets(buffer,130,f)==NULL||(strcmp(buffer,"<proie>\n")!= 0))printf("erreur");
  while(fgets(buffer,130,f)!= NULL&& strcmp(buffer,"</proie>\n")!=0){
    int x,y,dir[2];
    float energie;
    int n = sscanf(buffer,"x=%d,y=%d,dir=[%d,%d],e=%f",&x,&y,&dir[0],&dir[1],&energie);
    Animal * a = creer_animal(x,y,energie);
    a->dir[0]=dir[0];
    a->dir[1]=dir[1];
    *liste_proie = ajouter_en_tete_animal(*liste_proie,a);
  }
  if(fgets(buffer,130,f)==NULL||(strcmp(buffer,"<predateur>\n")!= 0)) printf("erreur");
  while(fgets(buffer,130,f)!= NULL&& strcmp(buffer,"</predateur>\n")!=0){
    int x,y,dir[2];
    float energie;
    int n = sscanf(buffer,"x=%d,y=%d,dir=[%d,%d],e=%f",&x,&y,&dir[0],&dir[1],&energie);
    Animal * a = creer_animal(x,y,energie);
    a->dir[0]=dir[0];
    a->dir[1]=dir[1];
    *liste_predateur= ajouter_en_tete_animal(*liste_predateur,a);
  }
  fclose(f);
}
