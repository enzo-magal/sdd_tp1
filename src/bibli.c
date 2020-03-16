#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bibli.h" 

/* -------------------------------------------------------------------- */
/* inserLivre     insère un livre dans une liste de livre               */
/*                                                                      */
/* En entrée :   prec_l : pointeur vers le premier livre de la liste    */
/*               num : le numéro du livre à insérer                     */
/*               nom : le nom du livre à insérer                        */
/* -------------------------------------------------------------------- */

void inserLivre(livre_t ** prec_l,int num,char * nom)
{
    while(*prec_l != NULL)
    {
        prec_l = &((*prec_l)->suiv);    
    }      /* prec_l pointe sur le dernier suiv de la liste de livre */
    livre_t * nouv_l = malloc(sizeof(livre_t));
    strcpy(nouv_l->nom,nom);
    nouv_l->num = num;
    nouv_l->emprunt = 0;
    nouv_l->suiv = NULL;
    *prec_l = nouv_l;     
}

/* -------------------------------------------------------------------- */
/* afficherLivre     affiche la liste des livres                        */
/*                                                                      */
/* En entrée :   cour : pointeur vers le premier livre de la liste      */                                    
/* -------------------------------------------------------------------- */

void afficherLivre(livre_t * cour)
{
    while(cour != NULL)
    {
        printf("%d\n", cour->num);
        printf("%s\n", cour->nom);
        printf("%d\n\n", cour->emprunt);
        cour = cour->suiv;
    }
}

/* -------------------------------------------------------------------- */
/* freeLivre     libère l'espace occupé par une liste de livre          */
/*                                                                      */
/* En entrée :   cour : pointeur vers le premier livre de la liste      */
/* -------------------------------------------------------------------- */

void freeLivre(livre_t * cour)
{       
    livre_t * suiv = NULL;
    while(cour != NULL)
    {   
        suiv = cour->suiv;
        free(cour);
        cour = suiv;
    }
}

/* -------------------------------------------------------------------- */
/* inserCategorie     insère une categorie dans une bibliotheque        */
/*                                                                      */
/* En entrée :   deb : première catégorie de la bibliotheque            */
/*               nom : nom de la catégorie à insérer                    */
/*                                                                      */
/* En sortie : nouv_c : pointeur vers la nouvelle catégorie créée       */
/* -------------------------------------------------------------------- */

categorie_t * inserCategorie(categorie_t ** deb,char * nom)
{       
    categorie_t * nouv_c = malloc(sizeof(categorie_t));
    strcpy(nouv_c->nom,nom);
    nouv_c->livre = NULL;
    nouv_c->suiv = *deb;
    *deb = nouv_c;
    return nouv_c;    
}

/* -------------------------------------------------------------------- */
/* afficherCategorie     affiche une liste de catégorie ainsi que leur  */
/*                       liste de livres respectives                    */
/*                                                                      */
/* En entrée :   cour : la première catégorie de la liste               */
/* -------------------------------------------------------------------- */

void afficherCategorie(categorie_t * cour)
{
    while(cour != NULL)
    {
        printf("%s\n\n", cour->nom);
        afficherLivre(cour->livre);
        cour = cour->suiv;
    }
    
}

/* -------------------------------------------------------------------- */
/* freeCategorie     libère l'espace occupé par une liste de catégorie  */
/*                                                                      */
/* En entrée :   cour : la première categorie de la liste               */
/* -------------------------------------------------------------------- */

void freeCategorie(categorie_t* cour)
{       
    categorie_t * suiv;
    while(cour != NULL)
    {   
        suiv = cour->suiv;
        freeLivre(cour->livre);
        free(cour);
        cour = suiv;
    }
}

/* -------------------------------------------------------------------- */
/* supprN    enlève le /n à la fin d'une chaine de caractère            */
/*                                                                      */
/* En entrée :   chaine : la chaine de caractère                        */
/* -------------------------------------------------------------------- */

void supprN(char * chaine)
{
    int i = 0;
    while (chaine[i] != '\0' && chaine[i] != '\n' && chaine[i] != '\r')
    {
        i++;
    }
    if (chaine[i] == '\n' || chaine[i] == '\r')
    {
        chaine[i] = 0;
    }
}

/* -------------------------------------------------------------------- */
/* creationBibli     creait une bibliothèque à partir d'un              */
/*                          fichier texte                               */
/*                                                                      */
/* En entrée :   prec_c : un pointeur vers le premier élément de notre  */
/*               bibliothèque                                           */
/*               fichier : le nom du fichier que l'on veut utiliser     */
/* -------------------------------------------------------------------- */

void creationBibli(categorie_t ** prec_c, char * fichier)
{
    printf("%s\n\n",fichier);
    categorie_t * cour = NULL;
    int nb_livre = 0;
    int i = 0;
    char nom_cat[3]; 
    char nom_livre[50];
    int num_livre = 0;
    
    FILE * mon_fichier = fopen(fichier, "r");
    
    if (mon_fichier != NULL)
    {
        while(!feof(mon_fichier))
        {
            fscanf(mon_fichier,"%s %d\n",nom_cat, &nb_livre);    
            cour = inserCategorie(prec_c,nom_cat);
            for (i = 0 ; i < nb_livre ; i++)
            {
                fscanf(mon_fichier,"%d",&num_livre);
                fgetc(mon_fichier);
                fgets(nom_livre,50,mon_fichier);
                supprN(nom_livre);
                inserLivre(&(cour->livre),num_livre,nom_livre);
            }
        }
        fclose(mon_fichier);
    }
    else
    {
        printf("L'ouverture du fichier a échoué (fichier inexistant)\n\n");
    }
}
