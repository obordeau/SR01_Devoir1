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

void menu(Voiture *parc, int n)
{
    int choix;
    int continuer = 1;
    while (continuer == 1)
    {
        printf("\n------------------MENU------------------\n");
        printf("1: Louer une voiture\n");
        printf("2: Retour d'une voiture\n");
        printf("3: Etat d'une voiture\n");
        printf("4: Etat du parc de voitures\n");
        printf("5: Sauvegarde de l'etat du parc\n");
        printf("0: fin du programme\n");

        scanf("%d", &choix);
        viderBuffer();
        printf("\n");
        switch (choix)
        {
        case 1:
            louer(parc, n);
            break;
        case 2:
            retour(parc, n);
            break;
        case 3:
            etat(parc, n);
            break;
        case 4:
            etatParc(parc, n);
            break;
        case 5:
            save(parc, n);
            break;
        case 0:
            free_parc(parc, n);
            continuer = 0;
            break;
        default:
            printf("Veuillez saisir un choix valide. \n");
            break;
        }
    }
}

Voiture *init(int n)
{
    Voiture *parc = (Voiture *)malloc(n * sizeof(Voiture));
    int choix = -1;
    printf("Avez-vous deja un fichier sauvegarde ? Oui : 1, Non : 0\n");
    scanf("%d", &choix);
    viderBuffer();
    if (choix == 0)
    {
        for (int i = 0; i < n; i++)
        {
            printf("Quel est le modele de la voiture %d ?\n", i + 1);
            lire(parc[i].modele, 21);

            printf("Quelle est l'immatriculation de la voiture %d ?\n", i + 1);
            lire(parc[i].immat, 9);

            printf("Quelle est le kilometrage de la voiture %d ?\n", i + 1);
            int km = -1;
            scanf("%d", &km);
            viderBuffer();
            while (km < 0)
            {
                printf("Veuillez indiquer un kilometrage positif ou nul");
                scanf("%d", &km);
                viderBuffer();
            }
            parc[i].km = km;

            printf("Quelle est l'etat de la voiture %d ? 0 : dispo, 1 louee\n", i + 1);
            int choix_etat = -1;
            scanf("%d", &choix_etat);
            viderBuffer();
            while (choix_etat != 1 && choix_etat != 0)
            {
                printf("Veuillez indiquer un etat de 0 ou 1\n");
                scanf("%d", &choix_etat);
                viderBuffer();
            }
            parc[i].etat = choix_etat;
        }
    }
    else
    {
        FILE *file = NULL;
        char fichier[30];
        printf("Quel est le nom du fichier ?\n");
        lire(fichier, 30);
        if ((file = fopen(fichier, "r")) == NULL)
        {
            perror("fopen");
            exit(1);
        }
        fread(parc, sizeof(Voiture), n, file);
        fclose(file);
        printf("Le parc a bien ete cree.\n");
        printf("Les immatriculations des voitures du parc sont les suivantes:\n");
        for (int i = 0; i < n; i++)
        {
            printf("- %s \n", parc[i].immat);
        }
    }
    return parc;
}

void retour(Voiture *voitures, int n)
{
    char immat[9];
    int ok = 0, km = -1;
    printf("Veuillez entrer l'immatriculation du vehicule a retourner.\n");
    lire(immat, 9);
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
                viderBuffer();
                while (km < 0)
                {
                    printf("Veuillez entrer un kilometrage positif.\n");
                    scanf("%d", &km);
                    viderBuffer();
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
    printf("Veuillez entrer l'immatriculation du vehicule a afficher.\n");
    lire(immat, 9);
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
    lire(immat, 9);

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
            voitures[voiture_index].etat = louee;
            printf("Le vehicule immatricule %s est maintenant loue ! \n", voitures[voiture_index].immat);
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

void etatParc(Voiture *voitures, int n)
{
    printf("Le parc automobile est actuellemnt compose de %d vehicules.\n", n);
    int nb_loc = 0;
    int sum_km = 0;
    for (int i = 0; i < n; i++)
    {
        if (voitures[i].etat == louee)
            nb_loc++;
        sum_km += voitures[i].km;
    }
    printf("%d vehicules sont loues.\n", nb_loc);
    printf("%d vehicules sont disponibles.\n", n - nb_loc);
    printf("Le kilometrage moyen de l'ensemble des voitures est de %.1f km.\n", (float)sum_km / (float)n);
}

void free_parc(Voiture *parc, int n)
{
    free(parc);
}

void save(Voiture *voitures, int n)
{
    FILE *file = NULL;
    char fichier[30];
    printf("Quel est le nom du fichier ?\n");
    lire(fichier, 30);
    if ((file = fopen(fichier, "w")) == NULL)
    {
        perror("fopen");
        exit(1);
    }
    fwrite(voitures, sizeof(Voiture), n, file);
    fclose(file);
}

int main(int argc, char const *argv[])
{
    Voiture *parc = init(TAILLE);
    menu(parc, TAILLE);
    return 0;
}