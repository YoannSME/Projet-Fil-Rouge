#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

int read_config(char *nomFichier){
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strchr(ligne, '=')){
            printf("%s", ligne);
        }      
    }

    // Fermer le fichier
    fclose(fichier);
    printf("\n");
    return EXIT_SUCCESS;
}

void supprimerDernierCaractere(char *chaine) {
    int longueur = strlen(chaine);
    
    // Vérifier si la chaîne n'est pas vide
    if (longueur > 0) {
        chaine[longueur - 1] = '\0';  // Remplacer le dernier caractère par '\0'
    }
}

char* find_in_config(char *nomFichier, char *configtofind){
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne
    static char result[255]; // static sinon warning

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strchr(ligne, '=')){ // vérif si il y'a un =
            if (strstr(ligne, configtofind)){ //vérif si cela correspond à la config chercher
                char *pos = strchr(ligne, '='); //garde que ce qui a après le =
                fclose(fichier);
                // char *result;
                strcpy(result, pos + 1); // Sorcellerie merci mon pote le dev
                supprimerDernierCaractere(result);
                return result;
            }
        }      
    }
    return "EXIT_FAILURE";
}