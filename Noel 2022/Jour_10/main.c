#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int i = 0;
    int j = 0;
    int k = 0;
    char buf[20];
    int cycle[500];
    int operand = 0;
    int x[500];
    char screen[40][6];
    int sprite_nom = 0;
    int sprite_min = 0;
    int sprite_max = 0;


    memset(cycle, 0, sizeof(cycle));
    memset(x, 0, sizeof(x));
    memset(screen, '.', sizeof(screen));

    printf("Debut\n\n");

    fic = fopen("nouveau.txt", "r");

    i = 1;

    //somme des cycles
    x[0] = 1;

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        while(!feof(fic))
        {
            fgets(buf, 20, fic);
            if(buf[0] == 'a')
            {
                sscanf(buf+4, "%d", &operand);

                cycle[i] = i;
                x[i] = x[i-1];
                printf("Cycle %d, instruction addx cycle 1 op=%d, xd = %d, xf = %d\n", cycle[i], operand, x[i-1], x[i]);
                i++;

                cycle[i] = i;
                x[i] = x[i-1] + operand;
                printf("Cycle %d, instruction addx cycle 2 op=%d, xd = %d, xf = %d\n", cycle[i], operand, x[i-1], x[i]);
                i++;
            }
            else
            {
                cycle[i] = i;
                x[i] = x[i-1];

                printf("Cycle %d, instruction noop              , xd = %d, xf = %d\n", cycle[i], x[i-1], x[i]);
                i++;
            }
        }


    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
        return(EXIT_FAILURE);
    }

    printf("Cycle[20] = %d\n", cycle[20]);
    printf("Signal strenght = %d\n", 20*x[20-1]+60*x[60-1]+100*x[100-1]+140*x[140-1]+180*x[180-1]+220*x[220-1]);

    //screen[x][y]
    //screen[0][0] = '0';
    //screen[2][1] = '2';
    i = 0;  //circulation dans le buffer

    for(j=0 ; j<6 ; j++)
    {
        for(k=0 ; k<40 ; k++)
        {
            sprite_nom = x[i];
            sprite_min = x[i] - 1;
            sprite_max = x[i] + 1;

            if(k == sprite_nom  || k == sprite_min || k == sprite_max)
            {
                screen[k][j] = '#';
            }

            printf("%c", screen[k][j]);
            i++;
        }
        printf("\n");
    }


    printf("\nfin\n");
    fclose(fic);
    fic = NULL;

    return(EXIT_SUCCESS);
}
