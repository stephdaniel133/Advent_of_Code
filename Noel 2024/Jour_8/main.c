#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>


//#define NBR_LINES   12
//#define NBR_COL     12
#define NBR_LINES   50
#define NBR_COL     50




int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    FILE *fic1 = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char buf[NBR_COL+1];
    unsigned char tab[NBR_LINES][NBR_COL];
    uint8_t tab2[NBR_LINES][NBR_COL];
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    char frequency = 0;
    int antenna1X = 0;
    int antenna1Y = 0;
    int antenna2X = 0;
    int antenna2Y = 0;
    int antinode1X = 0;
    int antinode1Y = 0;
    int antinode2X = 0;
    int antinode2Y = 0;
    int delta1X = 0;
    int delta1Y = 0;

    memset(tab, '.', sizeof(tab));
    memset(tab2, 0, sizeof(tab2));

    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            fgets(buf, NBR_COL+1, fic);
            memcpy(tab[i], buf, NBR_COL);
            fgetc(fic); //On echappe le saut à la ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data.txt\n");
    }
    fclose(fic);
    fic = NULL;


    //Impression du puzzle complet
    /*for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/


    for(frequency='0' ; frequency<='z' ; frequency++)       //On fait défiler les frequences
    {
        if(frequency == ':') //On saute les caractères entre 9 et A dans la table ASCII
            frequency = 'A';
        if(frequency == '[') //On saute les caractères entre 9 et A dans la table ASCII
            frequency = 'a';

        //On cherche les coordonnées de la 1er fréquence
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                if(tab[i][j] == frequency)
                {
                    antenna1X = i;
                    antenna1Y = j;

                    //On cherche les coordonnées de la 2e fréquence, différente de la 1er fréquence
                    for(k=0 ; k<NBR_LINES ; k++)
                    {
                        for(l=0 ; l<NBR_COL ; l++)
                        {
                            if(!((k == antenna1X) && (l == antenna1Y))) //On saute si on detecte la même antenne
                            {
                                if((frequency == tab[k][l]) && (k != antenna1X) && (l != antenna1Y))
                                {
                                    antenna2X = k;
                                    antenna2Y = l;

                                    //On calcule les coordonnées des antinodes
                                    antinode1X = 2*antenna1X - antenna2X;
                                    antinode1Y = 2*antenna1Y - antenna2Y;
                                    antinode2X = 2*antenna2X - antenna1X;
                                    antinode2Y = 2*antenna2Y - antenna1Y;

                                    if((antinode1X >= 0) && (antinode1X < NBR_LINES) && (antinode1Y >= 0) && (antinode1Y < NBR_COL) && (tab[antinode1X][antinode1Y] == '.'))
                                    {
                                        tab[antinode1X][antinode1Y] = '#';
                                    }
                                    if((antinode2X >= 0) && (antinode2X < NBR_LINES) && (antinode2Y >= 0) && (antinode2Y < NBR_COL) && (tab[antinode2X][antinode2Y] == '.'))
                                    {
                                        tab[antinode2X][antinode2Y] = '#';
                                    }

                                    if((antinode1X >= 0) && (antinode1X < NBR_LINES) && (antinode1Y >= 0) && (antinode1Y < NBR_COL))
                                    {
                                        tab2[antinode1X][antinode1Y] = tab2[antinode1X][antinode1Y] + 1;
                                    }
                                    if((antinode2X >= 0) && (antinode2X < NBR_LINES) && (antinode2Y >= 0) && (antinode2Y < NBR_COL))
                                    {
                                        tab2[antinode2X][antinode2Y] = tab2[antinode2X][antinode2Y] + 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    //Impression du resultat complet
    fic1 = fopen("reponse.txt", "w");

    if(fic1 != NULL)
    {
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                fprintf(fic1, "%c", tab[i][j]);
            }
            fprintf(fic1, "\n");
        }
        fprintf(fic1, "\n\n");

        //Impression du resultat complet
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                fprintf(fic1, "%d", tab2[i][j]);
            }
            fprintf(fic1, "\n");
        }
        fprintf(fic1, "\n\n");
    }
    else
    {
        printf("Impossible d'ouvrir le fichier reponse.txt\n");
    }
    fclose(fic1);
    fic1 = NULL;




    //On compte les antinodes
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab2[i][j] != 0)
                somme1 += 1;
        }
    }

    printf("Somme1 = %lld\n\n", somme1);
    //182 too low




    //--------------Part 2-----------------
    /*frequency = 0;
    antenna1X = 0;
    antenna1Y = 0;
    antenna2X = 0;
    antenna2Y = 0;
    antinode1X = 0;
    antinode1Y = 0;
    antinode2X = 0;
    antinode2Y = 0;*/

    memset(tab, '.', sizeof(tab));
    memset(tab2, 0, sizeof(tab2));

    //Récupération des valeurs dans le fichier data
    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            fgets(buf, NBR_COL+1, fic);
            memcpy(tab[i], buf, NBR_COL);
            fgetc(fic); //On echappe le saut à la ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data.txt\n");
    }
    fclose(fic);
    fic = NULL;


    //Impression du puzzle complet
    /*for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            printf("%c ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");*/


    for(frequency='0' ; frequency<='z' ; frequency++)       //On fait défiler les frequences
    {
        if(frequency == ':') //On saute les caractères entre 9 et A dans la table ASCII
            frequency = 'A';
        if(frequency == '[') //On saute les caractères entre 9 et A dans la table ASCII
            frequency = 'a';

        //On cherche les coordonnées de la 1er fréquence
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                if(tab[i][j] == frequency)
                {
                    antenna1X = i;
                    antenna1Y = j;

                    //On cherche les coordonnées de la 2e fréquence, différente de la 1er fréquence
                    for(k=0 ; k<NBR_LINES ; k++)
                    {
                        for(l=0 ; l<NBR_COL ; l++)
                        {
                            if(!((k == antenna1X) && (l == antenna1Y))) //On saute si on detecte la même antenne
                            {
                                if((frequency == tab[k][l]) && (k != antenna1X) && (l != antenna1Y))
                                {
                                    antenna2X = k;
                                    antenna2Y = l;

                                    //On calcule les coordonnées des antinodes
                                    antinode1X = 2*antenna1X - antenna2X;
                                    antinode1Y = 2*antenna1Y - antenna2Y;
                                    antinode2X = 2*antenna2X - antenna1X;
                                    antinode2Y = 2*antenna2Y - antenna1Y;
                                    delta1X = antenna1X - antenna2X;
                                    delta1Y = antenna1Y - antenna2Y;

                                    if((antinode1X >= 0) && (antinode1X < NBR_LINES) && (antinode1Y >= 0) && (antinode1Y < NBR_COL) && (tab[antinode1X][antinode1Y] == '.'))
                                    {
                                        tab[antinode1X][antinode1Y] = '#';  //On place le premier antinode si possible
                                    }

                                    do                                  //On place les suivants en ligne
                                    {
                                        antinode1X += delta1X;
                                        antinode1Y += delta1Y;

                                        if((antinode1X >= 0) && (antinode1X < NBR_LINES) && (antinode1Y >= 0) && (antinode1Y < NBR_COL) && (tab[antinode1X][antinode1Y] == '.'))
                                        {
                                            tab[antinode1X][antinode1Y] = '#';
                                        }

                                    }
                                    while((antinode1X >= 0) && (antinode1X < NBR_LINES) && (antinode1Y >= 0) && (antinode1Y < NBR_COL));

                                    if((antinode2X >= 0) && (antinode2X < NBR_LINES) && (antinode2Y >= 0) && (antinode2Y < NBR_COL) && (tab[antinode2X][antinode2Y] == '.'))
                                    {
                                        tab[antinode2X][antinode2Y] = '#';
                                    }

                                    do                                  //On place les suivants en ligne
                                    {
                                        antinode2X -= delta1X;
                                        antinode2Y -= delta1Y;

                                        if((antinode2X >= 0) && (antinode2X < NBR_LINES) && (antinode2Y >= 0) && (antinode2Y < NBR_COL) && (tab[antinode2X][antinode2Y] == '.'))
                                        {
                                            tab[antinode2X][antinode2Y] = '#';
                                        }

                                    }while((antinode2X >= 0) && (antinode2X < NBR_LINES) && (antinode2Y >= 0) && (antinode2Y < NBR_COL));
                                }
                            }
                        }
                    }
                }
            }
        }
    }


    //Impression du resultat complet
    /*fic1 = fopen("reponse.txt", "w");

    if(fic1 != NULL)
    {
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                fprintf(fic1, "%c", tab[i][j]);
            }
            fprintf(fic1, "\n");
        }
        fprintf(fic1, "\n\n");

        //Impression du resultat complet
        for(i=0 ; i<NBR_LINES ; i++)
        {
            for(j=0 ; j<NBR_COL ; j++)
            {
                fprintf(fic1, "%d", tab2[i][j]);
            }
            fprintf(fic1, "\n");
        }
        fprintf(fic1, "\n\n");
    }
    else
    {
        printf("Impossible d'ouvrir le fichier reponse.txt\n");
    }
    fclose(fic1);
    fic1 = NULL;*/

    //On ajoute toutes les solutions de chemins
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if(tab[i][j] != '.')
                somme2++;
        }
    }
    printf("Somme2 = %lld\n", somme2);

    return 0;
}
