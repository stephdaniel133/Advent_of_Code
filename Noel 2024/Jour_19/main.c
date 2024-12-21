#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


/*bool recur(char design[], int len, int towelNbr, char towel[][11], bool result, char towelTest[])
{
    int lenTest = 0;

    if(result == true)
        return true;
    else
    {
        char test[90];

        for(int j=0 ; j<towelNbr ; j++)
        {
            memset(test, '\0', sizeof(test));
            strcpy(test, towelTest);
            strcat(test, towel[j]);
            printf("%s : %s\n", design, test);
            lenTest = strlen(test);
            if(lenTest<len)
            {
                if(strncmp(design, test, lenTest) == 0)
                {
                    if(true == recur(design, len, towelNbr, towel, result, test))
                        return true;
                }
            }
            else if((lenTest == len) && (strncmp(design, test, lenTest) == 0))
            {
                    return true;
            }
        }

        return false;
    }
}*/


/*bool recur(char design[], int len, int towelNbr, char towel[][11], bool result)
{
    int lenTest = 0;

    if(result == true)
        return true;
    else
    {
        //char test[90];

        for(int j=0 ; j<towelNbr ; j++)
        {
            //printf("%s : %s\n", design, towel[j]);
            lenTest = strlen(towel[j]);
            if(lenTest<len)
            {
                if(strncmp(design, towel[j], lenTest) == 0)
                {
                    if(true == recur(design+lenTest, strlen(design+lenTest), towelNbr, towel, result))
                        return true;
                }
            }
            else if((lenTest == len) && (strncmp(design, towel[j], lenTest) == 0))
            {
                    return true;
            }
        }

        return false;
    }
}*/



bool recur(char design[], int towelNbr, char towel[][11])
{
    if(strlen(design) == 0)
        return true;
    else
    {
        for(int j=0 ; j<towelNbr ; j++)
        {
            if(strncmp(design, towel[j], strlen(towel[j])) == 0)
            {
                if(true == recur(design+strlen(towel[j]), towelNbr, towel))
                    return true;
            }
        }

        return false;
    }
}


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char buf[1000];
    char towel[450][11];
    char design[410][70];
    bool designPossible[450];
    int i = 0;
    int len = 0;
    int towelNbr = 0;
    int designNbr = 0;


    memset(buf, '\0', sizeof(buf));
    memset(towel, '\0', sizeof(towel));
    memset(design, '\0', sizeof(design));
    memset(designPossible, false, sizeof(designPossible));



    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //On recupère les towel
        i = 0;
        do
        {
            memset(buf, 0, sizeof(buf));
            fscanf(fic, "%s, ", buf);
            if(buf[strlen(buf)-1] == ',')
                strncpy(&towel[i][0], buf, strlen(buf)-1);
            else
                strncpy(&towel[i][0], buf, strlen(buf));

            len = strlen(buf);
            printf("longueur towel %d = %d\n", i, len);
            i++;
        }
        while(buf[len-1] == ',');

        towelNbr = i;

        //On recupère les design
        i = 0;
        do
        {
            memset(buf, 0, sizeof(buf));
            fscanf(fic, "%s\n", buf);
            strcpy(&design[i][0], buf);
            len = strlen(buf);
            printf("longueur design %d = %d\n", i, len);
            i++;
        }
        while(!feof(fic));

        designNbr = i;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }
    fclose(fic);
    fic = NULL;

    //printf("\n%s\n", design[designNbr-1]);
    //printf("\n%s\n", towel[towelNbr-1]);


    for(i=0 ; i<designNbr ; i++)
    {
        //designPossible[i] = recur(design[i], strlen(design[i]), towelNbr, &towel[0], false, "\0");
        //designPossible[i] = recur(design[i], strlen(design[i]), towelNbr, &towel[0], false);
        designPossible[i] = recur(design[i], towelNbr, &towel[0]);
        printf("Design number %d, %d\n", i, designPossible[i]);
    }



    for(i=0 ; i<designNbr ; i++)
    {
        if(designPossible[i] ==true)
        {
            somme1++;
        }
    }
    printf("\nSomme1 = %ld\n\n", somme1);





    //--------------Part 2-----------------
    //Récupération des valeurs dans le fichier data




    //On ajoute toutes les solutions de chemins
    /*for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            somme2 += tab2[i][j];
        }
    }
    printf("Somme2 = %ld\n", somme2);*/

    return 0;
}
