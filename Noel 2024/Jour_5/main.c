#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    int rulePage = 0;
    int rule[1200][2];
    int page[200][50];
    int temp1 = 0;
    int temp2 = 0;
    int i = 0;
    int j = 0;
    char c = 0;


    memset(rule, 0, sizeof(rule));
    memset(page, 0, sizeof(page));


    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            if(rulePage == 0)           //On recupere les rules
            {
                temp1 = 0;
                temp2 = 0;
                fscanf(fic, "%d|%d", &temp1, &temp2);
                if((temp1 != 0) && (temp2 != 0))
                {
                    rule[i][0] = temp1;
                    rule[i][1] = temp2;
                    i++;
                }
                else        //On a atteint le saut de ligne separant les pages des rules
                {
                    rulePage = 1;
                    printf("Fin rules, rule[0] = %d|%d, rule[%d] = %d|%d\n", rule[0][0], rule[0][1], i-1, rule[i-1][0], rule[i-1][1]);
                    page[0][0] = temp1; //Le dernier scanf a récupérer le premier nombre
                }
            }
            else                        //On recupere les pages
            {
                fscanf(fic, "%d", &temp1);
                c = getchar();
                if(c == ',')        //Si on detecte une virgule après le nombre, il y en a encore
                {
                    page[i][j] = temp1;
                    j++;
                }
                else                //Sinon on passe sur la liste de pages suivantes
                {
                    page[i][j] = temp1;
                    i++;
                    j = 0;
                }
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }
    fclose(fic);
    fic = NULL;






    printf("somme1 = %lld\n", somme1);





    //--------------Part 2-----------------
    fic = fopen("data.txt", "r");




    printf("somme2 = %lld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
