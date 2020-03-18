#ifndef LISTE
#define LISTE
#include "bibli.h"

#define TYPE emprunt_t

typedef struct emprunt emprunt_t;
struct emprunt
{
    int num;
    int date;
    emprunt_t * suiv;
};

int estPresentLivre(int num, categorie_t * deb_bibli);

int estPresentEmp(int num, emprunt_t * debliste);

void freeListeEmprunt(emprunt_t * cour);

emprunt_t ** recherche(emprunt_t * debliste, int date);

emprunt_t * creationEmprunt(int num, int date);

livre_t * trouveLivre(categorie_t * deb_bibli, int num);

void insertion(emprunt_t ** cour, emprunt_t * elt);

void supprElt(emprunt_t ** cour,emprunt_t * elt);

#endif