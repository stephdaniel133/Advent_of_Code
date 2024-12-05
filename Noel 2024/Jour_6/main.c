#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


int searchNumber(int tab[], int number)
{
    int i = 0;

    for(i = 0; i<23 ; i++)
    {
        if(tab[i] == number)
            return i;
    }

    return 100;  //Le nombre de pages à tester est inférieur
}


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    int rulePage = 0;
    int rule[1200][2];
    int page[200][23];
    int pagenumber[200];
    bool truth1[200];
    bool truth2[200];
    int temp1 = 0;
    int temp2 = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    char c = 0;
    int index1 = 0;
    int index2 = 0;
    int stop = 1;


    memset(rule, 0, sizeof(rule));
    memset(page, 0, sizeof(page));
    memset(pagenumber, 0, sizeof(pagenumber));
    memset(truth1, 1, sizeof(truth1));    //Les lignes sont considérées bonnes


    //Récupération des valeurs dans le fichier data
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
                    //page[0][0] = temp1; //Le dernier scanf a récupérer le premier nombre
                    fseek(fic, -2, SEEK_CUR);
                    i = 0;
                    j = 0;
                }
            }
            else                        //On recupere les pages
            {
                fscanf(fic, "%d", &temp1);
                c = fgetc(fic);
                if(c == ',')        //Si on detecte une virgule après le nombre, il y en a encore
                {
                    page[i][j] = temp1;
                    pagenumber[i]++;
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

    //Impression des pages complètes
    /*for(i=0 ; i<194 ; i++)
    {
        for(j=0 ; j<23 ; j++)
        {
            printf("%02d ", page[i][j]);
        }
        printf("\n");
    }*/


    for(i=0 ; i<194 ; i++)   //Defilement des lignes de pages
    {
        for(k=0 ; k<1176 ; k++)   //Defilement des lignes des rules
        {
            index1 = searchNumber(page[i], rule[k][0]);
            index2 = searchNumber(page[i], rule[k][1]);

            if((index1 > index2) && (index1 != 100) && (index2 != 100))     //Si le nombre de gauche est à droite
            {
                truth1[i] = 0;   //La règle n'est pas respectée
                break;
            }
        }
    }

    //On additionne toutes les pages qui respectent les règles
    for(i=0 ; i<194 ; i++)
    {
        if(truth1[i] == 1)
            somme1 += page[i][pagenumber[i]/2];
    }


    printf("somme1 = %lld\n", somme1);



    //--------------Part 2-----------------
    stop = 1;

    while(stop != 0)    //On repete les permutations jusqu'à ce que toutes les règles sont respectées
    {
        for(i=0 ; i<194 ; i++)   //Defilement des lignes de pages
        {
            for(k=0 ; k<1176 ; k++)   //Defilement des lignes des rules
            {
                index1 = searchNumber(page[i], rule[k][0]);
                index2 = searchNumber(page[i], rule[k][1]);

                if((index1 > index2) && (index1 != 100) && (index2 != 100))     //Si le nombre de gauche est à droite
                {
                    int temp = 0;
                    temp = page[i][index1];   //La règle n'est pas respectée donc on permute les valeurs
                    page[i][index1] = page[i][index2];
                    page[i][index2] = temp;
                    break;
                }
            }
        }

        memset(truth2, 1, sizeof(truth1));
        stop = 0;

        //On vérifie les règles s'ils elles sont toutes bonnes (A commenter)
        for(i=0 ; i<194 ; i++)   //Defilement des lignes de pages
        {
            for(k=0 ; k<1176 ; k++)   //Defilement des lignes des rules
            {
                index1 = searchNumber(page[i], rule[k][0]);
                index2 = searchNumber(page[i], rule[k][1]);

                if((index1 > index2) && (index1 != 100) && (index2 != 100))     //Si le nombre de gauche est à droite
                {
                    truth2[i] = 0;   //La règle n'est pas respectée
                    stop++;
                    break;
                }
            }
        }
    }


    //Les règles sont toutes bonnes, on additionne toutes les pages qui ne respectaient pas les règles de la question précédente
    for(i=0 ; i<194 ; i++)
    {
        if(truth1[i] == 0)
        {
            somme2 += page[i][pagenumber[i]/2];
        }
        //printf("truth1[%d] = %d, %d\n", i, truth1[i], truth2[i]);
    }

    printf("somme2 = %lld\n", somme2);

    return 0;
}
