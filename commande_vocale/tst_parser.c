
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main() {
     execute_python_script();
    // Charger les ressources lexicales depuis un fichier texte
    Lexicon lexicon = load_lexicon("dictionnaire.txt");
    if (!lexicon.loaded) {
        fprintf(stderr, "Erreur : Le lexique n'a pas été chargé correctement.\n");
        return 1;
    }

    // Lire une requête texte
    char transcription[1256];
    FILE *file = fopen("transcription.txt", "r");
    if (file == NULL) {
        printf("Erreur : Impossible d'ouvrir transcription.txt\n");
        return 1;
    }
    if (fgets(transcription, sizeof(transcription), file) != NULL) {
        printf("Transcription récupérée : %s\n", transcription);

        // Convertir la requête texte en commande
        char command[256];
        if (convert_request_to_command(transcription, lexicon, command)) {
        printf("Commande générée : %s\n", command);
        } else {
          printf("Erreur : Requête non reconnue.\n");
         }
    }
    // Libérer la mémoire utilisée par le lexique
    free_lexicon(lexicon);

    return 0;
}
