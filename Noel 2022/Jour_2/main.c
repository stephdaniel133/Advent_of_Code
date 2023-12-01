#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
score_1 table score
AX -> 1+3=4
AY -> 2+6=8
AZ -> 3+0=3
BX -> 1+0=1
BY -> 2+3=5
BZ -> 3+6=9
CX -> 1+6=7
CY -> 2+0=2
CZ -> 3+3=6

score_2 table score
AX -> +0=  (perd)
AY -> +3=  (égalité)
AZ -> +6=  (gagne)
BX -> +0=  (perd)
BY -> +3=  (égalité)
BZ -> +6=  (gagne)
CX -> +0=  (perd)
CY -> +3=  (égalité)
CZ -> +6=  (gagne)
*/


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    char buf[10];
    int score_1 = 0;
    int score_2 = 0;
    char joueur_1 = '\0';
    char joueur_2 = '\0';


    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 10, fic);
            //printf("%s, longueur = %llu\n", buf, strlen(buf));
            sscanf(buf, "%c %c", &joueur_1, &joueur_2);
            printf("joueur_1 = %c, joueur_2 = %c\n", joueur_1, joueur_2);

            if(joueur_1 == 'A' && joueur_2 == 'X')
            {
                score_1 += 4;
                score_2 += 3;
            }
            else if(joueur_1 == 'A' && joueur_2 == 'Y')
            {
                score_1 += 8;
                score_2 += 4;
            }
            else if(joueur_1 == 'A' && joueur_2 == 'Z')
            {
                score_1 += 3;
                score_2 += 8;
            }
            else if(joueur_1 == 'B' && joueur_2 == 'X')
            {
                score_1 += 1;
                score_2 += 1;
            }
            else if(joueur_1 == 'B' && joueur_2 == 'Y')
            {
                score_1 += 5;
                score_2 += 5;
            }
            else if(joueur_1 == 'B' && joueur_2 == 'Z')
            {
                score_1 += 9;
                score_2 += 9;
            }
            else if(joueur_1 == 'C' && joueur_2 == 'X')
            {
                score_1 += 7;
                score_2 += 2;
            }
            else if(joueur_1 == 'C' && joueur_2 == 'Y')
            {
                score_1 += 2;
                score_2 += 6;
            }
            else if(joueur_1 == 'C' && joueur_2 == 'Z')
            {
                score_1 += 6;
                score_2 += 7;
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }

    printf("score_1 = %d\n", score_1);
    printf("score_2 = %d\n", score_2);

    fclose(fic);
    fic = NULL;

    return 0;
}
