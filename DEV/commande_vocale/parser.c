#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cJSON.h" // Inclure la bibliothèque cJSON (assurez-vous de l'avoir installée)
#include <ctype.h>
// Définition de la structure Lexicon
typedef struct {
    char **keywords;  // Tableau contenant les mots-clés
    char **commands;  // Tableau contenant les commandes associées
    int count;        // Nombre total de mots-clés et commandes
    int loaded;       // Indique si le lexique a été chargé avec succès
} Lexicon;


int* extract_numbers(const char* chemin, int* size) {
    FILE *filename = fopen(chemin, "r");

    if (filename == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    char buffer[512];
    int* numbers = NULL;  // Tableau dynamique pour stocker les nombres
    *size = 0;            // Taille initiale du tableau

    // Lire le fichier ligne par ligne
    while (fgets(buffer, sizeof(buffer), filename) != NULL) {
        const char* ptr = buffer;
        while (*ptr != '\0') {
            // Identifier un nombre (positif ou négatif)
            if (isdigit(*ptr) || (*ptr == '-' && isdigit(*(ptr + 1)))) {
                int num = strtol(ptr, (char**)&ptr, 10);

                // Réallouer pour stocker le nouveau nombre
                numbers = realloc(numbers, (*size + 1) * sizeof(int));
                if (numbers == NULL) {
                    perror("Erreur d'allocation de memoire");
                    fclose(filename);
                    exit(EXIT_FAILURE);
                }

                numbers[*size] = abs(num); // Stocker la valeur absolue
                (*size)++;
            } else {
                ptr++; // Avancer si ce n'est pas un chiffre
            }
        }
    }

    fclose(filename);
    return numbers;
}



Lexicon load_lexicon(const char *filename, const char *language) {
    Lexicon lexicon = {NULL, NULL, 0, 0};  // Initialise le lexique

    // Ouvrir le fichier JSON
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir le fichier %s\n", filename);
        return lexicon;
    }

    // Lire le contenu du fichier dans un buffer
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = malloc(length);
    fread(data, 1, length, file);
    fclose(file);

    // Parser le JSON
    cJSON *json = cJSON_Parse(data);
    free(data);
    if (!json) {
        fprintf(stderr, "Erreur : Impossible de parser le fichier JSON\n");
        return lexicon;
    }

    // Extraire la section de langue choisie (fr ou en)
    cJSON *language_section = cJSON_GetObjectItemCaseSensitive(json, language);
    if (!language_section) {
        fprintf(stderr, "Erreur : Langue non trouvée dans le fichier JSON\n");
        cJSON_Delete(json);
        return lexicon;
    }

    // Compter les éléments dans la section de langue
    int count = cJSON_GetArraySize(language_section);
    lexicon.keywords = malloc(sizeof(char *) * count);
    lexicon.commands = malloc(sizeof(char *) * count);
    lexicon.count = count;

    // Remplir le lexique avec les mots et commandes
    int i = 0;
    cJSON *item = NULL;
    cJSON_ArrayForEach(item, language_section) {
        const char *key = item->string;
        const char *command = cJSON_GetStringValue(item);

        lexicon.keywords[i] = strdup(key);
        lexicon.commands[i] = strdup(command);
        i++;
    }

    lexicon.loaded = 1;
    cJSON_Delete(json);
    return lexicon;

    
}


// Fonction pour convertir une transcription en commande
int convert_request_to_command(const char *request, Lexicon lexicon, const char *language, char *command) {
    if (request == NULL || lexicon.keywords == NULL || lexicon.commands == NULL || language == NULL || command == NULL) {
        return 0; // Erreur : paramètres invalides
    }

    // Sélectionner les mots-clés en fonction de la langue
    char **keywords = lexicon.keywords;

    // Découper la transcription en mots
    char temp_request[256];
    strcpy(temp_request, request);  // Copie de la transcription pour modification

    char *word = strtok(temp_request, " ");
    while (word != NULL) {
        // Comparer chaque mot avec les mots-clés du lexique
        for (int i = 0; i < lexicon.count; i++) {
            if (strcmp(word, keywords[i]) == 0) { // Correspondance exacte
                strcpy(command, lexicon.commands[i]);
                return 1; // Commande trouvée
            }
        }
        word = strtok(NULL, " ");  // Passer au mot suivant
    }

    return 0; // Commande non trouvée
}
// Fonction principale pour traiter une transcription
void process_transcription(const char *filename, const char *language) {
    // Charger le dictionnaire JSON dans le lexique
    int nbElems;
    int* val1 = extract_numbers(filename,&nbElems);
    
    Lexicon lexicon = load_lexicon("dictionnaire.json", language);
    if (!lexicon.loaded) {
        fprintf(stderr, "Erreur : Le dictionnaire n'a pas pu être chargé.\n");
        return;
    }

    // Lire la transcription depuis le fichier
    char transcription[1256];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur : Impossible d'ouvrir %s\n", filename);
        return;
    }

    if (fgets(transcription, sizeof(transcription), file) != NULL) {
        printf("Transcription récupérée : %s\n", transcription);

        char command[256];
        if (convert_request_to_command(transcription, lexicon, language,command)) {
            make_file("commande/transcription.txt");
            add_row_to_file("commande/transcription.txt", command);
            // printf("Commande générée : %s(%d) \n ", command,val1[0]);
            
        } else {
            printf("Erreur : Aucune commande reconnue.\n");
        }
    }

    fclose(file);

    // Libérer la mémoire allouée dans le lexique
    for (int i = 0; i < lexicon.count; i++) {
        free(lexicon.keywords[i]);
        free(lexicon.commands[i]);
    }
    free(lexicon.keywords);
    free(lexicon.commands);
}

// Fonction pour exécuter le script Python (simulateur de reconnaissance vocale)
void execute_python_script() {
    system("python3 reconnaissance_vocale.py");

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




