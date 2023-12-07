#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>


#define FIVE_OF_KIND    7
#define FOUR_OF_A_KIND  6
#define FULL_HOUSE      5
#define THREE_OF_A_KIND 4
#define TWO_PAIR        3
#define ONE_PAIR        2
#define HIGH_CARD       1


typedef struct
{
    uint8_t cardListOrder[13] /*= {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'}*/;
    uint8_t order[13] /*= {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}*/;
} CARD;

typedef struct              //alignement sur 64 bits
{
    uint8_t letter[5];
    uint8_t type;
    uint16_t unused;
} RANK;

typedef struct
{
    char hands[5];
    uint32_t bid;
    union
    {
        RANK rank;
        uint64_t ranku;
    }u;
    uint8_t decomposition[13];
    uint8_t nbr_2;
    uint8_t nbr_3;
    uint8_t nbr_4;
    uint8_t nbr_5;
} HAND;


int main(int argc, char *argv[])
{
    char buf[300];
    char tempstr[100];
    long long i = 0;
    long long j = 0;
    HAND hand[1100];
    CARD card = {{'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'}, {12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};
    char letters[13];
    int handNbr = 0;
    long long result1 = 0;
    long long result2 = 0;


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(hand, 0, sizeof(hand));



    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        while(!feof(fic))
        {
            fgets(buf, 300, fic);
            sscanf(buf, "%s %d", hand[handNbr].hands, &hand[handNbr].bid);
            handNbr++;
        }

        //----------------Algo on passe aux calculs des types-------------------------
        //On tri par les cartes apparessant de la premiere à la derniere
        for(i=0 ; i<handNbr ; i++)
        {
            for(j=0 ; j<5 ; j++)
            {
                for(int k=0 ; k<13 ; k++)
                {
                    if(hand[i].hands[j] == card.cardListOrder[k])
                        hand[i].decomposition[k] += 1;
                }

                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[0] ? hand[i].u.rank.letter[4-j] + card.order[0] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[1] ? hand[i].u.rank.letter[4-j] + card.order[1] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[2] ? hand[i].u.rank.letter[4-j] + card.order[2] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[3] ? hand[i].u.rank.letter[4-j] + card.order[3] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[4] ? hand[i].u.rank.letter[4-j] + card.order[4] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[5] ? hand[i].u.rank.letter[4-j] + card.order[5] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[6] ? hand[i].u.rank.letter[4-j] + card.order[6] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[7] ? hand[i].u.rank.letter[4-j] + card.order[7] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[8] ? hand[i].u.rank.letter[4-j] + card.order[8] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[9] ? hand[i].u.rank.letter[4-j] + card.order[9] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[10] ? hand[i].u.rank.letter[4-j] + card.order[10] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[11] ? hand[i].u.rank.letter[4-j] + card.order[11] : hand[i].u.rank.letter[4-j]);
                hand[i].u.rank.letter[4-j] = (hand[i].hands[j] == card.cardListOrder[12] ? hand[i].u.rank.letter[4-j] + card.order[12] : hand[i].u.rank.letter[4-j]);
            }

            //on cherche si on a un Five of a kind, Four of a kind, Full house, Three of a kind, Two pair, One pair, High card
            //décomposition en chaque lettre
            for(int k=0 ; k<13 ; k++)
            {
                if(hand[i].decomposition[k] == 2)
                    hand[i].nbr_2 += 1;
                if(hand[i].decomposition[k] == 3)
                    hand[i].nbr_3 += 1;
                if(hand[i].decomposition[k] == 4)
                    hand[i].nbr_4 += 1;
                if(hand[i].decomposition[k] == 5)
                    hand[i].nbr_5 += 1;
            }
            if(hand[i].nbr_5 == 1)
                hand[i].u.rank.type = FIVE_OF_KIND;
            else if(hand[i].nbr_4 == 1)
                hand[i].u.rank.type = FOUR_OF_A_KIND;
            else if((hand[i].nbr_3 == 1) && (hand[i].nbr_2 == 1))
                hand[i].u.rank.type = FULL_HOUSE;
            else if(hand[i].nbr_3 == 1)
                hand[i].u.rank.type = THREE_OF_A_KIND;
            else if(hand[i].nbr_2 == 2)
                hand[i].u.rank.type = TWO_PAIR;
            else if(hand[i].nbr_2 == 1)
                hand[i].u.rank.type = ONE_PAIR;
            else
                hand[i].u.rank.type = HIGH_CARD;
        }

        //On trie les valeur par rapport au champ hand[i].u.ranku de chaque hand du fichier
        //Plus le le ranku est grand, plus le rang est grand



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
