#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

//#define NBR_LINES   16
//#define NBR_COL     15
#define NBR_LINES   142
#define NBR_COL     141



int main(int argc, char *argv[])
{
    char buf1[NBR_COL+1];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
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
    memset(tab2, 0, sizeof(tab2));


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
        printf("%2li ", i);
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab1[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("somme1 = %ld\n\n\n", somme1);


    //--------------Part 2-----------------
    for(i=NBR_LINES-2 ; i>1 ; i=i-2)    //On cherche les '^' depuis la base du sapin
    {
        for(j=0 ; j<NBR_COL ; j++)      //On parcours toute la ligne
        {
            if((tab1[i][j] == '^') && (tab1[i-1][j] == '|'))
            {
                for(k=i ; k<NBR_LINES ; k++)
                {
                    //On cherche dans la colonne de gauche en dessous si on tombre sur un '^'
                    if(tab1[k][j-1] == '^')
                    {
                        tab2[i][j] += tab2[k][j-1];
                        break;
                    }
                    else if(k == NBR_LINES-1)
                    {
                        tab2[i][j] += 1;
                    }
                }

                for(k=i ; k<NBR_LINES ; k++)
                {
                    //On cherche dans la colonne de droite en dessous si on tombre sur un '^'
                    if(tab1[k][j+1] == '^')
                    {
                        tab2[i][j] += tab2[k][j+1];
                        break;
                    }
                    else if(k == NBR_LINES-1)
                    {
                        tab2[i][j] += 1;
                    }
                }
            }
        }
    }

    somme2 = tab2[xS+2][yS];

    printf("somme2 = %ld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
