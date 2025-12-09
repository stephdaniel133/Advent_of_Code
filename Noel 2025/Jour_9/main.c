#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdbool.h>

//#define NBR_LINES 8
#define NBR_LINES 496

typedef struct
{
    int64_t a;
    int32_t p1;
    int32_t p2;
} area_t;


int comparer(const void *a, const void *b)
{
    const area_t *elemA = (const area_t *)a;
    const area_t *elemB = (const area_t *)b;

    return (elemA->a < elemB->a) ? 1 : -1;
}


int main(int argc, char *argv[])
{
    int64_t i = 0;
    int64_t j = 0;
    int64_t k = 0;
    int64_t somme1 = 0;
    int64_t somme2 = 0;

    typedef struct
    {
        int32_t x;
        int32_t y;
    } point_t;
    point_t tab1[NBR_LINES];


    area_t area[NBR_LINES*(NBR_LINES-1)/2];

    FILE *fic = NULL;
    FILE *fic2 = NULL;

    fic = fopen("data.txt", "r");
    fic2 = fopen("output.csv", "w");

    memset(tab1, 0, sizeof(tab1));
    memset(area, 0, sizeof(area));


    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i=0 ; i<NBR_LINES ; i++)
        {
            fscanf(fic, "%d,%d", &tab1[i].x, &tab1[i].y);
            fgetc(fic); //On echappe le saut à la ligne
        }
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }

    printf("\n");


    //Impression du puzzle complet et recherche du 'S'
    printf("x = %d\n", tab1[0].x);
    printf("y = %d\n", tab1[0].y);

    printf("x = %d\n", tab1[NBR_LINES-1].x);
    printf("y = %d\n", tab1[NBR_LINES-1].y);

    printf("\n");


    //--------------Part 1-----------------
    //On calcul les distances entre tous les points
    for(i=0 ; i<NBR_LINES ; i++)
    {
        for(j=i+1 ; j<NBR_LINES ; j++)
        {
            int64_t x = 0;
            int64_t y = 0;

            if(tab1[i].x >= tab1[j].x)
            {
                x = tab1[i].x - tab1[j].x + 1;
            }
            else
            {
                x = tab1[j].x - tab1[i].x + 1;
            }
            if(tab1[i].y >= tab1[j].y)
            {
                y = tab1[i].y - tab1[j].y + 1;
            }
            else
            {
                y = tab1[j].y - tab1[i].y + 1;
            }
            area[k].a = x * y;
            area[k].p1 = i;
            area[k].p2 = j;
            printf("%4ld, %4ld, %7lu\n", i, j, area[k].a);
            k++;
        }
    }

    //On trie le tableau de la plus petite à la plus grande distance entre points
    size_t taille = sizeof(area) / sizeof(area[0]);
    qsort(area, taille, sizeof(area_t), comparer);


    printf("\n-----------tableau trie--------------------\n");
    //Impression du tableau des distances
    for(i = 0; i < sizeof(area) / sizeof(area[0]) ; i++)
    {
        printf("%4d, %4d, %7lu\n", area[i].p1, area[i].p2, area[i].a);
    }
    printf("\n");

    if(fic != NULL)
    {
        printf("fichier ouvert\n");

        for(i = 0; i < sizeof(area) / sizeof(area[0]) ; i++)
        {
            fprintf(fic2, "%4d, %4d, %7lu\n", area[i].p1, area[i].p2, area[i].a);
        }
        printf("\n");
    }
    else
    {
        printf("Impossible d'ouvrir le fichier data\n");
    }
    fclose(fic2);
    fic2 = NULL;

    somme1 = area[0].a; //Le tableau le plus large est le premier de la liste

    printf("somme1 = %lu\n\n\n", somme1);

    //--------------Part 2-----------------

    //??????????

    printf("somme2 = %ld\n", somme2);

    fclose(fic);
    fic = NULL;

    return 0;
}






//Algo donné par Mistral pur le point 2
/*#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct
{
    int64_t x, y;
} Point;

// Fonction pour vérifier si un point est à l'intérieur du polygone
bool is_inside_polygon(Point p, Point *polygon, int n)
{
    bool inside = false;
    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        if (((polygon[i].y > p.y) != (polygon[j].y > p.y)) && (p.x < (polygon[j].x - polygon[i].x) * (p.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x))
        {
            inside = !inside;
        }
    }
    return inside;
}

// Fonction pour vérifier si un rectangle est valide
bool is_valid_rectangle(Point p1, Point p2, Point *polygon, int n)
{
    int64_t x1 = p1.x, y1 = p1.y;
    int64_t x2 = p2.x, y2 = p2.y;
    if (x1 > x2) { int64_t t = x1; x1 = x2; x2 = t; }
    if (y1 > y2) { int64_t t = y1; y1 = y2; y2 = t; }

    // Vérifier les 4 coins du rectangle
    Point corners[4] = {{x1, y1}, {x1, y2}, {x2, y1}, {x2, y2}};
    for (int i = 0; i < 4; i++)
    {
        bool on_polygon = false;
        for (int j = 0; j < n; j++)
        {
            if (corners[i].x == polygon[j].x && corners[i].y == polygon[j].y)
            {
                on_polygon = true;
                break;
            }
        }
        if (!on_polygon && !is_inside_polygon(corners[i], polygon, n))
        {
            return false;
        }
    }
    return true;
}

int main()
{
    // Lire les points depuis le fichier
    FILE *f = fopen("input.txt", "r");
    if (!f)
    {
        perror("Erreur d'ouverture");
        return 1;
    }

    Point *points = NULL;
    int n = 0, capacity = 1024;
    points = malloc(capacity * sizeof(Point));
    if (!points) {
        perror("Erreur d'allocation");
        return 1;
    }

    int64_t x, y;
    while (fscanf(f, "%" SCNd64 ",%" SCNd64, &x, &y) == 2)
    {
        if (n >= capacity)
        {
            capacity *= 2;
            points = realloc(points, capacity * sizeof(Point));
            if (!points)
            {
                perror("Erreur de réallocation");
                return 1;
            }
        }/?inc-order=passprisma&redirectTo=https%3A%2F%2Fwww.programme.tv%2Fprogramme-tnt%2Fsoiree%2Fsamedi.php&signupservice=PTV_PAYWALL_MODALE_SITE-PTV_ZERO-PUB&_sp_targeting_params=paymenttunnel:true
        points[n++] = (Point){x, y};
    }
    fclose(f);

    // Trouver la plus grande aire valide
    uint64_t max_area = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            uint64_t width = abs(points[i].x - points[j].x) + 1;
            uint64_t height = abs(points[i].y - points[j].y) + 1;
            uint64_t area = width * height;
            if (is_valid_rectangle(points[i], points[j], points, n) && area > max_area)
            {
                max_area = area;
            }
        }
    }

    printf("La plus grande aire valide est : %" PRIu64 "\n", max_area);
    free(points);
    return 0;
}
*/
