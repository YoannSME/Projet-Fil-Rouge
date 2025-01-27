#ifndef ANALYSE_COULEUR
#define ANALYSE_COULEUR

/**
 * @file analyse_couleur.h
 * @brief Définitions et prototypes pour l'analyse et la manipulation des couleurs.
 */

#include "../Utils/utils.h"

/**
 * @enum CouleurNom
 * @brief Représente les noms des couleurs possibles pour un objet.
 */
typedef enum {
    COL_BLEU,     /**< Couleur bleue. */
    COL_JAUNE,    /**< Couleur jaune. */
    COL_ORANGE,   /**< Couleur orange. */
    COL_INCONNU,  /**< Couleur inconnue. */
} CouleurNom;



/**
 * @brief Quantifie une valeur pour ses composantes RGB.
 * @param valeur Valeur d'entrée quantifiée.
 * @param r Pointeur pour stocker la composante rouge.
 * @param g Pointeur pour stocker la composante verte.
 * @param b Pointeur pour stocker la composante bleue.
 */
void quantification(int valeur, int8b *r, int8b *g, int8b *b);

/**
 * @brief Convertit une couleur RGB en HSV.
 *
 * @param r Composante rouge de la couleur (0-255).
 * @param g Composante verte de la couleur (0-255).
 * @param b Composante bleue de la couleur (0-255).
 * @param h Pointeur pour stocker la teinte (hue).
 * @param s Pointeur pour stocker la saturation.
 * @param v Pointeur pour stocker la valeur (luminosité))
 * @param max_val Valeur maximale pour normaliser les composantes RGB (généralement 255).
 */
void rgb_to_hsv(int8b r, int8b g, int8b b, float *h, float *s, float *v, int max_val);

/**
 * @brief Convertit une valeur entière en une couleur .
 *
 * @param valeur Valeur d'entrée représentant une couleur.
 * @return Le nom de la couleur correspondante.
 */
CouleurNom conversion_couleur(int valeur);

/**
 * @brief Associe un nom à une couleur.
 *
 * @param couleur Nom de la couleur à associer.
 */
void association_couleur(CouleurNom couleur);

#endif