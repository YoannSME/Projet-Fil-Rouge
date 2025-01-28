#ifndef CONFIG_H
#define CONFIG_H


/** @defgroup Gestions de la configuration et des logs
 *  @brief Les principales fonctionnalités incluent :
 * - La gestions des logs
 * - La gestions des différentes configuration
 *  @{
 */
/**
 * @file config.h
 * @brief Définitions et prototypes pour la gestion et le traitement des configurations.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PATH_CONFIG "Configuration/config"

/**
 * @brief Réalise les différentes étapes nécéssaire à l'initialisation du projet.
 * @return un entier : (code d'erreur).
 */
int init();

/**
 * @brief Ajoute une ligne au fichier log courrant.
 * @param message le message à écrire dans la nouvelle ligne.
 * @return un entier : (code d'erreur).
 */
int updateLog(const char *message);

/**
 * @brief Permet de savoir si un fichier existe.
 * @param nomFichier chemin vers le fichier potentiel.
 * @return un entier : 1 si le fichier existe / 0 si il n'existe pas.
 */
int file_exists(const char *filename);

/**
 * @brief Affiche le fichier config.
 * @param nomFichier chemin vers le fichier de config.
 * @return un entier : (code d'erreur).
 */
int read_config(char *nomFichier);

/**
 * @brief cherche dans le fichier config l'element corespondant dans le premier param afin d'en donner la valeur dans le deuxième param
 * @param configtofind tableau de char de la key cherchée.
 * @param exit tableau de char qui contiendra la value trouvée.
 * @return un entier : (code d'erreur).
 */
int find_in_config(char *configtofind, char *exit);

/**
 * @brief enlève le dernier caractère du chaine
 * @param chaine la chaine en question
 */
void remove_last_char(char *chaine);

/**
 * @brief change la value de la configuration donner à param 1 par la value du param 2. 
 * Si le param 2 et NULL alors il seras demander à l'utilisateur de le saisir
 * @param configtochange tableau de char de la key cherchée.
 * @param new_val_optional tableau de char qui contiendra la value à écrire. (Si le param 2 et == NULL alors il seras demander à l'utilisateur de le saisir)
 * @return un entier : (code d'erreur).
 */
int change_config(char *configtochange, const char *new_val_optional);

/**
 * @brief créé un fichier à l'emplacement du param 1
 * @param nomFichier chemin du fichier à créer.
 * @return un entier : (code d'erreur).
 */
int make_file(const char *nomFichier);

/**
 * @brief ajoute une ligne à un fichier donner en param
 * @param nomFichier chemin du fichier à modifier.
 * @param ligne tableau de char contenu de la ligne à écrire.
 * @return un entier : (code d'erreur).
 */
int add_row_to_file(const char *nomFichier, const char *ligne);

/**
 * @brief renome un fichier
 * @param ancienNom chemin/nom du fichier à modifier.
 * @param nouveauNom nouveau chemin/nom du fichier.
 * @return un entier : (code d'erreur).
 */
int rename_file(const char *ancienNom, const char *nouveauNom);

/**
 * @brief supprime un fichier
 * @param nomFichier chemin du fichier à supprimer.
 * @return un entier : (code d'erreur).
 */
int remove_file(const char *nomFichier);
#endif

/** @} */ // Fin du groupe ModuleNom