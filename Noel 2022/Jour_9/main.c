#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAILLE_X  10000
#define TAILLE_Y  10000
//#define TAILLE_X  26
//#define TAILLE_Y  21
//#define TAILLE_X  6
//#define TAILLE_Y  5

#define NBR_MAILLON 10
//#define NBR_MAILLON 2

typedef struct Coordonnee Coordonnee;
struct Coordonnee
{
    int x;
    int y;
};

int mem[TAILLE_X][TAILLE_Y];
char debug[TAILLE_X][TAILLE_Y];


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    int x = 0;
    int y = 0;
    int somme = 0;
    int deplacement;
    int nombre = 0;
    char buf[20];

    Coordonnee H[NBR_MAILLON] = {{TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}, {TAILLE_X/2, TAILLE_Y/2}};
    //Coordonnee H[NBR_MAILLON] = {{11, 5}, {11, 5}, {11, 5}, {11, 5}, {11, 5}, {11, 5}, {11, 5}, {11, 5}, {11, 5}, {11, 5}};
    //Coordonnee H[NBR_MAILLON] = {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}};


    memset(mem, 0, sizeof(mem));

    printf("Debut\n\n");

    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        while(!feof(fic))
        {

            fgets(buf, 20, fic);
            deplacement = buf[0];
            sscanf(buf+1, "%d", &nombre);
            //printf("Deplacement lu %c %d\n", deplacement, nombre);

            for(i=0 ; i<nombre ; i++)
            {
                if(deplacement == 'U')
                {
                    H[0].y++;

                    if(H[1].y < H[0].y-1)           //THT
                    {                               //ThT
                        H[1].y++;                   //TTT
                        H[1].x = H[0].x;
                    }
                }
                else if(deplacement == 'D')
                {
                    H[0].y--;

                    if(H[0].y+1 < H[1].y)           //TTT
                    {                               //ThT
                        H[1].y--;                   //THT
                        H[1].x = H[0].x;
                    }
                }
                else if(deplacement == 'L')
                {
                    H[0].x--;

                    if(H[0].x+1 < H[1].x)           //TTT
                    {                               //HhT
                        H[1].x--;                   //TTT
                        H[1].y = H[0].y;
                    }
                }
                else if(deplacement == 'R')
                {
                    H[0].x++;

                    if(H[1].x < H[0].x-1)           //TTT
                    {                               //ThH
                        H[1].x++;                   //TTT
                        H[1].y = H[0].y;
                    }
                }

                //On bouge les maillons
                if(NBR_MAILLON>2)
                {
                    for(k=2 ; k<NBR_MAILLON ; k++)
                    {
                        //Deplacement en diagonale haut droite
                        if(H[k].x < H[k-1].x-1 && H[k].y < H[k-1].y-1)
                        {
                            H[k].x++;
                            H[k].y++;
                        }

                        //Deplacement en diagonale haut gauche
                        else if(H[k-1].x+1 < H[k].x && H[k].y < H[k-1].y-1)
                        {
                            H[k].x--;
                            H[k].y++;
                        }

                        //Deplacement en diagonale bas droite
                        else if(H[k].x < H[k-1].x-1 && H[k-1].y+1 < H[k].y)
                        {
                            H[k].x++;
                            H[k].y--;
                        }

                        //Deplacement en diagonale bas gauche
                        else if(H[k-1].x+1 < H[k].x && H[k-1].y+1 < H[k].y)
                        {
                            H[k].x--;
                            H[k].y--;
                        }

                        //Deplacement des maillons en haut (U)
                        else if(H[k].y < H[k-1].y-1)    //THT
                        {                               //ThT
                            H[k].y++;                   //TTT
                            H[k].x = H[k-1].x;
                        }

                        //Deplacement des maillons en bas (D)
                        else if(H[k-1].y+1 < H[k].y)    //TTT
                        {                               //ThT
                            H[k].y--;                   //THT
                            H[k].x = H[k-1].x;
                        }

                        //Deplacement des maillons à gauhe (L)
                        else if(H[k-1].x+1 < H[k].x)    //TTT
                        {                               //HhT
                            H[k].x--;                   //TTT
                            H[k].y = H[k-1].y;
                        }

                        //Deplacement des maillons à droite (R)
                        else if(H[k].x < H[k-1].x-1)    //TTT
                        {                               //ThH
                            H[k].x++;                   //TTT
                            H[k].y = H[k-1].y;
                        }
                    }
                }

                mem[H[NBR_MAILLON-1].x][H[NBR_MAILLON-1].y] = 1;


                memset(debug, '.', sizeof(debug));
                debug[H[9].x][H[9].y] = '9';
                debug[H[8].x][H[8].y] = '8';
                debug[H[7].x][H[7].y] = '7';
                debug[H[6].x][H[6].y] = '6';
                debug[H[5].x][H[5].y] = '5';
                debug[H[4].x][H[4].y] = '4';
                debug[H[3].x][H[3].y] = '3';
                debug[H[2].x][H[2].y] = '2';
                debug[H[1].x][H[1].y] = '1';
                debug[H[0].x][H[0].y] = 'H';

                /*for(y=TAILLE_Y-1 ; y>=0 ; y--)
                {
                    for(x=0 ; x<TAILLE_X ; x++)
                    {
                        printf("%c", debug[x][y]);
                    }
                    printf("\n");
                }

                printf("\n");*/
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
        return(EXIT_FAILURE);
    }


    //printf("position H(%d;%d) et T(%d,%d)\n", H.x, H.y, T.x, T.y);

    somme = 0;
    for(y=TAILLE_Y-1 ; y>=0 ; y--)
    {
        for(x=0 ; x<TAILLE_X ; x++)
        {
            //printf("%d", mem[x][y]);
            if(mem[x][y] == 1)
                somme++;
        }
        //printf("\n");
    }
    printf("Nombre de cases utilisees = %d", somme);

    printf("\nfin\n");
    fclose(fic);
    fic = NULL;

    return(EXIT_SUCCESS);
}
