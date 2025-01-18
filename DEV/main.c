#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Image/traitement_images.h" 
#include "Couleur/analyse_couleur.h"

#include "Utils/utils.h"


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
        fprintf(stderr, "Usage[%s] nombre de bits de quantification\n", argv[0]);
        exit(1);
    }

    int nb_bits = atoi(argv[1]);
    if(nb_bits <3||nb_bits >7){
        fprintf(stderr, "Nombre de bits de quantification invalide, choisir entre 3 et 7, 2 pour les coquins.\n");
        if(nb_bits !=2){
            exit(1);
            
            
        }
    }

    etablir_nbBits(nb_bits);
    

    
    
    char chemin[20][512] = {
        "IMG_5389", "IMG_5390", "IMG_5391", "IMG_5392",
        "IMG_5393", "IMG_5394", "IMG_5395", "IMG_5396",
        "IMG_5397", "IMG_5398", "IMG_5399", "IMG_5400",
        "IMG_5401", "IMG_5402", "IMG_5403", "IMG_5404",
        "IMG_5405", "IMG_5406", "IMG_5407", "IMG_5408"};

    //char chemin[3][512] = {"IMG_5392", "IMG_5390", "IMG_5391"};
    char entree[1024];
    char sortie[1024];

    clock_t
        temps_initial, /* Temps initial en micro-secondes */
        temps_final;   /* Temps final en micro-secondes */
    float
        temps_cpu;
    /* Temps total en secondes */
    temps_initial = clock();
    boite_englobante boite;
    for (int i = 0; i <20; i++)
    {
        snprintf(entree, sizeof(entree), "Data/%.500s.txt", chemin[i]);
        snprintf(sortie, sizeof(sortie), "sortie/%.500s_v2.txt", chemin[i]);

        boite = traitement_image(entree,sortie,COL_BLEU);
        free_boite_englobante(boite);
        

        
    }

    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-5;
    printf("TEMPS CPU : %f\n", temps_cpu);

    return 0;
}