#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>



int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char buf[1000];
    char buf1[1000];
    char buf2[1000];
    uint64_t nombre = 0;
    uint64_t nombre1 = 0;
    uint64_t nombre2 = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;


    memset(buf, 0, sizeof(buf));
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));



    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");
        fgets(buf, 1000, fic);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }
    fclose(fic);
    fic = NULL;


    //Impression du puzzle complet
    /*for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/


    //Detection des 0 début des chemins
    for(i=0 ; i<strlen(buf) ; i++)
    {
        if(buf[i] != ' ')       //Si ce n'est pas un espace, on lit le nombre dans la chaine
        {
           nombre = nombre * 10 + atoi(&buf[i]);
        }
        else                    //Sinon on passe l'algo
        {
            if(nombre == 0)
            {
                nombre = 1;
            }
            else if(nombre % 2)
            {

            }

        }
    }


    //Impression du resultat complet
    printf("%s\n", buf);


    //On ajoute toutes les solutions de chemins
    /*for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            somme1 += tab2[i][j];
        }
    }*/

    printf("Somme1 = %lld\n\n", somme1);





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
    printf("Somme2 = %lld\n", somme2);*/

    return 0;
}
