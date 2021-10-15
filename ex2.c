#include <stdio.h>
#include <stdlib.h>

int *initpoints(int N)
{
    int *POINTS;
    POINTS = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
    {
        printf("Quelle est la note de l'etudiant %d \n", i + 1);
        scanf("%d", &POINTS[i]);
    }
    return (POINTS);
}

int nmax(int *tab, int N)
{
    int max = -1;
    for (int i = 0; i < N; i++)
    {
        if (tab[i] > max)
        {
            max = tab[i];
        }
    }
    return (max);
}

int nmin(int *tab, int N)
{
    int min = 100;
    for (int i = 0; i < N; i++)
    {
        if (tab[i] < min)
        {
            min = tab[i];
        }
    }
    return (min);
}

float moyenne(int *tab, int N)
{
    float total = 0, i = 0;
    for (int i = 0; i < N; i++)
    {
        total += tab[i];
    }
    return (total / N);
}

int main(int argc, char const *argv[])
{
    int N = 0;
    printf("Combien d'etudiants ont fait le devoir de SR01 ?\n");
    scanf("%d", &N);
    int *POINTS = initpoints(N);
    printf("%f", moyenne(POINTS, N));
    free(POINTS);
    return 0;
}
