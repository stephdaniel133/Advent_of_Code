#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int64_t somme1 = 0;
    int64_t somme2 = 0;
    char c = 0;
    int etape = 0;
    int nbr1 = 0;
    int nbr2 = 0;
    int mulvalid = 1;
    int etapevalide = 0;
    int etapeinvalide = 0;

    //      mul(xxx,y  y  y  )
    //etape 123456789 10 11 12

    fic = fopen("data.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            c = fgetc(fic);

            if(feof(fic))
            {
                break;
            }
            else
            {
                switch(c)
                {
                    case 'm':
                        if(etape == 0)
                            etape = 1;
                        break;
                    case 'u':
                        if(etape == 1)
                            etape = 2;
                        break;
                    case 'l':
                        if(etape == 2)
                            etape = 3;
                        break;
                    case '(':
                        if(etape == 3)
                            etape = 4;
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        if((etape == 4) || (etape == 5) || (etape == 6))
                        {
                            nbr1 = 10*nbr1 + atoi(&c);
                            etape ++;
                        }
                        else if((etape == 8) || (etape == 9) || (etape == 10))
                        {
                            nbr2 = 10*nbr2 + atoi(&c);
                            etape ++;
                        }
                        break;

                    case ',':
                        if((etape == 5) || (etape == 6) || (etape == 7))
                            etape = 8;
                        break;

                    case ')':
                        if((etape == 9) || (etape == 10) || (etape == 11))
                        {
                            etape = 0;
                            if((nbr1 < 1000) && (nbr2 < 1000))
                            {
                                somme1 += nbr1 * nbr2;
                                nbr1 = 0;
                                nbr2 = 0;
                            }
                        }
                        break;
                    default:
                        etape = 0;
                        nbr1 = 0;
                        nbr2 = 0;
                        break;
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

    printf("somme1 = %lld\n", somme1);





    //--------------Part 2-----------------
    fic = fopen("data.txt", "r");

    int nbrDO = 0;
    int nbrDONT = 0;

    //           do()     don't()
    //etapevalid 1234     56789 10 11 12
    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            c = fgetc(fic);

            if(feof(fic))
            {
                break;
            }
            else
            {
                switch(c)
                {
                    case 'd':
                        if(etapevalide == 0)
                        {
                            etape = 0;
                            etapevalide = 1;
                        }
                        if(etapeinvalide == 0)
                        {
                            etape = 0;
                            etapeinvalide = 1;
                        }
                        break;
                    case 'o':
                        if(etapevalide == 1)
                        {
                            etape = 0;
                            etapevalide = 2;
                        }
                        if(etapeinvalide == 1)
                        {
                            etape = 0;
                            etapeinvalide = 2;
                        }
                        break;
                    case 'n':
                        if(etapeinvalide == 2)
                        {
                            etape = 0;
                            etapevalide = 0;
                            etapeinvalide = 3;
                        }
                        break;
                    case '\'':
                        if(etapeinvalide == 3)
                        {
                            etape = 0;
                            etapevalide = 0;
                            etapeinvalide = 4;
                        }
                        break;
                    case 't':
                        if(etapeinvalide == 4)
                        {
                            etape = 0;
                            etapevalide = 0;
                            etapeinvalide = 5;
                        }
                        break;

                    case 'm':
                        if(etape == 0)
                            etape = 1;
                        break;
                    case 'u':
                        if(etape == 1)
                            etape = 2;
                        break;
                    case 'l':
                        if(etape == 2)
                            etape = 3;
                        break;
                    case '(':
                        if(etape == 3)
                        {
                            etape = 4;
                            etapevalide = 0;
                            etapeinvalide = 0;
                        }
                        if(etapevalide == 2)
                        {
                            etape = 0;
                            etapevalide = 3;
                            etapeinvalide = 0;
                        }
                        if(etapeinvalide == 5)
                        {
                            etape = 0;
                            etapevalide = 0;
                            etapeinvalide = 6;
                        }
                        break;
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        if((etape == 4) || (etape == 5) || (etape == 6))
                        {
                            nbr1 = 10*nbr1 + atoi(&c);
                            etape ++;
                        }
                        else if((etape == 8) || (etape == 9) || (etape == 10))
                        {
                            nbr2 = 10*nbr2 + atoi(&c);
                            etape ++;
                        }
                        break;

                    case ',':
                        if((etape == 5) || (etape == 6) || (etape == 7))
                            etape = 8;
                        break;

                    case ')':
                        if((etape == 9) || (etape == 10) || (etape == 11))
                        {
                            if((nbr1 < 1000) && (nbr2 < 1000) && (mulvalid == 1))
                            {
                                somme2 += nbr1 * nbr2;
                            }
                            etape = 0;
                            nbr1 = 0;
                            nbr2 = 0;
                            etapevalide = 0;
                            etapeinvalide = 0;
                        }
                        if(etapevalide == 3)    //fin du do()
                        {
                            etape = 0;
                            etapevalide = 0;
                            etapeinvalide = 0;
                            mulvalid = 1;
                            nbrDO++;
                        }
                        if(etapeinvalide == 6)  //fin du don't()
                        {
                            etape = 0;
                            etapevalide = 0;
                            etapeinvalide = 0;
                            mulvalid = 0;
                            nbrDONT++;
                        }
                        break;
                    default:
                        etape = 0;
                        etapevalide = 0;
                        etapeinvalide = 0;
                        nbr1 = 0;
                        nbr2 = 0;
                        break;
                }
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }




    printf("somme2 = %lld\n", somme2);
    //99.256.789 too low
    //99.959.008 too high

    fclose(fic);
    fic = NULL;

    return 0;
}
