#ifndef TRAITEMENT_IMAGES_H
#define  TRAITEMENT_IMAGES_H
#define NB_BITS_MAX 8




#define R 0
#define G 1
#define B 2

#define COEFF_R 0.299
#define COEFF_G 0.587
#define COEFF_B 0.114

typedef struct s_image3D{
    int ***image;
    int lignes;
    int colonnes;
}image3D,*image3D_ptr; 

typedef struct s_image2D{
    int** image;
    int lignes;
    int colonnes;
}image2D,*image2D_ptr;

typedef struct{
    int taille;
    int*tab;
}histogramme;

typedef struct{
    image3D image;
    int coordonnes[4];
}boite_engloblante;


typedef enum {
    COL_ROUGE,
    COL_BLEU,
    COL_JAUNE,
    COL_ORANGE,
    COL_BLANC,
    COL_INCONNU,
    COL_GRIS,
    COL_VERT
} CouleurNom;

typedef __int8_t int8b;


image3D_ptr creer_image3D(int ,int );
image2D_ptr creer_image2D(int ,int );

void lire_image3D(FILE* ,image3D_ptr);
/*void lire_image2D(FILE* filename,image2D im);*/
int quantification(int8b r_8b,int8b g_8b,int8b b_8b, int nb_bits);
image2D_ptr RGB_to_GREY(image3D_ptr im,histogramme* ,int nb_bits);
void free_image3D(image3D_ptr im);
void free_image2D(image2D_ptr im);

void free_histogramme(histogramme hist);

image2D_ptr pre_traitement(FILE *filename, int nb_bits);

const char *nom_couleur(CouleurNom c);
CouleurNom conversion_couleur(int valeur, int nb_bits);
void free_lut(CouleurNom ***lut, unsigned int nb_bits);
CouleurNom ***build_lut(unsigned int nb_bits);
image2D_ptr encadrer(const image2D_ptr image_binarise,int nb_bits);


image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur, int nb_bits);
#endif