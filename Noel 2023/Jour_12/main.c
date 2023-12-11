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


int main(int argc, char *argv[])
{
    char buf[400];
    long long i = 0;
    long long j = 0;
    //long long k = 0;
    char tab[NBR_LINES][NBR_COL];

    long long result1 = 0;
    long long result2 = 0;
    FILE *fic = NULL;


    memset(tab, 0, sizeof(tab));


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



        //--------------Part 2-----------------



        printf("Resultat 2 = %lld\n", result2);

    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    fclose(fic);
    fic = NULL;

    return 0;
}
