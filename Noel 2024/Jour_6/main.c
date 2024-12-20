#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//#define NBR_LINES   10
//#define NBR_COL     10
#define NBR_LINES   130
#define NBR_COL     130


//Attention l'algo prend 1526s (25mn) pour trouver les solutions

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
    int xcur = 0;
    int ycur = 0;
    int xcurOriginal = 0;
    int ycurOriginal = 0;
    bool boucle = 0;


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
    boucle = true;
    for(i=0 ; (i<NBR_LINES) && (boucle == true) ; i++)
    {
        for(j=0 ; (j<NBR_COL)  && (boucle == true) ; j++)
        {
            if(tab[i][j] == '^')
            {
                boucle = false;
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
    boucle = true;
    for(i=0 ; (i<NBR_LINES) && (boucle == true) ; i++)
    {
        for(j=0 ; (j<NBR_COL) && (boucle == true) ; j++)
        {
            if(tab[i][j] == '^')
            {
                boucle = false;
                xcur = i;
                ycur = j;
            }
        }
    }

    xcurOriginal = xcur;
    ycurOriginal = ycur;

    memcpy(tabOriginal, tab, NBR_LINES*NBR_COL);


    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tabOriginal[i][j] != '#' && tabOriginal[i][j] != '^')
            {
                memcpy(tab, tabOriginal, sizeof(tab));    //On reprend la tableau original
                memset(tab2, 0, sizeof(tab2));
                tab[i][j] = '#';

                xcur = xcurOriginal;
                ycur = ycurOriginal;

                //On a créé un nouveau tableau, il faut tester si on a créé une boucle inifie
                while(boucle == false)
                {
                    if(tab[xcur][ycur] == '^')
                    {
                        if(xcur==0)
                        {
                            tab2[xcur][ycur]++;
                            boucle = false;
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

                            if((tab2[xcur][ycur] & 0b0001) == 0)
                                tab2[xcur][ycur] |= 0b0001;
                            else
                                boucle = true;
                        }
                    }
                    else if(tab[xcur][ycur] == '>')
                    {
                        if(ycur==NBR_COL-1)
                        {
                            tab2[xcur][ycur]++;
                            boucle = false;
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

                            if((tab2[xcur][ycur] & 0b0010) == 0)
                                tab2[xcur][ycur] |= 0b0010;
                            else
                                boucle = true;
                        }
                    }
                    else if(tab[xcur][ycur] == 'v')
                    {
                        if(xcur==NBR_LINES-1)
                        {
                            tab2[xcur][ycur]++;
                            boucle = false;
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

                            if((tab2[xcur][ycur] & 0b0100) == 0)
                                tab2[xcur][ycur] |= 0b0100;
                            else
                                boucle = true;
                        }
                    }
                    else if(tab[xcur][ycur] == '<')
                    {
                        if(ycur==0)
                        {
                            tab2[xcur][ycur]++;
                            boucle = false;
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

                            if((tab2[xcur][ycur] & 0b1000) == 0)
                                tab2[xcur][ycur] |= 0b1000;
                            else
                                boucle = true;
                        }
                    }
                }       //Fin while

                if(boucle == true)
                {
                    printf("Boucle coordonnees x = %d, y = %d\n", i, j);
                    somme2++;
                    boucle = false;
                }
            }
        }   //Fin for j
    }   //Fin for i

    printf("Somme2 = %ld\n", somme2);

    return 0;
}
