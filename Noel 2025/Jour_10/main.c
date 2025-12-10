#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

//#define NBR_LINES 3
#define NBR_LINES 158

int main(int argc, char *argv[])
{
    int64_t i = 0;
    int64_t j = 0;
    //int64_t k = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    uint16_t swi[NBR_LINES][15];    //swi[0] : nombre de groupes de switches
                                    //swi[1..13] : état des switches
    uint8_t button[NBR_LINES];
    uint8_t jol[NBR_LINES][10];
    uint16_t sol[NBR_LINES];        //Tableau contenant le nombre minimum de boutons à appuyer par ligne
    char c = 0;
    uint8_t index = 0;
    uint16_t test = 0;

    FILE *fic = NULL;
    //FILE *fic2 = NULL;

    fic = fopen("data.txt", "r");
    //fic2 = fopen("output.csv", "w");

    memset(swi, 0, sizeof(swi));
    memset(button, 0, sizeof(button));
    memset(sol, 0xFF, sizeof(sol));
    memset(jol, 0, sizeof(jol));

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            index = 0;

            fgetc(fic);             //Echappe le [
            j = 0;
            do   //On lit le résultat entre []
            {
                c = fgetc(fic);
                if(c == '#')
                {
                    swi[i][0] |= 1 << j;
                }
                j++;
            }
            while(c != ']');

            do                      //On récupère les switches
            {
                c = fgetc(fic);
                if(c == '(')
                {
                    index += 1;
                }
                else if(isdigit(c))
                {
                    swi[i][index] |= 1 << (c - 0x30);
                }
            }
            while(c != '{');

            //On a finit de récupérer les switches, on stocke le nombre de boutons
            button[i] = index;

            index = 0;
            do                      //On récupère les {}
            {
                c = fgetc(fic);
                if(c == ',')
                {
                    index++;
                }
                else if(isdigit(c))
                {
                    jol[i][index] = jol[i][index] * 10 + c - 0x30;
                }
            }
            while(c != '\n' && !feof(fic));
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");


    //Impression du puzzle complet et recherche du 'S'
    printf("x = %d\n", swi[0][0]);
    printf("y = %d\n", swi[0][1]);

    printf("x = %d\n", swi[NBR_LINES-1][0]);
    printf("y = %d\n", swi[NBR_LINES-1][1]);

    printf("\n");


    //--------------Part 1-----------------
    //On calcul toutes les possibilité en binaire et on ne grade que celle qui a le moins de nombre de boutons
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=1 ; j<pow(2,button[i]) ; j++)
        {
            test = 0;                          //On a un maximum de 13 boutons
            test =  (j & (1))     ? swi[i][1] : 0;
            test ^= (j & (1<<1))  ? swi[i][2] : 0;
            test ^= (j & (1<<2))  ? swi[i][3] : 0;
            test ^= (j & (1<<3))  ? swi[i][4] : 0;
            test ^= (j & (1<<4))  ? swi[i][5] : 0;
            test ^= (j & (1<<5))  ? swi[i][6] : 0;
            test ^= (j & (1<<6))  ? swi[i][7] : 0;
            test ^= (j & (1<<7))  ? swi[i][8] : 0;
            test ^= (j & (1<<8))  ? swi[i][9] : 0;
            test ^= (j & (1<<9))  ? swi[i][10] : 0;
            test ^= (j & (1<<10)) ? swi[i][11] : 0;
            test ^= (j & (1<<11)) ? swi[i][12] : 0;
            test ^= (j & (1<<12)) ? swi[i][13] : 0;

            if(test == swi[i][0])
            {
                uint16_t nbr_button = __builtin_popcount(j);    //Donne le nombre de boutons activés
                if(nbr_button < sol[i])
                {
                    sol[i] = nbr_button;
                }
            }
        }
    }

    for(i=0 ; i<NBR_LINES ; i++)
    {
        somme1 += sol[i];
    }

    printf("somme1 = %lu\n\n\n", somme1);

    //--------------Part 2-----------------

    //??????????

    printf("somme2 = %ld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
