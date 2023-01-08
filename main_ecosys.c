#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 50
#define ENERGIE_PROIES 20
#define ENERGIE_PREDATEURS 20
#define T_WAIT 30000
#define NB_ITERATIONS 200

int main(void) {
  srand(time(NULL));

  int monde[SIZE_X][SIZE_Y];
	int i, j;

  // Initialisation de monde
	for(i = 0; i < SIZE_X; i++){
		for(j = 0; j < SIZE_Y; j++){
			monde[i][j] = 0;
		}
  }

  Animal *liste_proie = NULL;
  // Initialisation de liste_proie
    for (int i = 0; i < NB_PROIES; i++) {
        ajouter_animal( rand()%SIZE_X, rand()%SIZE_Y, ENERGIE_PROIES, &liste_proie);
    }

  Animal *liste_predateur = NULL;
  // Initialisation de liste_predateur
    for (int i = 0; i < NB_PREDATEURS; i++) {
        ajouter_animal( rand()%SIZE_X, rand()%SIZE_Y, ENERGIE_PREDATEURS, &liste_predateur);
    }

// Evolution du ecosysteme
  clear_screen();
  afficher_ecosys(liste_proie, liste_predateur);

  for (int i = 0; i < NB_ITERATIONS; i++) {
      if ( compte_animal_it(liste_proie) <= 0  ) {
        printf("Y'a plus de proies \n");
        break;
      };
      if ( compte_animal_it(liste_predateur) <= 0  ) {
        printf("Y'a plus de predateurs \n");
        break;
      };
      /* rafraichissement du ecosysteme */
      rafraichir_monde( monde );
      /* rafraichissement des proies */
      rafraichir_proies( &liste_proie, monde );
      /* rafraichissement des predateurs */
      rafraichir_predateurs( &liste_predateur, &liste_proie );
      
      /* rafraichissement de l'affichage */
      usleep(T_WAIT);         
      printf("Iteration  %d :\n", i+1);
      afficher_ecosys(liste_proie, liste_predateur);
    }


// liberation de la memoire
  liberer_liste_animaux(liste_predateur);
  liberer_liste_animaux(liste_proie);

  return 0;
}

