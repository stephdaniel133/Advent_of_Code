#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define max(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a > _b ? _a : _b; })
#define min(a,b) ({ __typeof__ (a) _a = (a); __typeof__ (b) _b = (b); _a < _b ? _a : _b; })

//#define NBR_LINES 10
#define NBR_LINES 140

//#define NBR_COL 10
#define NBR_COL 140


typedef struct
{
    uint16_t x;
    uint16_t y;
} COORD;


int main(int argc, char *argv[])
{
    //char buf[400];
    long long i = 0;
    long long j = 0;
    long long k = 0;
    char tab[NBR_LINES][NBR_COL];
    uint8_t Expensed[NBR_LINES*2][NBR_COL*2];
    uint8_t ExpensedX[NBR_LINES*2][NBR_COL*2];
    int ExpensedXSize = 0;
    int ExpensedXCur = 0;
    int ExpensedYSize = 0;
    int ExpensedYCur = 0;
    uint8_t Line[500];
    uint8_t LineIndex = 0;
    uint8_t Col[500];
    uint8_t ColIndex = 0;
    int galaxyNbr = 0;
    COORD galaxyCoord[500];
    uint64_t galaxyDist[500][500];
    long long result1 = 0;
    long long result2 = 0;
    FILE *fic = NULL;


    memset(tab, 0, sizeof(tab));
    memset(ExpensedX, 0, sizeof(ExpensedX));
    memset(Expensed, 0, sizeof(Expensed));
    memset(galaxyCoord, 0, sizeof(galaxyCoord));
    memset(Line, 0, sizeof(Line));
    memset(Col, 0, sizeof(Col));


    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //On lit les tableaux dans le fichier d'entrée
        while(!feof(fic))
        {
            for(i=0 ; i<NBR_LINES ; i++)
                fscanf(fic, "%s", tab[i]);
        }


        //On expense l'univers en X
        ExpensedXSize = NBR_LINES;
        ExpensedYSize = NBR_COL;
        ExpensedXCur = 0;
        galaxyNbr = 0;

        for(i=0 ; i<NBR_LINES ; i++)
        {
            bool completePoint = true;

            for(j=0 ; j<NBR_COL ; j++)
            {
                ExpensedX[ExpensedXCur][j] = tab[i][j];

                if(tab[i][j] == '#')
                {
                    completePoint = false;
                }
            }

            if(completePoint == true)   //Si on rencontre une ligne de '.'
            {
                ExpensedXSize++;            //On augmente la taille du tableau expensed
                ExpensedXCur++;
                printf("Ligne en %d\n", ExpensedXCur);
                Line[ExpensedXCur] = 1;

                for(k=0 ; k<ExpensedYSize ; k++)
                {
                    ExpensedX[ExpensedXCur][k] = '.';
                }
            }

            ExpensedXCur++;
        }

        //------Debug------------
        FILE* fic2 = NULL;
        fic2 = fopen("ExpensedX.txt", "w");

        for(i=0 ; i<ExpensedXSize ; i++)
        {
            for(j=0 ; j<ExpensedYSize ; j++)
            {
                fprintf(fic2, "%c", ExpensedX[i][j]);
            }
            fprintf(fic2, "\n");
        }

        fclose(fic2);
        fic2 = NULL;

        //On expense l'univers en Y
        ExpensedYSize = NBR_COL;
        ExpensedYCur = 0;

        for(j=0 ; j<NBR_COL ; j++)
        {
            bool completePoint = true;

            for(i=0 ; i<ExpensedXSize ; i++)
            {
                Expensed[i][ExpensedYCur] = ExpensedX[i][j];

                if(ExpensedX[i][j] == '#')
                {
                    completePoint = false;
                }
            }

            if(completePoint == true)   //Si on rencontre une ligne de '.'
            {
                ExpensedYSize++;            //On augmente la taille du tableau expensed
                ExpensedYCur++;
                printf("Colonne en %d\n", ExpensedYCur);
                Col[ExpensedYCur] = 1;

                for(k=0 ; k<ExpensedXSize ; k++)
                {
                    Expensed[k][ExpensedYCur] = '.';
                }
            }

            ExpensedYCur++;
        }

        //------Debug------------
        FILE* fic3 = NULL;
        fic3 = fopen("Expensed.txt", "w");

        for(i=0 ; i<ExpensedXSize ; i++)
        {
            for(j=0 ; j<ExpensedYSize ; j++)
            {
                fprintf(fic3, "%c", Expensed[i][j]);
            }
            fprintf(fic3, "\n");
        }

        fclose(fic3);
        fic3 = NULL;


        //On a expensé l'univers, on connait le nombre de galaxys, on prend les coordonnees de chacune
        for(i=0 ; i<ExpensedXSize ; i++)
        {
            for(j=0 ; j<ExpensedYSize ; j++)
            {
                if(Expensed[i][j] == '#')
                {
                    galaxyCoord[galaxyNbr].x = i;
                    galaxyCoord[galaxyNbr].y = j;
                    galaxyNbr++;
                }
            }
        }


        printf("\nNombre de galaxys = %d\n\n", galaxyNbr);
        result1 = 0;


        for(i=0 ; i<galaxyNbr ; i++)
        {
            for(j=i+1 ; j<galaxyNbr ; j++)
            {
                //printf("Distance X entre galaxy %d [%d ; %d] et %d [%d ; %d] =", i, galaxyCoord[i].x, galaxyCoord[i].y, j, galaxyCoord[j].x, galaxyCoord[j].y);

                //On compte combien de fois on traverse une ligne de points
                for(k = min(galaxyCoord[i].x, galaxyCoord[j].x) ; k < max(galaxyCoord[i].x, galaxyCoord[j].x) ; k++)
                {
                    if(Line[k] == 1)
                        galaxyDist[i][j] += 1;
                    else
                        galaxyDist[i][j] += 1;
                }

                //On compte combien de fois on traverse une colonne de points
                for(k = min(galaxyCoord[i].y, galaxyCoord[j].y) ; k < max(galaxyCoord[i].y, galaxyCoord[j].y) ; k++)
                {
                    if(Col[k] == 1)
                        galaxyDist[i][j] += 1;
                    else
                        galaxyDist[i][j] += 1;
                }



                result1 += galaxyDist[i][j];
            }
        }

        printf("Resultat 1 = %lld\n", result1);


        //--------------Part 2-----------------
        memset(galaxyDist, 0, sizeof(galaxyDist));
        FILE* fic4 = NULL;
        fic4 = fopen("Distances.txt", "w");

        for(i=0 ; i<galaxyNbr ; i++)
        {
            for(j=i+1 ; j<galaxyNbr ; j++)
            {
                //printf("Distance X entre galaxy %d [%d ; %d] et %d [%d ; %d] =", i, galaxyCoord[i].x, galaxyCoord[i].y, j, galaxyCoord[j].x, galaxyCoord[j].y);

                //On compte combien de fois on traverse une ligne de points
                for(k = min(galaxyCoord[i].x, galaxyCoord[j].x) ; k < max(galaxyCoord[i].x, galaxyCoord[j].x) ; k++)
                {
                    if(Line[k] == 1)
                        galaxyDist[i][j] += 999999;
                    else
                        galaxyDist[i][j] += 1;
                }

                //On compte combien de fois on traverse une colonne de points
                for(k = min(galaxyCoord[i].y, galaxyCoord[j].y) ; k < max(galaxyCoord[i].y, galaxyCoord[j].y) ; k++)
                {
                    if(Col[k] == 1)
                        galaxyDist[i][j] += 999999;
                    else
                        galaxyDist[i][j] += 1;
                }

                result2 += galaxyDist[i][j];
            }
        }


        printf("Resultat 2 = %lld\n", result2);

        fclose(fic4);
        fic4 = NULL;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    fclose(fic);
    fic = NULL;

    return 0;
}
