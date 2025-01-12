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
        printf("Erreur lors de l'ouverture du fichier");
        return 1;
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
    return 0;
}

void remove_last_char(char *chaine){
    int longueur = strlen(chaine);
    
    // Vérifier si la chaîne n'est pas vide
    if (longueur > 0) {
        chaine[longueur - 1] = '\0';  // Remplacer le dernier caractère par '\0'
    }
}

int make_file(const char *nomFichier){
    FILE *fichier = fopen(nomFichier, "w");  // Ouvre le fichier en mode écriture
    if (fichier == NULL) {
        printf("Erreur lors de la création du fichier");
        return 1;
    }
    fclose(fichier);
    return 0;
}

int add_row_to_file(const char *nomFichier, const char *ligne) {
    FILE *fichier = fopen(nomFichier, "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    fprintf(fichier, "%s\n", ligne);
    fclose(fichier);
    return 0;
}

int rename_file(const char *ancienNom, const char *nouveauNom) {
    if (rename(ancienNom, nouveauNom) == 0) return 0;
    return 1;
}

int remove_file(const char *nomFichier) {
    if (remove(nomFichier) == 0) return 0;
    return 1;
}

char* find_in_config(char *nomFichier, char *configtofind){
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne
    static char result[255]; // static sinon warning

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strchr(ligne, '=')){ // vérif si il y'a un =
            if (strstr(ligne, configtofind)){ //vérif si cela correspond à la config chercher
                char *pos = strchr(ligne, '='); //garde que ce qui a après le =
                fclose(fichier);
                strcpy(result, pos + 1); // Sorcellerie merci mon pote le dev
                remove_last_char(result); // pour retirer le retour chariot
                return result;
            }
        }      
    }
    printf("%s n'est pas reconnue comme une configuration existante\n", configtofind);
    return NULL;
}

int change_config(char *nomFichier, char *configtochange){
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne*
    char new_val[100];
    char new_ligne[256];

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier");
    }

    if (make_file("tempconfig")) return 1;
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strchr(ligne, '=') && strstr(ligne, configtochange)){
            printf("Quelle nouvelle valeur voulez vous donner à ce param ?\n");
            scanf("%20s", new_val);

            strcpy(new_ligne, configtochange);

            strcat(new_ligne, "=");
            strcat(new_ligne, new_val);
            add_row_to_file("tempconfig", new_ligne);

        }else{
            remove_last_char(ligne);
            add_row_to_file("tempconfig", ligne);
        }
    }
    fclose(fichier);
    if (remove_file("config")) return 1;
    if (rename_file("tempconfig", "config")) return 1;
    return 0;
}