
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

// Charger le lexique depuis un fichier texte
Lexicon load_lexicon(const char *filename) {
    Lexicon lexicon = {NULL, NULL, 0, 0};

    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return lexicon;
    }

    // Comptons les lignes pour savoir combien d'entrées charger
    char line[256];
    int line_count = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strchr(line, '=')) { // Vérifie qu'il y a une clé et une valeur
            line_count++;
        }
    }
    rewind(file);

    // Allouer la mémoire pour les mots-clés et commandes
    lexicon.keywords = malloc(sizeof(char *) * line_count);
    lexicon.commands = malloc(sizeof(char *) * line_count);
    lexicon.count = line_count;

    // Lire chaque ligne et remplir les tableaux
    int i = 0;
    while (fgets(line, sizeof(line), file)) {
        char *key = strtok(line, "="); // Extraction de la partie avant "="
        char *value = strtok(NULL, "\n"); // Extraction de la partie après "="

        if (key && value) {
            lexicon.keywords[i] = strdup(key);
            lexicon.commands[i] = strdup(value);
            i++;
        }
    }

    fclose(file);
    lexicon.loaded = 2;
    return lexicon;
}

// Convertir une requête texte en commande
int convert_request_to_command(const char *request, Lexicon lexicon, char *command) {
    for (int i = 0; i < lexicon.count; i++) {
        if (strcmp(request, lexicon.keywords[i]) == 0) { // Correspondance exacte
            strcpy(command, lexicon.commands[i]);
            return 1; // Commande trouvée
        }
    }
    return 0; // Commande non trouvée
}

// Libérer la mémoire utilisée par le lexique
void free_lexicon(Lexicon lexicon) {
    for (int i = 0; i < lexicon.count; i++) {
        free(lexicon.keywords[i]);
        free(lexicon.commands[i]);
    }
    free(lexicon.keywords);
    free(lexicon.commands);
}
void execute_python_script() {
    // Exécuter le script Python
    system("python3 reconnaissance_vocale.py");

    // Lire la transcription dans le fichier
    FILE *file = fopen("transcription.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir transcription.txt\n");
        return;
    }

    char transcription[1024];
    if (fgets(transcription, sizeof(transcription), file) != NULL) {
        printf("Transcription lue depuis le fichier : %s\n", transcription);
    }

    fclose(file);
}
