#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <math.h>   //Ajouter -lm dans les options du linker
#include <stdbool.h>

//#define NBR_LINES 20
#define NBR_LINES 1000

int main(int argc, char *argv[])
{
    //char buf1[NBR_COL+1];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    uint64_t dmin = 0;  //Distance mini entre points
    //uint64_t dist = 0;  //Distance entre points
    int group = 1;

    typedef struct
    {
        uint32_t x;
        uint32_t y;
        uint32_t z;
        int group;
        bool aff_group;
    } point_t;
    point_t tab1[NBR_LINES];

    typedef struct
    {
        uint64_t d;
        uint32_t p1;
        uint32_t p2;
    } dist_t;
    dist_t dist[NBR_LINES*(NBR_LINES-1)/2];




    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    //memset(buf1, 0, sizeof(buf1));
    memset(tab1, 0, sizeof(tab1));
    //memset(tab2, 0, sizeof(tab2));
    memset(dist, 0, sizeof(dist));


    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            fscanf(fic, "%d,%d,%d", &tab1[i].x, &tab1[i].y, &tab1[i].z);
            fgetc(fic); //On echappe le saut à la ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");


    //Impression du puzzle complet et recherche du 'S'
    printf("x = %d\n", tab1[0].x);
    printf("y = %d\n", tab1[0].y);
    printf("z = %d\n\n", tab1[0].z);

    printf("x = %d\n", tab1[NBR_LINES-1].x);
    printf("y = %d\n", tab1[NBR_LINES-1].y);
    printf("z = %d\n\n", tab1[NBR_LINES-1].z);

    printf("\n");


    //--------------Part 1-----------------
    //On calcul les distances entre tous les points
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=i+1 ; j<NBR_LINES ; j++)
        {
            dist[k].d = abs((tab1[i].x - tab1[j].x)*(tab1[i].x - tab1[j].x) +
                            (tab1[i].y - tab1[j].y) * (tab1[i].y - tab1[j].y) +
                            (tab1[i].z - tab1[j].z) * (tab1[i].z - tab1[j].z));
            dist[k].p1 = i;
            dist[k].p2 = j;
            printf("%4ld, %4ld, %7lu\n", i, j, dist[k].d);
            k++;
        }
    }

    //On trie le tableau de la plus petite à la plus grande distance entre points
    uint64_t temp = 0;

    for(i = 0; i < (sizeof(dist) / sizeof(dist[0]) - 1); i++)
    {
        for(j = 0; j < (sizeof(dist) / sizeof(dist[0]) - 1); j++)
        {
            if(dist[j].d > dist[j+1].d)  //Si la valeur de dessus est supérieure, on permutte les valeurs
            {
                temp = dist[j].d;
                dist[j].d = dist[j+1].d;
                dist[j+1].d = temp;

                temp = dist[j].p1;
                dist[j].p1 = dist[j+1].p1;
                dist[j+1].p1 = temp;

                temp = dist[j].p2;
                dist[j].p2 = dist[j+1].p2;
                dist[j+1].p2 = temp;
            }
        }
    }

    printf("\n-----------tableau trie--------------------\n");
    //Impression du tableau des distances
    for(i = 0; i < sizeof(dist) / sizeof(dist[0]) - 1; i++)
    {
        printf("%4d, %4d, %7lu\n", dist[i].p1, dist[i].p2, dist[i].d);
    }
    printf("\n");


    printf("somme1 = %ld\n\n\n", somme1);



                /*if((tab1[i].aff_group == false) || (tab1[j].aff_group == false))    //Si au moins 1 point n'a pas de groupe affecté
            {
                dist = abs(pow(tab1[i].x - tab1[j].x, 2) + pow(tab1[i].y - tab1[j].y, 2) + pow(tab1[i].z - tab1[j].z, 2));
                if(dist < dmin)
                {
                    dmin = dist;
                    if((tab1[i].group == 0) && (tab1[j].group == 0))  //Les 2 points trouvés n'ont pas de groupe affecté
                    {
                        tab1[i].group = group;
                        tab1[j].group = group;
                        group++;
                    }
                    else if((tab1[i].group != 0) && (tab1[j].group == 0))  //Le points 1 appartient déjà à un groupe, on affecte le nouveau point à ce groupe
                    {
                        tab1[j].group = tab1[i].group;
                    }
                    else if((tab1[i].group == 0) && (tab1[j].group != 0))  //Le points 2 appartient déjà à un groupe, on affecte le nouveau point à ce groupe
                    {
                        tab1[i].group = tab1[j].group;
                    }
                    i = 0;
                    dmin = 0xFFFFFFFFFFFFFFFF;
                    break;
                }
            }*/
    //--------------Part 2-----------------
    /*for(i=NBR_LINES-2 ; i>1 ; i=i-2)    //On cherche les '^' depuis la base du sapin
    {
        for(j=0 ; j<NBR_COL ; j++)      //On parcours toute la ligne
        {
            if((tab1[i][j] == '^') && (tab1[i-1][j] == '|'))
            {
                for(k=i ; k<NBR_LINES ; k++)
                {
                    //On cherche dans la colonne de gauche en dessous si on tombre sur un '^'
                    if(tab1[k][j-1] == '^')
                    {
                        tab2[i][j] += tab2[k][j-1];
                        break;
                    }
                    else if(k == NBR_LINES-1)
                    {
                        tab2[i][j] += 1;
                    }
                }

                for(k=i ; k<NBR_LINES ; k++)
                {
                    //On cherche dans la colonne de droite en dessous si on tombre sur un '^'
                    if(tab1[k][j+1] == '^')
                    {
                        tab2[i][j] += tab2[k][j+1];
                        break;
                    }
                    else if(k == NBR_LINES-1)
                    {
                        tab2[i][j] += 1;
                    }
                }
            }
        }
    }*/

    //somme2 = tab2[xS+2][yS];

    printf("somme2 = %ld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
