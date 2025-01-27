#ifndef UTILS_H
#define UTILS_H

/**
 * @file utils.h
 * @brief Utilitaires pour diverses opérations de base, gestion des piles et des fichiers de log.
 */

#include <stdio.h>  /**< Nécessaire pour le type FILE. */
#include <stdlib.h>

/**
 * @def PATH_LOGFILE
 * @brief Chemin du fichier de log pour le traitement des images.
 */
#define PATH_LOGFILE "/log/Logs_traitement_images"

/**
 * @brief Renvoie le minimum entre deux valeurs.
 */
#define min(a,b) (((a) < (b)) ? (a) : (b))

/**
 * @brief Renvoie le maximum entre deux valeurs.
 */
#define max(a,b) (((a) > (b)) ? (a) : (b))

/**
 * @brief Renvoie le maximum entre trois valeurs.
 */
#define max3(a, b, c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))

/**
 * @brief Renvoie le minimum entre trois valeurs.
 */
#define min3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))

/**
 * @struct coo
 * @brief Structure représentant une coordonnée avec des valeurs x et y.
 */
typedef struct {
  int x; /**< Coordonnée x. */
  int y; /**< Coordonnée y. */
} coo;

/**
 * @typedef Element
 * @brief Alias pour la structure coo.
 */
typedef coo Element;

/**
 * @typedef int8b
 * @brief Alias pour un type de caractère représentant un entier sur 8 bits.
 */
typedef char int8b;

/**
 * @struct s_Cellule
 * @brief Structure représentant une cellule d'une pile.
 */
typedef struct s_Cellule {
  Element val;              /**< Valeur stockée dans la cellule. */
  struct s_Cellule *suiv;   /**< Pointeur vers la cellule suivante. */
} Cellule;

/**
 * @typedef PILE
 * @brief Alias pour un pointeur vers une cellule (début de pile).
 */
typedef Cellule* PILE;

/**
 * @brief Variable globale représentant le nombre de bits.
 */
extern int8b nb_bits;

/**
 * @brief Initialise une pile vide.
 * @return Une pile vide (NULL).
 */
PILE init_PILE();

/**
 * @brief Affiche un message d'erreur et termine le programme.
 * @param message Message d'erreur à afficher.
 */
void Erreur(char *message);

/**
 * @brief Initialise le fichier de log.
 */
void init_logfile();

/**
 * @brief Écrit un message formaté dans le fichier de log.
 * @param message Message à écrire.
 * @param ... Arguments supplémentaires pour le formatage.
 */
void write_logfile(char* message, ...);

/**
 * @brief Ferme le fichier de log.
 */
void close_logfile();

/**
 * @brief Vérifie si une pile est vide.
 * @param p Pile à vérifier.
 * @return 1 si la pile est vide, 0 sinon.
 */
int PILE_estVide(PILE p);

/**
 * @brief Empile un élément dans une pile.
 * @param p Pile dans laquelle empiler.
 * @param e Élément à empiler.
 * @return La pile mise à jour.
 */
PILE emPILE(PILE p, Element e);

/**
 * @brief Dépile un élément d'une pile.
 * @param p Pile de laquelle dépiler.
 * @param e Pointeur pour stocker l'élément dépilé.
 * @return La pile mise à jour.
 */
PILE dePILE(PILE p, Element *e);

#endif
