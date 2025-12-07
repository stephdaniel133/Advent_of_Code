#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#define NBR_LINES   16
#define NBR_COL     15
//#define NBR_LINES   142
//#define NBR_COL     141

void printTable(char (*tab)[NBR_COL])
{
    int i = 0;
    int j = 0;

    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Recur(char (*tab)[NBR_COL], int xS, int j, int64_t *somme)
{
    int i = 0;

    if(xS == NBR_LINES)   //On a atteint l'avant dernière ligne
    {
        *somme += 1;
        if(*somme%100000==0)
        {
            //printTable(tab);
            printf("Fin du tableau atteinte, somme = %ld\n", *somme);
        }
        return;
    }

    for(i=xS ; i<NBR_LINES ; i++)
    {
        if((tab[i][j] == '^') && (tab[i-1][j] == '|'))  //On cherche une split avec une barre au dessus
        {
            //On teste à gauche du split
            tab[i][j-1] = '|';
            tab[i+1][j-1] = '|';
            Recur(tab, i+2, j-1, somme);
            tab[i+1][j-1] = '.';            //On remet le tableau propre
            tab[i][j-1] = '.';

            //On teste à droite du split
            tab[i][j+1] = '|';
            tab[i+1][j+1] = '|';
            Recur(tab, i+2, j+1, somme);
            tab[i+1][j+1] = '.';            //On remet le tableau propre
            tab[i][j+1] = '.';
        }
        else if((tab[i][j] == '.') && (tab[i-1][j] == '|'))
        {
            tab[i][j] = '|';                //Si on descend tout droit, on ajoute une barre
            Recur(tab, i+1, j, somme);
            tab[i][j] = '.';                //On remet le tableau propre
        }
    }
}


int main(int argc, char *argv[])
{
    char buf1[NBR_COL+1];
    int64_t i = 0;
    int64_t j = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char tab1[NBR_LINES][NBR_COL];
    int64_t tab2[NBR_LINES][NBR_COL];
    int xS = 0;
    int yS = 0;


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(buf1, 0, sizeof(buf1));
    memset(tab1, '1', sizeof(tab1));
    memset(tab2, '1', sizeof(tab2));


    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            fgets(buf1, NBR_COL+1, fic);
            memcpy(tab1[i], buf1, NBR_COL);
            fgetc(fic); //On echappe le saut à la ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");


    //Impression du puzzle complet et recherche du 'S'
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab1[i][j]);
            if(tab1[i][j] == 'S')
            {
                xS = i;
                yS = j;
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("xS = %d\n", xS);
    printf("yS = %d\n", yS);
    printf("\n");


    //--------------Part 1-----------------
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab1[i][j] == 'S')
            {
                tab1[i+1][j] = '|';
            }
            else if((tab1[i][j] == '^') && (tab1[i-1][j] == '|'))
            {
                tab1[i][j-1] = '|';
                tab1[i][j+1] = '|';
                tab1[i+1][j-1] = '|';
                tab1[i+1][j+1] = '|';
                somme1++;
            }
            else if((tab1[i][j] == '.') && (tab1[i-1][j] == '|'))
            {
                tab1[i][j] = '|';
            }
        }
    }

    //Impression du puzzle complet
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("somme1 = %ld\n\n\n", somme1);


    //--------------Part 2-----------------
    //On efface les beams
    printf("Efface les beams\n");
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab1[i][j] == '|')
            {
                tab1[i][j] = '.';
            }
            //printf("%c ", tab1[i][j]);
        }
        //printf("\n");
    }

    tab1[xS+1][yS] = '|';
    Recur(tab1, xS+2, yS, &somme2);

    printf("somme2 = %ld\n", somme2);


    fclose(fic);
    fic = NULL;

    return 0;
}
