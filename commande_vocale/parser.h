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


cJSON* load_lexicon_json(const char *filename);


Lexicon load_lexicon(const char *filename, const char *language);


int convert_request_to_command(const char *request, Lexicon lexicon, const char *language, char *command);

void execute_python_script();


void process_transcription(const char *filename, const char *language);

#endif // PARSER_H
