#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    char buf1[100];
    char buf2[100];
    char buf3[100];
    char *ptn = NULL;
    char *ptn2 = NULL;
    int i = 0;
    int j = 0;
    int somme = 0;


    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        while(!feof(fic))
        {
            ptn = NULL;
            ptn2 = NULL;
            memset(buf1, 0, sizeof(buf1));
            memset(buf2, 0, sizeof(buf2));
            memset(buf3, 0, sizeof(buf3));

            fgets(buf1, 100, fic);
            printf("%s, longueur = %llu\n", buf1, strlen(buf1));

            fgets(buf2, 100, fic);
            printf("%s, longueur = %llu\n", buf2, strlen(buf2));

            fgets(buf3, 100, fic);
            printf("%s, longueur = %llu\n", buf3, strlen(buf3));


            for(i=0;i<strlen(buf1);i++)
            {
                ptn = strchr(buf2, *(buf1+i));
                if(ptn!=NULL)
                {
                    ptn2 = strchr(buf3, *ptn);
                    if(ptn2!=NULL)
                        break;
                }
            }

            printf("Caractere trouve = %c\n\n", *ptn2);

            if(96<*ptn2 && *ptn2<123)
            {
                somme += *ptn2 - 96;
            }
            else if(64<*ptn2 && *ptn2<91)
            {
                somme += *ptn2 - 38;
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }

    printf("somme = %d", somme);

    fclose(fic);
    fic = NULL;

    return 0;
}

//int main(int argc, char *argv[])
//{
//    FILE *fic = NULL;
//    char buf[100];
//    char buf1[100];
//    char buf2[100];
//    char *ptn = NULL;
//    int i = 0;
//    int somme_1 = 0;
//
//
//    fic = fopen("nouveau.txt", "r");
//
//    if(fic != NULL)
//    {
//        printf("fichier ouvert\n\n");
//
//        while(!feof(fic))
//        {
//            fgets(buf, 100, fic);
//            printf("%s, longueur = %llu\n", buf, strlen(buf));
//
//            memset(buf1, 0, sizeof(buf1));
//            memset(buf2, 0, sizeof(buf2));
//
//            strncpy(buf1, buf, strlen(buf)/2);
//            printf("buf1 = %s\n", buf1);
//            strncpy(buf2, buf + strlen(buf)/2, strlen(buf + strlen(buf)/2));
//            printf("buf2 = %s\n", buf2);
//
//            for(i=0;i<strlen(buf1);i++)
//            {
//                ptn = strchr(buf2, *(buf1+i));
//                if(ptn!=NULL)
//                    break;
//            }
//
//            printf("Caractere trouve = %c\n\n", *ptn);
//
//            if(96<*ptn && *ptn<123)
//            {
//                somme_1 += *ptn - 96;
//            }
//            else if(64<*ptn && *ptn<91)
//            {
//                somme_1 += *ptn - 38;
//            }
//        }
//    }
//    else
//    {
//        printf("Impossible d'ouvrir le fichier\n");
//    }
//
//    printf("somme_1 = %d", somme_1);
//
//    fclose(fic);
//    fic = NULL;
//
//    return 0;
//}
