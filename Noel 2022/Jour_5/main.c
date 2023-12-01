#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int i = 0;
    char buf1[100];
    int lig = 0;
    int col = 0;
    int nbr = 0;
    int from = 0;
    int to = 0;
    char buf[1000][9];
    char car = '0';
    int pos_in = 0;
    int pos_out = 0;


    memset(buf, ' ', sizeof(buf));
    //Colonne 1
    buf[0][0] = 'M';
    buf[1][0] = 'J';
    buf[2][0] = 'C';
    buf[3][0] = 'B';
    buf[4][0] = 'F';
    buf[5][0] = 'R';
    buf[6][0] = 'L';
    buf[7][0] = 'H';

    //Colonne 2
    buf[0][1] = 'Z';
    buf[1][1] = 'C';
    buf[2][1] = 'D';

    //Colonne 3
    buf[0][2] = 'H';
    buf[1][2] = 'J';
    buf[2][2] = 'F';
    buf[3][2] = 'C';
    buf[4][2] = 'N';
    buf[5][2] = 'G';
    buf[6][2] = 'W';

    //Colonne 4
    buf[0][3] = 'P';
    buf[1][3] = 'J';
    buf[2][3] = 'D';
    buf[3][3] = 'M';
    buf[4][3] = 'T';
    buf[5][3] = 'S';
    buf[6][3] = 'B';

    //Colonne 5
    buf[0][4] = 'N';
    buf[1][4] = 'C';
    buf[2][4] = 'D';
    buf[3][4] = 'R';
    buf[4][4] = 'J';

    //Colonne 6
    buf[0][5] = 'W';
    buf[1][5] = 'L';
    buf[2][5] = 'D';
    buf[3][5] = 'Q';
    buf[4][5] = 'P';
    buf[5][5] = 'J';
    buf[6][5] = 'G';
    buf[7][5] = 'Z';

    //Colonne 7
    buf[0][6] = 'P';
    buf[1][6] = 'Z';
    buf[2][6] = 'T';
    buf[3][6] = 'F';
    buf[4][6] = 'R';
    buf[5][6] = 'H';

    //Colonne 8
    buf[0][7] = 'L';
    buf[1][7] = 'V';
    buf[2][7] = 'M';
    buf[3][7] = 'G';

    //Colonne 9
    buf[0][8] = 'C';
    buf[1][8] = 'B';
    buf[2][8] = 'G';
    buf[3][8] = 'P';
    buf[4][8] = 'F';
    buf[5][8] = 'Q';
    buf[6][8] = 'R';
    buf[7][8] = 'J';


    printf("Tableau =\n    0 1 2 3 4 5 6 7 8\n");

    for(lig=0 ; lig<10 ; lig++)
    {
        printf("%d   ", lig);
        for(col=0 ; col<9 ; col++)
        {
            printf("%c ", buf[lig][col]);
        }
        printf("\n");
    }

    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        fseek(fic, 335, SEEK_SET);

        while(!feof(fic))
        {
            fgets(buf1, 100, fic);
            printf("%s\n", buf1);

            sscanf(buf1, "move %d from %d to %d", &nbr, &from, &to);
            from = from - 1;
            to = to - 1;
            printf("nbr=%d, from=%d, to=%d\n", nbr, from, to);

            for(i=0 ; i<nbr ; i++)
            {
                //on recherche la position du top de la colonne de départ
                for(pos_in=0 ; pos_in<1000 ; pos_in++)
                {
                    if(buf[pos_in][from] == ' ')
                       break;
                }
                pos_in = pos_in - 1;
                for(pos_out=0 ; pos_out<1000 ; pos_out++)
                {
                    if(buf[pos_out][to] == ' ')
                       break;
                }
                printf("pos_in = %d, pos_out = %d\n\n", pos_in, pos_out);
                buf[pos_out + nbr - 1 - i][to] = buf[pos_in][from];
                buf[pos_in][from] = ' ';


                /*printf("Tableau modifie =\n    0 1 2 3 4 5 6 7 8\n");

                for(lig=0 ; lig<12 ; lig++)
                {
                    printf("%d   ", lig);
                    for(col=0 ; col<9 ; col++)
                    {
                        printf("%c ", buf[lig][col]);
                    }
                    printf("\n");
                }*/
            }

//            for(i=0 ; i<nbr ; i++)
//            {
//                //on recherche la position du top de la colonne de départ
//                for(pos_in=0 ; pos_in<1000 ; pos_in++)
//                {
//                    if(buf[pos_in][from] == ' ')
//                       break;
//                }
//                pos_in = pos_in - 1;
//                for(pos_out=0 ; pos_out<1000 ; pos_out++)
//                {
//                    if(buf[pos_out][to] == ' ')
//                       break;
//                }
//                printf("pos_in = %d, pos_out = %d\n\n", pos_in, pos_out);
//                buf[pos_out][to] = buf[pos_in][from];
//                buf[pos_in][from] = ' ';
//
//
//                printf("Tableau modifie =\n    0 1 2 3 4 5 6 7 8\n");
//
//                for(lig=0 ; lig<10 ; lig++)
//                {
//                    printf("%d   ", lig);
//                    for(col=0 ; col<9 ; col++)
//                    {
//                        printf("%c ", buf[lig][col]);
//                    }
//                    printf("\n");
//                }
//            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }



    printf("Tableau final =\n    0 1 2 3 4 5 6 7 8\n");

    for(lig=0 ; lig<100 ; lig++)
    {
        if(lig<10)
            printf("%d   ", lig);
        else
            printf("%d  ", lig);
        for(col=0 ; col<9 ; col++)
        {
            printf("%c ", buf[lig][col]);
        }
        printf("\n");
    }

    printf("fin\n");
    fclose(fic);
    fic = NULL;

    return 0;
}
