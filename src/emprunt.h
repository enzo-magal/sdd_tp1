#ifndef GESTION
#define GESTION
#include "bibli.h"
#include "liste_chainée.h"

void afficherEmprunts(emprunt_t * cour, categorie_t * bibli);

emprunt_t * creerListeEmprunt(char * fichier, categorie_t * bibli);

void supprEmprunt(emprunt_t * deb_liste, char * fichier, categorie_t * bibli);

void retourEmprunt(emprunt_t * cour, categorie_t * bibli, int date);

void nouvFichierEmprunt(emprunt_t * cour);

void afficherRetour(emprunt_t * deb_liste, categorie_t * bibli);

#endif