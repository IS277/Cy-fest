#include "utilitaire.h"

// Fonction pour afficher les détails de toutes les salles
void afficheSalle(Concert *tab, int nbSalle) {
  for (int i = 0; i < nbSalle; i++) {
    // Ecrire les information principale
    printf("Salle %d :\n", i + 1);
    printf("Nom de la salle : %s\n", tab[i].s.nom);
    printf("Fosse : %s\n", tab[i].fosse);
    printf("Nombre de place total : %d\n", tab[i].s.total);

    // Ecrire les informations de la date
    printf("\nLa date du concert est : %d/%d/%d\n", tab[i].d.jour,
           tab[i].d.mois, tab[i].d.annee);
    printf("Début : %.2fh/%.2fm/%.2fs\n", tab[i].d.heure_debut,
           tab[i].d.minutes_debut, tab[i].d.secondes_debut);
    printf("Fin : %.2fh/%.2fm/%.2fs\n", tab[i].d.heure_fin,
           tab[i].d.minutes_fin, tab[i].d.secondes_fin);

    for (int j = 0; j < 3; j++) {
      if ((strcmp(tab[i].fosse, "oui") == 0) && j == 0) {
        printf("\nFosse :\n");
      } else {
        printf("\nCatégorie %c :\n", 'A' + j);
      }

      // Écrire les informations des siège (rangé,place par rangé et prix)
      printf("%d\n", tab[i].s.nbr_rangées[j]);
      printf("%d\n", tab[i].s.nbr_places[j]);
      printf("%.2f\n", tab[i].s.prix[j]);
    }
  }
}

// Fonction pour crée les place d'une catégorie
int allouer_et_initialiser_sièges(Salle *salle, int indice, char place_symbole,
                                  int depart) {
  if (salle == NULL || indice < 0 || indice > 2 || place_symbole == ' ') {
    printf("Erreur des valeurs d'entrée dans allouer_et_initialiser_sièges.\n");
    return 1;
  }

  int fin = depart + salle->nbr_rangées[indice];

  for (int j = depart; j < fin; j++) {
    salle->siège[j] = (char *)malloc(salle->nbr_places[indice] * sizeof(char));
    if (salle->siège[j] == NULL) {
      printf("Erreur lors de l'allocation de mémoire.\n");
      for (int i = 0; i < j; i++) {
        free(salle->siège[i]);
      }
      return 1;
    }
    for (int k = 0; k < salle->nbr_places[indice]; k++) {
      salle->siège[j][k] = place_symbole;
    }
  }
  return 0;
}

// Remplie la date d'une salle
int attribuer_date(Date *d) {
  if (d == NULL) {
    printf("Erreur des valeurs d'entrée dans attribuer_date.\n");
    return 1;
  }
  int verif = 0;

  printf("Entrer la date du concert (jour/mois/année):\n");

  do {
    printf("Jour : ");
    verif = scanf("%d", &d->jour);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (d->jour < 1 || d->jour > 31) {
        printf("Jour incorrect, veuillez réessayer.\n");
      }
    }
  } while (d->jour < 1 || d->jour > 31 || verif != 1);

  do {
    printf("Mois : ");
    verif = scanf("%d", &d->mois);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (d->mois < 1 || d->mois > 12) {
        printf("Mois incorrect, veuillez réessayer.\n");
      }
    }
  } while (d->mois < 1 || d->mois > 12 || verif != 1);

  do {
    printf("Année : ");
    verif = scanf("%d", &d->annee);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (d->annee < 1900) {
        printf("Année incorrect, veuillez réessayer.\n");
      }
    }
  } while (d->annee < 1900 || verif != 1);

  do {
    printf("Entrer un horaire de début (HH MM SS) :\n");
    verif = scanf("%f %f %f", &d->heure_debut, &d->minutes_debut,
                  &d->secondes_debut);
    vide_buffer();
    if (verif != 3) {
      printf("Erreur.\n");
    } else {
      if (d->heure_debut < 0 || d->heure_debut > 23 || d->minutes_debut < 0 ||
          d->minutes_debut > 59 || d->secondes_debut < 0 ||
          d->secondes_debut > 59) {
        printf("Horaire incorrect, veuillez réessayer.\n");
      }
    }
  } while (d->heure_debut < 0 || d->heure_debut > 23 || d->minutes_debut < 0 ||
           d->minutes_debut > 59 || d->secondes_debut < 0 ||
           d->secondes_debut > 59 || verif != 3);

  do {
    printf("Entrer un horaire de fin (HH MM SS) :\n");
    verif = scanf("%f %f %f", &d->heure_fin, &d->minutes_fin, &d->secondes_fin);
    vide_buffer();
    if (verif != 3) {
      printf("Erreur.\n");
    } else {
      if (d->heure_fin < 0 || d->heure_fin > 23 || d->minutes_fin < 0 ||
          d->minutes_fin > 59 || d->secondes_fin < 0 || d->secondes_fin > 59) {
        printf("Horaire incorrect, veuillez réessayer.\n");
      }
    }
  } while (d->heure_fin < 0 || d->heure_fin > 23 || d->minutes_fin < 0 ||
           d->minutes_fin > 59 || d->secondes_fin < 0 || d->secondes_fin > 59 ||
           verif != 3);
  return 0;
}

// Remplire les catégorie d'une salle (nombre rangé, place par rangée, prix)
int attribuer_rangées_place_prix(Salle *salle, int j) {
  if (salle == NULL) {
    printf("Erreur des valeurs d'entrée dans attribuer_rangées_place_prix.\n");
    return 1;
  }
  if (j < 0 || j >= 3) {
    printf("Erreur des valeurs d'entrée dans attribuer_rangées_place_prix.\n");
    return 1;
  }
  int verif = 0;

  // Demander les rangées
  do {
    printf("Nombre de rangées : ");
    verif = scanf("%d", &salle->nbr_rangées[j]);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (salle->nbr_rangées[j] < 1) {
        printf("Le nombre de rangées ne peut pas être inferrieur à 1. Veuillez "
               "réessayer.\n");
      }
    }
  } while (salle->nbr_rangées[j] < 1 || verif != 1);

  // Demander le nombre de places
  do {
    printf("Nombre de places : ");
    verif = scanf("%d", &salle->nbr_places[j]);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (salle->nbr_places[j] < 1) {
        printf("Le nombre de places ne peut pas être inferrieur à 1. Veuillez "
               "réessayer.\n");
      }
    }
  } while (salle->nbr_places[j] < 1 || verif != 1);

  // Demander le prix
  do {
    printf("Entrer le prix: ");
    verif = scanf("%f", &salle->prix[j]);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (salle->prix[0] < 0) {
        printf("Le prix ne peut pas être négatif. Veuillez réessayer.\n");
      }
    }
  } while (salle->prix[0] < 0 || verif != 1);
  return 0;
}

// Fonction pour construire une salle
Concert *construire_Salle(int nbSalles) {
  // Verification des valeurs en paramètres
  if (nbSalles < 1) {
    printf("Erreur : Le nombre de salles doit être supérieur à 0 dans "
           "construire_Salle.\n");
    exit(1);
  }
  int verif = 0;
  char place_symbole = ' ';
  // Allocation dynamique du tableau de salles
  Concert *tabSalles = (Concert *)malloc(nbSalles * sizeof(Concert));
  if (tabSalles == NULL) {
    printf("Erreur lors de l'allocation de mémoire.\n");
    exit(1);
  }

  // Boucle pour chaque salle à créer
  for (int i = 0; i < nbSalles; i++) {
    tabSalles[i].s.total = 0;

    printf("\nSalle %d :\n", i + 1);

    // Demander et enregistrer le nom de la salle
    do {
      printf("Nom : ");
      verif = scanf("%s", tabSalles[i].s.nom);
      vide_buffer();
      if (verif != 1) {
        printf("Erreur.\n");
      } else {
        if (strlen(tabSalles[i].s.nom) + 4 > sizeof(tabSalles[i].s.nom)) {
          printf("Erreur , nom de salle trop grand.\n");
        }
      }
    } while (strlen(tabSalles[i].s.nom) + 4 > sizeof(tabSalles[i].s.nom) ||
             verif != 1);

    // Demander et enregistrer date
    verif = attribuer_date(&tabSalles[i].d);
    if (verif == 1) {
      free(tabSalles);
      exit(1);
    }

    // Demander si la salle a une fosse
    do {
      printf("Y a-t-il une fosse ? (oui/non) : ");
      verif = scanf("%s", tabSalles[i].fosse);
      vide_buffer();
      if (verif != 1) {
        printf("Erreur.\n");
      } else {
        if (strcmp(tabSalles[i].fosse, "oui") != 0 &&
            strcmp(tabSalles[i].fosse, "non") != 0) {
          printf("Erreur, veuillez entrer 'oui' ou 'non'.\n");
        }
      }
    } while ((strcmp(tabSalles[i].fosse, "oui") != 0 &&
              strcmp(tabSalles[i].fosse, "non") != 0) ||
             verif != 1);

    // Rangées , places et prix
    for (int j = 0; j < 3; j++) {
      if ((strcmp(tabSalles[i].fosse, "oui") == 0) && j == 0) {
        place_symbole = '!';
        printf("Fosse :\n");
      } else {
        place_symbole = 'o';
        printf("Catégorie %c :\n", 'A' + j);
      }

      // Demander et enregistrer le nombre de rangées, place et prix
      verif = attribuer_rangées_place_prix(&tabSalles[i].s, j);
      if (verif == 1) {
        printf("Erreur.\n");
        free(tabSalles);
        exit(1);
      }

      // Calculer le nombre total de sièges dans la salle
      tabSalles[i].s.total +=
          tabSalles[i].s.nbr_rangées[j] * tabSalles[i].s.nbr_places[j];
    }

    // Allocation de la mémoire pour les sièges
    int total_rangées = tabSalles[i].s.nbr_rangées[0] +
                        tabSalles[i].s.nbr_rangées[1] +
                        tabSalles[i].s.nbr_rangées[2];
    tabSalles[i].s.siège = (char **)malloc(total_rangées * sizeof(char *));
    if (tabSalles[i].s.siège == NULL) {
      printf("Erreur lors de l'allocation de mémoire.\n");
      free(tabSalles);
      exit(1);
    }

    // Initialiser les sièges (tableau)
    int separation = 0;

    for (int h = 0; h < 3; h++) {
      if (h == 1) {
        place_symbole = 'o';
      }
      verif = allouer_et_initialiser_sièges(&tabSalles[i].s, h, place_symbole,
                                            separation);
      if (verif == 1) {
        for (int n = 0; n < i - 1; n++) {
          liberer_salle(&tabSalles[n].s);
        }
        free(tabSalles);
        exit(1);
      }
      separation += tabSalles[i].s.nbr_rangées[h];
    }
  }
  return tabSalles;
}

// Fonction pour écrire les informations de la salle dans un fichier
void ecrireFichier(const char *nomFichier, Concert *salle) {
  if (nomFichier == NULL || salle == NULL) {
    printf("Erreur : les paramètres ne sont pas valides dans ecrireFichier.\n");
    exit(1);
  }
  FILE *fichier = fopen(nomFichier, "w+");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier %s.\n", nomFichier);
    liberer_salle(&salle->s);
    free(salle);
    exit(1);
  }
  int rangee_decalage = 0;
  // Ecrire les informations principale
  fprintf(fichier, "%s\n", salle->s.nom);
  fprintf(fichier, "%s\n", salle->fosse);
  fprintf(fichier, "%d\n", salle->s.total);

  // Ecrire les informations de la date
  fprintf(fichier, "%d\n", salle->d.jour);
  fprintf(fichier, "%d\n", salle->d.mois);
  fprintf(fichier, "%d\n", salle->d.annee);
  fprintf(fichier, "%f\n", salle->d.heure_debut);
  fprintf(fichier, "%f\n", salle->d.minutes_debut);
  fprintf(fichier, "%f\n", salle->d.secondes_debut);
  fprintf(fichier, "%f\n", salle->d.heure_fin);
  fprintf(fichier, "%f\n", salle->d.minutes_fin);
  fprintf(fichier, "%f\n", salle->d.secondes_fin);

  for (int j = 0; j < 3; j++) {
    // Écrire les informations des siège (rangé,place par rangé et prix)
    fprintf(fichier, "%d\n", salle->s.nbr_rangées[j]);
    fprintf(fichier, "%d\n", salle->s.nbr_places[j]);
    fprintf(fichier, "%.2f\n", salle->s.prix[j]);
  }
  for (int j = 0; j < 3; j++) {
    // Enregistrer tableau des siège des places
    for (int l = rangee_decalage; l < rangee_decalage + salle->s.nbr_rangées[j];
         l++) {
      for (int m = 0; m < salle->s.nbr_places[j]; m++) {
        fputc(salle->s.siège[l][m], fichier);
      }
      fputc('\n', fichier);
    }
    rangee_decalage += salle->s.nbr_rangées[j];
  }

  fclose(fichier);
}

// récupère les information d'un fichier
Concert *recup_information_salle(char *nomFichier) {
  if (nomFichier == NULL) {
    printf("Erreur: les paramètres ne sont pas valides dans "
           "recup_information_salle.\n");
    exit(1);
  }
  FILE *fichier = fopen(nomFichier, "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  // Allocation du concert
  Concert *salle = (Concert *)malloc(sizeof(Concert));
  if (salle == NULL) {
    printf("Erreur lors de l'alloccation mémoire de salle.\n");
    exit(1);
  }
  char place_symbole = ' ';
  int verif = 0;

  char ligne[100];
  int caractère = ' ';
  int i = -1, p = 0;

  // Lire la première ligne et la copier dans salle->s.nom
  if (fgets(ligne, 99, fichier) != NULL) {
    // Enlever le caractère de nouvelle ligne '\n' si présent
    ligne[strcspn(ligne, "\n")] = '\0';
    strncpy(salle->s.nom, ligne, sizeof(salle->s.nom) - 1);
    salle->s.nom[sizeof(salle->s.nom) - 1] =
        '\0'; // S'assurer de la terminaison nulle
  } else {
    printf("Erreur de lecture de la première ligne ou fichier vide\n");
    fclose(fichier);
    exit(1);
  }

  // Lire la deuxième ligne et la copier dans salle->fosse
  if (fgets(ligne, 4, fichier) != NULL) {
    // Enlever le caractère de nouvelle ligne '\n' si présent
    ligne[strcspn(ligne, "\n")] = '\0';
    strncpy(salle->fosse, ligne, sizeof(salle->fosse) - 1);
    salle->fosse[sizeof(salle->fosse) - 1] =
        '\0'; // S'assurer de la terminaison nulle
  } else {
    printf("Erreur de lecture de la première ligne ou fichier vide\n");
    fclose(fichier);
    exit(1);
  }

  fscanf(fichier, "%d", &salle->s.total);

  // Récupéré les information de la date
  fscanf(fichier, "%d", &salle->d.jour);
  fscanf(fichier, "%d", &salle->d.mois);
  fscanf(fichier, "%d", &salle->d.annee);
  fscanf(fichier, "%f", &salle->d.heure_debut);
  fscanf(fichier, "%f", &salle->d.minutes_debut);
  fscanf(fichier, "%f", &salle->d.secondes_debut);
  fscanf(fichier, "%f", &salle->d.heure_fin);
  fscanf(fichier, "%f", &salle->d.minutes_fin);
  fscanf(fichier, "%f", &salle->d.secondes_fin);

  // Récupéré les information des rangée, place , prix
  for (int j = 0; j < 3; j++) {
    fscanf(fichier, "%d", &salle->s.nbr_rangées[j]);
    fscanf(fichier, "%d", &salle->s.nbr_places[j]);
    fscanf(fichier, "%f", &salle->s.prix[j]);
  }

  if (strcmp(salle->fosse, "oui") == 0) {
    place_symbole = '!';
  } else {
    place_symbole = 'o';
  }

  // Allocation de la mémoire pour les sièges
  int total_rangées = salle->s.nbr_rangées[0] + salle->s.nbr_rangées[1] +
                      salle->s.nbr_rangées[2];

  salle->s.siège = (char **)malloc(total_rangées * sizeof(char *));
  if (salle->s.siège == NULL) {
    printf("Erreur lors de l'allocation de mémoire.\n");
    free(salle);
    exit(1);
  }
  /*Degugage
  printf("%d",salle->s.nbr_rangées[0]);
  printf("%d",salle->s.nbr_places[0]);
  printf("%f\n",salle->s.prix[0]);

  printf("%d",salle->s.nbr_rangées[1]);
  printf("%d",salle->s.nbr_places[1]);
  printf("%f\n",salle->s.prix[1]);

  printf("%d",salle->s.nbr_rangées[2]);
  printf("%d",salle->s.nbr_places[2]);
  printf("%f\n",salle->s.prix[2]);
  */

  // Initialiser les sièges (tableau)
  int separation = 0;

  for (int h = 0; h < 3; h++) {
    if (h == 1) {
      place_symbole = 'o';
    }
    verif =
        allouer_et_initialiser_sièges(&salle->s, h, place_symbole, separation);
    if (verif == 1) {
      for (int n = 0; n < i - 1; n++) {
        liberer_salle(&salle->s);
      }
      free(salle);
      exit(1);
    }
    separation += salle->s.nbr_rangées[h];
  }

  // récupérer les place sous symbole
  fseek(fichier,
        -(1 + salle->s.total + salle->s.nbr_rangées[0] +
          salle->s.nbr_rangées[1] + salle->s.nbr_rangées[2]),
        2);
  caractère = fgetc(fichier);
  while (caractère != EOF) {
    if (caractère != '\n') {
      salle->s.siège[i][p] = caractère;
      // printf("%c",salle->s.siège[i][p]);
      p++;
    } else {
      i++;
      // printf("\n");
      p = 0;
    }
    caractère = fgetc(fichier);
  }

  fclose(fichier);
  return salle;
}

// Fonction pour afficher la liste des salles et retourner le nombre de salle
int afficher_liste_salles(int affichage) {
  if (affichage != 1 && affichage != 0) {
    printf("Erreur : valeurs d'entrée dans afficher_liste_salles.\n");
    exit(1);
  }
  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }

  static char nomSalle[100];
  int i = 00;
  if (affichage == 1) {
    while (fgets(nomSalle, sizeof(nomSalle), fichier) != NULL) {
      i++;
      printf("%d. %s", i, nomSalle);
    }
  } else if (affichage == 0) {
    while (fgets(nomSalle, sizeof(nomSalle), fichier) != NULL) {
      i++;
    }
  }

  fclose(fichier);
  return i;
}

// Modifier chaque option d'une salle
void modifier_info_salle(Concert *salle) {
  if (salle == NULL) {
    printf("Erreur lors de la lecture des informations de la salle.\n");
    exit(1);
  }
  int verif = 0;
  int i = 0;
  int place_symbole = ' ';
  int choix = 0;

  do {
    clrscr(); // on efface l'écran et affiche le menu
    i = 0;
    afficheSalle(salle, 1);
    printf("\nQue souhaitez-vous modifier?\n");

    printf("1. Indication de la présence d'une fosse\n");
    printf("2. La date\n");
    if (strcmp(salle->fosse, "non") == 0) {
      printf("3. Catégorie A\n");
    } else {
      printf("3. Fosse\n");
    }
    printf("4. Catégorie B\n");
    printf("5. Catégorie C\n");
    printf("6. Quitter\n");
    printf("Choix: ");
    verif = scanf("%d", &choix);

    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      switch (choix) {
      // La fosse
      case 1:
        do {
          printf("La fosse est-elle présente (oui/non): ");
          verif = scanf("%s", salle->fosse);
          vide_buffer();
          if (verif != 1) {
            printf("Erreur.\n");
          } else {
            if (strcmp(salle->fosse, "oui") != 0 &&
                strcmp(salle->fosse, "non") != 0) {
              printf("Erreur, veuillez entrer 'oui' ou 'non'.\n");
            }
          }
        } while ((strcmp(salle->fosse, "oui") != 0 &&
                  strcmp(salle->fosse, "non") != 0) ||
                 verif != 1);
        i = 0;
      // La date
      case 2:
        if (choix == 2) {
          attribuer_date(&salle->d);
          break;
        }
      // les catégorie (rangée, place, prix)
      case 3:
        if (choix == 3) {
          i = 0;
        }
      case 4:
        if (choix == 4) {
          i = 1;
        }
      case 5:
        if (choix == 5) {
          i = 2;
        }
        attribuer_rangées_place_prix(&salle->s, i);
        break;

      case 6:
        printf("Quitter.\n");
        break;

      default:
        printf("Choix invalide. Veuillez réessayer.\n");
        break;
      }
    }
  } while (choix != 6);

  salle->s.total = salle->s.nbr_rangées[0] * salle->s.nbr_places[0] +
                   salle->s.nbr_rangées[1] * salle->s.nbr_places[1] +
                   salle->s.nbr_rangées[2] * salle->s.nbr_places[2];

  // Allocation de la mémoire pour les sièges
  int total_rangées = salle->s.nbr_rangées[0] + salle->s.nbr_rangées[1] +
                      salle->s.nbr_rangées[2];
  salle->s.siège = (char **)malloc(total_rangées * sizeof(char *));
  if (salle->s.siège == NULL) {
    printf("Erreur lors de l'allocation de mémoire.\n");
    free(salle);
    exit(1);
  }
  if (strcmp(salle->fosse, "oui") == 0) {
    place_symbole = '!';
  } else {
    place_symbole = 'o';
  }
  // Initialiser les sièges (tableau)
  int separation = 0;

  for (int h = 0; h < 3; h++) {
    if (h == 1) {
      place_symbole = 'o';
    }
    verif =
        allouer_et_initialiser_sièges(&salle->s, h, place_symbole, separation);
    if (verif == 1) {
      for (int n = 0; n < i - 1; n++) {
        liberer_salle(&salle->s);
      }
      free(salle);
      exit(1);
    }
    separation += salle->s.nbr_rangées[h];
  }
}

// supprimer une ligne d'un fichier
void supprimer_ligne_fichier(int ligne_supprimer) {
  if (ligne_supprimer < 1) {
    printf("Erreur da la valeurs d'entrer dans supprimer_ligne_fichier.\n");
    exit(1);
  }
  FILE *fichier, *fichiertemp2;
  char nomfichier[16] = "LISTE_SALLE.txt";
  char ch = ' ';
  int temp = 1;

  // ouvrire le fichier en mode lecture
  fichier = fopen(nomfichier, "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier.\n");
    exit(1);
  }

  // ouvrire un nouveau fichier pour copier les nom
  fichiertemp2 = fopen("copy.txt", "w");
  ch = getc(fichier);
  ;
  while (ch != EOF) {
    // saute la ligne à supprimer
    if (temp != ligne_supprimer) {
      // copie des ligne
      putc(ch, fichiertemp2);
    }
    if (ch == '\n') {
      temp++;
    }
    ch = getc(fichier);
  }
  fclose(fichier);
  fclose(fichiertemp2);
  remove(nomfichier);

  // renomer le fichier
  rename("copy.txt", nomfichier);

  printf("\n The contents of file after being modified are as follows:\n");
  fichier = fopen(nomfichier, "r");
  ch = getc(fichier);
  while (ch != EOF) {
    printf("%c", ch);
    ch = getc(fichier);
  }
  fclose(fichier);
}

int salle_existe_deja(char *ligne_a_trouver) {
  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier");
    exit(1);
  }

  char ligne[100];
  int trouver = 0;

  while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
    // enlever le retour a la ligne
    ligne[strcspn(ligne, "\n")] = '\0';

    if (strcmp(ligne, ligne_a_trouver) == 0) {
      trouver = 1;
      break;
    }
  }

  fclose(fichier);
  return trouver;
}

/*
#############################################################
Programmes principaux
#############################################################
*/

// Fonction pour modifier une salle existante
void modifier_salle() {
  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }
  char nom_salle[100];
  char *nomSalleChoisi = (char *)malloc(100);
  if (nomSalleChoisi == NULL) {
    fclose(fichier);
    exit(1);
  }
  int choixsalle = 0;
  int verif = 0;
  int nbr_salle = 0;
  // afficher menue et demander la salle à modifier (numéro)
  do {
    printf("\nQuelle salle voulez-vous modifier (saisissez le numéro) :\n");
    nbr_salle = afficher_liste_salles(1);
    verif = scanf("%d", &choixsalle);
    clrscr();
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (choixsalle < 1 || choixsalle > nbr_salle) {
        printf("Erreur, numéro de salle incorrect.\n");
      }
    }

  } while (choixsalle < 1 || choixsalle > nbr_salle || verif != 1);
  // trouver le nom de la salle et le modifier avec .txt
  for (int j = 0; j < choixsalle; j++) {
    fgets(nom_salle, sizeof(nom_salle) - 4, fichier);
  }
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
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }
  // on modifie les info de la salle et on l'écris dans le fichier
  modifier_info_salle(salle);
  snprintf(nom_salle, sizeof(nom_salle), "%s.txt", salle->s.nom);
  ecrireFichier(nom_salle, salle);
  clrscr();
  // Libérer la mémoire allouée
  free(nomSalleChoisi);
  liberer_salle(&salle->s);
  free(salle);
}

// Fonction pour créer des salles et les enregistrer dans un fichier
void creer_salle() {
  FILE *fichier = fopen("LISTE_SALLE.txt", "a");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }
  int nbSalles = 0;
  int verif = 0;
  int trouver = 0;
  do {
    printf("Entrer le nombre de salles : ");
    verif = scanf("%d", &nbSalles);
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    }
  } while (nbSalles < 1 || verif != 1);

  Concert *tabSalles = construire_Salle(nbSalles);
  if (tabSalles == NULL) {
    printf("Erreur lors de l'allocation mémoire de tabSalles.\n");
    exit(1);
  }

  printf("\nSalles créées :\n");

  for (int i = 0; i < nbSalles; i++) {
    char nomFichier[100];
    snprintf(nomFichier, sizeof(nomFichier), "%s.txt", tabSalles[i].s.nom);
    ecrireFichier(nomFichier, &tabSalles[i]);
    if (salle_existe_deja(tabSalles[i].s.nom) == 0) {
      // Écrire le nom de la salle sans nouvelle ligne additionnelle au début
      fprintf(fichier, "%s\n", tabSalles[i].s.nom);
    }
  }

  for (int i = 0; i < nbSalles; i++) {
    liberer_salle(&tabSalles[i].s);
  }
  free(tabSalles);
  fclose(fichier);
  clrscr();
}

void supprimer_salle() {
  FILE *fichier = fopen("LISTE_SALLE.txt", "r");
  if (fichier == NULL) {
    printf("Erreur lors de l'ouverture du fichier LISTE_SALLE.txt.\n");
    exit(1);
  }
  char nom_salle[100];
  char *nomSalleChoisi = (char *)malloc(100);
  int ligne_supprimer = 0;
  int verif = 0;
  int nbrsalle = 0;
  do {
    printf("\nQuelle salle voulez-vous supprimer (saisissez le numéro) :\n");
    nbrsalle = afficher_liste_salles(1);
    verif = scanf("%d", &ligne_supprimer);
    clrscr();
    vide_buffer();
    if (verif != 1) {
      printf("Erreur.\n");
    } else {
      if (ligne_supprimer < 1 || ligne_supprimer > nbrsalle) {
        printf("Erreur, numéro de salle incorrect.\n");
      }
    }
  } while (ligne_supprimer < 1 || ligne_supprimer > nbrsalle || verif != 1);

  supprimer_ligne_fichier(ligne_supprimer);
  // trouver le nom de la salle et le modifier avec .txt
  for (int j = 0; j < ligne_supprimer; j++) {
    fgets(nom_salle, sizeof(nom_salle) - 4, fichier);
  }
  if (strlen(nom_salle) + 4 < sizeof(nom_salle)) {
    nom_salle[strlen(nom_salle) - 1] = '\0';
    sprintf(nomSalleChoisi, "%s.txt", nom_salle);
  } else {
    printf("Erreur: Le nom de la salle est trop long.\n");
    fclose(fichier);
    exit(1);
  }
  remove(nomSalleChoisi);
  free(nomSalleChoisi);
  free(fichier);
}
