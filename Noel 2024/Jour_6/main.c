#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define NBR_LINES   10
#define NBR_COL     10
//#define NBR_LINES   130
//#define NBR_COL     130


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char buf[NBR_COL+1];
    char tab[NBR_LINES][NBR_COL];
    char tab1[NBR_LINES][NBR_COL];
    char tab2[NBR_LINES][NBR_COL];
    char tabOriginal[NBR_LINES][NBR_COL];
    int i = 0;
    int j = 0;
    int k = 0;
    int xcur = 0;
    int ycur = 0;
    int c =0;


    memset(tab, '0', sizeof(tab));
    memset(tab1, '0', sizeof(tab1));



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


    //Detection du caractere de départ
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab[i][j] == '^')
            {
                xcur = i;
                ycur = j;
                tab1[xcur][ycur] = '1';
            }
        }
    }



    while(1)
    {
        if(tab[xcur][ycur] == '^')
        {
            if(xcur==0)
            {
                tab1[xcur][ycur] = '1';
                break;
            }
            else if(tab[xcur-1][ycur] == '#')
            {
                tab[xcur][ycur] = '>';
            }
            else
            {
                xcur--;
                tab[xcur][ycur] = '^';
                tab1[xcur][ycur] = '1';
            }
        }
        else if(tab[xcur][ycur] == '>')
        {
            if(ycur==NBR_COL-1)
            {
                tab1[xcur][ycur] = '1';
                break;
            }
            else if(tab[xcur][ycur+1] == '#')
            {
                tab[xcur][ycur] = 'v';
            }
            else
            {
                ycur++;
                tab[xcur][ycur] = '>';
                tab1[xcur][ycur] = '1';
            }
        }
        else if(tab[xcur][ycur] == 'v')
        {
            if(xcur==NBR_LINES-1)
            {
                tab1[xcur][ycur] = '1';
                break;
            }
            else if(tab[xcur+1][ycur] == '#')
            {
                tab[xcur][ycur] = '<';
            }
            else
            {
                xcur++;
                tab[xcur][ycur] = 'v';
                tab1[xcur][ycur] = '1';
            }
        }
        else if(tab[xcur][ycur] == '<')
        {
            if(ycur==0)
            {
                tab1[xcur][ycur] = '1';
                break;
            }
            else if(tab[xcur][ycur-1] == '#')
            {
                tab[xcur][ycur] = '^';
            }
            else
            {
                ycur--;
                tab[xcur][ycur] = '<';
                tab1[xcur][ycur] = '1';
            }
        }
    }


    //Impression du resultat complet
    /*for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab1[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/


    //On compte le nombre de positions
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab1[i][j] == '1')
            {
                somme1++;
            }
        }
    }

    printf("Somme1 = %ld\n", somme1);





    //--------------Part 2-----------------
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

    //Detection du caractere de départ
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab[i][j] == '^')
            {
                xcur = i;
                ycur = j;
                tab1[xcur][ycur] = '1';
            }
        }
    }

    memcpy(tabOriginal, tab, NBR_LINES*NBR_COL);


    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            memcpy(tab, tabOriginal, NBR_LINES*NBR_COL);    //On reprend la tableau original
            memset(tab1, '.', sizeof(tab1));
            memset(tab2, '.', sizeof(tab2));

            if(tab[i][j] != '#')
            {
                tab[i][j] = '#';

                //On a créé un nouveau tableau, il faut tester si on a créé une boucle inifie
                while(1)
                {
                    if(tab[xcur][ycur] == '^')
                    {
                        if(xcur==0)
                        {
                            tab1[xcur][ycur] = '1';
                            break;
                        }
                        else if(tab[xcur-1][ycur] == '#')
                        {
                            tab[xcur][ycur] = '>';
                        }
                        else
                        {
                            xcur--;
                            tab[xcur][ycur] = '^';
                            tab1[xcur][ycur] = '1';
                        }
                    }
                    else if(tab[xcur][ycur] == '>')
                    {
                        if(ycur==NBR_COL-1)
                        {
                            tab1[xcur][ycur] = '1';
                            break;
                        }
                        else if(tab[xcur][ycur+1] == '#')
                        {
                            tab[xcur][ycur] = 'v';
                        }
                        else
                        {
                            ycur++;
                            tab[xcur][ycur] = '>';
                            tab1[xcur][ycur] = '1';
                        }
                    }
                    else if(tab[xcur][ycur] == 'v')
                    {
                        if(xcur==NBR_LINES-1)
                        {
                            tab1[xcur][ycur] = '1';
                            break;
                        }
                        else if(tab[xcur+1][ycur] == '#')
                        {
                            tab[xcur][ycur] = '<';
                        }
                        else
                        {
                            xcur++;
                            tab[xcur][ycur] = 'v';
                            tab1[xcur][ycur] = '1';
                        }
                    }
                    else if(tab[xcur][ycur] == '<')
                    {
                        if(ycur==0)
                        {
                            tab1[xcur][ycur] = '1';
                            break;
                        }
                        else if(tab[xcur][ycur-1] == '#')
                        {
                            tab[xcur][ycur] = '^';
                        }
                        else
                        {
                            ycur--;
                            tab[xcur][ycur] = '<';
                            tab1[xcur][ycur] = '1';
                        }
                    }
                    c=0;
                }       //Fin while
                printf("Fin while\n");


            }
        }   //Fin for j
    }   //Fin for i

    printf("Somme2 = %ld\n", somme2);

    return 0;
}
