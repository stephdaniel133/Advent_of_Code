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
    FILE *fic2 = NULL;
    uint64_t somme1 = 0;
    uint64_t somme2 = 0;
    char buf[TAILLE_STRING];
    int64_t tab[100000];
    //int64_t tab[100];
    uint32_t taille_index[TAILLE_STRING][2];
    int taille_tab = 0;
    uint64_t i = 0;
    uint64_t j = 0;
    uint64_t k = 0;
    uint64_t index = 0;


    memset(tab, -1, sizeof(tab));

    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        //printf("fichier fic ouvert\n");
        fgets(buf, TAILLE_STRING, fic);
        fclose(fic);
        fic = NULL;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
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


    taille_tab = j - 1;

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


    printf("\nSomme1 = %ld\n\n", somme1);

    //Reponse 6291146824486











    //--------------Part 2-----------------

    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        //printf("fichier fic ouvert\n");
        fgets(buf, TAILLE_STRING, fic);
        fclose(fic);
        fic = NULL;
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    index = 0;
    i = 0;
    j = 0;

    for(i = 0 ; i<(sizeof(tab)/sizeof(int64_t)) ; i++)
    {
        tab[i] = -1;
    }

    memset(taille_index, 0, sizeof(taille_index));


    //On construit la table de jeu
    for(i = 0 ; i<strlen(buf) ; i+=2)
    {
        //On lit les chiffres impaires la taille des blocs
        if(buf[i] == '1')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            taille_index[i/2][0] = 1;
        }
        else if(buf[i] == '2')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 2;
        }
        else if(buf[i] == '3')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 3;
        }
        else if(buf[i] == '4')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 4;
        }
        else if(buf[i] == '5')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 5;
        }
        else if(buf[i] == '6')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 6;
        }
        else if(buf[i] == '7')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 7;
        }
        else if(buf[i] == '8')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 8;
        }
        else if(buf[i] == '9')
        {
            taille_index[i/2][1] = j;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            tab[j++] = index;
            taille_index[i/2][0] = 9;
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

    fic1 = fopen("reponse1.txt", "w");
    if(fic1 != NULL)
    {
        //printf("fichier fic1 ouvert\n");
    }
    else
    {
        printf("Impossible d'ouvrir le fichier reponse\n");
    }

    for(i = 0 ; i<(sizeof(tab)/sizeof(int64_t)) ; i++)
    {
        fprintf(fic1, "tab[%ld] = %ld\n", i, tab[i]);
    }
    fclose(fic1);
    fic1 = NULL;


    for(k = 0 ; k<10 ; k++)
    {
        i = index - 1;
        do
        {
            if(taille_index[i][0] == 1)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1))
                    {
                        tab[j]   = i;
                        tab[taille_index[i][1]]   = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 2)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 3)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 4)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1) && (tab[j+3] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[j+3] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        tab[taille_index[i][1]+3] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 5)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1) && (tab[j+3] == -1) && (tab[j+4] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[j+3] = i;
                        tab[j+4] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        tab[taille_index[i][1]+3] = -1;
                        tab[taille_index[i][1]+4] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 6)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1) && (tab[j+3] == -1) && (tab[j+4] == -1) && (tab[j+5] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[j+3] = i;
                        tab[j+4] = i;
                        tab[j+5] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        tab[taille_index[i][1]+3] = -1;
                        tab[taille_index[i][1]+4] = -1;
                        tab[taille_index[i][1]+5] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 7)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1) && (tab[j+3] == -1) && (tab[j+4] == -1) && (tab[j+5] == -1) && (tab[j+6] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[j+3] = i;
                        tab[j+4] = i;
                        tab[j+5] = i;
                        tab[j+6] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        tab[taille_index[i][1]+3] = -1;
                        tab[taille_index[i][1]+4] = -1;
                        tab[taille_index[i][1]+5] = -1;
                        tab[taille_index[i][1]+6] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 8)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1) && (tab[j+3] == -1) && (tab[j+4] == -1) && (tab[j+5] == -1) && (tab[j+6] == -1) && (tab[j+7] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[j+3] = i;
                        tab[j+4] = i;
                        tab[j+5] = i;
                        tab[j+6] = i;
                        tab[j+7] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        tab[taille_index[i][1]+3] = -1;
                        tab[taille_index[i][1]+4] = -1;
                        tab[taille_index[i][1]+5] = -1;
                        tab[taille_index[i][1]+6] = -1;
                        tab[taille_index[i][1]+7] = -1;
                        break;
                    }
                }
            }

            if(taille_index[i][0] == 9)
            {
                for(j=0 ; (j<(sizeof(tab)/sizeof(tab[1]))) && (taille_index[i][1] > j) ; j++)
                {
                    if((tab[j] == -1) && (tab[j+1] == -1) && (tab[j+2] == -1) && (tab[j+3] == -1) && (tab[j+4] == -1) && (tab[j+5] == -1) && (tab[j+6] == -1) && (tab[j+7] == -1) && (tab[j+8] == -1))
                    {
                        tab[j]   = i;
                        tab[j+1] = i;
                        tab[j+2] = i;
                        tab[j+3] = i;
                        tab[j+4] = i;
                        tab[j+5] = i;
                        tab[j+6] = i;
                        tab[j+7] = i;
                        tab[j+8] = i;
                        tab[taille_index[i][1]]   = -1;
                        tab[taille_index[i][1]+1] = -1;
                        tab[taille_index[i][1]+2] = -1;
                        tab[taille_index[i][1]+3] = -1;
                        tab[taille_index[i][1]+4] = -1;
                        tab[taille_index[i][1]+5] = -1;
                        tab[taille_index[i][1]+6] = -1;
                        tab[taille_index[i][1]+7] = -1;
                        tab[taille_index[i][1]+8] = -1;
                        break;
                    }
                }
            }

            i--;    //Index suivant
        }
        while(i > 0);   //On fait défiler les index avec i
    }


    fic2 = fopen("reponse2.txt", "w");
    if(fic2 != NULL)
    {
        //printf("fichier fic1 ouvert\n");
    }
    else
    {
        printf("Impossible d'ouvrir le fichier reponse\n");
    }

    for(i = 0 ; i<(sizeof(tab)/sizeof(int64_t)) ; i++)
    {
        fprintf(fic2, "tab[%ld] = %ld\n", i, tab[i]);
    }
    fclose(fic2);
    fic2 = NULL;




    //On compte le score
    for(i = 0 ; i<(sizeof(tab)/sizeof(int64_t)) ; i++)
    {
        if(tab[i] != -1)
        {
            uint64_t temp = tab[i]*i;
            somme2 += temp;
            //fprintf(fic1, "tab[%lld] = %lld * %lld, somme = %lld\n", i, tab[i], i, somme2);
        }
    }
    printf("\nSomme2 = %ld\n", somme2);
    //   630.727.996.320 too low
    //34.749.607.868.319
    //13.647.640.601.942 too high

    return 0;
}
