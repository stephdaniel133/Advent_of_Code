#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct
{
    int time;
    int dst;
} RACE;


int main(int argc, char *argv[])
{
    char buf[300];
    char tempstr[100];
    long long i = 0;
    long long j = 0;
    RACE race[4];
    long long result1 = 0;
    long long result2 = 0;


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(race, 0, sizeof(race));



    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //On obtient les races
        fgets(buf, 300, fic);
        sscanf(buf, "%s %d%d%d%d", tempstr, &race[0].time, &race[1].time, &race[2].time, &race[3].time);

        //On obtient les distances
        fgets(buf, 300, fic);
        sscanf(buf, "%s %d%d%d%d", tempstr, &race[0].dst, &race[1].dst, &race[2].dst, &race[3].dst);

        //----------------Algo on passe aux calculs des courses-------------------------


        printf("Impossible d'ouvrir le fichier data\n");

    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    //On calcule le minimum

    //printf("location part 1 minimum = %lld\n", result1);



    //Part 2
    //long long temp = 0;




    fclose(fic);
    fic = NULL;

    return 0;
}
