#include <stdio.h>
#include <stdlib.h>
#include "emprunt.h"

#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KWHT  "\x1B[37m"
#define KBLU  "\x1B[34m"

/* -------------------------------------------------------------------- */
/* afficherEmprunts        affiche la liste des emprunts                */
/*                                                                      */
/* En entrée :      cour : pointeur sur le premier emprunt de la liste  */
/*                  bibli : pointeur sur la bibliotheque                */
/* -------------------------------------------------------------------- */

void afficherEmprunts(emprunt_t * cour, categorie_t * bibli)
{
    livre_t * pt_livre = NULL;
    while (cour != NULL)
    {
        pt_livre = trouveLivre(bibli, cour->num);
        printf("%s\n", pt_livre->nom);
        printf("%d\n", cour->num);
        printf("%d\n\n", cour->date);
        cour = cour->suiv;
    }
}

/* -------------------------------------------------------------------- */
/* creerListeEmprunt        créée une liste d'emprunt à partir d'un     */
/*                          fichier texte                               */
/*                                                                      */
/* En entrée :      fichier : le nom du fichier texte                   */
/*                  bibli : pointeur sur la bibliotheque                */
/*                                                                      */
/* En sortie :      deb_liste : pointeur vers la liste d'emprunt créée  */
/* -------------------------------------------------------------------- */

emprunt_t * creerListeEmprunt(char * fichier, categorie_t * bibli)
{
    FILE * monFichier = fopen(fichier,"r");
    emprunt_t * deb_liste = NULL;
    int num = 0;
    int date = 0;
    emprunt_t * nouv = NULL;
    livre_t * plivre = NULL;
    if (monFichier != NULL)
    {
        while(!feof(monFichier))
        {
            fscanf(monFichier,"%d", &num);
            fscanf(monFichier,"%d", &date);
            if (estPresentLivre(num, bibli))
            {
                if (!estPresentEmp(num, deb_liste))
                {
                    nouv = creationEmprunt(num,date);
                    insertion(&deb_liste,nouv);
                    plivre = trouveLivre(bibli,num);
                    plivre->emprunt = 1;
                }
                else
                {
                    printf(KRED);
                    printf("Emprunt en double\n\n");
                    printf(KWHT);
                }
            }
            else
            {
                printf(KRED);
                printf("Le livre n'existe pas\n\n");
                printf(KWHT);
            } 
        }
        fclose(monFichier);
    }
    else
    {
        printf(KRED);
        printf("Fichier inexistant\n\n");
        printf(KWHT);    
    }
    return deb_liste;
}

/* -------------------------------------------------------------------- */
/* supprEmprunt        supprime les emprunts présents dans un fichier   */
/*                     texte                                            */
/*                                                                      */
/* En entrée :      deb_liste : pointeur sur une liste d'emprunt        */
/*                  fichier : le nom du fichier contenant les emprunts  */
/*                  à supprimer                                         */
/*                  bibli : pointeur sur la bibliotheque                */
/* -------------------------------------------------------------------- */

void supprEmprunt(emprunt_t ** deb_liste, char * fichier, categorie_t * bibli)
{
    int num = 0;
    int date = 0;
    FILE * monFichier = fopen(fichier, "r");
    
    if (monFichier != NULL)
    {
        while(!feof(monFichier))
        {
            fscanf(monFichier, "%d", &num);
            fscanf(monFichier, "%d", &date);
            if(estPresentEmp(num,*deb_liste) == 1)
            {
                
                emprunt_t * temp = malloc(sizeof(emprunt_t));
                temp->num = num;
                temp->date = date;
                supprElt(deb_liste, temp);
                free(temp);
                livre_t * plivre = NULL;
                plivre = trouveLivre(bibli,num);
                plivre->emprunt = 0;
            }
            else
            {
                printf(KRED);
                printf("Livre non emprunté\n\n");
                printf(KWHT);
            }
        }
        fclose(monFichier);
    }
    else
    {
        printf(KRED);
        printf("Fichier inexistant\n\n");
        printf(KWHT);
    }

    if (*deb_liste == NULL)
    {
        printf(KGRN);
        printf("Tout les emprunts ont été rendus \n\n");
        printf(KWHT);
    }
}

/* -------------------------------------------------------------------- */
/* retourEmprunt      affiche la liste des emprunts devant être rendus  */
/*                    avant une date donnée                             */
/*                                                                      */
/* En entrée :      cour : pointeur sur la liste des emprunts           */
/*                  bibli : pointeur sur la bibliotheque                */
/*                  date : la date pour laquelle on veut connaitre les  */
/*                  livres à rendre                                     */
/* -------------------------------------------------------------------- */

void retourEmprunt(emprunt_t * cour, categorie_t * bibli, int date)
{
    int rendre_livre = 0;
    while (cour != NULL)
    {
        if (cour->date <= date)
        {
            livre_t * plivre = trouveLivre(bibli, cour->num);
            printf("%s\n", plivre->nom);
            printf("Doit être rendu\n\n");
            rendre_livre = 1;
        }
        cour = cour->suiv;
    }
    if (rendre_livre == 0)
    {
        printf(KGRN);
        printf("Aucun livre à rendre\n\n");
        printf(KWHT);
    }
}

/* -------------------------------------------------------------------- */
/* nouvFichierEmrpunt        créée un fichier à partir de la liste des  */
/*                           emprunts                                   */
/*                                                                      */
/* En entrée :      cour : pointeur sur la liste des emprunts           */
/* -------------------------------------------------------------------- */

void nouvFichierEmprunt(emprunt_t * cour)
{
    FILE * monFichier = fopen("data/fichier_emprunt.txt", "w+");
    if (monFichier != NULL)
    {
        while (cour != NULL)
        {
            fprintf(monFichier, "%d %d\n", cour->num, cour->date);
            cour = cour->suiv;
        }
        fclose(monFichier);
    }
    else
    {
        printf("Problème d'ouverture de fichier");
    }
    
}

/* -------------------------------------------------------------------- */
/* afficherRetour        affiche tout les livres devant être rendu à    */
/*                       une date donnée par l'utilisateur              */
/*                                                                      */
/* En entrée :      deb_liste : pointeur sur le début de la liste       */
/*                  d'emprunts                                          */
/*                  bibli : pointeur sur la bibliotheque                */
/* -------------------------------------------------------------------- */

void afficherRetour(emprunt_t * deb_liste, categorie_t * bibli)
{
    int date_max = 0;
    printf(KBLU);
    printf("Date de retour max (AAAAMMJJ): ");
    printf(KWHT);
    scanf("%d", &date_max);
    printf("\n\n");
    retourEmprunt(deb_liste, bibli, date_max);
}