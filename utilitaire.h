#ifndef UTILITAIRE_H
#define UTILITAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// Efface l'écran et replace le curseur en haut à gauche
#define clrscr() printf("\033[H\033[2J")

// Sélection de couleurs
#define couleur(param) printf("\033[%sm", param)
/*   param devant être un const char *, vide (identique à "0") ou formé
     d'une où plusieurs valeurs séparées par des ; parmi
         0  réinitialisation         1  haute intensité (des caractères)
         5  clignotement             7  video inversé
         30, 31, 32, 33, 34, 35, 36, 37 couleur des caractères
         40, 41, 42, 43, 44, 45, 46, 47 couleur du fond
            les couleurs, suivant la logique RGB, étant respectivement
               noir, rouge, vert, jaune, bleu, magenta, cyan et blanc */

typedef struct {
  int jour;
  int mois;
  int annee;
  float heure_debut;
  float minutes_debut;
  float secondes_debut;
  float heure_fin;
  float minutes_fin;
  float secondes_fin;
} Date;

// Structure pour représenter une salle
typedef struct {
  char nom[100];

  int nbr_rangées[3]; // Nombre de rangées par catégorie
  int nbr_places[3];  // Nombre de sièges par rangée pour chaque catégorie
  float prix[3];      // Prix des catégories de sièges

  int total;    // Nombre total de sièges dans la salle
  char **siège; // Tableau des sièges dans la salle
} Salle;

// Structure pour représenter un concert
typedef struct {
  Date d;        // Date et heure de début et de fin du concert
  Salle s;       // Informations sur la salle
  char fosse[4]; // Indication de la présence d'une fosse

} Concert;

// festivalier
int afficher_statut_salle(int statut);
void reserver(void);

// manager
void creer_salle(void);
void supprimer_salle(void);
void modifier_salle(void);

// fonction principale
void liberer_salle(Salle *salle);
void vide_buffer(void);
void afficheSalle(Concert *tab, int nbSalle);
char *texte_a_minuscule(char texte[]);
int afficher_liste_salles(void);
Concert *recup_information_salle(char *nomFichier);
void ecrireFichier(const char *nomFichier, Concert *salle);
#endif
