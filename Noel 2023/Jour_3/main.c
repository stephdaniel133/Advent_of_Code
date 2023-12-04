#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE    140 //DanS le fichier de données max colonne = max ligne

//Retourne 1 si un charactere entourant le caractere testé est un symbole
int searchsymbol(char tab[MAX_LINE+2][MAX_LINE+2], int x, int y)
{
    //On recherche autour du chiffre si on a un charactere autre que un '.' ou un chiffre
    //algebre de bool: symbol = /((isdigit() || '.') = /isdigit() && /'.' vu qu'on ne connait pas la liste des symboles

    if(!(isdigit(tab[x-1][y]) || (tab[x-1][y] == '.')))         //On cherche à gauche
    {
        return 1;
    }
    else if (!(isdigit(tab[x-1][y+1]) || (tab[x-1][y+1] == '.')))   //On cherche en bas à gauche
    {
        return 1;
    }
    else if (!(isdigit(tab[x][y+1]) || (tab[x][y+1] == '.')))   //On cherche en bas
    {
        return 1;
    }
    else if (!(isdigit(tab[x+1][y+1]) || (tab[x+1][y+1] == '.')))   //On cherche en bas à droite
    {
        return 1;
    }
    else if (!(isdigit(tab[x+1][y]) || (tab[x+1][y] == '.')))   //On cherche à droite
    {
        return 1;
    }
    else if (!(isdigit(tab[x+1][y-1]) || (tab[x+1][y-1] == '.')))   //On cherche en haut à droite
    {
        return 1;
    }
    else if (!(isdigit(tab[x][y-1]) || (tab[x][y-1] == '.')))   //On cherche en haut
    {
        return 1;
    }
    else if (!(isdigit(tab[x-1][y-1]) || (tab[x-1][y-1] == '.')))    //On cherche en haut à gauche
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int findnumber(char tab[MAX_LINE+2][MAX_LINE+2], int i, int j)
{
    int number = 0;
    char c = tab[i][j-1];

    if(isdigit(tab[i][j-1]))
    {
        number = findnumber(tab, i, j-1)*10 + tab[i][j]-48;
        return number;
    }
    else
    {
        return tab[i][j]-48;
    }
}

int nettoieValeursSeules(char tab[][MAX_LINE+2], int x, int y)
{
    char number_1 = tab[x][y];
    char number_2 = tab[x][y+1];
    char number_3 = tab[x][y+2];

    if(number_2 == '.' || number_2 == '*')      //On cherche à droite un chiffre pour voir si valeur > 10
    {
        //printf("Chiffre < 10 en %d, %d\n", x, y);
        //On teste les 8 caracteres autour du chiffre pour voir s'il y a une '*'
        if(tab[x+0][y-1] != '*' &&      //a gauche
           tab[x-1][y-1] != '*' &&      //en haut a gauche
           tab[x-1][y+0] != '*' &&      //en haut
           tab[x-1][y+1] != '*' &&      //en haut a droite
           tab[x+0][y+1] != '*' &&      //a droite
           tab[x+1][y+1] != '*' &&      //en bas a droite
           tab[x+1][y+0] != '*' &&      //en bas
           tab[x+1][y-1] != '*' )       //en bas a gauche
        {
            tab[x][y] = '.';
        }
        return 0;
    }
    else
    {
        if(number_3 == '.' || number_3 == '*')
        {
            //printf("Chiffre < 100 en %d, %d\n", x, y);
            //On teste les 10 caracteres autour du nombre à 2 chiffres pour voir s'il y a une '*'
            if(tab[x+0][y-1] != '*' &&      //a gauche
               tab[x-1][y-1] != '*' &&      //en haut a gauche
               tab[x-1][y+0] != '*' &&      //en haut
               tab[x-1][y+1] != '*' &&      //en haut de gauche à droite
               tab[x-1][y+2] != '*' &&      //en haut de gauche à droite
               tab[x+0][y+2] != '*' &&      //a droite
               tab[x+1][y+2] != '*' &&      //en bas a droite
               tab[x+1][y+1] != '*' &&      //en bas a droite
               tab[x+1][y+0] != '*' &&      //en bas
               tab[x+1][y-1] != '*' )       //en bas a gauche
            {
                tab[x+0][y+0] = '.';
                tab[x+0][y+1] = '.';
            }
            return 1;
        }
        else
        {
            //printf("Chiffre < 1000 en %d, %d\n", x, y);
            //On teste les 12 caracteres autour du nombre à 3 chiffres pour voir s'il y a une '*'
            if(tab[x+0][y-1] != '*' &&      //a gauche
               tab[x-1][y-1] != '*' &&      //en haut a gauche
               tab[x-1][y+0] != '*' &&      //en haut
               tab[x-1][y+1] != '*' &&      //en haut de gauche à droite
               tab[x-1][y+2] != '*' &&      //en haut de gauche à droite
               tab[x-1][y+3] != '*' &&      //en haut de gauche à droite
               tab[x+0][y+3] != '*' &&      //a droite
               tab[x+1][y+3] != '*' &&      //en bas de droite à gauche
               tab[x+1][y+2] != '*' &&      //en bas a droite
               tab[x+1][y+1] != '*' &&      //en bas a droite
               tab[x+1][y+0] != '*' &&      //en bas
               tab[x+1][y-1] != '*' )       //en bas a gauche
            {
                tab[x+0][y+0]   = '.';
                tab[x+0][y+1]   = '.';
                tab[x+0][y+2]   = '.';
            }

        return 2;
        }
    }
    printf("%c%c%c\n", number_1, number_2, number_3);
    return 0;
}




//Cherche en haut à gauche
//.......
//XXX*...
//.......
// input le tableau et les coordonnées de l'étoile
int chercheNombreG(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrG = 0;

    nbrG = isdigit(tab[i][j-1])? ((isdigit(tab[i][j-2])? ((isdigit(tab[i][j-3])? ((tab[i][j-3]-48)*100) : 0) + (tab[i][j-2]-48)*10) : 0) + (tab[i][j-1]-48)) : 0;

    return nbrG;
}

//Cherche en haut à gauche
//XXX....
//...*...
//.......
// input le tableau et les coordonnées de l'étoile
int chercheNombreHG(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrHG = 0;

    nbrHG = isdigit(tab[i-1][j-1])? ((isdigit(tab[i-1][j-2])? ((isdigit(tab[i-1][j-3])? ((tab[i-1][j-3]-48)*100) : 0) + (tab[i-1][j-2]-48)*10) : 0) + (tab[i-1][j-1]-48)) : 0;

    return nbrHG;
}

//Cherche en haut au milieu
//.XXXXX.
//...*...
//.......
// input le tableau et les coordonnées de l'étoile
int chercheNombreHM(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrHM = 0;

    if(isdigit(tab[i-1][j-2]) && isdigit(tab[i-1][j-1]) && isdigit(tab[i-1][j]))
    {
        nbrHM = (tab[i-1][j-2]-48)*100 + (tab[i-1][j-1]-48)*10 + tab[i-1][j]-48;
    }
    else if(isdigit(tab[i-1][j-1]) && isdigit(tab[i-1][j]) && isdigit(tab[i-1][j+1]))
    {
        nbrHM = (tab[i-1][j-1]-48)*100 + (tab[i-1][j]-48)*10 + tab[i-1][j+1]-48;
    }
    else if(isdigit(tab[i-1][j]) && isdigit(tab[i-1][j+1]) && isdigit(tab[i-1][j+2]))
    {
        nbrHM = (tab[i-1][j]-48)*100 + (tab[i-1][j+1]-48)*10 + tab[i-1][j+2]-48;
    }
    else if(isdigit(tab[i-1][j-1]) && isdigit(tab[i-1][j]))
    {
        nbrHM = (tab[i-1][j-1]-48)*10 + tab[i-1][j]-48;
    }
    else if(isdigit(tab[i-1][j]) && isdigit(tab[i-1][j+1]))
    {
        nbrHM = (tab[i-1][j]-48)*10 + tab[i-1][j+1]-48;
    }
    else if(isdigit(tab[i-1][j]))
    {
        nbrHM = tab[i-1][j]-48;
    }

    return nbrHM;
}

//Cherche en haut à droite
//....XXX
//...*...
//.......
// input le tableau et les coordonnées de l'étoile
int chercheNombreHD(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrHD = 0;

    if(isdigit(tab[i-1][j+1]))
    {
        nbrHD = tab[i-1][j+1]-48;
        if(isdigit(tab[i-1][j+2]))
        {
            nbrHD = nbrHD*10 + tab[i-1][j+2]-48;
            if(isdigit(tab[i-1][j+3]))
            {
                nbrHD = nbrHD*10 + tab[i-1][j+3]-48;
            }
        }
    }

    return nbrHD;
}

//Cherche à droite
//.......
//...*XXX
//.......
// input le tableau et les coordonnées de l'étoile
int chercheNombreD(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrD = 0;

    if(isdigit(tab[i][j+1]))
    {
        nbrD = tab[i][j+1]-48;
        if(isdigit(tab[i][j+2]))
        {
            nbrD = nbrD*10 + tab[i][j+2]-48;
            if(isdigit(tab[i][j+3]))
            {
                nbrD = nbrD*10 + tab[i][j+3]-48;
            }
        }
    }

    return nbrD;
}

//Cherche en bas à droite
//.......
//...*...
//....XXX
// input le tableau et les coordonnées de l'étoile
int chercheNombreBD(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrBD = 0;

    if(isdigit(tab[i+1][j+1]))
    {
        nbrBD = tab[i+1][j+1]-48;
        if(isdigit(tab[i+1][j+2]))
        {
            nbrBD = nbrBD*10 + tab[i+1][j+2]-48;
            if(isdigit(tab[i+1][j+3]))
            {
                nbrBD = nbrBD*10 + tab[i+1][j+3]-48;
            }
        }
    }

    return nbrBD;
}

//Cherche en bas au milieu
//.......
//...*...
//.XXXXX.
// input le tableau et les coordonnées de l'étoile
int chercheNombreBM(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrBM = 0;

    if(isdigit(tab[i+1][j-2]) && isdigit(tab[i+1][j-1]) && isdigit(tab[i+1][j]))
    {
        nbrBM = (tab[i+1][j-2]-48)*100 + (tab[i+1][j-1]-48)*10 + tab[i+1][j]-48;
    }
    else if(isdigit(tab[i+1][j-1]) && isdigit(tab[i+1][j]) && isdigit(tab[i+1][j+1]))
    {
        nbrBM = (tab[i+1][j-1]-48)*100 + (tab[i+1][j]-48)*10 + tab[i+1][j+1]-48;
    }
    else if(isdigit(tab[i+1][j]) && isdigit(tab[i+1][j+1]) && isdigit(tab[i+1][j+2]))
    {
        nbrBM = (tab[i+1][j]-48)*100 + (tab[i+1][j+1]-48)*10 + tab[i+1][j+2]-48;
    }
    else if(isdigit(tab[i+1][j-1]) && isdigit(tab[i+1][j]))
    {
        nbrBM = (tab[i+1][j-1]-48)*10 + tab[i+1][j]-48;
    }
    else if(isdigit(tab[i+1][j]) && isdigit(tab[i+1][j+1]))
    {
        nbrBM = (tab[i+1][j]-48)*10 + tab[i+1][j+1]-48;
    }
    else if(isdigit(tab[i+1][j]))
    {
        nbrBM = tab[i+1][j]-48;
    }


    return nbrBM;
}

//Cherche en bas à gauche
//.......
//...*...
//XXX....
// input le tableau et les coordonnées de l'étoile
int chercheNombreBG(char tab[][MAX_LINE+2], int i, int j)
{
    int nbrBG = 0;

    nbrBG = isdigit(tab[i+1][j-1])? ((isdigit(tab[i+1][j-2])? ((isdigit(tab[i+1][j-3])? ((tab[i+1][j-3]-48)*100) : 0) + (tab[i+1][j-2]-48)*10) : 0) + (tab[i+1][j-1]-48)) : 0;

    return nbrBG;
}



int main(int argc, char *argv[])
{
    int i = 0;
    int j = 0;
    char tab[MAX_LINE+2][MAX_LINE+2];
    int nbr = 0;
    int nbrvalid = 0;
    int nbrsum = 0;
    int nbrG = 0;
    int nbrHG = 0;
    int nbrHM = 0;
    int nbrHD = 0;
    int nbrD = 0;
    int nbrBD = 0;
    int nbrBM = 0;
    int nbrGB = 0;
    int mul = 0;


    FILE *fic = NULL;
    FILE *fic2 = NULL;
    FILE *fic3 = NULL;

    fic = fopen("data.txt", "r");

    memset(tab, '.', sizeof(tab));

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=1 ; i<MAX_LINE+1 ; i++)
        {
            for(j=1 ; j<MAX_LINE+1 ; j++)
            {
                tab[i][j] = fgetc(fic);
            }
            fgetc(fic); //Saut de ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }



    for(i=0 ; i<MAX_LINE+2 ; i++)
    {
        for(j=0 ; j<MAX_LINE+2 ; j++)
        {
            if(isdigit(tab[i][j]))
            {
                nbr = nbr*10 + tab[i][j] - 48;
                nbrvalid += searchsymbol(tab, i, j);
            }
            else// if(tab[i][j] ==  '.')
            {
                //On trouve un '.', si le nombre était valid, on l'additionne
                if(nbrvalid != 0)
                {
                    nbrsum += nbr;
                }
                nbr = 0;
                nbrvalid = 0;
            }
        }
    }


    printf("somme des nombre valides = %d\n", nbrsum);


    //Part 2
    //On nettoie le fichier en remplacant les caracteres autres que '*' et digit par des points
    /*for(i=0 ; i<MAX_LINE+2 ; i++)
    {
        for(j=0 ; j<MAX_LINE+2 ; j++)
        {
            if(!((tab[i][j] == '*') || (isdigit(tab[i][j]))))
            {
                tab[i][j] = '.';
            }
        }
    }

    fic2 = fopen("test.txt", "wr");
    for(i=0 ; i<MAX_LINE+2 ; i++)
    {
        //fprintf(fic2, "%d", i>=10?i-10:i);
        for(j=0 ; j<MAX_LINE+2 ; j++)
        {
            fprintf(fic2, "%c", tab[i][j]);
        }
        fprintf(fic2, "\n");
    }
    fclose(fic2);*/

    //On nettoie le fichier avec les valeurs qui ne touchent pas une '*'
    /*for(i=0 ; i<MAX_LINE+2 ; i++)
    {
        for(j=0 ; j<MAX_LINE+2 ; j++)
        {
            if(isdigit(tab[i][j]))
            {
                j += nettoieValeursSeules(tab, i, j);
            }
        }
    }


    fic3 = fopen("test1.txt", "wr");
    for(i=0 ; i<MAX_LINE+2 ; i++)
    {
        for(j=0 ; j<MAX_LINE+2 ; j++)
        {
            fprintf(fic3, "%c", tab[i][j]);
        }
        fprintf(fic3, "\n");
    }
    fclose(fic3);*/

    nbrsum = 0;

    //On cherche les étoiles
    for(i=0 ; i<MAX_LINE+2 ; i++)
    {
        for(j=0 ; j<MAX_LINE+2 ; j++)
        {
            if(tab[i][j] == '*')
            {
                nbrG  = chercheNombreG(tab, i, j);
                nbrD  = chercheNombreD(tab, i, j);

                //Si au dessus on a un ., on peut avoir 2 operandes en haut à gauche et en haut à droite
                if(tab[i-1][j] == '.')
                {
                    nbrHG = chercheNombreHG(tab, i, j);
                    nbrHD = chercheNombreHD(tab, i, j);
                }
                else
                {
                    nbrHM = chercheNombreHM(tab, i, j);
                }

                //Si en dessous on a un ., on peut avoir 2 operandes en bas à gauche et en bas à droite
                if(tab[i+1][j] == '.')
                {
                    nbrBD = chercheNombreBD(tab, i, j);
                    nbrGB = chercheNombreBG(tab, i, j);
                }
                else
                {
                    nbrBM = chercheNombreBM(tab, i, j);
                }

                //On a les 2 opérandes (s'il y en a 2), il reste à les multiplier
                mul = nbrG*nbrD + nbrG*nbrHG + nbrG*nbrHD + nbrG*nbrHM + nbrG*nbrBD + nbrG*nbrGB + nbrG*nbrBM +
                                  nbrD*nbrHG + nbrD*nbrHD + nbrD*nbrHM + nbrD*nbrBD + nbrD*nbrGB + nbrD*nbrBM +
                                               nbrHG*nbrHD + nbrHG*nbrHM + nbrHG*nbrBD + nbrHG*nbrGB + nbrHG*nbrBM +
                                                             nbrHD*nbrHM + nbrHD*nbrBD + nbrHD*nbrGB + nbrHD*nbrBM +
                                                                           nbrHM*nbrBD + nbrHM*nbrGB + nbrHM*nbrBM +
                                                                                         nbrBD*nbrGB + nbrBD*nbrBM +
                                                                                                       nbrGB*nbrBM;
                nbrsum += mul;

                //On remet tous les opérandes à 0 ppour la prochaine étoile
                nbrG = 0;
                nbrHG = 0;
                nbrHM = 0;
                nbrHD = 0;
                nbrD = 0;
                nbrBD = 0;
                nbrBM = 0;
                nbrGB = 0;
            }
        }
    }

    printf("somme des nombres relies par des etoiles = %d\n", nbrsum);

    fclose(fic);
    fic = NULL;

    return 0;
}
