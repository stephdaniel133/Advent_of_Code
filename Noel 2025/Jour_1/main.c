#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    char buf[1000];
    int i = 0;
    int j = 0;
    int nbrligne = 0;
    int dial = 50;
    int somme1 = 0;
    int somme2 = 0;
    char tab1[5000];
    int tab2[5000];

    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(buf, 0, sizeof(buf));
    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 100, fic);

            if(feof(fic))
            {
                break;
            }
            else
            {
                sscanf(buf, "%c %d", &tab1[nbrligne], &tab2[nbrligne]);
                //printf("car1= %c, nbr1= %d\n", buf[nbrligne], tab1[nbrligne]);
            }

            nbrligne++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }


    //--------------Part 1-----------------
    dial = 50;

    for(i=0 ; i<nbrligne ; i++)
    {
        //printf("car1= %c, nbr1= %d, dial= ", tab1[i], tab2[i]);

        if(tab1[i] == 'L')
        {
            for(j=0 ; j<tab2[i] ; j++)
            {
                dial -= 1;

                if(dial<0)
                {
                    dial = 99;
                }
            }
        }
        else    //'R'
        {
            for(j=0 ; j<tab2[i] ; j++)
            {
                dial += 1;

                if(dial>=100)
                {
                    dial = 0;
                }

            }
        }

        if(dial == 0)
        {
            somme1++;
        }

        //printf("%d, Somme1 = %d\n", dial, somme1);
    }

    printf("Code1 = %d\n", somme1);


    //--------------Part 2-----------------
    dial = 50;

    for(i=0 ; i<nbrligne ; i++)
    {
        //printf("car1= %c, nbr1= %d, dial= ", tab1[i], tab2[i]);

        if(tab1[i] == 'L')
        {
            for(j=0 ; j<tab2[i] ; j++)
            {
                dial -= 1;

                if(dial == 0)
                {
                    somme2++;
                }

                if(dial<0)
                {
                    dial = 99;
                }

            }
        }
        else    //'R'
        {
            for(j=0 ; j<tab2[i] ; j++)
            {
                dial += 1;

                if(dial == 0)
                {
                    somme2++;
                }

                if(dial>=100)
                {
                    dial = 0;
                    somme2++;
                }
            }
        }

        //printf("%d, Somme2 = %d\n", dial, somme2);
    }

    printf("Code2 = %d\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
