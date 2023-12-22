#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

//#define NBR_COL 6       //Nombre de colonne dans le fichier de base
#define NBR_COL 21

int main(int argc, char *argv[])
{
    //char buf[400];
    long long i = 0;
    long long j = 0;
    long long k = 0;
    int tab[NBR_COL+2][NBR_COL+2][300];
    int nbrtab = 0;
    long long result = 0;
    long long result1 = 0;
    long long result2 = 0;
    FILE *fic = NULL;


    memset(tab, 0, sizeof(tab));

    FILE *fic2 = NULL;
    fic2 = fopen("data_apres_tri.txt", "w");

    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");
        //On lit les tableaux dans le fichier d'entrée
        while(!feof(fic))
        {
            //fprintf(fic2, "Tableau %d:\n", nbrtab);

            for(j=0 ; j<NBR_COL ; j++)
            {
                fscanf(fic, "%d", &tab[0][j][nbrtab]);
                //fprintf(fic2, "%d ", tab[0][j][nbrtab]);
            }
            nbrtab++;
            //fprintf(fic2, "\n");
        }

        printf("\nNombre de tableaux %d:\n\n", nbrtab);

        //----------------On calcule jusqu'en bas-------------------------
        for(k=0 ; k<nbrtab ; k++)
        {
            for(i=1 ; i<NBR_COL ; i++)
            {
                for(j=0 ; j<NBR_COL-i ; j++)
                {
                    tab[i][j][k] = tab[i-1][j+1][k] - tab[i-1][j][k];
                    fprintf(fic2, "%d ", tab[i][j][k]);
                }
                fprintf(fic2, "\n");
            }

            //---------On remonte-----------
            i--;
            while(i>=0)
            {
                j = NBR_COL - i;
                fprintf(fic2, "%d %d %d\n", tab[i][j][k], tab[i][j-1][k], tab[i+1][j-1][k]);
                tab[i][j][k] = tab[i][j-1][k] + tab[i+1][j-1][k];

                for(j=0 ; j<NBR_COL+1-i ; j++)
                {
                    fprintf(fic2, "%d ", tab[i][j][k]);
                }
                fprintf(fic2, "\n");
                i--;
                j++;
            }

            result = tab[0][j-2][k];
            fprintf(fic2, "Resultat tableau %lld = %lld\n\n", k, result);

            result1 += result;
            printf("Resultat 1 total = %lld\n\n", result1);
        }



        //--------------Part 2----------------------
        //On lit les tableaux dans le fichier d'entrée
        fseek(fic, 0, SEEK_SET);        //On revient au début du fichier
        memset(tab, 0, sizeof(tab));
        i = 0;
        j = 0;
        k = 0;
        nbrtab = 0;

        while(!feof(fic))
        {
            fprintf(fic2, "Tableau %d:\n", nbrtab);

            for(j=1 ; j<NBR_COL+1 ; j++)
            {
                fscanf(fic, "%d", &tab[0][j][nbrtab]);
                fprintf(fic2, "%d ", tab[0][j][nbrtab]);
            }
            nbrtab++;
            fprintf(fic2, "\n");
        }

        fprintf(fic2, "\nNombre de tableaux %d:\n\n", nbrtab);

        //----------------On calcule jusqu'en bas-------------------------
        for(k=0 ; k<nbrtab ; k++)
        {
            for(i=1 ; i<NBR_COL ; i++)
            {
                for(j=1 ; j<NBR_COL+1-i ; j++)
                {
                    tab[i][j][k] = tab[i-1][j+1][k] - tab[i-1][j][k];
                    fprintf(fic2, "%d ", tab[i][j][k]);
                }
                fprintf(fic2, "\n");
            }

            //---------On remonte-----------
            i--;
            while(i>=0)
            {
                //j = NBR_COL - i;
                fprintf(fic2, "%d = %d - %d\n", tab[i][0][k], tab[i][1][k], tab[i+1][0][k]);
                tab[i][0][k] = tab[i][1][k] - tab[i+1][0][k];

                for(j=0 ; j<NBR_COL+1-i ; j++)
                {
                    fprintf(fic2, "%d ", tab[i][j][k]);
                }
                fprintf(fic2, "\n");
                i--;
                j++;
            }

            result = tab[0][0][k];
            fprintf(fic2, "Resultat tableau %lld = %lld\n\n", k, result);

            result2 += result;
            printf("Resultat 2 total = %lld\n\n", result2);
        }


        printf("Resultat 2 = %lld\n", result2);

        fclose(fic2);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    fclose(fic);
    fic = NULL;

    return 0;
}
