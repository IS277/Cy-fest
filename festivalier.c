#include "utilitaire.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fonction pour retourner le maximum de trois valeurs
int maxDeTrois(int a, int b, int c) {
  int max = a; // Supposons initialement que 'a' est le plus grand
  if (b > max) {
    max = b; // Si 'b' est plus grand que 'max', alors 'b' est le plus grand
             // jusqu'à présent
  }
  if (c > max) {
    max = c; // Si 'c' est plus grand que 'max', alors 'c' est le plus grand
  }
  return max; // Retourner la valeur maximale
}

// Définition de la fonction pour afficher les détails d'une salle avec ses
// sièges
void afficher_details_Salle(Concert *tab) {
  if (tab == NULL) {
    printf("Erreur, paramètre dans afficher_details_Salle.\n");
  }

  int decalage = 0;
  clrscr();
  // Afficher les informations de la date
  printf("\nLa date du concert est : %d/%d/%d\n", tab->d.jour, tab->d.mois,
         tab->d.annee);
  printf("Début : %.2fh/%.2fm/%.2fs\n", tab->d.heure_debut,
         tab->d.minutes_debut, tab->d.secondes_debut);
  printf("Fin : %.2fh/%.2fm/%.2fs\n", tab->d.heure_fin, tab->d.minutes_fin,
         tab->d.secondes_fin);

  printf("Nombre de places total : %d\n", tab->s.total);
  printf("👐 Plan de la scène %s: 🤘\n\n", tab->s.nom);
  for (int b = 0; b < maxDeTrois(tab->s.nbr_places[0], tab->s.nbr_places[1],
                                 tab->s.nbr_places[2]) /
                          2;
       b++) {
    printf(" ");
  }
  printf("🎵 SCENE 🎵\n");
  printf("------------------------------\n");

  for (int j = 0; j < 3; j++) {

    if ((strcmp(tab->fosse, "oui") == 0) && j == 0) {
      printf("\nFosse :\n");
    } else {
      printf("\nCatégorie %c :\n", 'A' + j);
    }

    // Afficher les sièges de la salle
    for (int k = decalage; k < decalage + tab->s.nbr_rangées[j]; k++) {
      for (int l = 0; l < tab->s.nbr_places[j]; l++) {
        if (tab->s.siège[k][l] == 'x') {
          couleur("31");
        } else {
          couleur("32");
        }
        printf("%c", tab->s.siège[k][l]);
      }
      printf("\n");
    }
    printf("\n");
    couleur("0");
    decalage += tab->s.nbr_rangées[j];
  }

  // Afficher les informations des sièges (rangée, places par rangée et prix)
  for (int j = 0; j < 3; j++) {
    if ((strcmp(tab->fosse, "oui") == 0) && j == 0) {
      printf("\nPrix Fosse : %.2f\n", tab->s.prix[j]);
    } else {
      printf("\nPrix Catégorie %c : %.2f\n", 'A' + j, tab->s.prix[j]);
    }
  }
  printf("\n");
}

// calcule la difference de temps entre maintenant et la fin du concert
long concert_fini(Date date) {
  struct tm fin = {0};

  // Remplir la structure tm pour l'heure de fin
  fin.tm_year = date.annee - 1900; // Années depuis 1900
  fin.tm_mon = date.mois - 1;      // Mois (0-11)
  fin.tm_mday = date.jour;         // Jour du mois (1-31)
  fin.tm_hour = (int)date.heure_fin;
  fin.tm_min = (int)date.minutes_fin;
  fin.tm_sec = (int)date.secondes_fin;

  // Déclarer une structure time_t pour stocker le temps actuel
  time_t maintenant;
  // Obtenir le temps actuel
  time(&maintenant);
  // Convertir le temps en une structure tm pour une représentation plus lisible
  struct tm *temps_local = localtime(&maintenant);

  time_t secondes_fin = mktime(&fin);

  long difference_secondes = difftime(secondes_fin, maintenant);
  // printf("%ld  ",difference_secondes);

  return difference_secondes;
}

// calcule la difference de temps entre maintenant et le début du concert
long concert_debuter(Date date) {
  struct tm debut = {0};

  // Remplir la structure tm pour l'heure de début
  debut.tm_year = date.annee - 1900; // Années depuis 1900
  debut.tm_mon = date.mois - 1;      // Mois (0-11)
  debut.tm_mday = date.jour;         // Jour du mois (1-31)
  debut.tm_hour = (int)date.heure_debut;
  debut.tm_min = (int)date.minutes_debut;
  debut.tm_sec = (int)date.secondes_debut;

  // Déclarer une structure time_t pour stocker le temps actuel
  time_t maintenant;
  // Obtenir le temps actuel
  time(&maintenant);
  // Convertir le temps en une structure tm pour une représentation plus lisible
  struct tm *temps_local = localtime(&maintenant);

  time_t secondes_debut = mktime(&debut);

  long difference_secondes = difftime(secondes_debut, maintenant);
  // printf("%ld\n",difference_secondes);

  return difference_secondes;
}

/*
#############################################################
Programmes principaux
#############################################################
*/

int afficher_statut_salle(int statut) {
  if (statut != 1 && statut != 2 && statut != 3) {
    printf("Erreur valeurs d'entrer de afficher_statut_salle.\n");
    exit(1);
  }

  int nbrsalle = afficher_liste_salles(0);
  int temps_difference_fin = 0, temps_difference_debut = 0;
  int i = 0;
  char nom_salle[100];
  char *nomSalleChoisi = (char *)malloc(100);
  if (nomSalleChoisi == NULL) {
    printf(
        "Erreur : impossible d'allouer de la mémoire pour nomSalleChoixi.\n");
    exit(1);
  }
  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }

  printf("Liste des salles avec leurs statut :\n");
  for (int j = 0; j < nbrsalle;
       j++) { // choixsalle est la ligne de la salle choisie
    fgets(nom_salle, sizeof(nom_salle) - 4,
          fichier); // on parcours le fichier et récupère la ligne avec le nom
    if (strlen(nom_salle) + 4 < sizeof(nom_salle)) {
      nom_salle[strlen(nom_salle) - 1] = '\0';
      sprintf(
          nomSalleChoisi, "%s.txt",
          nom_salle); // on rajout .txt au nom, le nom est dans nomSalleChoisi
    } else {
      printf("Erreur: Le nom de la salle est trop long.\n");
      fclose(fichier);
      exit(1);
    }

    Concert *salle = recup_information_salle(nomSalleChoisi);
    if (salle == NULL) {
      printf("Erreur lors de l'atribution de salle.\n");
      exit(1);
    }

    temps_difference_fin = concert_fini(salle->d);
    temps_difference_debut = concert_debuter(salle->d);
    switch (statut) {
    case 1:
      if (temps_difference_fin < 0 && temps_difference_debut < 0) {
        i++;
        printf("%d. %s [Terminer]\n", i, nom_salle);
        break;
      }
    case 2:
      if (temps_difference_fin > 0 && temps_difference_debut < 0) {
        i++;
        printf("%d. %s [En cours]\n", i, nom_salle);
        break;
      }
    case 3:
      if (temps_difference_fin > 0 && temps_difference_debut > 0) {
        i++;
        printf("%d. %s [Pas Commencer]\n", i, nom_salle);
        break;
      }
    }

    liberer_salle(&salle->s);
    free(salle);
  }
  printf("\n");
  fclose(fichier);
  return i;
}

/*
// Définition de la fonction pour afficher les détails d'une salle sélectionnée
void afficher_details_salle_selectionnee() {

  int choixSalle;
  int nombreSalles = afficher_liste_salles(1);
  printf("Entrez le numéro de la salle que vous voulez afficher : ");
  scanf("%d", &choixSalle);

  if (choixSalle < 1 || choixSalle > nombreSalles) {
    printf("Numéro de salle invalide.\n");
    return;
  }

  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }

  char nom_salle[100];
  for (int j = 0; j < choixSalle; j++) {
    fgets(nom_salle, sizeof(nom_salle), fichier);
  }

  // Supprimer le caractère de nouvelle ligne
  if (nom_salle[strlen(nom_salle) - 1] == '\n') {
    nom_salle[strlen(nom_salle) - 1] = '\0';
  }

  fclose(fichier);

  char nomSalleChoisi[100];
  snprintf(nomSalleChoisi, sizeof(nomSalleChoisi), "%s.txt", nom_salle);

  Concert *salle = recup_information_salle(nomSalleChoisi);
  if (salle == NULL) {
    printf("Erreur : Impossible de récupérer les informations de la salle.\n");
    return;
  }

  // Afficher les détails de la salle sélectionnée avec ses sièges
  afficher_details_Salle(salle);

  // Libérer la mémoire allouée pour la structure salle
  liberer_salle(&salle->s);
  free(salle);
}
*/

Concert *bonne_salle(int statut) {
  if (statut != 1 && statut != 2 && statut != 3) {
    printf("Erreur valeurs d'entrer de afficher_statut_salle.\n");
    exit(1);
  }
  int nbrsalle = afficher_liste_salles(0);
  int temps_difference_fin = 0, temps_difference_debut = 0;
  int i = 1;
  int maximum_list = 0;
  int verif = 0;
  int choix = 0;
  char nom_salle[100];
  char *nomSalleChoisi = (char *)malloc(100);
  if (nomSalleChoisi == NULL) {
    printf(
        "Erreur : impossible d'allouer de la mémoire pour nomSalleChoixi.\n");
    exit(1);
  }

  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }
  do {
    printf("\nQuelle salle voulez-vous prendre :\n");
    maximum_list = afficher_statut_salle(statut);
    verif = scanf("%d", &choix);
    clrscr();
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (choix < 1 || choix > maximum_list) {
        printf("Erreur, numéro de salle incorrect.\n");
      }
    }
  } while (choix < 1 || choix > maximum_list || verif != 1);

  for (int j = 0; j < nbrsalle; j++) {
    fgets(nom_salle, sizeof(nom_salle) - 4, fichier);

    if (strlen(nom_salle) + 4 < sizeof(nom_salle)) {
      nom_salle[strlen(nom_salle) - 1] = '\0';
      sprintf(nomSalleChoisi, "%s.txt", nom_salle);
    } else {
      printf("Erreur: Le nom de la salle est trop long.\n");
      fclose(fichier);
      exit(1);
    }

    Concert *salle = recup_information_salle(nomSalleChoisi);
    if (salle == NULL) {
      printf("Erreur lors de l'atribution de salle.\n");
      exit(1);
    }

    temps_difference_fin = concert_fini(salle->d);
    temps_difference_debut = concert_debuter(salle->d);
    switch (statut) {
    case 1:
      if (temps_difference_fin < 0 && temps_difference_debut < 0) {
        i++;
        break;
      }
    case 2:
      if (temps_difference_fin > 0 && temps_difference_debut < 0) {
        i++;
        break;
      }
    case 3:
      if (temps_difference_fin > 0 && temps_difference_debut > 0) {
        i++;
        break;
      }
    }
    if (i == maximum_list) {
      fclose(fichier);
      printf("%s", salle->s.nom);
      return salle;
    }
    liberer_salle(&salle->s);
    free(salle);
  }
  printf("\n");
  fclose(fichier);
}

void reserver() {
  int choixSalle;
  int verif = 0;
  int cat = 0;
  int nombreSalles = afficher_liste_salles(0);
  /*
  printf("Entrez le numéro de la salle que vous voulez réserver : ");
  scanf("%d", &choixSalle);

  if (choixSalle < 1 || choixSalle > nombreSalles) {
    printf("Numéro de salle invalide.\n");
    return;
  }

  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    return;
  }


  for (int j = 0; j < choixSalle; j++) {
    fgets(nom_salle, sizeof(nom_salle), fichier);
  }

  // Supprimer le caractère de nouvelle ligne
  if (nom_salle[strlen(nom_salle) - 1] == '\n') {
    nom_salle[strlen(nom_salle) - 1] = '\0';
  }

  fclose(fichier);



  Concert *salle = recup_information_salle(nomSalleChoisi);
  if (salle == NULL) {
    printf("Erreur : Impossible de récupérer les informations de la salle.\n");
    return;
  }
  */
  Concert *salle = bonne_salle(2);
  if (salle == NULL) {
    printf("Erreur : Impossible de récupérer les informations de la salle.\n");
    return;
  }
  char nomSalleChoisi[100];
  snprintf(nomSalleChoisi, sizeof(nomSalleChoisi), "%s.txt", salle->s.nom);

  int r = 0, c = 0;
  int rangee = 0;
  afficher_details_Salle(salle);

  do {
    printf("Dans quelle catégorie voulez vous reserver :\n");
    for (int k = 0; k < 3; k++) {
      if ((strcmp(salle->fosse, "oui") == 0) && k == 0) {
        printf("%d. Fosse\n", k + 1);
      } else {
        printf("%d. Catégorie %c :\n", k + 1, 'A' + k);
      }
    }
    verif = scanf("%d", &cat);

    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      switch (cat) {
      case 1:
        rangee = 0;
        break;
      case 2:
        rangee += salle->s.nbr_rangées[0];
        break;
      case 3:
        rangee += salle->s.nbr_rangées[0] + salle->s.nbr_rangées[1];
        ;
        break;
      }
    }
  } while ((cat != 1 && cat != 2 && cat != 3) || verif != 1);

  do {
    printf("Veuillez saisir le numéro de la rangée et de la colonne:\n");
    verif = scanf("%d %d", &r, &c);
    r = r + rangee - 1, c -= 1;
    clrscr();
    vide_buffer();
    if (verif != 2) {
      printf("Erreur.\n");
    } else {
      if (r < 0 || r >= rangee + salle->s.nbr_rangées[cat - 1] || c < 0 ||
          c >= salle->s.nbr_places[cat - 1]) {
        printf("Numéro de rangée ou de colonne invalide.\n");
      }
    }
  } while (r < 0 || r >= rangee + salle->s.nbr_rangées[cat - 1] || c < 0 ||
           c >= salle->s.nbr_places[cat - 1] || verif != 2);

  // Vérification de l'état du siège
  if (salle->s.siège[r][c] == 'x') {
    printf("Le siège est déjà réservé.\n");
  } else {
    salle->s.siège[r][c] = 'x';
    printf("Réservation réussie !\n");
    ecrireFichier(nomSalleChoisi, salle);
  }

  // Libérer la mémoire allouée pour la structure salle
  liberer_salle(&salle->s);
  free(salle);
}