#include <stdlib.h>
#include <stdio.h>
#include "interface.h"

int readInterface(char nomFichier[100]) {
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    // Fermer le fichier
    fclose(fichier);
    printf("\n");
    return 0;
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");  // Ouvre le fichier en mode lecture
    if (file) {
        fclose(file);  // Ferme le fichier si ouvert avec succès
        return 1;  // Le fichier existe
    }
    return 0;  // Le fichier n'existe pas
}

int convert_to_int_after_slash(const char *str) {
    char *pos = strchr(str, '/');
    if (pos != NULL) {
        // Convertir la chaîne après '/' en entier avec strtol
        char *endptr;
        long result = strtol(pos + 1, &endptr, 10);  // Base 10 pour décimal
        
        // Vérifier si la conversion a réussi
        if (*endptr == '\0') {  // Aucun caractère non numérique après le nombre
            return (int)result;
        } else {
            // Si la conversion échoue (par exemple, s'il y a des caractères non numériques après le nombre)
            return 0;
        }
    }
    
    return 0;  // Si '/' n'est pas trouvé
}