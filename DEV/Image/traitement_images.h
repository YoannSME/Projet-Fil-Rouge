#ifndef TRAITEMENT_IMAGES_H
#define TRAITEMENT_IMAGES_H
#define NB_BITS_MAX 8

#include "../Utils/utils.h"

#include "../Couleur/analyse_couleur.h"

typedef enum
{
    CARRE,
    BALLE,
    NONE,
} Objet;

typedef struct s_image3D
{
    int ***image;
    int lignes;
    int colonnes;
} image3D, *image3D_ptr;

typedef struct s_image2D
{
    int **image;
    int lignes;
    int colonnes;
} image2D, *image2D_ptr;

typedef struct
{
    int taille;
    int *tab;
} histogramme;

typedef struct
{
    image2D_ptr image;
    int lig_haut, lig_bas, col_gauche, col_droite;
    int aire;
    int centre_objet[2];
    Objet objet;
    CouleurNom couleurObjet;
} boite_englobante;

typedef struct s_tab_boite_englobante
{
    int taille;
    boite_englobante *tabBoites;
} tab_boite_englobante;

void lire_image3D(FILE *, image3D_ptr);
image3D_ptr creer_image3D(int, int);
image2D_ptr creer_image2D(int, int);
image2D_ptr copier_image(image2D_ptr image_origine);
void initialiser_image(image2D_ptr image, int valeur);
image2D_ptr lire_image2D(FILE *filename);
image2D_ptr additionner_deux_images(image2D_ptr image1, image2D_ptr image2);
image2D_ptr pre_traitement(FILE *filename);
image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur);
int labelliserImage_8voisinage(image2D_ptr binaire, image2D_ptr labels);
Objet reconnaissance_objet(boite_englobante bte);

void association_objet(Objet objet);
void calculer_boites_englobantes(image2D_ptr labels, image2D_ptr, boite_englobante *boites, int nbLabels);
boite_englobante creer_boiteEnglobante(image2D_ptr image, int lig_haut, int lig_bas, int col_gauche, int col_droite);
void entourer_objet(boite_englobante b);

void free_image3D(image3D_ptr im);
void free_image2D(image2D_ptr im);

void free_histogramme(histogramme hist);
void free_tab_boites_englobantes(tab_boite_englobante tab);


void afficherImage(image2D_ptr im, FILE *fileout);
void free_boite_englobante(boite_englobante boite);
tab_boite_englobante traitement_images(image2D_ptr image_pretraitee, CouleurNom couleur);
tab_boite_englobante traiter_image_selon_forme(image2D_ptr image_pretraitee, Objet objet);
#endif