#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

//#define NBR_RANGES   4
//#define NBR_INGR     6
#define NBR_RANGES   187
#define NBR_INGR     1000


// Fonction pour comparer deux intervalles (pour qsort)
int comparerIntervalles(const void *a, const void *b)
{
    const long long *ia = *(const long long **)a;
    const long long *ib = *(const long long **)b;
    return (ia[0] > ib[0]) ? 1 : -1;
}

int main(int argc, char *argv[])
{
    int64_t i = 0;
    int64_t j = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    int64_t tab1[NBR_RANGES][2];
    int64_t tab2[NBR_INGR][2];
    int64_t tab3[NBR_RANGES][2];
    int newRange = 0;
    int nbrRange = 0;
    int encore = 0;


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));
    memset(tab3, 0, sizeof(tab3));


    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //On récupère les ranges
        for(i=0 ; i<NBR_RANGES ; i++)
        {
            fscanf(fic, "%ld-%ld", &tab1[i][0], &tab1[i][1]);
        }

        //On passe le saut de ligne
        fgetc(fic);

        for(i=0 ; i<NBR_INGR ; i++)
        {
            fscanf(fic, "%ld", &tab2[i][0]);
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");


    //Impression du premier et dernier range lu
    printf("Premier range : %ld-%ld\n", tab1[0][0], tab1[0][1]);
    printf("Dernier range : %ld-%ld\n",  tab1[NBR_RANGES-1][0], tab1[NBR_RANGES-1][1]);

    //Impression du premier et dernier ingredient lu
    printf("Premier ingredient : %ld\n", tab2[0][0]);
    printf("Dernier ingredient : %ld\n",  tab2[NBR_INGR-1][0]);


    //--------------Part 1-----------------
    for(i=0 ; i<NBR_INGR ; i++)
    {
        for(j=0 ; j<NBR_RANGES ; j++)
        {
            if((tab1[j][0] <= tab2[i][0]) && (tab2[i][0] <= tab1[j][1]))
            {
                tab2[i][1] += 1;
            }
        }
    }

    for(i=0 ; i<NBR_INGR ; i++)
    {
        if(tab2[i][1] >= 1)
            somme1 += 1;
    }

    printf("somme1 = %ld\n\n\n", somme1);


    //--------------Part 2-----------------
    //On va trier les intervales du plus petits au plus grand
    uint64_t temp = 0;

    for(i=0 ; i<NBR_RANGES-1 ; i++)
    {
        for(j=0 ; j<NBR_RANGES-1 ; j++)
        {
            if(tab1[j][0] > tab1[j+1][0])  //Si la valeur de dessus est supérieure, on permutte les valeurs
            {
                temp = tab1[j][0];
                tab1[j][0] = tab1[j+1][0];
                tab1[j+1][0] = temp;

                temp = tab1[j][1];
                tab1[j][1] = tab1[j+1][1];
                tab1[j+1][1] = temp;
            }
        }
    }

    nbrRange = NBR_RANGES;

    do
    {
        tab3[0][0] = tab1[0][0];
        tab3[0][1] = tab1[0][1];
        newRange = 0;
        encore = 0;
        int dejaTraite = 0;

        for(i=0 ; i<nbrRange ; i++)
        {
            dejaTraite = 0;

            for(j=0 ; j<newRange ; j++)
            {
                //Si les intervalles sont égaux
                if((tab3[j][0] == tab1[i][0]) && (tab3[j][1] == tab1[i][1]))
                {
                    dejaTraite = 1;
                    break;
                }

                //Si le nouvel intervalle est inclu dans un existant dans le nouveau tableau
                if((tab3[j][0] <= tab1[i][0]) &&     //Butée gauche supérieure
                    (tab3[j][1] >= tab1[i][1]))      //Butée doite inférieure
                {
                    dejaTraite = 1;
                    break;
                }

                //Si le nouvel intervalle inclu un intervalle déjà existant
                if((tab3[j][0] >= tab1[i][0]) &&     //Butée gauche inférieure
                    (tab3[j][1] <= tab1[i][1]))      //Butée doite supérieure
                {
                    tab3[j][0] = tab1[i][0];    //On change la butée gauche
                    tab3[j][1] = tab1[i][1];    //On change la butée droite
                    dejaTraite = 1;
                    encore = 1;
                    break;
                }

                //Si les intervalles se recoupent, on agrandit l'intervalle
                //Si le range depasse par la droite
                if((tab3[j][0] <= tab1[i][0]) && (tab3[j][1] >= tab1[i][0]))// &&    //Butée gauche contenu dans l'intervalle
                   //(tab3[j][1] < tab1[i][1]))                                   //Butée droite à l'extérieur de l'intervalle
                {
                    if(tab1[i][0] != tab1[i][1])    //Elimine les cas ou les 2 butées sont égales
                        tab3[j][1] = tab1[i][1];    //On change la butée droite
                    dejaTraite = 1;
                    encore = 1;
                    break;
                }

                //Si les intervalles se recoupent, on agrandit l'intervalle
                //Si le range depasse par la gauche
                if((tab3[j][0] <= tab1[i][1]) && (tab3[j][1] >= tab1[i][1]))// &&    //Butée droite contenu dans l'intervalle
                   //(tab3[j][0] > tab1[i][0]))                                   //Butée gauche à l'extérieur de l'intervalle
                {
                    if(tab1[i][0] != tab1[i][1])    //Elimine les cas ou les 2 butées sont égales
                        tab3[j][0] = tab1[i][0];    //On change la butée gauche
                    dejaTraite = 1;
                    encore = 1;
                    break;
                }
            }

            if(dejaTraite == 0)
            {
                //Si les intervalles ne se recoupent pas, on recopie l'intervalle dans la tableau final
                    tab3[newRange][0] = tab1[i][0];
                    tab3[newRange][1] = tab1[i][1];
                    newRange += 1;
            }
        }

        memset(tab1, 0, sizeof(tab1));
        memcpy(tab1, tab3, sizeof(tab1));
        memset(tab3, 0, sizeof(tab3));
        nbrRange = newRange;
    }
    while(encore == 1);



    // Affichage des intervalles fusionnés
    /*for(i = 0; i < nbrRange; i++)
    {
        printf("%ld-%ld\n", tab1[i][0], tab1[i][1]);
    }*/

    printf("Nombre d'intervalles apres fusion : %d\n", nbrRange);

    for(i=0 ; i<nbrRange ; i++)
    {
        somme2 += tab1[i][1] - tab1[i][0] + 1;
    }

    printf("somme2 = %ld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
