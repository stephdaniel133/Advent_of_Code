#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


//#define NBR_LINES   10
//#define NBR_COL     10
#define NBR_LINES   140
#define NBR_COL     140

int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    int i = 0;
    int j = 0;
    char tab[NBR_LINES][NBR_COL];
    char c = 0;


    memset(tab, 0, sizeof(tab));

    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            for(i=0 ; i<NBR_LINES ; i++)
                fscanf(fic, "%s", tab[i]);
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    fclose(fic);
    fic = NULL;


    //On cherche dans les lignes le mot XMAS à l'endroit
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<(NBR_COL-strlen("XMAS")+1) ; j++)
        {
            if((tab[i][j] == 'X') && (tab[i][j+1] == 'M') && (tab[i][j+2] == 'A') && (tab[i][j+3] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les lignes le mot XMAS à l'envers
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=0 ; j<(NBR_COL-strlen("XMAS")+1) ; j++)
        {
            if((tab[i][j+3] == 'X') && (tab[i][j+2] == 'M') && (tab[i][j+1] == 'A') && (tab[i][j] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les colonnes le mot XMAS à l'endroit
    for(i=0 ; i<(NBR_LINES-strlen("XMAS")+1) ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if((tab[i][j] == 'X') && (tab[i+1][j] == 'M') && (tab[i+2][j] == 'A') && (tab[i+3][j] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les colonnes le mot XMAS à l'envers
    for(i=0 ; i<(NBR_LINES-strlen("XMAS")+1) ; i++)
    {
        for(j=0 ; j<NBR_COL ; j++)
        {
            if((tab[i+3][j] == 'X') && (tab[i+2][j] == 'M') && (tab[i+1][j] == 'A') && (tab[i][j] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les diagonales descendantes à droite le mot XMAS à l'endroit
    for(i=0 ; i<(NBR_LINES-strlen("XMAS")+1) ; i++)
    {
        for(j=0 ; j<(NBR_COL-strlen("XMAS")+1) ; j++)
        {
            if((tab[i][j] == 'X') && (tab[i+1][j+1] == 'M') && (tab[i+2][j+2] == 'A') && (tab[i+3][j+3] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les diagonales descendantes à droite le mot XMAS à l'envers
    for(i=0 ; i<(NBR_LINES-strlen("XMAS")+1) ; i++)
    {
        for(j=0 ; j<(NBR_COL-strlen("XMAS")+1) ; j++)
        {
            if((tab[i+3][j+3] == 'X') && (tab[i+2][j+2] == 'M') && (tab[i+1][j+1] == 'A') && (tab[i][j] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les diagonales descendantes à gauche le mot XMAS à l'endroit
    for(i=0 ; i<(NBR_LINES-strlen("XMAS")+1) ; i++)
    {
        for(j=(strlen("XMAS")-1) ; j<NBR_COL ; j++)
        {
            if((tab[i][j] == 'X') && (tab[i+1][j-1] == 'M') && (tab[i+2][j-2] == 'A') && (tab[i+3][j-3] == 'S'))
                somme1++;
        }
    }

    //On cherche dans les diagonales descendantes à gauche le mot XMAS à l'envers
    for(i=0 ; i<(NBR_LINES-strlen("XMAS")+1) ; i++)
    {
        for(j=(strlen("XMAS")-1) ; j<NBR_COL ; j++)
        {
            c = tab[i][j];
            if((tab[i+3][j-3] == 'X') && (tab[i+2][j-2] == 'M') && (tab[i+1][j-1] == 'A') && (tab[i][j] == 'S'))
                somme1++;
        }
    }

    printf("somme1 = %lld\n", somme1);



    //--------------Part 2-----------------

    //On cherche le premier motif M.S
    //                             A
    //                            M.S
    for(i=0 ; i<(NBR_LINES-2) ; i++)
    {
        for(j=0 ; j<(NBR_COL-2) ; j++)
        {
            if((tab[i][j] == 'M') && (tab[i][j+2] == 'S') && (tab[i+1][j+1] == 'A')  && (tab[i+2][j] == 'M') && (tab[i+2][j+2] == 'S'))
                somme2++;
        }
    }

    //On cherche le premier motif S.M
    //                             A
    //                            S.M
    for(i=0 ; i<(NBR_LINES-2) ; i++)
    {
        for(j=0 ; j<(NBR_COL-2) ; j++)
        {
            if((tab[i][j] == 'S') && (tab[i][j+2] == 'M') && (tab[i+1][j+1] == 'A')  && (tab[i+2][j] == 'S') && (tab[i+2][j+2] == 'M'))
                somme2++;
        }
    }

    //On cherche le premier motif S.S
    //                             A
    //                            M.M
    for(i=0 ; i<(NBR_LINES-2) ; i++)
    {
        for(j=0 ; j<(NBR_COL-2) ; j++)
        {
            if((tab[i][j] == 'S') && (tab[i][j+2] == 'S') && (tab[i+1][j+1] == 'A')  && (tab[i+2][j] == 'M') && (tab[i+2][j+2] == 'M'))
                somme2++;
        }
    }

    //On cherche le premier motif M.M
    //                             A
    //                            S.S
    for(i=0 ; i<(NBR_LINES-2) ; i++)
    {
        for(j=0 ; j<(NBR_COL-2) ; j++)
        {
            if((tab[i][j] == 'M') && (tab[i][j+2] == 'M') && (tab[i+1][j+1] == 'A')  && (tab[i+2][j] == 'S') && (tab[i+2][j+2] == 'S'))
                somme2++;
        }
    }

    printf("somme2 = %lld\n", somme2);

    return 0;
}
