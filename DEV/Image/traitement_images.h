#ifndef TRAITEMENT_IMAGES_H
#define TRAITEMENT_IMAGES_H

/**
 * @file traitement_images.h
 * @brief Définitions et prototypes pour la gestion et le traitement des images et des.
 */

#define NB_BITS_MAX 8

#include "../Utils/utils.h"
#include "../Couleur/analyse_couleur.h"


/**
 * @enum Objet
 * @brief Types d'objets détectables dans une image.
 */
typedef enum
{
    CARRE,  /**< Représente un carré détecté. */
    BALLE,  /**< Représente une balle détectée. */
    NONE    /**< Aucun objet détecté. */
} Objet;

/**
 * @struct s_image3D
 * @brief Structure représentant une image 3D.
 */
typedef struct s_image3D
{
    int ***image; /**< Pointeur vers les données de l'image 3D. */
    int lignes;   /**< Nombre de lignes dans l'image. */
    int colonnes; /**< Nombre de colonnes dans l'image. */
} image3D, *image3D_ptr;

/**
 * @struct s_image2D
 * @brief Structure représentant une image 2D.
 */
typedef struct s_image2D
{
    int **image;  /**< Pointeur vers les données de l'image 2D. */
    int lignes;   /**< Nombre de lignes dans l'image. */
    int colonnes; /**< Nombre de colonnes dans l'image. */
} image2D, *image2D_ptr;

/**
 * @struct histogramme
 * @brief Structure représentant un histogramme.
 */
typedef struct
{
    int taille; /**< Taille de l'histogramme. */
    int *tab;   /**< Tableau contenant les données de l'histogramme. */
} histogramme;

/**
 * @struct boite_englobante
 * @brief Structure représentant une boîte englobante pour un objet détecté.
 */
typedef struct
{
    image2D_ptr image;    /**< Image associée à l'objet. */
    int lig_haut;         /**< Ligne supérieure de la boîte englobante. */
    int lig_bas;          /**< Ligne inférieure de la boîte englobante. */
    int col_gauche;       /**< Colonne gauche de la boîte englobante. */
    int col_droite;       /**< Colonne droite de la boîte englobante. */
    int aire;             /**< Aire de l'objet englobé. */
    int centre_objet[2];  /**< Coordonnées du centre de l'objet. */
    Objet objet;          /**< Type de l'objet détecté. */
    CouleurNom couleurObjet; /**< Couleur associée à l'objet. */
} boite_englobante;

/**
 * @struct s_tab_boite_englobante
 * @brief Structure représentant un tableau de boîtes englobantes.
 */
typedef struct s_tab_boite_englobante
{
    int taille;                 /**< Taille du tableau. */
    boite_englobante *tabBoites; /**< Tableau des boîtes englobantes. */
} tab_boite_englobante;

/**
 * @brief Définit le nombre de bits pour la quantification.
 * @param nb Nombre de bits à définir.
 */
void etablir_nbBits(int8b nb);

/**
 * @brief Lit une image 3D depuis un fichier.
 * @param file Pointeur vers le fichier d'entrée.
 * @param image Pointeur vers l'image 3D à remplir.
 */
void lire_image3D(FILE *file, image3D_ptr image);

/**
 * @brief Alloue de la mémoire pour une image 3D.
 * @param lignes Nombre de lignes dans l'image.
 * @param colonnes Nombre de colonnes dans l'image.
 * @return Pointeur vers la nouvelle image 3D.
 */
image3D_ptr creer_image3D(int lignes, int colonnes);

/**
 * @brief Alloure de la mémoire pour une image 2D.
 * @param lignes Nombre de lignes dans l'image.
 * @param colonnes Nombre de colonnes dans l'image.
 * @return Pointeur vers la nouvelle image 2D.
 */
image2D_ptr creer_image2D(int lignes, int colonnes);

/**
 * @brief Copie une image 2D.
 * @param image_origine Pointeur vers l'image à copier.
 * @return Pointeur vers la copie de l'image.
 */
image2D_ptr copier_image(image2D_ptr image_origine);

/**
 * @brief Initialise une image avec une valeur donnée.
 * @param image Pointeur vers l'image à initialiser.
 * @param valeur Valeur d'initialisation.
 */
void initialiser_image(image2D_ptr image, int valeur);

/**
 * @brief Lit une image 2D depuis un fichier.
 * @param filename Nom du fichier contenant l'image.
 * @return Pointeur vers l'image lue.
 */
image2D_ptr lire_image2D(FILE *filename);

/**
 * @brief Additionne deux images 2D pixel par pixel.
 * @param image1 Première image.
 * @param image2 Deuxième image.
 * @return Pointeur vers l'image résultante.
 */
image2D_ptr additionner_deux_images(image2D_ptr image1, image2D_ptr image2);

/**
 * @brief Effectue une quantification sur nb_bits sur une image RGB.
 * @param filename Nom du fichier contenant l'image à traiter.
 * @return Pointeur vers l'image prétraitée.
 */
image2D_ptr pre_traitement(FILE *filename);

/**
 * @brief Applique un seuillage à une image en fonction d'une couleur.
 * @param img Pointeur vers l'image d'entrée.
 * @param couleur Couleur utilisée pour le seuillage.
 * @return Pointeur vers l'image seuillée.
 */
image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur);

/**
 * @brief Etiquette les pixels d'une image binaire en utilisant le 8-voisinage.
 * @param binaire Pointeur vers l'image binaire à labelliser.
 * @param labels Pointeur vers l'image des labels.
 * @return Nombre de labels trouvés.
 */
int labelliserImage_8voisinage(image2D_ptr binaire, image2D_ptr labels);

/**
 * @brief Reconnaît l'objet représenté par une boîte englobante.
 * @param bte La boîte englobante à analyser.
 * @return Type de l'objet détecté.
 */
Objet reconnaissance_objet(boite_englobante bte);

/**
 * @brief Associe un type d'objet à une chaîne de caractères descriptive.
 * @param objet Type de l'objet.
 * @return Chaîne de caractères décrivant l'objet.
 */
char* association_objet(Objet objet);

/**
 * @brief Calcule les boîtes englobantes des différents objets présents dans l'image à partir d'une image étiquetée (labellisée).
 * @param labels Pointeur vers l'image des labels.
 * @param boites Tableau des boîtes englobantes à remplir.
 * @param nbLabels Nombre de labels dans l'image.
 */
void calculer_boites_englobantes(image2D_ptr labels, image2D_ptr image, boite_englobante *boites, int nbLabels);

/**
 * @brief Crée une boîte englobante pour un objet, cette fonction vient aussi calculer l'aire de la boite englobante 
 * et le centre de l'objet. l'aire pourra être utilisée plus tard pour estimer une distance entre le robot et l'objet.
 * @param image Image contenant l'objet.
 * @param lig_haut Ligne supérieure de la boîte.
 * @param lig_bas Ligne inférieure de la boîte.
 * @param col_gauche Colonne gauche de la boîte.
 * @param col_droite Colonne droite de la boîte.
 * @return La boîte englobante créée.
 */
boite_englobante creer_boiteEnglobante(image2D_ptr image, int lig_haut, int lig_bas, int col_gauche, int col_droite);

/**
 * @brief Entoure un objet détecté par une boîte englobante dans une image, le pointeur vers l'image est stockée 
 * dans un paramètre de la boite englobante
 * @param b La boîte englobante de l'objet.
 */
void entourer_objet(boite_englobante b);

/**
 * @brief Libère la mémoire allouée pour une image 3D.
 * @param im Pointeur vers l'image à libérer.
 */
void free_image3D(image3D_ptr im);

/**
 * @brief Libère la mémoire allouée pour une image 2D.
 * @param im Pointeur vers l'image à libérer.
 */
void free_image2D(image2D_ptr im);

/**
 * @brief Libère la mémoire allouée pour un histogramme.
 * @param hist Histogramme à libérer.
 */
void free_histogramme(histogramme hist);

/**
 * @brief Libère la mémoire allouée pour un tableau de boîtes englobantes.
 * @param tab Tableau de boîtes à libérer.
 */
void free_tab_boites_englobantes(tab_boite_englobante tab);

/**
 * @brief Affiche une image 2D dans un fichier de sortie.
 * @param im Pointeur vers l'image à afficher.
 * @param fileout Fichier de sortie.
 */
void afficherImage(image2D_ptr im, FILE *fileout);

/**
 * @brief Libère la mémoire allouée pour une boîte englobante.
 * @param boite Boîte englobante à libérer.
 */
void free_boite_englobante(boite_englobante boite);

/**
 * @brief Effectue le traitement complet d'une image prétraitée.
 * @param image_pretraitee Image 2D prétraitée.
 * @param couleur Couleur utilisée pour le traitement.
 * @return Tableau des boîtes englobantes détectées.
 */
tab_boite_englobante traitement_images(image2D_ptr image_pretraitee, CouleurNom couleur);

/**
 * @brief Traite une image pour détecter des objets d'une certaine forme.
 * @param image_pretraitee Image 2D prétraitée.
 * @param objet Forme de l'objet à détecter.
 * @return Tableau des boîtes englobantes détectées.
 */
tab_boite_englobante traiter_image_selon_forme(image2D_ptr image_pretraitee, Objet objet);

/**
 * @brief Initialise le fichier log pour le traitement d'images.
 */
void initialisationLogfileTraitementImage();

/**
 * @brief Lance le traitement d'une image selon sa couleur à partir d'un fichier d'entrée et écrit le résultat dans un fichier de sortie. 
 * Surtout utilisé pour la démonstration du PFR1
 * @param entree Nom du fichier d'entrée.
 * @param sortie Nom du fichier de sortie.
 */
void appel_traitement_image_selon_couleur(char entree[], char sortie[],CouleurNom couleur);

void appel_traitement_image_selon_forme(char entree[], char sortie[],Objet objet);

#endif