#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    char buf1[100];
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int somme = 0;
    int somme2 = 0;


    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        while(!feof(fic))
        {
            fgets(buf1, 100, fic);
            printf("%s, longueur = %llu\n", buf1, strlen(buf1));

            sscanf(buf1, "%d-%d,%d-%d", &a, &b, &c, &d);
            printf("a=%d, b=%d, c=%d, d=%d\n", a, b, c, d);

            if((a<=c && d<=b) || (c<=a && b<=d))
            {
                somme += 1;
            }

            if(!((a<c && b<c) || (c<a && d<a)))
            {
                somme2 += 1;
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }

    printf("somme = %d\n", somme);
    printf("somme2 = %d\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
