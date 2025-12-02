#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    char buf1[100];
    char buf2[100];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    int64_t nbrligne = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    int64_t tab1[2000];
    int64_t tab2[2000];
    int64_t tab3[2000];
    int64_t tab4[2000];


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));
    memset(tab3, 0, sizeof(tab3));
    memset(tab4, 0, sizeof(tab4));

    i = sizeof("one");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            //fgets(buf, 100, fic);

            if(feof(fic))
            {
                break;
            }
            else
            {
                fscanf(fic, "%ld-%ld,", &tab1[nbrligne], &tab2[nbrligne]);
                char temp1[100];
                char temp2[100];
                sprintf(temp1, "%ld", tab1[nbrligne]);
                sprintf(temp2, "%ld", tab2[nbrligne]);
                printf("nbr1= %ld, nbr2= %ld, taille1= %d, taille2= %d\n", tab1[nbrligne], tab2[nbrligne], (int)strlen(temp1), (int)strlen(temp2));
            }

            nbrligne++;
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");

    //On trie pour mettre les valeurs inférieure dans le tableau 1
    for(i=0 ; i<nbrligne ; i++)
    {
        if(tab1[i] > tab2[i])
        {
            int temp = tab1[i];
            tab1[i] = tab2[i];
            tab2[i] = temp;
            printf("Change\n");
        }
        printf("nbr1= %ld, nbr2= %ld\n", tab1[i], tab2[i]);
    }

    //On cherche les invalids ID
    for(i=0 ; i<nbrligne ; i++)
    {
        for(j=tab1[i] ; j<tab2[i]+1 ; j++)  //On fait défiler tous le range entre les 2 nombres
        {
            sprintf(buf1, "%ld", j);

            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/2);

            if(0 == strncmp(buf1, buf1+strlen(buf1)/2, strlen(buf1)/2) && (0 == strlen(buf1)%2))
            {
                printf("Invalid ID: %ld\n", j);
                tab3[k++] = j;
            }
        }
    }

    for(i=0 ; i<k ; i++)
    {
        somme1 += tab3[i];
    }

    printf("somme1 = %ld\n\n\n", somme1);


    //--------------Part 2-----------------
    //On cherche les invalids ID
    k = 0;

    for(i=0 ; i<nbrligne ; i++)
    {
        for(j=tab1[i] ; j<tab2[i]+1 ; j++)  //On fait défiler tous le range entre les 2 nombres
        {
            sprintf(buf1, "%ld", j);

            //Detection d'une sequence double
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/2);
            if((strlen(buf1) >= 2) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/2, strlen(buf1)/2)) &&
               (0 == strlen(buf1)%2))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence triple
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/3);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/3);
            if((strlen(buf1) >= 3) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/3, strlen(buf1)/3)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/3, strlen(buf1)/3)) &&
               (0 == strlen(buf1)%3))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence quadruple
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/4);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/4);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/4);
            if((strlen(buf1) >= 4) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/4, strlen(buf1)/4)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/4, strlen(buf1)/4)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/4, strlen(buf1)/4)) &&
               (0 == strlen(buf1)%4))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence cinq
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+4*strlen(buf1)/5);
            if((strlen(buf1) >= 5) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/5, strlen(buf1)/5)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/5, strlen(buf1)/5)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/5, strlen(buf1)/5)) &&
               (0 == strncmp(buf1, buf1+4*strlen(buf1)/5, strlen(buf1)/5)) &&
               (0 == strlen(buf1)%5))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence six
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+4*strlen(buf1)/5);
            if((strlen(buf1) >= 6) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/6, strlen(buf1)/6)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/6, strlen(buf1)/6)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/6, strlen(buf1)/6)) &&
               (0 == strncmp(buf1, buf1+4*strlen(buf1)/6, strlen(buf1)/6)) &&
               (0 == strncmp(buf1, buf1+5*strlen(buf1)/6, strlen(buf1)/6)) &&
               (0 == strlen(buf1)%6))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence sept
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+4*strlen(buf1)/5);
            if((strlen(buf1) >= 7) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/7, strlen(buf1)/7)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/7, strlen(buf1)/7)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/7, strlen(buf1)/7)) &&
               (0 == strncmp(buf1, buf1+4*strlen(buf1)/7, strlen(buf1)/7)) &&
               (0 == strncmp(buf1, buf1+5*strlen(buf1)/7, strlen(buf1)/7)) &&
               (0 == strncmp(buf1, buf1+6*strlen(buf1)/7, strlen(buf1)/7)) &&
               (0 == strlen(buf1)%7))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence huit
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+4*strlen(buf1)/5);
            if((strlen(buf1) >= 8) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strncmp(buf1, buf1+4*strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strncmp(buf1, buf1+5*strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strncmp(buf1, buf1+6*strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strncmp(buf1, buf1+7*strlen(buf1)/8, strlen(buf1)/8)) &&
               (0 == strlen(buf1)%8))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence neuf
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+4*strlen(buf1)/5);
            if((strlen(buf1) >= 9) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+4*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+5*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+6*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+7*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strncmp(buf1, buf1+8*strlen(buf1)/9, strlen(buf1)/9)) &&
               (0 == strlen(buf1)%9))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }

            //Detection d'une sequence dix
            //printf("chaine1: %s\n", buf1);
            //printf("chaine2: %s\n", buf1+strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+2*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+3*strlen(buf1)/5);
            //printf("chaine2: %s\n", buf1+4*strlen(buf1)/5);
            if((strlen(buf1) >= 10) &&
               (0 == strncmp(buf1, buf1+strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+2*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+3*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+4*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+5*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+6*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+7*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+8*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strncmp(buf1, buf1+9*strlen(buf1)/10, strlen(buf1)/10)) &&
               (0 == strlen(buf1)%10))
            {
                printf("Invalid ID: %ld\n", j);
                tab4[k++] = j;
                //break;
            }
        }
    }

    //On élimine les ID en apparaissant plusieurs fois
    for(i=0 ; i<k ; i++)
    {
        for(j=i+1 ; j<k ; j++)
        {
            if(tab4[i] == tab4[j])
            {
                tab4[j] = 0;
            }
        }
    }

    for(i=0 ; i<k ; i++)
    {
        somme2 += tab4[i];
    }

    printf("somme2 = %ld\n", somme2);


    fclose(fic);
    fic = NULL;

    return 0;
}
