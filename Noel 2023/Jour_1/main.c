#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int searchdigit(char* str, int* nombre)
{
    if(!strncmp(str, "one", sizeof("one")-1))
    {
        *nombre = 1;
        return 0;
    }
    else if(!strncmp(str, "two", sizeof("two")-1))
    {
        *nombre = 2;
        return 0;
    }
    else if(!strncmp(str, "three", sizeof("three")-1))
    {
        *nombre = 3;
        return 0;
    }
    else if(!strncmp(str, "four", sizeof("four")-1))
    {
        *nombre = 4;
        return 0;
    }
    else if(!strncmp(str, "five", sizeof("five")-1))
    {
        *nombre = 5;
        return 0;
    }
    else if(!strncmp(str, "six", sizeof("six")-1))
    {
        *nombre = 6;
        return 0;
    }
    else if(!strncmp(str, "seven", sizeof("seven")-1))
    {
        *nombre = 7;
        return 0;
    }
    else if(!strncmp(str, "eight", sizeof("eight")-1))
    {
        *nombre = 8;
        return 0;
    }
    else if(!strncmp(str, "nine", sizeof("nine")-1))
    {
        *nombre = 9;
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char buf[100];
    int i = 0;
    int nbrligne = 0;
    int nbr = 0;
    int nbrtemp = 0;
    int listnbr[2000];
    int sommenbr = 0;

    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(listnbr, 0, sizeof(listnbr));

    i = sizeof("one");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 100, fic);
            //printf("%s, longueur = %d\n", buf, (int)strlen(buf));

            if(feof(fic))
            {
                break;
            }
            else
            {
                for(i=0;i<strlen(buf);i++)
                {
                    if(isdigit(buf[i]))
                    {
                        nbr = (buf[i]-48) * 10;
                        break;
                    }
                    if(!searchdigit(&buf[i], &nbrtemp))
                    {
                        nbr = nbrtemp * 10;
                        break;
                    }
                }
                for(i=strlen(buf)-1;i>=0;i--)
                {
                    if(isdigit(buf[i]))
                    {
                        nbr += buf[i]-48;
                        break;
                    }
                    if(!searchdigit(&buf[i], &nbrtemp))
                    {
                        nbr += nbrtemp;
                        break;
                    }
                }
                printf("%s, longueur = %d, nbr = %d\n", buf, (int)strlen(buf), nbr);
            }

            //On ajoute à la liste de nombres
            listnbr[nbrligne] = nbr;
            //On calcule la somme de tous les nombres
            sommenbr += nbr;
            nbrligne++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("somme des nombres = %d\n", sommenbr);

    fclose(fic);
    fic = NULL;

    return 0;
}
