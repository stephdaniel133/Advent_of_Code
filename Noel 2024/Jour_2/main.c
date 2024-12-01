#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Tri à bulle
void sort(int tab[], int taille)
{
    int i = 0;
    int j = 0;
    int temp = 0;

    for(i=0 ; i<taille-1 ; i++)
    {
        for(j=0 ; j<taille-1 ; j++)
        {
            if(tab[j] > tab[j+1])  //Si la valeur de dessus est supérieure, on permutte les valeurs
            {
                temp = tab[j];
                tab[j] = tab[j+1];
                tab[j+1] = temp;
            }
        }
    }
}


int search(int tab[], int taille, int nbrToSearch)
{
    int i = 0;
    int somme = 0;

    for(i=0 ; i<taille ; i++)
    {
        if(tab[i] == nbrToSearch)
        {
            somme++;
        }
    }

    return somme;
}


int main(int argc, char *argv[])
{
    char buf[100];
    int i = 0;
    int nbrligne = 0;
    int nbr = 0;
    int nbrtemp = 0;
    int somme1 = 0;
    int somme2 = 0;
    int tab1[1000];
    int tab2[1000];

    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));

    i = sizeof("one");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 100, fic);

            if(feof(fic))
            {
                break;
            }
            else
            {
                sscanf(buf, "%d %d", &tab1[nbrligne], &tab2[nbrligne]);
                //printf("nbr1= %d, nbr2= %d\n", tab1[nbrligne], tab2[nbrligne]);
            }

            nbrligne++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    sort(tab1, 1000);
    sort(tab2, 1000);

    for(i=0 ; i<1000 ; i++)
    {
        somme1 += abs(tab2[i] - tab1[i]);
    }

    printf("somme1 des distances = %d\n", somme1);


    //--------------Part 2-----------------
    for(i=0 ; i<1000 ; i++)
    {
        somme2 += tab1[i] * search(tab2, 1000, tab1[i]);
    }

    printf("somme2 = %d\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
