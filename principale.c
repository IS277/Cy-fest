#include "utilitaire.h"

// Fonction pour vider le buffer
void vide_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

// Fontion texte en minuscule
char *texte_a_minuscule(char texte[]) {
  int i = 0;
  while (texte[i] != '\0') {
    if (texte[i] >= 'A' && texte[i] <= 'Z') {
      texte[i] = texte[i] - 'A' + 'a'; // on met la lettre en minsucule
    }
    i++;
  }
  return texte;
}

void liberer_salle(Salle *salle) {
  for (int i = 0; i < salle->nbr_rangées[0] + salle->nbr_rangées[1] +
                          salle->nbr_rangées[2];
       i++) {
    free(salle->siège[i]); // Libérer chaque sous-pointeur
  }
  free(salle->siège); // Libérer le pointeur principal
}

void mode_festivalier(void) {
  int choix = 0;
  int verif = 0;
  int fin_programme = 0;

  do {
    printf("Choisiser l'action que vous voulez effectuer:\n");
    printf("1. Afficher les salles\n");
    printf("2. Reserver une place\n");
    printf("3. Retour\n");

    verif = scanf("%d", &choix);
    clrscr(); // on efface l'écran et affiche le menu
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      switch (choix) {
      case 1:
        afficher_statut_salle(1);
        break;
      case 2:
        reserver();
        break;
      case 3:
        fin_programme = 1;
        break;

      default:
        printf("Choix invalide. Veuillez réessayer.\n");
        break;
      }
    }
  } while (fin_programme != 1 || verif != 1); // on viens fermer le mode manager
}

void mode_manager(void) {
  int choix = 0;
  int verif = 0;
  int fin_programme = 0;

  do {
    printf("Choisiser l'action que vous voulez effectuer:\n");
    printf("1. Créer une ou plusieurs salle(s)\n");
    printf("2. Modifier une salle existante\n");
    printf("3. Supprimer une salle\n");
    printf("4. Retour\n");

    verif = scanf("%d", &choix);
    clrscr(); // on efface l'écran et affiche le menu
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      switch (choix) {
      case 1:
        creer_salle();
        break;

      case 2:
        modifier_salle();
        break;

      case 3:
        supprimer_salle();
        break;

      case 4:
        fin_programme = 1;
        break;

      default:
        printf("Choix invalide. Veuillez réessayer.\n");
        break;
      }
    }
  } while (fin_programme != 1 || verif != 1); // on viens fermer le mode manager
}

int main(void) {
  int mode = 0;
  int verif = 0;
  int fin_programme =
      0; // on empeche que le programe s'arrete (permetra de revenir en arriere)
  do {
    printf("Choisiser le mode:\n");
    printf("1. Mode manager\n");
    printf("2. Mode festivalier\n");
    printf("3. Quitter\n");
    verif = scanf("%d", &mode);
    clrscr(); // on efface l'écran et affiche le menu
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      switch (mode) {
      case 1:
        mode_manager();
        break;

      case 2:
        mode_festivalier();
        break;

      case 3:
        fin_programme = 1;
        break;
      default:
        printf("Mode invalide. Veuillez réessayer.\n");
        break;
      }
    }
  } while (fin_programme != 1 || verif != 1);

  printf("Fin du programme\n");
  return 0;
}