#ifndef GESTION
#define GESTION
#include "bibli.h"
#include "liste_chainée.h"

void afficherEmprunts(emprunt_t * cour, categorie_t * deb_bibli);

emprunt_t * creerListeEmprunt(char * fichier, categorie_t * deb_bibli);

void supprEmprunt(emprunt_t ** deb_liste, char * fichier, categorie_t * deb_bibli);

void retourEmprunt(emprunt_t * cour, categorie_t * deb_bibli, int date);

void nouvFichierEmprunt(emprunt_t * cour);

void afficherRetour(emprunt_t * deb_liste, categorie_t * deb_bibli);

#endif