typedef struct Voiture {
    char modele[20];
    char immat[8];
    int km;
    enum Etat {dispo, louee} etat;
} Voitures;