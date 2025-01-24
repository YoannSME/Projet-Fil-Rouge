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


#define tl 2
int main(int argc, char **argv)
{

    if (argc < 2)
    {
        fprintf(stderr, "Usage[%s] nombre de bits de quantification\n", argv[0]);
        exit(1);
    }

    int nb_bits = atoi(argv[1]);
    if (nb_bits < 3 || nb_bits > 7)
    {
        fprintf(stderr, "Nombre de bits de quantification invalide, choisir entre 3 et 7, 2 pour les coquins.\n");
        if (nb_bits != 2)
        {
            exit(1);
        }
    }

    etablir_nbBits(nb_bits);

    /*char chemin[21][512] = {
        "IMG_5389", "IMG_5390", "IMG_5391", "IMG_5392",
        "IMG_5393", "IMG_5394", "IMG_5395", "IMG_5396",
        "IMG_5397", "IMG_5398", "IMG_5399", "IMG_5400",
        "IMG_5401", "IMG_5402", "IMG_5403", "IMG_5404",
        "IMG_5405", "IMG_5406", "IMG_5407", "IMG_5408","img_1"};*/

    char chemin[tl][512] = { "IMG_5402","IMG_5395"};
    
    /*char chemin[tl][512] = {"IMG_5389", "IMG_5390", "IMG_5391", "IMG_5392", "IMG_5393", "IMG_5394","IMG_5395","IMG_5396","IMG_5397","IMG_5398",
     "IMG_5399", "IMG_5400","IMG_5401", "IMG_5402", "IMG_5403","IMG_5404",
        "IMG_5405", "IMG_5406", "IMG_5407","IMG_5408","img_1"};*/
    char entree[1024];
    char sortie[1024];
    clock_t
        temps_initial, /* Temps initial en micro-secondes */
        temps_final;   /* Temps final en micro-secondes */
    float
        temps_cpu;
    /* Temps total en secondes */
    temps_initial = clock();
    // boite_englobante boite;
    for (int i = 0; i < tl; i++)
    {
        snprintf(entree, sizeof(entree), "Data/%.500s.txt", chemin[i]);
        snprintf(sortie, sizeof(sortie), "sortie/%.500s_v2.txt", chemin[i]);
        FILE *fichier_entree = fopen(entree, "r");
        FILE *fichier_sortie = fopen(sortie, "w");

        image2D_ptr image_pretraitee = pre_traitement(fichier_entree);
        tab_boite_englobante tab = traiter_image_selon_forme(image_pretraitee,BALLE);
        afficherImage(tab.tabBoites[0].image,fichier_sortie);
        free_tab_boites_englobantes(tab);
        
        free_image2D(image_pretraitee); 
       
        fclose(fichier_sortie);
        fclose(fichier_entree);
    }

    temps_final = clock();
    temps_cpu = (temps_final - temps_initial) * 1e-5;
    printf("TEMPS CPU : %f\n", temps_cpu);

    return 0;
}


/*image2D_ptr im_test = pre_traitement(fichier_entree);
        image2D_ptr imSeuille = seuillage(im_test, COL_ORANGE);
        image2D_ptr labels = creer_image2D(imSeuille->lignes, imSeuille->colonnes);
        int nbComp = labelliserImage_8voisinage(imSeuille, labels);
        printf("%d objets trouvés\n", nbComp);
        tab_boite_englobante tab;
        tab.tabBoites = malloc(nbComp * sizeof(boite_englobante));

        if (!tab.tabBoites)
        {
            Erreur("tab boite");
        }
        tab.taille = nbComp;
        
        calculer_bounding_boxes(labels, tab.tabBoites, nbComp);
       
       for(int j =0;j<nbComp;j++){
            tab.tabBoites[j].image = imSeuille;
            entourer_objet(tab.tabBoites[j]); 
       }
        afficherImage(imSeuille, fichier_sortie);
        

        free_image2D(im_test);
        free(tab.tabBoites);
        free_image2D(imSeuille);
        free_image2D(labels);*/


//V2
  /*for (int i = 0; i < tl; i++)
    {
        snprintf(entree, sizeof(entree), "Data/%.500s.txt", chemin[i]);
        snprintf(sortie, sizeof(sortie), "sortie/%.500s_v2.txt", chemin[i]);
        FILE *fichier_entree = fopen(entree, "r");
        FILE *fichier_sortie = fopen(sortie, "w");

        image2D_ptr image_pretraitee = pre_traitement(fichier_entree);
        tab_boite_englobante tab = traitement_images(image_pretraitee, COL_ORANGE);
        if(tab.tabBoites != NULL){
            afficherImage(tab.tabBoites[0].image,fichier_sortie);

        }
        free_tab_boites_englobantes(tab);
        
        free_image2D(image_pretraitee); 
       
        fclose(fichier_sortie);
        fclose(fichier_entree);*/