#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TAILLE  99


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    int buf[TAILLE][TAILLE];
    int visible[TAILLE][TAILLE];
    int visible_haut[TAILLE][TAILLE];
    int visible_bas[TAILLE][TAILLE];
    int visible_gauche[TAILLE][TAILLE];
    int visible_droite[TAILLE][TAILLE];
    int scene_score[TAILLE][TAILLE];
    int somme = TAILLE+TAILLE+(TAILLE-2)+(TAILLE-2);
    int max = 0;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;


    memset(visible, 0, sizeof(visible));
    memset(visible_haut, 0, sizeof(visible));
    memset(visible_bas, 0, sizeof(visible));
    memset(visible_droite, 0, sizeof(visible));
    memset(visible_gauche, 0, sizeof(visible));


    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                buf[i][j] = fgetc(fic) - 48;
                printf("%d", buf[i][j]);
            }
            fgetc(fic);
            printf("\n");
        }
        printf("\n");


        printf("Tab[y=2][x=3] %d\n\n", buf[2][3]);


        //Vers le haut
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            for(j=1 ; j<=TAILLE-2 ; j++)
            {
                //Calcul vers le haut
                max = buf[i][j];

                for(k=i-1 ; k>=0 ; k--)
                {
                    visible_haut[i][j] += 1;

                    a = buf[k][j];
                    if(a>=max)
                    {
                        break;
                    }
                }
            }
        }

        printf("Tableau haut :\n");
        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible_haut[i][j]);
            }
            printf("\n");
        }
        printf("\n");



        //Vers le bas
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            for(j=1 ; j<=TAILLE-2 ; j++)
            {
                //Calcul vers le haut
                max = buf[i][j];

                for(k=i+1 ; k<=TAILLE-1 ; k++)
                {
                    visible_bas[i][j] += 1;

                    a = buf[k][j];
                    if(a>=max)
                    {
                        break;
                    }
                }
            }
        }

        printf("Tableau bas :\n");
        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible_bas[i][j]);
            }
            printf("\n");
        }
        printf("\n");



        //Vers la gauche
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            for(j=1 ; j<=TAILLE-2 ; j++)
            {
                //Calcul vers le haut
                max = buf[i][j];

                for(k=j-1 ; k>=0 ; k--)
                {
                    visible_gauche[i][j] += 1;

                    a = buf[i][k];
                    if(a>=max)
                    {
                        break;
                    }
                }
            }
        }

        printf("Tableau gauche :\n");
        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible_gauche[i][j]);
            }
            printf("\n");
        }
        printf("\n");



        //Vers la droite
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            for(j=1 ; j<=TAILLE-2 ; j++)
            {
                //Calcul vers le haut
                max = buf[i][j];

                for(k=j+1 ; k<=TAILLE-1 ; k++)
                {
                    visible_droite[i][j] += 1;

                    a = buf[i][k];
                    if(a>=max)
                    {
                        break;
                    }
                }
            }
        }

        printf("Tableau droite :\n");
        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible_droite[i][j]);
            }
            printf("\n");
        }
        printf("\n");


        //On multiplie les 4 dimensions et on cherche le max
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            for(j=1 ; j<=TAILLE-2 ; j++)
            {
                visible[i][j] = visible_haut[i][j] * visible_bas[i][j] * visible_gauche[i][j] * visible_droite[i][j];
                if(visible[i][j] > max)
                    max = visible[i][j];
            }
        }


        printf("Tableau final :\n");

        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible[i][j]);
            }
            printf("\n");
        }

    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }


    printf("max = %d\n", max);

    printf("\nfin\n");
    fclose(fic);
    fic = NULL;

    return 0;
}



/*        printf("somme pourtour = %d\n", somme);


////////////////////////////////////////////////////////////////////
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            max = buf[i][0];

            for(j=1 ; j<=TAILLE-2 ; j++)
            {
                if(buf[i][j]>max && visible[i][j]==1)
                {
                    max = buf[i][j];
                }
                if(buf[i][j]>max && visible[i][j]==0)
                {
                    somme +=1;
                    max = buf[i][j];
                    visible[i][j] = 1;
                }
            }
        }

        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible[i][j]);
            }
            printf("\n");
        }
        printf("somme de gauche a droite = %d\n", somme);


////////////////////////////////////////////////////////////////////
        for(i=1 ; i<=TAILLE-2 ; i++)
        {
            max = buf[i][TAILLE-1];

            for(j=TAILLE-2 ; j>=1 ; j--)
            {
                if(buf[i][j]>max && visible[i][j]==1)
                {
                    max = buf[i][j];
                }
                if(buf[i][j]>max && visible[i][j]==0)
                {
                    somme +=1;
                    max = buf[i][j];
                    visible[i][j] = 1;
                }
            }
        }

        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible[i][j]);
            }
            printf("\n");
        }
        printf("somme de droite a gauche = %d\n", somme);


////////////////////////////////////////////////////////////////////
        for(j=1 ; j<=TAILLE-2 ; j++)
        {
            max = buf[0][j];

            for(i=1 ; i<=TAILLE-2 ; i++)
            {
                if(buf[i][j]>max && visible[i][j]==1)
                {
                    max = buf[i][j];
                }
                if(buf[i][j]>max && visible[i][j]==0)
                {
                    somme +=1;
                    max = buf[i][j];
                    visible[i][j] = 1;
                }
            }
        }

        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible[i][j]);
            }
            printf("\n");
        }
        printf("somme de haut en bas = %d\n", somme);


////////////////////////////////////////////////////////////////////
        for(j=1 ; j<=TAILLE-2 ; j++)
        {
            max = buf[TAILLE-1][j];

            for(i=TAILLE-2 ; i>=1 ; i--)
            {
                if(buf[i][j]>max && visible[i][j]==1)
                {
                    max = buf[i][j];
                }
                if(buf[i][j]>max && visible[i][j]==0)
                {
                    somme +=1;
                    max = buf[i][j];
                    visible[i][j] = 1;
                }
            }
        }

        for(i=0 ; i<TAILLE ; i++)
        {
            for(j=0 ; j<TAILLE ; j++)
            {
                printf("%d", visible[i][j]);
            }
            printf("\n");
        }
        printf("somme de bas en haut = %d\n", somme);
////////////////////////////////////////////////////////////////////
*/
