#ifndef TRAITEMENT_IMAGES_H
#define  TRAITEMENT_IMAGES_H
#define NB_BITS_MAX 8

#include "../Utils/utils.h"

#include "../Couleur/analyse_couleur.h"


typedef enum{
    CARRE,
    BALLE,
    INDEFINI
}Objet;
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
    int lig_haut,lig_bas,col_gauche,col_droite;
    int aire;
    int centre_objet[2];
    Objet objet;
}boite_englobante;

typedef struct s_tabBoiteEnglobante{
    boite_englobante** tabBoiteEnglobante;
    int taille;
}tab_boite_englobante;



Objet reconnaissance_objet(boite_englobante bte);



image3D_ptr creer_image3D(int ,int );
image2D_ptr creer_image2D(int ,int );

void lire_image3D(FILE* ,image3D_ptr);
/*void lire_image2D(FILE* filename,image2D im);*/
void free_image3D(image3D_ptr im);
void free_image2D(image2D_ptr im);

void free_histogramme(histogramme hist);

image2D_ptr pre_traitement(FILE *filename);



image2D_ptr detecter_Objet(image2D_ptr image_binarises,boite_englobante*);

void creer_boiteEnglobante(boite_englobante* bteEnglobante,int lig_haut,int lig_bas,int col_gauche,int col_droite, image2D_ptr im);

image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur);

void afficherImage(image2D_ptr im, FILE *fileout);
void free_boite_englobante(boite_englobante boite);
boite_englobante traitement_image(char image_entree[], char image_sortie[], CouleurNom couleur);
#endif