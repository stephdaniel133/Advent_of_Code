#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int i = 0;
    int j = 0;
    char buf[4096];
    char buf1[20];
    char a, b, c, d;
    int trouve = 0;
    char *rep = NULL;


    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        fgets(buf, 4096, fic);
        printf("%s\n", buf);

        for(i=0 ; i<4096-14 ; i++)
        {
            //a = buf[i]; b=buf[i+1]; c=buf[i+2]; d=buf[i+3];
            //printf("caractere %d = %c\n", i, buf[i]);
            //printf("caractere %d = %c\n", i+1, buf[i+1]);
            //printf("caractere %d = %c\n", i+2, buf[i+2]);
            //printf("caractere %d = %c\n", i+3, buf[i+3]);

            //if((a != b) && (a != c) && (a != d) && (b!=c) && (b!=d) && (c!=d))
            //    break;

            memset(buf1, 0, sizeof(buf1));

            strncpy(buf1, buf+i, 14);
            printf("chaine = %s\n", buf1);

            for(j=0 ; j<14 ; j++)
            {
                printf("caractere teste = %c\n", *(buf1+j));

                rep = strchr(buf1+j+1, *(buf1+j));

                if(NULL != rep)
                {
                    break;
                }
            }

            if(j == 14)
                break;
        }

        printf("first marker after character %d\n", i+14);


    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }


    printf("\nfin\n");
    fclose(fic);
    fic = NULL;

    return 0;
}
