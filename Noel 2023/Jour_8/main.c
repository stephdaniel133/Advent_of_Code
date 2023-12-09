#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

typedef struct
{
    char start[3];
    char left[3];
    char right[3];
} STEP;

int main(int argc, char *argv[])
{
    char buf[400];
    long long i = 0;
    long long j = 0;
    long long k = 0;
    STEP step[800];
    int nbrStep = 0;
    char nextStep[3];
    char seq[1000];
    int nbrSeq = 0;
    long long result1 = 0;
    char GhostNextStep[800][3];
    int nbrGhost = 0;           //Nombre de fantomes
    long long result2 = 0;
    FILE *fic = NULL;


    memset(step, 0, sizeof(step));
    memset(GhostNextStep, 0, sizeof(GhostNextStep));

    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(nbrSeq=0 ; nbrSeq<sizeof(seq) ; nbrSeq++)      //On lit la séquence jusqu'au saut de ligne
        {
            fscanf(fic, "%c", &seq[nbrSeq]);
            if(seq[nbrSeq] == '\n')
            {
                seq[nbrSeq] = '\0';
                break;
            }
        }

        fscanf(fic, "%s", NULL);    //On saute la ligne

        while(!feof(fic))
        {
            fgets(buf, 300, fic);
            sscanf(buf, "%s = (%s %s)", step[nbrStep].start, step[nbrStep].left, step[nbrStep].right);
            nbrStep++;
        }

        //----------------On calcule le chemin-------------------------
        memcpy(nextStep, "AAA", 3);     //On initialise la premiere recherche à "AAA"

        do
        {
            for(i=0 ; i<nbrStep ; i++)      //On cherche les step dans la table de step
            {
                if(!strncmp(nextStep, step[i].start, 3))    //Si la valeur du step correspond au prochain step recherché
                {
                    if(seq[j] == 'L')
                    {
                        memcpy(nextStep, step[i].left, 3);
                    }
                    else
                    {
                        memcpy(nextStep, step[i].right, 3);
                    }

                    if(++j >= nbrSeq)
                    {
                        result1 += nbrSeq;
                        j = 0;
                    }

                    break;
                }
            }
        }
        while(strncmp(nextStep, "ZZZ", 3));

        result1 += j;

        printf("Resultat 1 = %lld\n", result1);

    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }


    //--------------Part 2----------------------
    for(k=0 ; k<nbrStep ; k++)
    {
        if(step[k].start[2] == 'A')     //On recherche les step finissant par A
        {
            strncpy(GhostNextStep[nbrGhost],  step[k].start, 3);
            nbrGhost++;
        }
    }
    printf("Nombre de fantomes = %d\n", nbrGhost);

    int out = 0;
    nbrGhost = 1;
    memcpy(GhostNextStep[0], "KKA", 3);     //Changer la sequence du prochain fantome

    do
    {
        out = 1;    //Condition de sortie de boucle sur les fantomes

        for(k=0 ; k<nbrGhost ; k++)      //On cherche si tous les nextStep des fantomes finissent par un Z
        {
            for(i=0 ; i<nbrStep ; i++)      //On cherche les step dans la table de step
            {
                if(!strncmp(GhostNextStep[k], step[i].start, 3))    //Si la valeur du step correspond au prochain step recherché
                {
                    if(seq[j] == 'L')
                    {
                        memcpy(GhostNextStep[k], step[i].left, 3);
                    }
                    else
                    {
                        memcpy(GhostNextStep[k], step[i].right, 3);
                    }

                    break;
                }
            }


            if(GhostNextStep[k][2] != 'Z')
            {
                out = 0;            //On ne sort pas de la boucle car au moins un fantome ne se finit pas par un 'Z'
            }
        }

        if(++j >= nbrSeq)
        {
            result2 += nbrSeq;
            j = 0;
        }
    }
    while(out != 1);

    result2 += j;

    printf("Resultat 2 = %lld\n", result2);



    fclose(fic);
    fic = NULL;

    return 0;
}
