#include <stdio.h>
#include <stdlib.h>
#include "bibli.h"
#include "emprunt.h"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"



int main(int argc, char ** argv)
{
    categorie_t * bibli = NULL;
    emprunt_t * emprunt = NULL;
    int sortie = 0;
    int choix = 0;
    if (argc == 4)
    {
        while (sortie == 0)
        {
            printf("Veuillez choisir l'action à effectuer\n\n");
            printf("1 : creer une bibliotheque\n");
            printf("2 : afficher bibliotheque\n");
            printf("3 : creer une liste d'emprunt\n");
            printf("4 : supprimer des emprunts\n");
            printf("5 : afficher la liste des emprunts\n");
            printf("6 : afficher les livre qui doivent etre rendus\n");
            printf("7 : creer un fichier avec les livres qui sont empruntés\n");
            printf("8 : sortir du programme\n\n");
            printf(KBLU);
            printf("Votre choix : ");
            printf(KWHT);
            scanf("%d", &choix);
            printf("\n");
            switch(choix)
            {
                case 1 : creationBibli(&bibli,argv[1]);
                        if (bibli == NULL)
                        {
                                printf(KRED);
                                printf("La bibliotheque n'existe pas\n\n");
                                printf(KWHT);
                        }
                        else
                        {
                                printf(KGRN);
                                printf("Creation de la bibliotheque effectuée\n\n");
                                printf(KWHT);
                        }
                        break;
                case 2 : afficherCategorie(bibli); break;
                case 3 : emprunt = creerListeEmprunt(argv[2],bibli);
                        if (emprunt != NULL)
                        {
                                printf(KGRN);
                                printf("Creation emprunt effectuée\n\n");
                                printf(KWHT);
                        }
                        break;
                case 4 : supprEmprunt(&emprunt, argv[3], bibli);
                        printf(KGRN); 
                        printf("Emprunts supprimés avec succès\n\n");
                        printf(KWHT);
                        break;
                case 5 : afficherEmprunts(emprunt, bibli); break;
                case 6 : afficherRetour(emprunt, bibli); break;
                case 7 : nouvFichierEmprunt(emprunt);
                        printf(KGRN);
                        printf("Fichier d'emprunts créé succès\n\n");
                        printf(KWHT);
                        break;
                case 8 : sortie = 1;
                        printf(KYEL);
                        printf("Travail terminé !!!\n\n");
                        printf(KWHT);
                        break;
                default : printf(KRED);
                        printf("Erreur dans le programme\n\n");
                        printf(KWHT);
                        sortie = 1;
            }
        }
    }
    else
    {
        printf("\n");
        printf(KRED);
        printf("Mauvais renseignement des noms de fichiers\n\n");
        printf(KWHT);    
    }
    
    freeCategorie(bibli);
    freeListeEmprunt(emprunt); 

    return 0;
}
