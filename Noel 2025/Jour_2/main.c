#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Fonction qui teste une ligne unique
int isSafe(int tab[2000][10], int ligne)
{
    int i = 0;
    int isSafe = 0; // = 1 when safe


    //On teste les conditions increase
    if((tab[ligne][1] > tab[ligne][0]) && (tab[ligne][1] <= tab[ligne][0]+3))
    {
        i = 2;

        while(tab[ligne][i] != -1)
        {
            if((tab[ligne][i] > tab[ligne][i-1]) && (tab[ligne][i] <= tab[ligne][i-1]+3))
            {
                isSafe = 1;
                i++;
            }
            else
            {
                isSafe = 0;
                break;
            }
        }
    }
    //On teste les conditions decrease
    else if((tab[ligne][0] > tab[ligne][1]) && (tab[ligne][0] <= tab[ligne][1]+3))
    {
        i = 2;

        while(tab[ligne][i] != -1)
        {
            if((tab[ligne][i-1] > tab[ligne][i]) && (tab[ligne][i-1] <= tab[ligne][i]+3))
            {
                isSafe = 1;
                i++;
            }
            else
            {
                isSafe = 0;
                break;
            }
        }
    }
    else
    {
        isSafe = 0;  //Les 2 valeurs sont égales, la condition n'est pas respectée, on sort de la fonction
    }

    return isSafe;
}





int main(int argc, char *argv[])
{
    char buf[100];
    int i = 0;
    int nbrligne = 0;
    int somme1 = 0;
    int somme2 = 0;
    int tab1[2000][10];
    int tab2[2000][10];
    int tabResult[2000];


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(tab1, -1, sizeof(tab1)); //Initialise à -1 parce qu'il n'y a pas de valeur négative dans les données

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
                sscanf(buf, "%d %d %d %d %d %d %d %d", &tab1[nbrligne][0], &tab1[nbrligne][1], &tab1[nbrligne][2], &tab1[nbrligne][3], &tab1[nbrligne][4], &tab1[nbrligne][5], &tab1[nbrligne][6], &tab1[nbrligne][7]);
                //printf("nbr1= %d, nbr2= %d\n", tab1[nbrligne], tab2[nbrligne]);
            }

            nbrligne++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }


    for(i=0 ; i<nbrligne ; i++)
    {
        somme1 += isSafe(tab1, i);
    }

    printf("somme1 = %d\n", somme1);


    //--------------Part 2-----------------
    //On va retirer une à une les colonne du tableau et repasser l'algorithme de recherche des lignes SAFE

    //On cherche les SAFE dans le tableau initial
    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab1, i);
    }

    //Puis on cherche dans les tableaux tronqués d'une colonne et on additionne les SAFE supplémentaires

    //On retire la colonne 0
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][1];
        tab2[i][1] = tab1[i][2];
        tab2[i][2] = tab1[i][3];
        tab2[i][3] = tab1[i][4];
        tab2[i][4] = tab1[i][5];
        tab2[i][5] = tab1[i][6];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }

    //On retire la colonne 1
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][2];
        tab2[i][2] = tab1[i][3];
        tab2[i][3] = tab1[i][4];
        tab2[i][4] = tab1[i][5];
        tab2[i][5] = tab1[i][6];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }

    //On retire la colonne 2
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][1];
        tab2[i][2] = tab1[i][3];
        tab2[i][3] = tab1[i][4];
        tab2[i][4] = tab1[i][5];
        tab2[i][5] = tab1[i][6];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }


    //On retire la colonne 3
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][1];
        tab2[i][2] = tab1[i][2];
        tab2[i][3] = tab1[i][4];
        tab2[i][4] = tab1[i][5];
        tab2[i][5] = tab1[i][6];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }


    //On retire la colonne 4
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][1];
        tab2[i][2] = tab1[i][2];
        tab2[i][3] = tab1[i][3];
        tab2[i][4] = tab1[i][5];
        tab2[i][5] = tab1[i][6];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }


    //On retire la colonne 5
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][1];
        tab2[i][2] = tab1[i][2];
        tab2[i][3] = tab1[i][3];
        tab2[i][4] = tab1[i][4];
        tab2[i][5] = tab1[i][6];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }


    //On retire la colonne 6
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][1];
        tab2[i][2] = tab1[i][2];
        tab2[i][3] = tab1[i][3];
        tab2[i][4] = tab1[i][4];
        tab2[i][5] = tab1[i][5];
        tab2[i][6] = tab1[i][7];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }


    //On retire la colonne 7
    memset(tab2, -1, sizeof(tab2));
    for(i=0 ; i<nbrligne ; i++)
    {
        tab2[i][0] = tab1[i][0];
        tab2[i][1] = tab1[i][1];
        tab2[i][2] = tab1[i][2];
        tab2[i][3] = tab1[i][3];
        tab2[i][4] = tab1[i][4];
        tab2[i][5] = tab1[i][5];
        tab2[i][6] = tab1[i][6];
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        tabResult[i] += isSafe(tab2, i);
    }


    //On termine par ocmpter le nombre de lignes bonnes
    for(i=0 ; i<1000 ; i++)
    {
        if(tabResult[i] > 0)
        {
            somme2 += 1;
        }
    }

    printf("somme2 = %d\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
