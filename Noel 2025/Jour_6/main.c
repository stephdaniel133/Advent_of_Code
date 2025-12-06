#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

//#define NBR_LIGNES 3
//#define NBR_CALCULS 4
#define NBR_LIGNES 4
#define NBR_CALCULS 1000


int main(int argc, char *argv[])
{
    char buf1[NBR_LIGNES+1][3800];    //Les lignes ne dépassent pas 3781 caractères
    char buf2[3800][NBR_LIGNES+1];
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    int64_t tab1[5][1010];
    char tab2[1010];
    int tab3[4];
    //int64_t tab4[NBR_LIGNES];
    char c = 0;
    int len = 0;

    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    memset(tab1, 0, sizeof(tab1));
    memset(tab2, 0, sizeof(tab2));
    memset(tab3, 0, sizeof(tab3));


    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //On récupère les nombres
        for(i=0 ; i<NBR_LIGNES ; i++)
        {
            for(j=0 ; j<NBR_CALCULS ; j++)
            {
                fscanf(fic, "%ld", &tab1[i][j]);
            }
        }

        //On récupère les opérandes
        i = 0;
        do
        {
            if((c == '+') || (c == '*'))
            {
                tab2[i] = c;
                i++;
            }
            c = getc(fic);
        }
        while(!feof(fic));
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");

    //Vérification des tableaux
    printf("nombre lignes = %d\n", NBR_LIGNES);
    printf("nombre calculs = %d\n", NBR_CALCULS);
    //printf("calculs = %s\n", tab2);

    for(i=0 ; i<NBR_LIGNES ; i++)
    {
        printf("premier ligne %ld = %ld\n", i, tab1[i][0]);
        printf("dernier ligne %ld = %ld\n", i, tab1[i][NBR_CALCULS-1]);
    }


    //--------------Part 1-----------------
    int64_t temp = 0;
    for(j=0 ; j<NBR_CALCULS ; j++)
    {
        if(tab2[j] == '+')
        {
            temp = tab1[0][j];
            for(i=1 ; i<NBR_LIGNES ; i++)
            {
                temp += tab1[i][j];
            }
        }
        else
        {
            temp = tab1[0][j];
            for(i=1 ; i<NBR_LIGNES ; i++)
            {
                temp *= tab1[i][j];
            }
        }
        somme1 += temp;
    }

    printf("somme1 = %ld\n\n\n", somme1);

    //--------------Part 2-----------------
    //On relit le fichier et on le met dans un tableau de caractères
    fseek(fic, 0, SEEK_SET); // Retourne au début du fichier

    for(i=0 ; i<NBR_LIGNES+1 ; i++)
    {
        fgets(buf1[i], 3800, fic);
        buf1[i][strcspn(buf1[i], "\n")] = '\0';
        //printf("%s\n", buf1[i]);
    }

    len = strlen(buf1[0]);
    printf("longueur de la ligne 1 : %d\n", len);
    /*for(i=0 ; i<NBR_LIGNES ; i++)
    {
        printf("dernier caractere de la ligne %ld : %c\n", i, buf1[i][len-1]);
    }*/

    //On transpose le tableau afin de lire les nombres comme dans une chaine de caractères normale
    for(j=len-1 ; j>=0 ; j--)
    {
        for(i=0 ; i<NBR_LIGNES ; i++)
        {
            buf2[len-1-j][i] = buf1[i][j];
            //printf("%c", buf2[len-1-j][i]);
        }
        //printf("\n");
    }

    //k pointe sur l'index de l'opération du tableau tab2
    k = 0;
    for(i=0 ; i<len ; i++)
    {
        if(strncmp(buf2[i], "     ", NBR_LIGNES))  //Si on lit autre chose que des espaces
        {
            sscanf(buf2[i], "%d", &tab3[k]);
            k++;
        }
        if(buf1[NBR_LIGNES][len-i-1] != ' ')  //On fait le calcul lorsqu'on a un opérande dans buf1
        {
            if(buf1[NBR_LIGNES][len-i-1] == '+')
            {
                int64_t result = 0;
                result = tab3[0] + tab3[1] + tab3[2] + tab3[3];
                somme2 += result;
                k = 0;
                memset(tab3, 0, sizeof(tab3));  //On efface le tableau pour recommencer
            }
            else if(buf1[NBR_LIGNES][len-i-1] == '*')
            {
                int64_t result = 0;
                //Il n'y a pas de 0 dans le fichier d'épreuve donc si une valeur est à 0 dans tab3, il ne faut pas la prendre
                result = tab3[0] * tab3[1];
                if(tab3[2] !=0)
                    result *= tab3[2];
                if(tab3[3] !=0 && NBR_LIGNES == 4)
                    result *= tab3[3];
                somme2 += result;
                k = 0;
                memset(tab3, 0, sizeof(tab3));  //On efface le tableau pour recommencer
            }
        }
    }

    printf("somme2 = %ld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}
