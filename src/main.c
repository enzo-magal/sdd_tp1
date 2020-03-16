#include <stdio.h>
#include <stdlib.h>
#include "bibli.h"
#include "emprunt.h"



int main(int argc, char ** argv)
{
    categorie_t * bibli = NULL;
    emprunt_t * emprunt = NULL;
    int sortie = 0;
    int choix = 0;
    if (argc > 1)
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
            printf("Votre choix : ");
            scanf("%d", &choix);
            switch(choix)
            {
                case 1 : creationBibli(&bibli,argv[1]);
                        printf("Creation de la bibliotheque effectuée\n\n");
                        if (bibli == NULL)
                        {
                                printf("La bibliotheque est vide !\n");
                        }
                        break;
                case 2 : afficherCategorie(bibli); break;
                case 3 : emprunt = creerListeEmprunt("emprunt_c.txt",bibli);
                        printf("Creation emprunt effectuée\n\n");
                        break;
                case 4 : supprEmprunt(emprunt, "retour.txt", bibli); 
                        printf("Emprunts supprimés avec succès\n\n");
                        break;
                case 5 : afficherEmprunts(emprunt, bibli); break;
                case 6 : afficherRetour(emprunt, bibli); break;
                case 7 : nouvFichierEmprunt(emprunt);
                        printf("Fichier d'emprunts créé succès\n\n");
                        break;
                case 8 : sortie = 1;
                        printf("Travail terminé !!!\n\n");
                        break;
                default : printf("Erreur dans le programme\n\n"); sortie = 1;
            }
        }
    }
    else
    {
        printf("Pas de fichier renseigné\n\n");    
    }
    
    freeCategorie(bibli);
    freeListeEmprunt(emprunt); 

    return 0;
}
