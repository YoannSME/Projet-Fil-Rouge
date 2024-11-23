#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traitement_images.h"

void Erreur(char *message)
{
    fprintf(stderr, "%s.\n", message);
    exit(EXIT_FAILURE);
}

image3D creer_image3D(int lignes, int colonnes)
{
    image3D Im = (image3D)malloc(sizeof(image3D));
    Im->lignes = lignes;
    Im->colonnes = colonnes;
    if (Im == NULL)
    {
        Erreur("Erreur malloc image3D");
    }
    /*printf("Image allouée\n.");*/
    Im->image = (int***)malloc(sizeof(int***)*lignes);
    for (int i = 0; i < lignes; i++)
    {
        Im->image[i] = (int **)malloc(sizeof(int **) * colonnes);
        if (Im->image[i] == NULL)
        {
            Erreur("Erreur malloc image3D");
        }
        /*printf("Image[i] allouée\n.");*/

        for (int j = 0; j < colonnes; j++)
        {
            Im->image[i][j] = (int *)malloc(3 * sizeof(int));
            if (Im->image[i][j] == NULL)
            {
                Erreur("Erreur malloc image3D");
            }
            /*printf("Image[col] allouée\n.");*/
        }
    }

    return Im;
}

image2D creer_image2D(int lignes, int colonnes)
{
    image2D Im = (image2D)malloc(sizeof(image2D));
    Im->lignes = lignes;
    Im->colonnes = colonnes;
    if (Im == NULL)
    {
        Erreur("Erreur malloc image2D");
    }
    Im->image = (int **)malloc(sizeof(int *) * lignes);
     if (Im->image == NULL)
    {
        Erreur("Erreur malloc image2D");
    }

    for (int i = 0; i < colonnes; i++)
    {
        Im->image[i] = (int*)malloc(sizeof(int));
        if (Im->image[i] == NULL)
        {
            Erreur("Erreur malloc image2D");
        }
    }

    return Im;
}

void lire_image3D(FILE *filename, image3D im)
{
    int v1;
    for(int k = 0;k<3;k++){
    for (int i = 0; i < im->lignes; i++)
    {
        for (int j = 0; j < im->colonnes; j++)
        {
            fscanf(filename, "%d",&v1);
            im->image[i][j][k] = v1;
        }
    }
    }
    for (int i = 0; i < im->lignes; i++)
    {
        for (int j = 0; j < im->colonnes; j++)
        {
            printf("%2d %2d %2d ", im->image[i][j][R], im->image[i][j][G], im->image[i][j][B]);
        }
        printf("\n");
    }
     printf("\n");
}
/*void lire_image2D(FILE *filename, image2D im)
{
}*/