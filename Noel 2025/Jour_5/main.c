#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

//#define NBR_LINES   10
//#define NBR_COL     10
#define NBR_LINES   140
#define NBR_COL     140

int main(int argc, char *argv[])
{
    char buf1[NBR_COL+2];
    char buf2[NBR_COL+2];
    int nbrRolls = 0;
    int encore = 0;
    int64_t i = 0;
    int64_t j = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char tab1[NBR_LINES+2][NBR_COL+2];
    char tab2[NBR_LINES+2][NBR_COL+2];
    char tab3[NBR_LINES+2][NBR_COL+2];


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(tab1, '1', sizeof(tab1));
    memset(tab2, '1', sizeof(tab2));
    memset(tab3, '1', sizeof(tab3));


    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=1 ; i<NBR_LINES+1 ; i++)
        {
            fgets(buf1, NBR_COL+1, fic);
            memcpy(tab1[i]+1, buf1, NBR_COL);
            fgetc(fic); //On echappe le saut à la ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");


    //Impression du puzzle complet
    for(i=0 ; i<NBR_LINES+2 ; i++)
    {
        for(j=0 ; j<NBR_COL+2 ; j++)
        {
            printf("%c ", tab1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    //--------------Part 1-----------------
    for(i=1 ; i<NBR_LINES+1 ; i++)
    {
        for(j=1 ; j<NBR_COL+1 ; j++)
        {
            nbrRolls = 0;

            if(tab1[i][j] == '@')
            {
                if(tab1[i][j+1] == '@') //à droite
                    nbrRolls++;
                if(tab1[i+1][j+1] == '@') //en bas à droite
                    nbrRolls++;
                if(tab1[i+1][j] == '@') //en bas
                    nbrRolls++;
                if(tab1[i+1][j-1] == '@') //en bas à gauche
                    nbrRolls++;
                if(tab1[i][j-1] == '@') //à gauche
                    nbrRolls++;
                if(tab1[i-1][j-1] == '@') //en haut à gauche
                    nbrRolls++;
                if(tab1[i-1][j] == '@') //en haut
                    nbrRolls++;
                if(tab1[i-1][j+1] == '@') //en haut à droite
                    nbrRolls++;

                if(nbrRolls < 4)
                {
                    tab2[i][j] = 'x';
                    nbrRolls = 0;
                }
                else
                {
                    tab2[i][j] = '.';
                }
            }
            else
            {
                tab2[i][j] = ';';
            }
        }
    }

    //Impression du puzzle complet
    for(i=0 ; i<NBR_LINES+2 ; i++)
    {
        for(j=0 ; j<NBR_COL+2 ; j++)
        {
            printf("%c ", tab2[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    for(i=1 ; i<NBR_LINES+1 ; i++)
    {
        for(j=1 ; j<NBR_COL+1 ; j++)
        {
            if(tab2[i][j] == 'x')
                somme1 += 1;
        }
    }

    printf("somme1 = %ld\n\n\n", somme1);


    //--------------Part 2-----------------
    do
    {
        encore = 0;
        for(i=1 ; i<NBR_LINES+1 ; i++)
        {
            for(j=1 ; j<NBR_COL+1 ; j++)
            {
                nbrRolls = 0;

                if(tab1[i][j] == '@')
                {
                    if(tab1[i][j+1] == '@') //à droite
                        nbrRolls++;
                    if(tab1[i+1][j+1] == '@') //en bas à droite
                        nbrRolls++;
                    if(tab1[i+1][j] == '@') //en bas
                        nbrRolls++;
                    if(tab1[i+1][j-1] == '@') //en bas à gauche
                        nbrRolls++;
                    if(tab1[i][j-1] == '@') //à gauche
                        nbrRolls++;
                    if(tab1[i-1][j-1] == '@') //en haut à gauche
                        nbrRolls++;
                    if(tab1[i-1][j] == '@') //en haut
                        nbrRolls++;
                    if(tab1[i-1][j+1] == '@') //en haut à droite
                        nbrRolls++;

                    if(nbrRolls < 4)
                    {
                        tab1[i][j] = '.';
                        tab3[i][j] = 'x';
                        nbrRolls = 0;
                        encore = 1;
                    }
                }
            }
        }
    }
    while(encore == 1);

    for(i=1 ; i<NBR_LINES+1 ; i++)
    {
        for(j=1 ; j<NBR_COL+1 ; j++)
        {
            if(tab3[i][j] == 'x')
                somme2 += 1;
        }
    }

    printf("somme2 = %ld\n", somme2);


    fclose(fic);
    fic = NULL;

    return 0;
}
