#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//#define NBR_LINES   10
#define NBR_LINES   860
#define NBR_OPE_MAX 15


//Renvoi si le résultat est trouvé
bool recur1(int line_nbr, uint64_t resultToFind, int col, uint32_t tabNum[][NBR_OPE_MAX], uint64_t previousResult, bool found)
{
    if(found == true)
        return true;
    else if(tabNum[line_nbr][col] == 0)
    {
        return false;   //On a atteint le nombre max de nombres on retourne
    }
    else if(resultToFind == (previousResult * tabNum[line_nbr][col]) && (tabNum[line_nbr][col+1] == 0))
    {
        return true;
    }
    else if(resultToFind == (previousResult + tabNum[line_nbr][col]) && (tabNum[line_nbr][col+1] == 0))
    {
        return true;
    }
    else if(true == recur1(line_nbr, resultToFind, col+1, tabNum, previousResult * tabNum[line_nbr][col], found))
    {
        return true;
    }
    else if(true == recur1(line_nbr, resultToFind, col+1, tabNum, previousResult + tabNum[line_nbr][col], found))
    {
        return true;
    }
    else
        return false;
}


//Renvoi si le résultat est trouvé
bool recur2(int line_nbr, uint64_t resultToFind, int col, uint32_t tabNum[][NBR_OPE_MAX], uint64_t previousResult, bool found)
{
    char buf1[50];
    char buf2[50];
    uint64_t temp = 0;


    if(found == true)
        return true;
    else if(col == 0)
    {
        if(true == recur2(line_nbr, resultToFind, 1, tabNum, tabNum[line_nbr][0], found))
            return true;
    }
    else
    {
        if(tabNum[line_nbr][col] == 0)
        {
            return false;   //On a atteint le nombre max de nombres on retourne
        }
        else if(resultToFind == (previousResult * tabNum[line_nbr][col]) && (tabNum[line_nbr][col+1] == 0))
        {
            return true;
        }
        else if(resultToFind == (previousResult + tabNum[line_nbr][col]) && (tabNum[line_nbr][col+1] == 0))
        {
            return true;
        }
        else if(true == recur2(line_nbr, resultToFind, col+1, tabNum, previousResult * tabNum[line_nbr][col], found))
        {
            return true;
        }
        else if(true == recur2(line_nbr, resultToFind, col+1, tabNum, previousResult + tabNum[line_nbr][col], found))
        {
            return true;
        }
        else
        {
            if(tabNum[line_nbr][col] != 0)
            {
                //On recole les nombre avec l'operateur ||
                memset(buf1, '\0', sizeof(buf1));
                memset(buf2, '\0', sizeof(buf2));

                sprintf(buf1, "%lld", previousResult);    //On converti en ASCII le resultat precedent
                sprintf(buf2, "%d", tabNum[line_nbr][col]);
                strcat(buf1, buf2);
                temp = atoll(buf1);

                if((tabNum[line_nbr][col+1] == 0) && (resultToFind == temp))
                    return true;


                if(true == recur2(line_nbr, resultToFind, col+1, tabNum, temp, found))
                {
                    return true;
                }
            }
            else
                return false;
        }
    }

    return false;
}



int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    uint64_t somme1 = 0;
    int64_t somme2 = 0;
    char buf[100];
    uint64_t tab[NBR_LINES];
    uint32_t tab1[NBR_LINES][NBR_OPE_MAX];
    bool tabResult[NBR_LINES];
    int nbr_lignes = 0;
    int i = 0;


    memset(tab, 0, sizeof(tab));
    memset(tab1, 0, sizeof(tab1));
    memset(tabResult, false, sizeof(tabResult));



    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");
        i = 0;

        while(!feof(fic))
        {
            memset(buf, '\0', sizeof(buf));
            fgets(buf, 100, fic);
            sscanf(buf, "%lld: %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &tab[i], &tab1[i][0], &tab1[i][1], &tab1[i][2], &tab1[i][3], &tab1[i][4]
                                                                      , &tab1[i][5], &tab1[i][6], &tab1[i][7], &tab1[i][8], &tab1[i][9]
                                                                      , &tab1[i][10], &tab1[i][11], &tab1[i][12], &tab1[i][13]);
            i++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }
    fclose(fic);
    fic = NULL;

    nbr_lignes = i;

    printf("Nombre de lignes: %d\n", nbr_lignes);

    printf("tab[0] = %lld\n", tab[0]);
    printf("tab1[0][0] = %d\n", tab1[0][0]);
    printf("tab[%d] = %lld\n", nbr_lignes-1, tab[nbr_lignes-1]);
    printf("tab1[%d][4] = %d\n", nbr_lignes-1, tab1[nbr_lignes-1][4]);

    for(i = 0 ; i<nbr_lignes ; i++)
    {
        tabResult[i] = recur1(i, tab[i], 1, tab1, tab1[i][0], false);
    }

    //On compte le score
    for(i = 0 ; i<nbr_lignes ; i++)
    {
        if(true == tabResult[i])
        {
            printf("Ligne bonne %d\n", i);
            somme1 += tab[i];
        }
    }

    printf("\nSomme1 = %lld\n\n", somme1);



    //--------------Part 2-----------------
    //On remet à 0 les résultats
    memset(tabResult, false, sizeof(tabResult));

    for(i = 0 ; i<nbr_lignes ; i++)
    {
        tabResult[i] = recur2(i, tab[i], 0, tab1, 0, false);
    }

    //On compte le score
    for(i = 0 ; i<nbr_lignes ; i++)
    {
        if(true == tabResult[i])
        {
            printf("Ligne bonne %d\n", i);
            somme2 += tab[i];
        }
    }

    printf("\nSomme2 = %lld\n", somme2);

    return 0;
}
