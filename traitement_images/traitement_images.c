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
    Im->image = (int **)malloc(sizeof(int **) * lignes);
    for (int i = 0; i < lignes; i++)
    {
        Im->image[i] = (int **)malloc(sizeof(int *) * colonnes);
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
        Im->image[i] = (int *)malloc(sizeof(int));
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
    int lignes, colonnes;
    lignes = im->lignes;
    colonnes = im->colonnes;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i <lignes; i++)
        {

            for (int j = 0; j <colonnes; j++)
            {

                fscanf(filename, "%d", &v1);
                im->image[i][j][k] = v1;
            }
        }
    }
    printf("\n");
}

image2D RGB_to_GREY(image3D im,histogramme *hist,int nb_bits){
    int taille = 1<<(nb_bits*3);
    printf("taille = %d\n",taille);
    hist->tab = (int*)calloc(taille,sizeof(int));
    hist->taille = taille;
    if(hist->tab == NULL){
        Erreur("Malloc histogramme RGB_to_GREY");
    }
    int8b r,g,b;
    int8b somme = 0;
    image2D im_retour = creer_image2D(im->lignes,im->colonnes);
    for(int i = 0;i<im->lignes;i++){
        for(int j = 0;j<im->colonnes;j++){
            r = im->image[i][j][R];
            g = im->image[i][j][G];
            b = im->image[i][j][B];
            somme = quantification(r,g,b,nb_bits);
            //im_retour->image[i][j] = r*COEFF_R+g*COEFF_G+b*COEFF_B;
            im_retour->image[i][j] = somme;
            hist->tab[somme]++;
        }
    }

    return im_retour;

}


int quantification(int8b r_8b,int8b g_8b,int8b b_8b, int nb_bits){
    if(nb_bits<1 || nb_bits>NB_PIXELS_MAX){
        Erreur("Quantification : NB_BITS INVALIDE");
    }

    unsigned char r = r_8b>>(NB_PIXELS_MAX-nb_bits)&((1<<nb_bits)-1);
    unsigned char g = g_8b>>(NB_PIXELS_MAX-nb_bits)&((1<<nb_bits)-1);
    unsigned char b = b_8b>>(NB_PIXELS_MAX-nb_bits)&((1<<nb_bits)-1);
    return r<<(2*nb_bits)|g<<(nb_bits)|b;
    
}


