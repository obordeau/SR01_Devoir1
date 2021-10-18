typedef struct Voiture
{
    char modele[20];
    char immat[9];
    int km;
    enum Etat
    {
        dispo,
        louee
    } etat;
} Voiture;

void viderBuffer();
int lire(char *chaine, int longueur);
void menu(Voiture *parc, int n);
Voiture *init(int n);
void retour(Voiture *voitures, int n);
void etat(Voiture *voitures, int n);
Voiture *init(int n);
void louer(Voiture *voitures, int n);
void save(char *fichier, Voiture *voitures, int n);
void etatParc(Voiture *voitures, int n);
void free_parc(Voiture *parc, int n);
