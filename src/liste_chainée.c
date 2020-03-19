#include <stdio.h>
#include <stdlib.h>
#include "liste_chainée.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"

/* -------------------------------------------------------------------- */
/* estPresentLivre     verifie la presence d'un élément dans une        */
/*                     bibliotheque                                     */
/*                                                                      */
/* En entrée :   num : le numéro du livre à rechercher                  */
/*               deb_bibli : un pointeur sur la bibliotheque            */            
/*                                                                      */
/* En sortie :   p : un booléen permettant de vérifier la présence du   */ 
/*                 livre recherché                                      */
/* -------------------------------------------------------------------- */

int estPresentLivre(int num, categorie_t * deb_bibli)
{
    int p = 0;
    categorie_t * cour_c = deb_bibli;
    livre_t * cour_l = NULL;
    while (cour_c != NULL)
    {
        cour_l = cour_c->livre;
        while (cour_l != NULL)
        {
            if (cour_l->num == num)
            {
                p = 1;
            }
            cour_l = cour_l->suiv;
        }
        cour_c = cour_c->suiv;
    }
    return p;
}

/* -------------------------------------------------------------------- */
/* estPresentEmp     verifie la presence d'un emprunt dans une liste    */
/*                                                                      */
/* En entrée :   num : le numéro du livre emprunté à rechercher         */
/*               deb_liste : un pointeur sur la liste des emprunts      */          
/*                                                                      */
/* En sortie :   p : un booléen permettant de vérifier la présence de   */ 
/*                 l'emprunt recherché                                  */
/* -------------------------------------------------------------------- */

int estPresentEmp(int num, emprunt_t * deb_liste)
{
    int p = 0;
    emprunt_t * cour = deb_liste;
    while (cour != NULL)
    {
        if (cour->num == num)
        {
            p = 1;
        }
        cour = cour->suiv;
    }
    return p;
}

/* -------------------------------------------------------------------- */
/* freeListeEmprunt    libère l'espace occupé par une liste d'emprunts  */
/*                                                                      */
/* En entrée :     cour : un pointeur sur le début de la liste des      */  
/*                 emprunts                                             */
/* -------------------------------------------------------------------- */

void freeListeEmprunt(emprunt_t * cour)
{
    emprunt_t * prec = NULL;
    while (cour != NULL)
    {
        prec = cour;
        cour = cour->suiv;
        free(prec);
    }
}

/* -------------------------------------------------------------------- */
/* recherche        cherche le dernier emprunt avec une date inferieure */
/*                  à une date donnée                                   */
/*                                                                      */
/* En entrée :      deb_liste : un pointeur sur la liste des emprunts   */
/*                  date : la date de l'emprunt recherché               */
/*                                                                      */
/* En sortie :      pt_retour : un pointeur sur le suiv du dernier      */
/*                  élément inférieur à la date donnée                  */
/* -------------------------------------------------------------------- */

emprunt_t ** recherche(emprunt_t * deb_liste, int date)
{   
    emprunt_t ** pt_retour = &deb_liste;
    emprunt_t * cour = deb_liste;
    while((cour->suiv) != NULL && (cour->suiv)->date < date)
    {
        pt_retour = &(cour->suiv);
        cour = cour->suiv;
    }
    return pt_retour;
}

/* -------------------------------------------------------------------- */
/* creationEmprunt     créé un emprunt                                  */
/*                                                                      */
/* En entrée :   num : le numéro du livre emprunté                      */
/*               date : la date de l'emprunt                            */
/*                                                                      */
/* En sortie : nouv : un pointeur vers l'emprunt créé                   */
/* -------------------------------------------------------------------- */

emprunt_t * creationEmprunt(int num, int date)
{
    emprunt_t * nouv = malloc(sizeof(emprunt_t));
    nouv->num = 0;
    nouv->date = 0;
    nouv->suiv = NULL;
    if (nouv != NULL)
    {
        nouv->num = num;
        nouv->date = date;
    }
    return nouv;
}

/* -------------------------------------------------------------------- */
/* trouveLivre     cherche un livre selon un numéro donné               */
/*                                                                      */
/* En entrée :   deb_bibli : un pointeur vers le début de la            */
/*               bibliothèque                                           */
/*               num : le numéro du livre recherché                     */
/*                                                                      */
/* En sortie : livre_trouve : un pointeur vers le livre trouvé          */
/* -------------------------------------------------------------------- */

livre_t * trouveLivre(categorie_t * deb_bibli, int num)
{
    livre_t * livre_trouve = NULL;
    livre_t * cour_l = NULL;
    categorie_t * cour_c = NULL;
    if (estPresentLivre(num,deb_bibli) == 1)
    {
        cour_c = deb_bibli;
        while(cour_c != NULL && livre_trouve == NULL)
        {
            cour_l = cour_c->livre;
            while(cour_l != NULL && livre_trouve == NULL)
            {
                if (cour_l->num == num)
                {
                    livre_trouve = cour_l;
                }
                cour_l = cour_l->suiv;
            }
            cour_c = cour_c->suiv;
        }
    }
    return livre_trouve;
}

/* -------------------------------------------------------------------- */
/* insertion     insere un nouvel élément dans une liste chainée        */
/*               d'emprunt                                              */
/*                                                                      */
/* En entrée :  cour : un pointeur sur le pointeur du début de la liste */
/*              d'emprunts                                              */
/*              elt : un pointeur sur l'emprunt à inserer               */
/* -------------------------------------------------------------------- */

void insertion(emprunt_t ** cour, emprunt_t * elt)
{  
    emprunt_t ** prec = NULL;
    if (*cour == NULL || (*cour)->date > elt->date)
    {
        elt->suiv = *cour;
        *cour = elt;
    }
    else
    {
        prec = recherche(*cour, elt->date);
        elt->suiv = (*prec)->suiv;
        (*prec)->suiv = elt;
    }
}

/* -------------------------------------------------------------------- */
/* supprElt     supprime un élément d'une liste chainée d'emprunt       */
/*                                                                      */
/* En entrée :   cour : un double pointeur sur le début de la liste     */
/*               d'emprunts                                             */
/*               elt : un pointeur sur une copie de l'emprunt à         */
/*               supprimer                                              */
/* -------------------------------------------------------------------- */

void supprElt(emprunt_t ** cour, emprunt_t * elt)
{
    int num = elt->num;
    int date = elt->date;
    emprunt_t ** prec = cour;
    while( (*cour)->num != num || (*cour)->date != date)
    { 
        prec = cour;
        cour = &((*cour)->suiv);
    }
    emprunt_t * sup = *cour;
    if (prec == cour)            /*cas suppression en tête*/
    {
        *prec = (*cour)->suiv;
    }
    else
    {
        (*prec)->suiv = (*cour)->suiv;
    }
    free(sup);
}