#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char **keywords;     // Tableau des mots-clés
    char **commands;     // Tableau des commandes associées
    int count;           // Nombre de paires (mot-clé, commande)
    int loaded;          // 1 si le lexique est chargé avec succès, sinon 0
} Lexicon;

// Déclaration de la fonction qui exécute le script Python
void execute_python_script();

// Charger le lexique depuis un fichier texte
Lexicon load_lexicon(const char *filename);

// Convertir une requête texte en commande
int convert_request_to_command(const char *request, Lexicon lexicon, char *command);

// Libérer la mémoire utilisée par le lexique
void free_lexicon(Lexicon lexicon);

#endif
