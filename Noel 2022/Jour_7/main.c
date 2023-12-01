#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct Element Element;
struct Element
{
    char nom[100];
    int taille;
    Element *ptn_parent;
    Element *ptn_enfants[1000];
};

typedef enum
{
    COMMANDE_LISTE,         //ls
    COMMANDE_VA_REP,        //cd xxx
    COMMANDE_REMONTE_1,     //cd..
    COMMANDE_REMONTE_TOUT,  //cd /
    CREER_REP,              //créer un repertoire
    CREER_FIC,              //créer un fichier
    INIT                    //début du programme
} Etat;



Element *create_element(char *nom, int taille, Element *ptn_parent)
{
    Element *ptn_element = malloc(sizeof(Element));

    memset(ptn_element, 0, sizeof(Element));

    if(ptn_element == NULL)
    {
        exit(EXIT_FAILURE);
    }

    strcpy(ptn_element->nom, nom);
    ptn_element->taille = taille;
    ptn_element->ptn_parent = ptn_parent;

    return ptn_element;
}


void associate_parent_enfant(Element *ptn_courant, Element *ptn_temp)
{
    int i = 0;
    Element *element = ptn_courant;

    while(element->ptn_enfants[i++] != NULL);      //On fait circuler les pointeurs de l'objet pour avoir la dernière place disponible

    element->ptn_enfants[i-1] = ptn_temp;
}


int main(int argc, char *argv[])
{
    FILE *fic = NULL;
    int i = 0;
    int j = 0;
    char buf[100];
    char buf1[100];
    Etat etat = INIT;
    int taille = 0;

    Element *dd = create_element("dd", 0, NULL);
    Element *ptn_courant = dd;
    Element *ptn_temp = NULL;


    fic = fopen("nouveau.txt", "r");

    if(fic != NULL)
    {
        printf("fichier ouvert\n\n");

        while(!feof(fic))
        {
            fgets(buf, 50, fic);
            printf("%s", buf);

            if(buf[0] == '$')
            {
                printf(" --> Commande\n");

                if(buf[2] == 'l' && buf[3] == 's')  //Commande 'ls'
                {
                    etat = COMMANDE_LISTE;
                }
                else if(buf[2] == 'c' && buf[3] == 'd' && buf[5] == '.')  //Commande 'cd ..'
                {
                    etat = COMMANDE_REMONTE_1;
                    ptn_courant = ptn_courant->ptn_parent;
                }
                else if(buf[2] == 'c' && buf[3] == 'd' && buf[5] == '/')  //Commande 'cd /'
                {
                    etat = COMMANDE_REMONTE_TOUT;
                    ptn_courant = dd;
                }
                else                                                      //Commande 'cd xxxx'
                {
                    etat = COMMANDE_REMONTE_TOUT;
                    ptn_courant = dd;
                }
            }
            else if(buf[0] == 'd')                  //detection du mot dir
            {
                printf(" --> Directory\n");
                etat = CREER_REP;
                ptn_temp = create_element(buf+4 , 0, ptn_courant);
                associate_parent_enfant(ptn_courant, ptn_temp);
            }
            else if('0' <= buf[0] && buf[0] <= '9')
            {
                printf(" --> File\n");
                etat = CREER_FIC;
                //On recupere le nom et la taille
                sscanf(buf, "%d %s", &taille, buf1);
                //on creer le fichier
                ptn_temp = create_element(buf1 , taille, ptn_courant);
                associate_parent_enfant(ptn_courant, ptn_temp);
                //On ajoute la taille du fichier dans le dossier
                ptn_courant->taille += taille;
            }
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier\n");
    }


    printf("\nfin\n");
    fclose(fic);
    fic = NULL;

    return 0;
}

/*
                    fgets(buf, 50, fic);
                    printf("%s", buf);

                    if('0' < buf[0] && buf[0] < '9')    //On rencontre un fichier, on le créé
                    {

                    }
                    else if(buf[0] == 'd')    //On rencontre un répertoire, on le créé
                    {

                    }*/
