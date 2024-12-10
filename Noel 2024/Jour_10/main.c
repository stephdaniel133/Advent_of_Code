#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//#define NBR_LINES   4
//#define NBR_COL     4
//#define NBR_LINES   8
//#define NBR_COL     8
#define NBR_LINES   52
#define NBR_COL     52


void recur(int i, int j, unsigned char tab[][NBR_COL], unsigned char tab1[][NBR_COL], char next)
{
    if((tab[i][j] == '9') && (next == '9'))    //Si on recontre un 9, on marque le 9 atteint car le chemin est valide
    {
        tab1[i][j] = '1';
        return;
    }
    if(tab[i][j] != next)    //Si le caractère recherché n'est pas dans cette case
    {
        return;
    }
    if(i-1 >= 0)         //On cherche en haut
    {
        recur(i-1, j, tab, tab1, next+1);
    }
    if(i+1 < NBR_LINES) //On cherche en bas
    {
        recur(i+1, j, tab, tab1, next+1);
    }
    if(j-1 >= 0)         //On cherche à gauche
    {
        recur(i, j-1, tab, tab1, next+1);
    }
    if(j+1 < NBR_COL)   //On cherche à droite
    {
        recur(i, j+1, tab, tab1, next+1);
    }
}


void recur2(int i, int j, unsigned char tab[][NBR_COL], unsigned char tab1[][NBR_COL], char next)
{
    if((tab[i][j] == '9') && (next == '9'))    //Si on recontre un 9, on ajoute 1 à la case atteinte car le chemin est valide
    {
        tab1[i][j] += 1;
        return;
    }
    if(tab[i][j] != next)    //Si le caractère recherché n'est pas dans cette case
    {
        return;
    }
    if(i-1 >= 0)         //On cherche en haut
    {
        recur2(i-1, j, tab, tab1, next+1);
    }
    if(i+1 < NBR_LINES) //On cherche en bas
    {
        recur2(i+1, j, tab, tab1, next+1);
    }
    if(j-1 >= 0)         //On cherche à gauche
    {
        recur2(i, j-1, tab, tab1, next+1);
    }
    if(j+1 < NBR_COL)   //On cherche à droite
    {
        recur2(i, j+1, tab, tab1, next+1);
    }
}


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char buf[NBR_COL+1];
    unsigned char tab[NBR_LINES][NBR_COL];
    unsigned char tab1[NBR_LINES][NBR_COL];
    unsigned char tab2[NBR_LINES][NBR_COL];
    int tab3[NBR_LINES][NBR_COL];
    int tab4[NBR_LINES][NBR_COL];
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int xcur = 0;
    int ycur = 0;
    bool boucle = 0;


    memset(tab, '.', sizeof(tab));
    memset(tab1, '0', sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));



    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            fgets(buf, NBR_COL+1, fic);
            memcpy(tab[i], buf, NBR_COL);
            fgetc(fic); //On echappe le saut à la ligne
        }
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
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab[i][j] == '0')
            {
                memset(tab1, '0', sizeof(tab1));

                recur(i, j, tab, tab1, '0');

                //On compte le nombre de 1 dans le tableau (représente le nombre de 9 accessibles depuis le 0 aux coordonnées (i,j)
                for(k=0 ; k<NBR_LINES ; k++)
                {
                    for(l=0 ; l<NBR_COL ; l++)
                    {
                        if(tab1[k][l] == '1')
                            tab2[i][j] += 1;
                    }
                }
            }
        }
    }


    //Impression du resultat complet
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%d ", tab2[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    //On ajoute toutes les solutions de chemins
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            somme1 += tab2[i][j];
        }
    }

    printf("Somme1 = %lld\n\n", somme1);





    //--------------Part 2-----------------
    //Récupération des valeurs dans le fichier data





    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));

    //Detection des 0 début des chemins
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab[i][j] == '0')
            {
                memset(tab1, 0, sizeof(tab1));

                recur2(i, j, tab, tab1, '0');

                //On compte le nombre de 1 dans le tableau (représente le nombre de 9 accessibles depuis le 0 aux coordonnées (i,j)
                for(k=0 ; k<NBR_LINES ; k++)
                {
                    for(l=0 ; l<NBR_COL ; l++)
                    {
                         tab2[i][j] += tab1[k][l];
                    }
                }
            }
        }
    }


    //Impression du resultat complet
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%02d ", tab2[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    //On ajoute toutes les solutions de chemins
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            somme2 += tab2[i][j];
        }
    }
    printf("Somme2 = %lld\n", somme2);

    return 0;
}
