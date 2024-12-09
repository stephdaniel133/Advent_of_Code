#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

//#define TAILLE_STRING   200
#define TAILLE_STRING   20100

int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    FILE *fic1 = NULL;
    uint64_t somme1 = 0;
    uint64_t somme2 = 0;
    char buf[TAILLE_STRING];
    int64_t tab[100000];
    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t index = 0;


    memset(tab, -1, sizeof(tab));

    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier fic ouvert\n");
        fgets(buf, TAILLE_STRING, fic);
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }
    fclose(fic);
    fic = NULL;

    fic1 = fopen("reponse.txt", "w");
    if(fic1 != NULL)
    {
        printf("fichier fic1 ouvert\n");
    }

    //On construit la table de jeu
    for(i = 0 ; i<strlen(buf) ; i+=2)
    {
        //On lit les chiffres impaires la taille des blocs
        if(buf[i] == '1')
        {
            tab[j++] = index;
        }
        else if(buf[i] == '2')
        {
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '3')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '4')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '5')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '6')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '7')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '8')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }
        else if(buf[i] == '9')
        {
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
        }

        index++;    //On incrémente l'index pour la prochaine boucle


        if(buf[i+1] == '1')
        {
            tab[j++] = -1;
        }
        else if(buf[i+1] == '2')
        {
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '3')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '4')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '5')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '6')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '7')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '8')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
        else if(buf[i+1] == '9')
        {
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
            tab[j++] = -1;
        }
    }

    for(i = 0 ; i<(sizeof(tab)/sizeof(int64_t)) ; i++)
    {
        fprintf(fic1, "tab[%lld] = %lld\n", i, tab[i]);
    }

    int taille_tab = j - 1;
    //On prends les derniers caractères et on les mets dans les trous un par un
    for(i = taille_tab ; i >= 0 ; i--)
    {
        if(tab[i] != -1)
        {
            for(j = 0 ; j < taille_tab ; j++)
            {
                if(tab[j] == -1)
                    break;
            }

            if(j > i)
                break;
            tab[j] = tab[i];
            tab[i] = -1;
        }
    }

    //On compte le score
    for(i = 0 ; i<(sizeof(tab)/sizeof(int64_t)) ; i++)
    {
        if(tab[i] != -1)
        {
            uint64_t temp = tab[i]*i;
            somme1 += temp;
            //fprintf(fic1, "tab[%lld] = %lld * %lld, somme = %lld\n", i, tab[i], i, somme1);
        }
    }


    printf("\nSomme1 = %lld\n\n", somme1);
    fprintf(fic1, "\nSomme1 = %lld\n\n", somme1);
    //Reponse 6291146824486

    fclose(fic1);


    //--------------Part 2-----------------



    printf("\nSomme2 = %lld\n", somme2);


    return 0;
}
