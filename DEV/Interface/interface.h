#ifndef INTERFACE_H
#define INTERFACE_H


/** @defgroup Gestions des interfaces
 *  @brief Les principales fonctionnalités incluent :
 * - L'afichage et le changement d'interfaces
 * - L'appel des diverses fonctionalité du PFR1
 *  @{
 */
/**
 * @file interface.h
 * @brief Définitions et prototypes pour la gestion et le traitement des interfaces.
 */

#include <stdlib.h>
#include <stdio.h>
#include "../Configuration/config.h"
#include "../Image/traitement_images.h"
#include "../Couleur/analyse_couleur.h"
#include "../Commande_vocale/traitement_vocal.h"
#include "../Utils/utils.h"
#define PATH_INTERFACE "Interface/"

/**
 * @brief Affiche l'interface désiré.
 * @param nomFichier chemin vers l'interface à afficher.
 */
int readInterface(char* nomFichier);

/**
 * @brief récuprère le code de l'interface.
 * @param str l'interface sous forme de tableau de char.
 * @return un entier : .
 */
int convert_interface_to_int(const char *str);


/**
 * @brief récuprère l'interface en cours afin de demander à l'utilisateur ce qu'il veut faire 
 * et change l'interface courrante en fonction du choix de l'utilisateur.
 * @param currentInterface l'interface en cours sous forme de tableau de char.
 * @return un entier : (code d'erreur)
 */
int switchInterface(char * currentInterface);

/**
 * @brief récuprère l'interface en cours et change l'interface courrante en fonction du deuxième param.
 * @param currentInterface l'interface en cours sous forme de tableau de char.
 * @param nextInterface simule un choix utilisateur.
 * @return un entier : (code d'erreur)
 */
int switchInterfaceBis(char * currentInterface, char * nextInterface);

/**
 * @brief récuprère l'interface en cours et execute divers code nécéssaire dans cette interface.
 * @param currentInterfaceButitsAnInteger le code de l'interface en cours sous forme d'entier.
 * @param currentInterface l'interface en cours sous forme de tableau de char.
 */
void actionByInterface(int* currentInterfaceButitsAnInteger, char* currentInterface);

#endif

/** @} */ // Fin du groupe ModuleNom