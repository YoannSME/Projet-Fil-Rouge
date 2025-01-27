#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON.h" // Inclure la bibliothèque cJSON

// Définition de la structure Lexicon
typedef struct {
    char **keywords;  // Tableau des mots-clés (en français ou en anglais)
    char **commands;  // Tableau des commandes associées
    int count;        // Nombre d'entrées dans le lexique
    int loaded;       // Indique si le lexique est chargé (1 pour oui, 0 pour non)
} Lexicon;

// Déclaration des fonctions

/**
 * Charge un fichier JSON contenant le lexique dans une structure cJSON.
 * @param filename Le nom du fichier JSON à charger.
 * @return Un pointeur vers l'objet cJSON représentant le fichier JSON, ou NULL en cas d'erreur.
 */
cJSON* load_lexicon_json(const char *filename);

/**
 * Charge un lexique à partir d'un fichier JSON pour une langue spécifique.
 * @param filename Le nom du fichier JSON contenant le lexique.
 * @param language La langue ("fr" ou "en") pour laquelle charger le lexique.
 * @return Une structure Lexicon contenant les mots-clés et commandes pour la langue spécifiée.
 */
Lexicon load_lexicon(const char *filename, const char *language);

/**
 * Convertit une requête utilisateur en commande associée, en se basant sur un lexique.
 * @param request La transcription ou la requête utilisateur.
 * @param lexicon La structure Lexicon contenant les mots-clés et commandes.
 * @param language La langue utilisée ("fr" ou "en").
 * @param command Une chaîne pour stocker la commande générée (doit être allouée par l'appelant).
 * @return 1 si une commande a été trouvée, 0 sinon.
 */
int convert_request_to_command(const char *request, Lexicon lexicon, const char *language, char *command);

/**
 * Exécute un script Python de reconnaissance vocale pour produire une transcription.
 * La transcription est sauvegardée dans un fichier texte.
 */
void execute_python_script();

/**
 * Lit une transcription depuis un fichier texte et la convertit en commande.
 * @param filename Le nom du fichier contenant la transcription.
 * @param language La langue utilisée pour interpréter la transcription.
 */
void process_transcription(const char *filename, const char *language);

#endif // PARSER_H
