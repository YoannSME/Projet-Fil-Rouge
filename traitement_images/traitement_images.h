#ifndef TRAITEMENT_IMAGES_H
#define  TRAITEMENT_IMAGES_H

#define R 0
#define G 1
#define B 2
typedef struct{
    int ***image;
    int lignes;
    int colonnes;
}*image3D;

typedef struct{
    int** image;
    int lignes;
    int colonnes;
}*image2D;


image3D creer_image3D(int lignes,int colonnes);
image2D creer_image2D(int lignes,int colonnes);

void lire_image3D(FILE* filename,image3D im);
/*void lire_image2D(FILE* filename,image2D im);*/




#endif