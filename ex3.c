#include <stdio.h>
#include <stdlib.h>
#include "ex3.h"

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

int main(){
    int choix = menu();
    return 0;
}