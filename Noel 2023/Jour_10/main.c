#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

//#define NBR_LINES 10
#define NBR_LINES 140

//#define NBR_COL 20
#define NBR_COL 140



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
    char Inside[NBR_LINES][NBR_COL];
    long long result1 = 0;
    long long result2 = 0;
    FILE *fic = NULL;


    memset(tab, 0, sizeof(tab));
    memset(S, 0, sizeof(S));
    memset(AlreadyPassed, 'O', sizeof(AlreadyPassed));
    memset(Inside, ',', sizeof(Inside));

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
        //On scanne si les tuiles du tableau tab sont à l'interieur ou à l'exterieur de la courbe du chemin
        bool outside = true;   //On se considère par defaut en dehors de la surface
        char lastCaract = '.';

        //Remplace le S par un caractere pour fermer le chemin
        if(S[0] != 0 && S[1] !=0)
            tab[xS][yS] = 'L';          //Le nord et l'est sont connectés
        else if(S[0] != 0 && S[2] !=0)
            tab[xS][yS] = '|';          //Le nord et le sud sont connectés
        else if(S[0] != 0 && S[3] !=0)
            tab[xS][yS] = 'J';          //Le nord et l'ouest sont connectés
        else if(S[1] != 0 && S[2] !=0)
            tab[xS][yS] = 'F';          //Le sud et l'est sont connectés
        else if(S[1] != 0 && S[2] !=0)
            tab[xS][yS] = '-';          //L'ouest et l'est sont connectés

        //On parcours le tableau dans le sens horizontal
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                if(AlreadyPassed[i][j] == '1')
                {
                    Inside[i][j] = tab[i][j];

                    if(tab[i][j] == '|')   //Si on traverse une ligne, on entre ou sort de la surface
                    {
                        outside = !outside;
                    }
                    else if(tab[i][j] == '-')   //La rien ne change car on suit la meme direction que le chemin
                    {

                    }
                    else if(tab[i][j] == 'L')   //On arrive d'en haut, on va ầ droite
                    {
                        lastCaract = 'L';
                    }
                    else if(tab[i][j] == 'F')   //On arrive d'en bas, on va à droite
                    {
                        lastCaract = 'F';
                    }
                    else if(tab[i][j] == 'J')   //On arrive de la gauche, on va en haut
                    {
                        if(lastCaract == 'F')
                            outside = !outside;
                        //else if(lastCaract == 'L')
                    }
                    else if(tab[i][j] == '7')   //On arrive de la gauche, on va en bas
                    {
                        if(lastCaract == 'L')
                            outside = !outside;
                    }

                }
                else            //Toutes les tuiles inside doivent être comptées
                {
                    if(outside == false)
                    {
                        result2++;
                        Inside[i][j] = 'I';
                    }
                    else
                    {
                        Inside[i][j] = '.';
                    }
                }
            }

            outside = true;     //Pour la prochaine ligne on considere qu'on est en dehors du chemin
        }

        FILE* fic3 = NULL;
        fic3 = fopen("Inside.txt", "w");
        if(fic3 != 0)
        {
            for(i=0 ; i<NBR_LINES ; i++)
            {
                for(j=0 ; j<NBR_COL ; j++)
                    fprintf(fic3, "%c", Inside[i][j]);

                fprintf(fic3, "\n");
            }
        }
        fclose(fic3);
        fic3 = NULL;



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
