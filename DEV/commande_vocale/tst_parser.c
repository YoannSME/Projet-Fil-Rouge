#include <stdio.h>
#include "parser.h"

int main() {
    printf("=== Programme de traitement de transcription ===\n");

    // Étape 1 : Exécuter le script Python
    printf("[INFO] Exécution du script Python pour récupérer la transcription...\n");
    execute_python_script();

    // Étape 2 : Choisir la langue
    char langue[10];
    find_in_config("Langue", langue);
    const char *language = "FR";  // Par défaut, on utilise le français
    printf("[INFO] Langue sélectionnée : %s\n", langue);

    // Étape 3 : Traiter la transcription
    printf("[INFO] Traitement de la transcription...\n");
    process_transcription("transcription.txt", langue);

    printf("[INFO] Programme terminé.\n");
    return 0;
}
