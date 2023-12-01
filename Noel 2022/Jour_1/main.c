#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char buf[80];
    int nbr_elf = 1;
    int calorie = 0;
    int somme_calorie = 0;
    int max_calorie_1 = 0;
    int max_calorie_2 = 0;
    int max_calorie_3 = 0;
    FILE *fic = NULL;

    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 10, fic);
            //printf("%s, longueur = %d\n", buf, strlen(buf));

            //if(strlen(buf) == 1)
            if(!strcmp(buf, "\n"))
            {
                printf("Elf %d : somme_calorie = %d\n", nbr_elf, somme_calorie);
                if(somme_calorie > max_calorie_1)
                {
                    max_calorie_3 = max_calorie_2;
                    max_calorie_2 = max_calorie_1;
                    max_calorie_1 = somme_calorie;
                    printf("\tNouveau max_calorie_1 = %d, max_calorie_2 = %d, max_calorie_3 = %d\n", max_calorie_1, max_calorie_2, max_calorie_3);
                }
                else if(somme_calorie > max_calorie_2)
                {
                    max_calorie_3 = max_calorie_2;
                    max_calorie_2 = somme_calorie;
                    printf("\tNouveau max_calorie_1 = %d, max_calorie_2 = %d, max_calorie_3 = %d\n", max_calorie_1, max_calorie_2, max_calorie_3);
                }
                else if(somme_calorie > max_calorie_3)
                {
                    max_calorie_3 = somme_calorie;
                    printf("\tNouveau max_calorie_1 = %d, max_calorie_2 = %d, max_calorie_3 = %d\n", max_calorie_1, max_calorie_2, max_calorie_3);
                }

                nbr_elf++;
                somme_calorie = 0;
            }
            else if(feof(fic))
            {
                sscanf(buf, "%d", &calorie);
                somme_calorie += calorie;
                printf("Elf %d : somme_calorie = %d\n", nbr_elf, somme_calorie);
                if(somme_calorie > max_calorie_1)
                {
                    max_calorie_1 = somme_calorie;
                    printf("\tNouveau max_calorie_1 = %d\n", max_calorie_1);
                }

                nbr_elf++;
            }
            else
            {
                sscanf(buf, "%d", &calorie);
                somme_calorie += calorie;
                //printf("somme_calorie = %d\n", somme_calorie);
            }
        }

        printf("Somme des calorie des 3 premiers elfs = %d\n", max_calorie_1+max_calorie_2+max_calorie_3);

    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }

    printf("nbr_elf = %d\n", nbr_elf - 1);

    fclose(fic);
    fic = NULL;

    return 0;
}
