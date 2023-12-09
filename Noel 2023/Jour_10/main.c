#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>



int main(int argc, char *argv[])
{
    char buf[400];
    long long i = 0;
    long long j = 0;
    long long k = 0;
    long long result1 = 0;
    long long result2 = 0;
    FILE *fic = NULL;


    memset(buf, 0, sizeof(buf));

    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //On lit les tableaux dans le fichier d'entrée
        while(!feof(fic))
        {

        }

        printf("Resultat 1 = %lld\n", result1);



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
