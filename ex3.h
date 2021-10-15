typedef struct Voiture {
    char modele[20];
    char immat[8];
    int km;
    enum Etat {dispo, louee} etat;
} Voiture;

void viderBuffer();
int lire(char *chaine, int longueur);
int menu();
Voiture* init (int n);