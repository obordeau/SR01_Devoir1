#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "ex3.h"

void viderBuffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL)
    {
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL)
        {
            *positionEntree = '\0';
        }
        else
        {
            viderBuffer();
        }
        return 1;
    }
    else
    {
        viderBuffer();
        return 0;
    }
}

int menu()
{
    int choix = 0;
    printf("------------------MENU------------------\n");
    printf("1: Louer une voiture\n");
    printf("2: Retour d'une voiture\n");
    printf("3: Etat d'une voiture\n");
    printf("4: Etat du parc de voitures\n");
    printf("5: Sauvegarde de l'etat du parc\n");
    printf("0: fin du programme\n");

    return choix;
}

Voiture *init(int n)
{
    Voiture *parc = (Voiture *)malloc(n * sizeof(Voiture));
    int choix = -1;
    printf("Avez-vous deja un fichier sauvegarde ? Oui : 0, Non : 1\n");
    scanf("%d", &choix);
    if (choix == 1)
    {
        for (int i = 0; i < n; i++)
        {
            printf("Quel est le modele de la voiture %d ?\n", i + 1);
            scanf("%20s", parc[i].modele);

            printf("Quelle est l'immatriculation de la voiture %d ?\n", i + 1);
            scanf("%8s", parc[i].immat);

            printf("Quelle est le kilometrage de la voiture %d ?\n", i + 1);
            int km = -1;
            scanf("%d", &km);
            while (km < 0)
            {
                printf("Veuillez indiquer un kilometrage positif ou nul");
                scanf("%d", &km);
            }
            parc[i].km = km;

            printf("Quelle est l'etat de la voiture %d ? 0 : dispo, 1 louee\n", i + 1);
            int choix_etat = -1;
            scanf("%d", &choix_etat);
            while (choix_etat != 1 && choix_etat != 0)
            {
                printf("Veuillez indiquer un etat de 0 ou 1\n");
                scanf("%d", &choix_etat);
            }
            parc[i].etat = choix_etat;
        }
    }
    else
    {
        FILE *file = NULL;
        char fichier[30];
        printf("Quel est le nom du fichier ?\n");
        scanf("%s", fichier);
        if ((file = fopen(fichier, "r")) == NULL)
        {
            perror("fopen");
            exit(1);
        }
        fread(parc, sizeof(Voiture), n, file);
        fclose(file);
    }
    return parc;
}

void retour(Voiture *voitures, int n)
{
    char immat[9];
    int ok = 0, km = -1;
    printf("Veuillez entrer l'immatriculation du vehicule a retourner.\n");
    scanf("%s", &immat);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(voitures[i].immat, immat) == 0)
        {
            ok = 1;
            if (voitures[i].etat == dispo)
            {
                printf("La voiture n'etait pas en location.\n");
            }
            else
            {
                printf("Combien de kilometres avez-vous fait ?\n");
                scanf("%d", &km);
                while (km < 0)
                {
                    printf("Veuillez entrer un kilometrage positif.\n");
                    scanf("%d", &km);
                }
                voitures[i].km += km;
                voitures[i].etat = dispo;
                printf("La voiture est de nouveau disponible avec %d km au compteur.\n", voitures[i].km);
            }
        }
    }
    if (ok == 0)
    {
        printf("Aucun vehicule ne correspond a cette immatriculation.\n");
    }
}

void etat(Voiture *voitures, int n)
{
    char immat[9];
    int ok = 0;
    printf("Veuillez entrer l'immatriculation du vehicule a retourner.\n");
    scanf("%8s", &immat);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(voitures[i].immat, immat) == 0)
        {
            ok = 1;
            printf("La voiture est une %s\n", voitures[i].modele);
            printf("L'immatriculation de la voiture est : %s\n", voitures[i].immat);
            printf("La voiture a %d km au compteur\n", voitures[i].km);
            if (voitures[i].etat == dispo)
            {
                printf("La voiture est disponible a la location.\n");
            }
            else
            {
                printf("La voiture est deja louee.\n");
            }
        }
    }
    if (ok == 0)
    {
        printf("Aucun vehicule ne correspond a cette immatriculation.\n");
    }
}

void louer(Voiture *voitures, int n)
{
    printf("Veuillez entrer l'immatriculation du vehicule a louer\n");
    char immat[9];
    scanf("%8s", immat);

    int voiture_index = -1;
    for (int i = 0; i < n; i++)
    {
        if (strcmp(voitures[i].immat, immat) == 0)
        {
            voiture_index = i;
        }
    }

    if (voiture_index != -1)
    {
        if (voitures[voiture_index].etat == dispo)
        {
            voitures[voiture_index].etat == louee;
            printf("Le vehicule immatricule %s est maintenant loué ! \n", voitures[voiture_index].immat);
        }
        else
        {
            printf("Cette voiture est deja louee.\n");
        }
    }
    else
    {
        printf("Aucun vehicule ne correspond a cette immatriculation.\n");
    }
}

void free_parc(Voiture *parc, int n)
{
    free(parc);
}

void save(char *fichier, Voiture *voitures, int n)
{
    FILE *file = NULL;
    if ((file = fopen(fichier, "w")) == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fwrite(voitures, sizeof(Voiture), n, file);
    fclose(file);
}

int main()
{
    Voiture *parc = init(2);
    //save("test.txt", parc, 2);
    etat(parc, 2);
    free(parc);
    return 0;
}