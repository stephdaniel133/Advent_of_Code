#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

#define NBR_LINES 10
//#define NBR_LINES 140

#define NBR_COL 20
//#define NBR_COL 140


//x, y : Cordonnées de la case à tester
//dir : direction du déplacement

int TestChemin(char tab[NBR_LINES][NBR_COL], char AlreadyPassed[NBR_LINES][NBR_COL], int x, int y, char dir)
{
    if(x<0 || x>=NBR_LINES || y<0 || y>=NBR_COL)    //On teste si on est dans le tableau
        return 0;

    if(tab[x][y] == '.')                        //Si on rencontre un '.', le chemin s'arrête
        return 0;
    else
    {
        AlreadyPassed[x][y] = '1';

        if(tab[x][y] == '|' && dir == 'N')     //Tu viens du sud, tu pars vers le nord
            return 1+TestChemin(tab, AlreadyPassed, x-1, y, 'N');
        else if(tab[x][y] == '|' && dir == 'S')     //Tu viens du nord, tu pars vers le sud
            return 1+TestChemin(tab, AlreadyPassed, x+1, y, 'S');

        else if(tab[x][y] == '-' && dir == 'W')     //Tu viens de l'est, tu pars vers l'ouest
            return 1+TestChemin(tab, AlreadyPassed, x, y-1, 'W');
        else if(tab[x][y] == '-' && dir == 'E')     //Tu viens de l'ouest, tu pars vers l'est
            return 1+TestChemin(tab, AlreadyPassed, x, y+1, 'E');

        else if(tab[x][y] == 'L' && dir == 'S')     //Tu viens du nord et tu pars à l'est   |_
            return 1+TestChemin(tab, AlreadyPassed, x, y+1, 'E');
        else if(tab[x][y] == 'L' && dir == 'W')     //Tu viens de l'est, tu pars au nord
            return 1+TestChemin(tab, AlreadyPassed, x-1, y, 'N');

        else if(tab[x][y] == 'J' && dir == 'S')     //Tu viens du nord, tu pars vers l'ouest   _|
            return 1+TestChemin(tab, AlreadyPassed, x, y-1, 'W');
        else if(tab[x][y] == 'J' && dir == 'E')     //Tu viens de l'ouest, tu pars vers nord
            return 1+TestChemin(tab, AlreadyPassed, x-1, y, 'N');

        else if(tab[x][y] == '7' && dir == 'N')     //Tu viens du sud, tu pars vers l'ouest
            return 1+TestChemin(tab, AlreadyPassed, x, y-1, 'W');
        else if(tab[x][y] == '7' && dir == 'E')     //Tu viens de l'ouest, tu pars vers le sud
            return 1+TestChemin(tab, AlreadyPassed, x+1, y, 'S');

        else if(tab[x][y] == 'F' && dir == 'N')     //Tu viens du sud, tu pars vers l'est
            return 1+TestChemin(tab, AlreadyPassed, x, y+1, 'E');
        else if(tab[x][y] == 'F' && dir == 'W')     //Tu viens de l'est, tu pars vers le sud
            return 1+TestChemin(tab, AlreadyPassed, x+1, y, 'S');

        else
            return 0;                               //Combinaison interdite ou blocage dans le chemin
    }
}

int main(int argc, char *argv[])
{
    //char buf[400];
    long long i = 0;
    long long j = 0;
    //long long k = 0;
    int xS = 0;
    int yS = 0;
    int S[4];
    char tab[NBR_LINES][NBR_COL];
    char AlreadyPassed[NBR_LINES][NBR_COL];
    char InsideX[NBR_LINES][NBR_COL];
    char InsideY[NBR_LINES][NBR_COL];
    char Inside[NBR_LINES][NBR_COL];
    long long result1 = 0;
    long long result2 = 0;
    FILE *fic = NULL;


    memset(tab, 0, sizeof(tab));
    memset(S, 0, sizeof(S));
    memset(AlreadyPassed, 'O', sizeof(AlreadyPassed));
    memset(InsideX, 'O', sizeof(InsideX));
    memset(InsideY, 'O', sizeof(InsideY));
    memset(Inside, 'O', sizeof(Inside));

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

        //On cherche le S de départ
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                if(tab[i][j] == 'S')
                {
                    xS = i;
                    yS = j;
                }
            }
        }

        printf("Coordonnees de S [x;y] = [%d;%d]\n", xS, yS);

        //On part du 'S' et on teste tous les chemins autour
        S[0] = TestChemin(tab, AlreadyPassed, xS-1, yS  , 'N');   //On teste au nord
        S[1] = TestChemin(tab, AlreadyPassed, xS  , yS+1, 'E');   //On teste à l'est
        S[2] = TestChemin(tab, AlreadyPassed, xS+1, yS  , 'S');   //On teste au sud
        S[3] = TestChemin(tab, AlreadyPassed, xS  , yS-1, 'W');   //On teste à l'ouest

        //S'arrêter en mode debug, prendre les chemins de même taille faire (taille + 1) / 2
        result1 = (S[0] + 1) / 2;
        printf("Resultat 1 = %lld\n", result1);

        FILE* fic2 = NULL;
        fic2 = fopen("chemin.txt", "w");
        if(fic2 != 0)
        {
            for(i=0 ; i<NBR_LINES ; i++)
            {
                for(j=0 ; j<NBR_COL ; j++)
                    fprintf(fic2, "%c", AlreadyPassed[i][j]);

                fprintf(fic2, "\n");
            }
        }
        fclose(fic2);
        fic2 = NULL;


        //--------------Part 2-----------------Don't work !
        //On scanne si les 'O' du tableau AlreadyPassed sont à l'interieur ou à l'exterieur de la courbe du chemin
        //Un caractere 'O' veut dire qu'un chemin n'est pas passé par ce point donc ces points sont soit à l'intérieur, soit à l'exterieur
        //Un caractere '1' veut dire qu'un chemin est pas passé par ce point donc ce point est considéré à l'exterieur
        FILE* fic3 = NULL;
        fic3 = fopen("InsideX.txt", "w");

        bool outside = true;   //On se considère par defaut en dehors de la surface
        //On parcours le tableau dans le sens horizontal

        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                if(AlreadyPassed[i][j] == '1')   //Si on traverse une ligne, on entre dans la surface
                {
                    outside = !outside;
                    InsideX[i][j] = '1';
                }
                else                            //Si c'est un 'O'
                {
                    if(outside == true)
                    {
                        InsideX[i][j] = 'O';
                    }
                    else
                    {
                        InsideX[i][j] = 'I';
                    }
                }
            }
            outside = true;
        }

        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                fprintf(fic3, "%c", InsideX[i][j]);
            }
            fprintf(fic3, "\n");
        }

        fclose(fic3);
        fic3 = NULL;



        FILE* fic4 = NULL;
        fic4 = fopen("InsideY.txt", "w");

        outside = true;   //On se considère par defaut en dehors de la surface
        //On parcours le tableau dans le sens vertical

        for(j=0 ; j<NBR_COL ; j++)
        {
            for(i=0 ; i<NBR_LINES ; i++)
            {
                if(AlreadyPassed[i][j] == '1')   //Si on traverse une ligne, on entre dans la surface
                {
                    outside = !outside;
                    InsideY[i][j] = '1';
                }
                else                            //Si c'est un 'O'
                {
                    if(outside == true)
                    {
                        InsideY[i][j] = 'O';
                    }
                    else
                    {
                        InsideY[i][j] = 'I';
                    }
                }
            }
            outside = true;
        }

        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                fprintf(fic4, "%c", InsideY[i][j]);
            }
            fprintf(fic4, "\n");
        }

        fclose(fic4);
        fic4 = NULL;



        FILE* fic5 = NULL;
        fic5 = fopen("Inside.txt", "w");

        //On parcours les 2 tableaux, si les 2 points sont inside, le point est à l'interieur
        result2 = 0;

        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                if((InsideX[i][j] == 'I') && (InsideY[i][j] == 'I'))   //Si les 2  points sont à l'interieur
                {
                    Inside[i][j] = 'I';
                    result2++;
                }
                else
                {
                    Inside[i][j] = 'O';
                }

                fprintf(fic5, "%c", Inside[i][j]);
            }

            fprintf(fic5, "\n");
        }

        fclose(fic5);
        fic5 = NULL;


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
