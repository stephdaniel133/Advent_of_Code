#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RED     12
#define MAX_GREEN   13
#define MAX_BLUE    14


int main(int argc, char *argv[])
{
    char buf[200];
    int i = 0;
    int red = 0;
    int green = 0;
    int blue = 0;
    int max_red = 0;
    int max_green = 0;
    int max_blue = 0;
    int color = 0;
    int game = 0;
    int listgameOK[2000];   //1 gamme possible, 0 game impossible
    int listgammepower[2000]; //somme des power de chaque gamme
    int sommegame = 0;
    int sommepower = 0;
    char tempstr[1000];

    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(listgameOK, 1, sizeof(listgameOK));  //On considere les games toutes possibles et on les élimine au fur et à mesure de l'analyse des sets en les mettant à 0

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 200, fic);
            //printf("%s, longueur = %d\n", buf, (int)strlen(buf));

            if(feof(fic))
            {
                break;
            }
            else
            {
                color = 0;
                red = 0;
                green = 0;
                blue = 0;
                max_red = 0;
                max_green = 0;
                max_blue = 0;

                //On obtient le numéro du game
                sscanf(buf, "%s %d", tempstr, &game);
                //printf("%s, string = %s, game = %d", buf, tempstr, game);
                printf("Game = %d", game);

                if(game==88)
                    printf(" ");

                for(i=7;i<strlen(buf);i++)
                {
                    //On recherche les couleurs
                    if(isdigit(buf[i]))
                    {
                        sscanf(&buf[i], "%d %s", &color, tempstr);

                        if(!strncmp(tempstr, "red", sizeof("red")-1))
                        {
                            red += color;
                            i += 2;
                        }
                        else if(!strncmp(tempstr, "green", sizeof("green")-1))
                        {
                            green += color;
                            i += 2;
                        }
                        else if(!strncmp(tempstr, "blue", sizeof("blue")-1))
                        {
                            blue += color;
                            i += 2;
                        }
                    }

                    //On recherche le ; pour remmettre à 0 les couleurs puisque les cubes sont remis dans le sac
                    if(buf[i] == ';' || buf[i] == '\n')
                    {
                        //printf(", red = %d, green = %d, blue = %d", red, green, blue);

                        //On compare si on a un nombre de cube qui ne dépasse pas la condition
                        if((red<=MAX_RED) && (green<=MAX_GREEN) && (blue<=MAX_BLUE))
                        {
                            printf(", set OK");
                        }
                        else
                        {
                            printf(", set PAS OK");
                            //On met la game à 0 dans la liste pour montrer qu'elle n'est pas possible
                            listgameOK[game] = 0;
                        }

                        if(max_red<red) max_red = red;
                        if(max_green<green) max_green = green;
                        if(max_blue<blue) max_blue = blue;

                        red = 0;
                        green = 0;
                        blue = 0;
                    }
                }
            }

            listgammepower[game] = max_red * max_green * max_blue;
            printf("power = %d\n", listgammepower[game]);
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    //On calcule la somme de toutes les game possibles
    for(i=1;i<=100;i++)
    {
        if(listgameOK[i] != 0)
        {
            sommegame += i;
        }

        sommepower += listgammepower[i];
    }

    printf("somme des games = %d\n", sommegame);
    printf("somme des power = %d\n", sommepower);

    fclose(fic);
    fic = NULL;

    return 0;
}
