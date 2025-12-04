#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    char buf1[210][110];
    char buf2[100];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    int64_t nbrligne = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    uint8_t nbrCaraRestant = 0;
    char tab1[210][2];
    char tab2[210][2];
    char tab3[210][110];    //Tableau refletant les caracteres que l'on conserve
    int64_t tab4[210];


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));
    memset(tab3, 1, sizeof(tab3));
    //memset(tab4, 0, sizeof(tab4));

    i = sizeof("one");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            //fgets(buf, 100, fic);

            if(feof(fic))
            {
                break;
            }
            else
            {
                fscanf(fic, "%s", &buf1[nbrligne]);
                //printf("nbr1= %ld, nbr2= %ld, taille1= %d, taille2= %d\n", tab1[nbrligne], tab2[nbrligne], (int)strlen(temp1), (int)strlen(temp2));
            }

            nbrligne++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");

    //--------------Part 1-----------------
    //On cherche les invalids ID
    for(i=0 ; i<nbrligne ; i++)
    {
        //Recherche du premier caractères le plus grand
        for(j=0 ; j<strlen(buf1[i])-1 ; j++)
        {
            if(tab1[i][0] < buf1[i][j])
            {
                tab1[i][0] = buf1[i][j];
                tab1[i][1] = j;
            }
        }

        //Recherche du second caractères le plus grand
        for(j=tab1[i][1]+1 ; j<strlen(buf1[i]) ; j++)
        {
            if(tab2[i][0] < buf1[i][j])
            {
                tab2[i][0] = buf1[i][j];
                tab2[i][1] = j;
            }
        }
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        somme1 += (tab1[i][0]-0x30) * 10 + (tab2[i][0] - 0x30);
    }

    printf("somme1 = %ld\n\n\n", somme1);


    //--------------Part 2-----------------
    for(i=0 ; i<nbrligne ; i++)
    {
        int len = strlen(buf1[i]);
        int remove = len - 12; //On veut garder 12 caractères

        //On élimine un chiffre si le suivant est plus grand de gauche à droite
        //ou on retire le dernier si on n'en trouve pas
        while(remove > 0)
        {
            for(j=0 ; j<len-1 ; j++)
            {
                if(buf1[i][j] < buf1[i][j+1])
                {
                    break;
                }
            }

            //On supprimer le chiffre plus petit trouvé en decalant à gauche la suite du nombre
            for(k = j ; k<len-1 ; k++)
            {
                buf1[i][k] = buf1[i][k+1];
            }

            len--;
            buf1[i][len] = '\0';
            remove--;
        }
    }

    //On rtransforme l'ASCII en nombre
    for(i=0 ; i<nbrligne ; i++)
    {
        for(j=0 ; j<strlen(buf1[i]) ; j++)
        {
            tab4[i] = 10 * tab4[i] + buf1[i][j] - 0x30; //Transformation des ASCII en nombre
        }
    }

    for(i=0 ; i<nbrligne ; i++)
    {
        somme2 += tab4[i];
    }

    printf("somme2 = %ld\n", somme2);


    fclose(fic);
    fic = NULL;

    return 0;
}
