#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

//#define SEED_NBR    4
#define SEED_NBR    20

typedef struct
{
    long long dst;
    long long src;
    long long len;
    int nbrDeTable;
} MAP;

long long moulinette(long long seed, MAP *seedToSoil, MAP *soilToFertilizer, MAP *fertilizerToWater, MAP *waterToLight, MAP *lightToTemperature, MAP *temperatureToHumidity, MAP *humidityToLocation);


int main(int argc, char *argv[])
{
    char buf[300];
    char tempstr[100];
    long long i = 0;
    int j = 0;
    long long seed[SEED_NBR];
    long long seedresult[SEED_NBR];
    MAP seedToSoil[50];
    MAP soilToFertilizer[50];
    MAP fertilizerToWater[50];
    MAP waterToLight[50];
    MAP lightToTemperature[50];
    MAP temperatureToHumidity[50];
    MAP humidityToLocation[50];
    long long result1 = 0;
    long long result2 = 0;


    FILE *fic = NULL;

    fic = fopen("data.txt", "r");

    memset(seed, 0, sizeof(seed));
    memset(seedToSoil, 0, sizeof(seedToSoil));
    memset(soilToFertilizer, 0, sizeof(soilToFertilizer));
    memset(fertilizerToWater, 0, sizeof(fertilizerToWater));
    memset(waterToLight, 0, sizeof(waterToLight));
    memset(lightToTemperature, 0, sizeof(lightToTemperature));
    memset(temperatureToHumidity, 0, sizeof(temperatureToHumidity));
    memset(humidityToLocation, 0, sizeof(humidityToLocation));



    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        //while(!feof(fic))
        {
            fgets(buf, 300, fic);
            //printf("%s, longueur = %d\n", buf, (int)strlen(buf));

            //On obtient les seed
            //sscanf(buf, "%s %lld%lld%lld%lld", tempstr, &seed[0], &seed[1], &seed[2], &seed[3]);

            sscanf(buf, "%s %lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld%lld", tempstr,
                        &seed[0], &seed[1], &seed[2], &seed[3], &seed[4], &seed[5], &seed[6], &seed[7], &seed[8], &seed[9],
                        &seed[10], &seed[11], &seed[12], &seed[13], &seed[14], &seed[15], &seed[16], &seed[17], &seed[18], &seed[19]);


            for(j=0 ; j<SEED_NBR ; j++)
            {
                seedresult[j] = seed[j];
            }

            fgets(buf, 300, fic); // on saute la ligne
            fgets(buf, 300, fic); //on saute le seed-to-soil map

            i = 0;
            do
            {
                fgets(buf, 300, fic); // on saute la ligne
                sscanf(buf, "%lld%lld%lld", &seedToSoil[i].dst, &seedToSoil[i].src, &seedToSoil[i].len);
                i++;
            }
            while(strcmp(buf, "\n"));
            seedToSoil[0].nbrDeTable = i-1;

            fgets(buf, 300, fic); //on saute le soil-to-fertilizer map

            i = 0;
            do
            {
                fgets(buf, 300, fic); // on saute la ligne
                sscanf(buf, "%lld%lld%lld", &soilToFertilizer[i].dst, &soilToFertilizer[i].src, &soilToFertilizer[i].len);
                i++;
            }
            while(strcmp(buf, "\n"));
            soilToFertilizer[0].nbrDeTable = i-1;

            fgets(buf, 300, fic); //on saute le fertilizer-to-water map

            i = 0;
            do
            {
                fgets(buf, 300, fic); // on saute la ligne
                sscanf(buf, "%lld%lld%lld", &fertilizerToWater[i].dst, &fertilizerToWater[i].src, &fertilizerToWater[i].len);
                i++;
            }
            while(strcmp(buf, "\n"));
            fertilizerToWater[0].nbrDeTable = i-1;

            fgets(buf, 300, fic); //on saute le water-to-light map

            i = 0;
            do
            {
                fgets(buf, 300, fic); // on saute la ligne
                sscanf(buf, "%lld%lld%lld", &waterToLight[i].dst, &waterToLight[i].src, &waterToLight[i].len);
                i++;
            }
            while(strcmp(buf, "\n"));
            waterToLight[0].nbrDeTable = i-1;

            fgets(buf, 300, fic); //on saute le light-to-temperature map

            i = 0;
            do
            {
                fgets(buf, 300, fic); // on saute la ligne
                sscanf(buf, "%lld%lld%lld", &lightToTemperature[i].dst, &lightToTemperature[i].src, &lightToTemperature[i].len);
                i++;
            }
            while(strcmp(buf, "\n"));
            lightToTemperature[0].nbrDeTable = i-1;

            fgets(buf, 300, fic); //on saute le temperature-to-humidity map

            i = 0;
            do
            {
                fgets(buf, 300, fic); // on saute la ligne
                sscanf(buf, "%lld%lld%lld", &temperatureToHumidity[i].dst, &temperatureToHumidity[i].src, &temperatureToHumidity[i].len);
                i++;
            }
            while(strcmp(buf, "\n"));
            temperatureToHumidity[0].nbrDeTable = i-1;

            fgets(buf, 300, fic); //on saute le humidity-to-location map

            i = 0;
            while(!feof(fic))
            {
                fgets(buf, 300, fic); // on saute la ligne

                sscanf(buf, "%lld%lld%lld\n\n", &humidityToLocation[i].dst, &humidityToLocation[i].src, &humidityToLocation[i].len);
                i++;
            }
            humidityToLocation[0].nbrDeTable = i;

        }

        //----------------Algo on passe les seed dans les tables-------------------------
        for(j=0 ; j<SEED_NBR ; j++)
        {
            printf("Seed %lld", seed[j]);
            for(i=0 ; i<seedToSoil[0].nbrDeTable ; i++)
            {
                if((seedToSoil[i].src <= seedresult[j]) && (seedresult[j] < seedToSoil[i].src + seedToSoil[i].len))
                {
                    seedresult[j] = seedresult[j] - seedToSoil[i].src + seedToSoil[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }

            printf(", %lld", seedresult[j]);

            for(i=0 ; i<soilToFertilizer[0].nbrDeTable ; i++)
            {
                if((soilToFertilizer[i].src <= seedresult[j]) && (seedresult[j] < soilToFertilizer[i].src + soilToFertilizer[i].len))
                {
                    seedresult[j] = seedresult[j] - soilToFertilizer[i].src + soilToFertilizer[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }

            printf(", %lld", seedresult[j]);

            for(i=0 ; i<fertilizerToWater[0].nbrDeTable ; i++)
            {
                if((fertilizerToWater[i].src <= seedresult[j]) && (seedresult[j] < fertilizerToWater[i].src + fertilizerToWater[i].len))
                {
                    seedresult[j] = seedresult[j] - fertilizerToWater[i].src + fertilizerToWater[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }

            printf(", %lld", seedresult[j]);

            for(i=0 ; i<waterToLight[0].nbrDeTable ; i++)
            {
                if((waterToLight[i].src <= seedresult[j]) && (seedresult[j] < waterToLight[i].src + waterToLight[i].len))
                {
                    seedresult[j] = seedresult[j] - waterToLight[i].src + waterToLight[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }

            printf(", %lld", seedresult[j]);

            for(i=0 ; i<lightToTemperature[0].nbrDeTable ; i++)
            {
                if((lightToTemperature[i].src <= seedresult[j]) && (seedresult[j] < lightToTemperature[i].src + lightToTemperature[i].len))
                {
                    seedresult[j] = seedresult[j] - lightToTemperature[i].src + lightToTemperature[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }

            printf(", %lld", seedresult[j]);

            for(i=0 ; i<temperatureToHumidity[0].nbrDeTable ; i++)
            {
                if((temperatureToHumidity[i].src <= seedresult[j]) && (seedresult[j] < temperatureToHumidity[i].src + temperatureToHumidity[i].len))
                {
                    seedresult[j] = seedresult[j] - temperatureToHumidity[i].src + temperatureToHumidity[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }

            printf(", %lld", seedresult[j]);

            for(i=0 ; i<humidityToLocation[0].nbrDeTable ; i++)
            {
                if((humidityToLocation[i].src <= seedresult[j]) && (seedresult[j] < humidityToLocation[i].src + humidityToLocation[i].len))
                {
                    seedresult[j] = seedresult[j] - humidityToLocation[i].src + humidityToLocation[i].dst;
                    break;
                }
                else
                    seedresult[j] = seedresult[j];
            }


            printf(", %lld\n", seedresult[j]);
        }


        printf("Impossible d'ouvrir le fichier data\n");

    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    //On calcule le minimum
    result1 = seedresult[0];
    for(i=1 ; i<SEED_NBR ; i++)
    {
        if(seedresult[i] < result1)
            result1 = seedresult[i];
    }
    printf("location part 1 minimum = %lld\n", result1);



    //Part 2
    long long temp = 0;
    result2 = 0x7FFFFFFFFFFFFFFF;

    temp = seed[0]+seed[1];
    for(i=seed[0] ; i<(seed[0]+seed[1]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 1er lot = %lld\n", result2);

    temp = seed[2]+seed[3];
    for(i=seed[2] ; i<(seed[2]+seed[3]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 2e lot = %lld\n", result2);

    temp = seed[4]+seed[5];
    for(i=seed[4] ; i<(seed[4]+seed[5]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 3e lot = %lld\n", result2);

    temp = seed[6]+seed[7];
    temp = seed[6];
    for(i=seed[6] ; i<(seed[6]+seed[7]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 4e lot = %lld\n", result2);

    for(i=seed[8] ; i<(seed[8]+seed[9]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 5e lot = %lld\n", result2);

    for(i=seed[10] ; i<(seed[10]+seed[11]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 6e lot = %lld\n", result2);

    for(i=seed[12] ; i<(seed[12]+seed[13]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 7e lot = %lld\n", result2);

    for(i=seed[14] ; i<(seed[14]+seed[15]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 8e lot = %lld\n", result2);

    for(i=seed[16] ; i<(seed[16]+seed[17]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location minimum 9e lot = %lld\n", result2);

    for(i=seed[18] ; i<(seed[18]+seed[19]) ; i++)
    {
        temp = moulinette(i, seedToSoil, soilToFertilizer, fertilizerToWater, waterToLight, lightToTemperature, temperatureToHumidity, humidityToLocation);
        if(temp < result2)
            result2 = temp;
    }
    printf("location part 2 minimum 10e lot = %lld\n", result2);

    fclose(fic);
    fic = NULL;

    return 0;
}







long long moulinette(long long seed, MAP *seedToSoil, MAP *soilToFertilizer, MAP *fertilizerToWater, MAP *waterToLight, MAP *lightToTemperature, MAP *temperatureToHumidity, MAP *humidityToLocation)
{
    long long i = 0;
    long long result = seed;

    for(i=0 ; i<seedToSoil[0].nbrDeTable ; i++)
    {
        if((seedToSoil[i].src <= result) && (result < seedToSoil[i].src + seedToSoil[i].len))
        {
            result = result - seedToSoil[i].src + seedToSoil[i].dst;
            break;
        }
        else
            result = result;
    }

    //printf(", %lld", result);

    for(i=0 ; i<soilToFertilizer[0].nbrDeTable ; i++)
    {
        if((soilToFertilizer[i].src <= result) && (result < soilToFertilizer[i].src + soilToFertilizer[i].len))
        {
            result = result - soilToFertilizer[i].src + soilToFertilizer[i].dst;
            break;
        }
        else
            result = result;
    }

    //printf(", %lld", result);

    for(i=0 ; i<fertilizerToWater[0].nbrDeTable ; i++)
    {
        if((fertilizerToWater[i].src <= result) && (result < fertilizerToWater[i].src + fertilizerToWater[i].len))
        {
            result = result - fertilizerToWater[i].src + fertilizerToWater[i].dst;
            break;
        }
        else
            result = result;
    }

    //printf(", %lld", result);

    for(i=0 ; i<waterToLight[0].nbrDeTable ; i++)
    {
        if((waterToLight[i].src <= result) && (result < waterToLight[i].src + waterToLight[i].len))
        {
            result = result - waterToLight[i].src + waterToLight[i].dst;
            break;
        }
        else
            result = result;
    }

    //printf(", %lld", result);

    for(i=0 ; i<lightToTemperature[0].nbrDeTable ; i++)
    {
        if((lightToTemperature[i].src <= result) && (result < lightToTemperature[i].src + lightToTemperature[i].len))
        {
            result = result - lightToTemperature[i].src + lightToTemperature[i].dst;
            break;
        }
        else
            result = result;
    }

    //printf(", %lld", result);

    for(i=0 ; i<temperatureToHumidity[0].nbrDeTable ; i++)
    {
        if((temperatureToHumidity[i].src <= result) && (result < temperatureToHumidity[i].src + temperatureToHumidity[i].len))
        {
            result = result - temperatureToHumidity[i].src + temperatureToHumidity[i].dst;
            break;
        }
        else
            result = result;
    }

    //printf(", %lld", result);

    for(i=0 ; i<humidityToLocation[0].nbrDeTable ; i++)
    {
        if((humidityToLocation[i].src <= result) && (result < humidityToLocation[i].src + humidityToLocation[i].len))
        {
            result = result - humidityToLocation[i].src + humidityToLocation[i].dst;
            break;
        }
        else
            result = result;
    }

    return result;
}
