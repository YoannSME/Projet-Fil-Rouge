#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include "config.h"



int init(){
    char timestampButItsAChar[20];
    char logFileName[25] = "log/";
    time_t timestamp = time(NULL); // Timestamp en secondes
    snprintf(timestampButItsAChar, sizeof(timestampButItsAChar), "%ld", timestamp);
    if (!file_exists(PATH_CONFIG)) return 1;
    if (change_config("currentLogFile", timestampButItsAChar)) return 1;
    if (make_file(strcat(logFileName, timestampButItsAChar))) return 1;
    if (updateLog("Création du fichier log")) return 1;

    return 0;
}   

int updateLog(const char *message){
    char timestampButItsAChar[20];
    char logFile[25] = "log/";
    if(find_in_config("currentLogFile", timestampButItsAChar)) return 1;
    strcat(logFile, timestampButItsAChar);

    FILE *fichier = fopen(logFile, "a");
    if (fichier == NULL) {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier %s",logFile);
        return 1;
    }

    time_t timestamp = time(NULL);
    snprintf(timestampButItsAChar, sizeof(timestampButItsAChar), "%ld", timestamp);

    fprintf(fichier, "%s\t:\t%s\n", timestampButItsAChar, message);
    fclose(fichier);
    return 0;
}

int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");  // Ouvre le fichier en mode lecture
    if (file) {
        fclose(file);  // Ferme le fichier si ouvert avec succès
        return 1;  // Le fichier existe
    }
    fprintf(stderr,"Le fichier %s n'existe pas\n", filename);
    return 0;  // Le fichier n'existe pas
}

int read_config(char *nomFichier){
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier %s",nomFichier);
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
        fprintf(stderr,"Erreur lors de la création du fichier %s",nomFichier);
        return 1;
    }
    fclose(fichier);
    return 0;
}

int add_row_to_file(const char *nomFichier, const char *ligne) {
    FILE *fichier = fopen(nomFichier, "a");
    if (fichier == NULL) {
        fprintf(stderr,"Erreur lors de l'ajout d'une ligne dans le fichier %s\n",nomFichier);
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

int find_in_config(char *configtofind, char *exit){
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(PATH_CONFIG, "r");
    if (fichier == NULL) {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier %s rien trouvé dans config\n", PATH_CONFIG);
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strchr(ligne, '=')){ // vérif si il y'a un =
            if (strstr(ligne, configtofind)){ //vérif si cela correspond à la config chercher
                fclose(fichier);
                strcpy(exit, strchr(ligne, '=') + 1); //garde que ce qui a après le = // et le copy dans exit
                remove_last_char(exit); // pour retirer le retour chariot
                return 0;
            }
        }      
    }
    printf("%s n'est pas reconnue comme une configuration existante\n", configtofind);
    return 1;
}

int change_config(char *configtochange, const char *new_val_optional) {
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne
    char new_val[100]; // Valeur temporaire
    char new_ligne[256];

    // Ouvrir le fichier en mode lecture
    fichier = fopen(PATH_CONFIG, "r");
    if (fichier == NULL) {
        fprintf(stderr,"Erreur lors du changement du fichier %s",PATH_CONFIG);
        return 1;
    }

    // Créer un fichier temporaire
    if (make_file("tempconfig")) {
        fclose(fichier);
        return 1;
    }

    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        if (strchr(ligne, '=') && strstr(ligne, configtochange)) {
            if (new_val_optional == NULL) {
                printf("Quelle nouvelle valeur voulez-vous donner à ce param ?\n");
                scanf("%99s", new_val);
            } else { // si jamais la nouvelle valeur est déjà passer un param
                strncpy(new_val, new_val_optional, sizeof(new_val) - 1);
                new_val[sizeof(new_val) - 1] = '\0'; // Sécurité pour éviter un débordement
            }

            // Construire la nouvelle ligne
            snprintf(new_ligne, sizeof(new_ligne), "%s=%s", configtochange, new_val);
            add_row_to_file("tempconfig", new_ligne);
        } else {
            remove_last_char(ligne); // Supprime le dernier caractère si nécessaire
            add_row_to_file("tempconfig", ligne);
        }
    }

    fclose(fichier);

    // Remplacer le fichier original
    if (remove_file(PATH_CONFIG)) return 1;
    if (rename_file("tempconfig", PATH_CONFIG)) return 1;

    return 0;
}