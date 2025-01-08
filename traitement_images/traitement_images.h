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
    image2D_ptr image;
    int coordonnes[4];
    int aire;
}boite_englobante;


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
int quantification(int8b r_8b,int8b g_8b,int8b b_8b);
image2D_ptr RGB_to_GREY(image3D_ptr im,histogramme*);
void free_image3D(image3D_ptr im);
void free_image2D(image2D_ptr im);

void free_histogramme(histogramme hist);

image2D_ptr pre_traitement(FILE *filename);

const char *nom_couleur(CouleurNom c);
CouleurNom conversion_couleur(int valeur);

image2D_ptr encadrer(image2D_ptr image_binarises,boite_englobante*);
void creer_boiteEnglobante(boite_englobante* bteEnglobante,int lig_haut,int lig_bas,int col_gauche,int col_droite, image2D_ptr im);
void etablir_nbBits(int );

image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur);
#endif