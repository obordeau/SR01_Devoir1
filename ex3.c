#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

int menu(){
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

Voiture* init (int n){
    Voiture* parc = (Voiture*) malloc(n * sizeof(Voiture));
    for (int i = 0; i < n; i++){
        printf("Quel est le modele de la voiture %d ?\n", i + 1);
        lire(parc[i].modele, 20);

        printf("Quelle est l'immatriculation de la voiture %d ?\n", i + 1);
        lire(parc[i].immat, 8);

        printf("Quelle est le kilometrage de la voiture %d ?\n", i + 1);
        int km = -1;
        scanf("%d", &km);
        while (km < 0){
            printf("Veuillez indiquer un kilometrage positif ou nul");
            scanf("%d", &km);
        }
        parc[i].km = km;

        printf("Quelle est l'etat de la voiture %d ? 0 : dispo, 1 louee\n", i + 1);
        int choix_etat = -1;
        scanf("%d", &choix_etat);
        while (choix_etat != 1 && choix_etat != 0){
            printf("Veuillez indiquer un etat de 0 ou 1");
            scanf("%d", &choix_etat);
        }
        parc[i].etat = choix_etat;

        printf("%s %s %d %d", parc[i].modele, parc[i].immat, parc[i].km, parc[i].etat);
    }
    return parc;
}

int main(){
    Voiture *parc = init(1);
    return 0;
}