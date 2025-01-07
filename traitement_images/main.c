#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "traitement_images.h" // Contient les déclarations de pre_traitement, seuillage, etc.

// Affichage simple d’une image 2D quantifiée
void afficherImage(image2D_ptr im, FILE *fileout)
{
    // On peut afficher dans la console et/ou dans le fichier de sortie.
    // Ici, juste un exemple : impression dans 'fileout'.
    fprintf(fileout, "%d %d\n", im->lignes, im->colonnes);
    for (int i = 0; i < im->lignes; i++)
    {
        for (int j = 0; j < im->colonnes; j++)
        {
            fprintf(fileout, "%d ", im->image[i][j]);
        }
        fprintf(fileout, "\n");
    }
}

// Affichage d’un histogramme (optionnel)
void afficher_hist(histogramme h)
{
    int taille = h.taille;
    for (int i = 0; i < taille; i++)
    {
        if (h.tab[i] > 0)
        {
            printf("Valeur : %d | %d\n", i, h.tab[i]);
        }
    }
}

int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage[%s] nombre de bits de quantification", argv[0]);
        exit(1);
    }

    clock_t
        temps_initial, /* Temps initial en micro-secondes */
        temps_final;   /* Temps final en micro-secondes */
    float
        temps_cpu;
    /* Temps total en secondes */
    temps_initial = clock();
    int nb_bits = atoi(argv[1]);

    FILE *filename = NULL, *fileout = NULL;
    image2D_ptr im = NULL;
    image2D_ptr img = NULL;

    
    char chemin[20][512] = {
        "IMG_5389", "IMG_5390", "IMG_5391", "IMG_5392",
        "IMG_5393", "IMG_5394", "IMG_5395", "IMG_5396",
        "IMG_5397", "IMG_5398", "IMG_5399", "IMG_5400",
        "IMG_5401", "IMG_5402", "IMG_5403", "IMG_5404",
        "IMG_5405", "IMG_5406", "IMG_5407", "IMG_5408"};

    //char chemin[1][512] = {"IMG_5391"};
    char buffer[512];
    char sortie[512];

    for (int i = 0; i < 20; i++)
    {
        sprintf(buffer, "Data/%s.txt", chemin[i]);

        filename = fopen(buffer, "r");
        if (!filename)
        {
            fprintf(stderr, "Impossible d’ouvrir le fichier %s\n", buffer);
            continue;
        }

        sprintf(sortie, "sortie/%s_v2.txt", chemin[i]);

        fileout = fopen(sortie, "w");
        if (!fileout)
        {
            fprintf(stderr, "Impossible de créer le fichier %s\n", sortie);
            fclose(filename);
            continue;
        }

        im = pre_traitement(filename, nb_bits);

        img = seuillage(im, COL_JAUNE, nb_bits);
        img = encadrer(img);

        afficherImage(img, fileout);

        fclose(fileout);
        fclose(filename);
        free_image2D(im);
        free_image2D(img);
    }

    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-5;
    printf("TEMPS CPU : %f\n", temps_cpu);

    return 0;
}
