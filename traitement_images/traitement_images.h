#ifndef TRAITEMENT_IMAGES_H
#define  TRAITEMENT_IMAGES_H
#define NB_PIXELS_MAX 8
#define R 0
#define G 1
#define B 2

#define COEFF_R 0.299
#define COEFF_G 0.587
#define COEFF_B 0.114

typedef struct s_imageRGB{
    int ***image;
    int lignes;
    int colonnes;
}*image3D;

typedef struct{
    int** image;
    int lignes;
    int colonnes;
}*image2D;

typedef struct{
    int taille;
    int*tab;
}histogramme;

typedef struct{
    image3D image;
    int coordonnes[4];
}boite_engloblante;


typedef __int8_t int8b;


image3D creer_image3D(int ,int );
image2D creer_image2D(int ,int );

void lire_image3D(FILE* ,image3D);
/*void lire_image2D(FILE* filename,image2D im);*/
int quantification(int8b r_8b,int8b g_8b,int8b b_8b, int nb_bits);
image2D RGB_to_GREY(image3D im,histogramme* ,int nb_bits);



#endif