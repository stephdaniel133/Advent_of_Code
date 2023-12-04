#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define NBR_WINNING 5
//#define NBR_LIST    8
#define NBR_WINNING 10
#define NBR_LIST    25

int main(int argc, char *argv[])
{
    char buf[200];
    int i = 0;
    int j = 0;
    int card = 0;
    int listWin[10];
    int listTest[25];
    int listNbrMatch[300];
    int listInstance[300];
    int factoriel = 0;
    int sommegame = 0;
    char tmpstr[200];

    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(listWin, 0, sizeof(listWin));
    memset(listTest, 0, sizeof(listTest));
    memset(listNbrMatch, 0, sizeof(listNbrMatch));

    for(i=0 ; i<(sizeof(listInstance)/sizeof(int)) ; i++)
        listInstance[i] = 1;

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 200, fic);
            //printf("%s, longueur = %d\n", buf, (int)strlen(buf));

            //On obtient le numéro du game
            sscanf(buf, "%s %d", tmpstr, &card);
            //printf("%s, string = %s, game = %d", buf, tempstr, game);
            printf("Game = %d : ", card);

            /*
            sscanf(&buf[8], "%d%d%d%d%d", &listWin[0], &listWin[1], &listWin[2], &listWin[3], &listWin[4]);
            sscanf(&buf[25], "%d%d%d%d%d%d%d%d", &listTest[0], &listTest[1], &listTest[2], &listTest[3],
                                                 &listTest[4], &listTest[5], &listTest[6], &listTest[7]);
            */
            sscanf(&buf[10], "%d%d%d%d%d%d%d%d%d%d", &listWin[0], &listWin[1], &listWin[2], &listWin[3], &listWin[4], &listWin[5],
                                                     &listWin[6], &listWin[7], &listWin[8], &listWin[9]);
            sscanf(&buf[42], "%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d%d", &listTest[0], &listTest[1], &listTest[2], &listTest[3], &listTest[4],
                                                                                   &listTest[5], &listTest[6], &listTest[7], &listTest[8], &listTest[9],
                                                                                   &listTest[10], &listTest[11], &listTest[12], &listTest[13], &listTest[14],
                                                                                   &listTest[15], &listTest[16], &listTest[17], &listTest[18], &listTest[19],
                                                                                   &listTest[20], &listTest[21], &listTest[22], &listTest[23], &listTest[24]);

            printf("numero gagnants :");



            for(i=0 ; i<NBR_WINNING ; i++)
            {
                for(j=0 ; j<NBR_LIST ; j++)
                {
                    if(listWin[i] == listTest[j])
                    {
                        printf(" %d ", listWin[i]);

                        listNbrMatch[card-1] += 1;   //Utile pour la partie 2

                        if(factoriel == 0)
                        {
                            factoriel = 1;
                        }
                        else
                        {
                            factoriel *= 2;
                        }
                    }
                }
            }

            printf(", factorielle = %d, nombre de match = %d\n", factoriel, listNbrMatch[card-1]);
            sommegame += factoriel;
            factoriel = 0;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    //On calcule la somme de toutes les games possibles
    printf("somme des factorielles = %d\n", sommegame);

    //Part 2
    int firstTime = 0;
    for(i=1 ; i<card+1 ; i++)
    {
        for(int k=0 ; k<listInstance[i-1] ; k++)
        {
            for(j=0 ; j<listNbrMatch[i-1] ; j++)
            {
                listInstance[i-1+j+1] += 1;
            }
        }
    }

    //Calcul de la somme
    int totalscratchcard = 0;
    for(i=0 ; i<card ; i++)
    {
        totalscratchcard += listInstance[i];
    }

    printf("somme des totalscratchcard = %d\n", totalscratchcard);

    fclose(fic);
    fic = NULL;

    return 0;
}
