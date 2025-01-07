#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traitement_images.h"  // Contient les déclarations de pre_traitement, seuillage, etc.

// Affichage simple d’une image 2D quantifiée
void afficherImage(image2D_ptr im, FILE* fileout) {
    // On peut afficher dans la console et/ou dans le fichier de sortie.
    // Ici, juste un exemple : impression dans 'fileout'.
    fprintf(fileout, "%d %d\n", im->lignes, im->colonnes);
    for (int i = 0; i < im->lignes; i++) {
        for (int j = 0; j < im->colonnes; j++) {
            fprintf(fileout, "%d ", im->image[i][j]);
        }
        fprintf(fileout, "\n");
    }
}

// Affichage d’un histogramme (optionnel)
void afficher_hist(histogramme h) {
    int taille = h.taille;
    for (int i = 0; i < taille; i++) {
        if (h.tab[i] > 0) {
            printf("Valeur : %d | %d\n", i, h.tab[i]);
        }
    }
}

int main(int argc, char** argv) {
    // On vérifie qu’au moins un argument est passé (par ex. argv[1] = "dossier" ou autre)


    // Nombre de bits que vous utilisez pour quantifier la couleur
    int nb_bits = 2;

    // Déclarations des variables
    FILE *filename = NULL, *fileout = NULL;
    image2D_ptr im = NULL;
    image2D_ptr img = NULL;

    // Tableau des fichiers de base (sans extension .txt)
    // On a bien 20 chaînes ici :
    char chemin[20][512] = {
        "IMG_5389", "IMG_5390", "IMG_5391", "IMG_5392",
        "IMG_5393", "IMG_5394", "IMG_5395", "IMG_5396", 
        "IMG_5397", "IMG_5398", "IMG_5399", "IMG_5400",
        "IMG_5401", "IMG_5402", "IMG_5403", "IMG_5404",
        "IMG_5405", "IMG_5406", "IMG_5407", "IMG_5408"
    };


    // Buffers pour fabriquer les noms de fichier
    char buffer[512];  // Pour le fichier d’entrée
    char sortie[512];  // Pour le fichier de sortie

    // On boucle sur 20 images
    for (int i = 0; i < 20; i++) {
        // 1) Construire le nom du fichier d’entrée : "IMG_53xx.txt"
        sprintf(buffer, "Data/%s.txt", chemin[i]);  // ex: "IMG_5389.txt"
        
        // 2) Ouvrir le fichier en lecture
        filename = fopen(buffer, "r");
        if (!filename) {
            fprintf(stderr, "Impossible d’ouvrir le fichier %s\n", buffer);
            continue; // On passe à l’image suivante
        }

        // 3) Construire le nom du fichier de sortie : "IMG_53xx_v2.txt"
        sprintf(sortie, "sortie/%s_v2.txt", chemin[i]);  // ex: "IMG_5389_v2.txt"

        // 4) Ouvrir le fichier de sortie
        fileout = fopen(sortie, "w");
        if (!fileout) {
            fprintf(stderr, "Impossible de créer le fichier %s\n", sortie);
            fclose(filename);
            continue;
        }

        // 5) Traitement de l’image
        // pre_traitement va lire dans 'filename' et créer une structure d’image
        im = pre_traitement(filename, nb_bits);

        // 6) Seuillage (par exemple sur la couleur COL_JAUNE)
        img = seuillage(im, COL_JAUNE, nb_bits);

        // 7) Affichage / Écriture de l’image résultat dans le fichier de sortie
        afficherImage(img, fileout);


        // 9) Fermeture des deux fichiers
        fclose(fileout);
        fclose(filename);
    }

    return 0;
}
