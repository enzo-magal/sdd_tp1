#ifndef LISTE_CHAINEE
#define LISTE_CHAINEE



typedef struct livre livre_t;
struct livre 
{
    int num;
    char nom[10];
    int emprunt;
    livre_t * suiv;
};

typedef struct categorie categorie_t;
struct categorie
{
    char nom[3];
    livre_t * livre;
    categorie_t * suiv;
};

void inserLivre(livre_t ** prec_l,int num,char * nom);

void afficherLivre(livre_t * cour);

void freeLivre(livre_t* cour);

categorie_t * inserCategorie(categorie_t ** deb,char * nom);

void afficherCategorie(categorie_t * cour);

void freeCategorie(categorie_t* cour);

void supprN(char * chaine);

void creationBibli(categorie_t ** prec_c, char * fichier);

#endif