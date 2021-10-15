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

int *initnotes(int *POINTS, int N)
{
    int *NOTES;
    NOTES = (int *)malloc(7 * sizeof(int));
    for (int i = 0; i < 7; i++)
    {
        NOTES[i] = 0;
    }

    for (int i = 0; i < N; i++)
    {
        if (POINTS[i] >= 0 && POINTS[i] <= 9)
        {
            NOTES[0]++;
        }
        else if (POINTS[i] >= 10 && POINTS[i] <= 19)
        {
            NOTES[1]++;
        }
        else if (POINTS[i] >= 20 && POINTS[i] <= 29)
        {
            NOTES[2]++;
        }
        else if (POINTS[i] >= 30 && POINTS[i] <= 39)
        {
            NOTES[3]++;
        }
        else if (POINTS[i] >= 40 && POINTS[i] <= 49)
        {
            NOTES[4]++;
        }
        else if (POINTS[i] >= 50 && POINTS[i] <= 59)
        {
            NOTES[5]++;
        }
        else if (POINTS[i] == 60)
        {
            NOTES[6]++;
        }
    }
    return (NOTES);
}

int main(int argc, char const *argv[])
{
    int N = 0;
    printf("Combien d'etudiants ont fait le devoir de SR01 ?\n");
    scanf("%d", &N);
    int *POINTS = initpoints(N);
    int *NOTES = initnotes(POINTS, N);
    for (int i = 0; i < 7; i++)
    {
        printf("%d\n", NOTES[i]);
    }
    free(POINTS);
    free(NOTES);
    return 0;
}