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


bool SearchToList(char* wordToSearch, char List[][70])
{
    for(size_t i = 0; i<1000 ; i++)
    {
        if(List[i][0] == '\0')
            break;
        if(!strcmp(wordToSearch, List[i]))
            return true;
    }

    return false;
}


void AddToList(char* wordToAdd, char List[][70])
{
    size_t i = 0;

    if(SearchToList(wordToAdd, List))   //Si le mot est déjà dans la liste, on ne l'ajoute pas
        return;

    for(i = 0; i<1000 ; i++)
    {
        if(List[i][0] == '\0')
            break;
    }
    strcpy(List[i], wordToAdd);
}


bool recur(char design[], int towelNbr, char towel[][11], char List[][70])
{
    if(strlen(design) == 0)
        return true;
    else
    {
        if(SearchToList(design, List))   //Si le mot est déjà dans la liste, c'est qu'on l'a déjà cherché
            return false;

        for(int j=0 ; j<towelNbr ; j++)
        {
            if(strncmp(design, towel[j], strlen(towel[j])) == 0)
            {
                if(true == recur(design+strlen(towel[j]), towelNbr, towel, List))
                    return true;
            }
        }

        AddToList(design, List);
        return false;
    }
}


/*bool recur2(char design[], int towelNbr, char towel[][11], char List[][70], uint32_t *designPossibleNbr)
{
    if(strlen(design) == 0)
    {
        (*designPossibleNbr)++;
        return true;
    }
    else
    {
        if(SearchToList(design, List))   //Si le mot est déjà dans la liste, c'est qu'on l'a déjà cherché
            return false;

        for(int j=0 ; j<towelNbr ; j++)
        {
            if(strncmp(design, towel[j], strlen(towel[j])) == 0)
            {
                if(true == recur2(design+strlen(towel[j]), towelNbr, towel, List, designPossibleNbr))
                {
                    //(*designPossibleNbr)++;
                    //return true;
                }
            }
        }

        //AddToList(design, List);
        return false;
    }
}*/


uint32_t recur2(char design[], int towelNbr, char towel[][11], char List[][70])
{
    uint32_t trouve = 0;

    if(strlen(design) == 0)
    {
        //printf("trouve\n");
        return 1;
    }
    else
    {
        if(SearchToList(design, List))   //Si le mot est déjà dans la liste, c'est qu'on l'a déjà cherché
            return trouve;

        for(int j=0 ; j<towelNbr ; j++)
        {
            //printf("%s : %s\n", design, towel[j]);
            if(strncmp(design, towel[j], strlen(towel[j])) == 0)
            {
                trouve += recur2(design+strlen(towel[j]), towelNbr, towel, List);
            }
        }

        if(trouve == 0)
        {
            AddToList(design, List);
        }

        return trouve;
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
    char list[1000][70];
    uint32_t designPossibleNbr[450];
    int i = 0;
    int len = 0;
    int towelNbr = 0;
    int designNbr = 0;


    memset(buf, '\0', sizeof(buf));
    memset(towel, '\0', sizeof(towel));
    memset(design, '\0', sizeof(design));
    memset(designPossible, false, sizeof(designPossible));
    memset(list, '\0', sizeof(list));
    memset(designPossibleNbr, 0, sizeof(designPossibleNbr));


    /*strcpy(list[0], "string 1");
    strcpy(list[1], "string 2");

    bool ans = SearchToList("string 2", list);
    AddToList("string 2", list);*/

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
            //printf("longueur towel %d = %d\n", i, len);
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
            //printf("longueur design %d = %d\n", i, len);
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
        memset(list, '\0', sizeof(list));
        designPossible[i] = recur(design[i], towelNbr, &towel[0], list);
        printf("Design number %d, %d\n", i, designPossible[i]);
    }



    for(i=0 ; i<designNbr ; i++)
    {
        if(designPossible[i] ==true)
        {
            somme1++;
        }
    }
    printf("\nSomme1 = %lld\n\n", somme1);





    //--------------Part 2-----------------
    //Récupération des valeurs dans le fichier data

    for(i=0 ; i<designNbr ; i++)
    {
        //designPossible[i] = recur(design[i], strlen(design[i]), towelNbr, &towel[0], false, "\0");
        //designPossible[i] = recur(design[i], strlen(design[i]), towelNbr, &towel[0], false);
        memset(list, '\0', sizeof(list));
        //recur2(design[i], towelNbr, &towel[0], list, &designPossibleNbr[i]);
        designPossibleNbr[i] = recur2(design[i], towelNbr, &towel[0], list);
        printf("Design number %d, %d\n", i, designPossibleNbr[i]);
    }


    //On ajoute toutes les solutions de chemins
    for(i=0 ; i<designNbr ; i++)
    {
        somme2 += designPossibleNbr[i];
    }
    printf("Somme2 = %lld\n", somme2);
    //865 too low

    return 0;
}
