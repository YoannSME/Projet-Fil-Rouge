#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traitement_images.h"


void afficherImage(image2D_ptr im){
    printf("%d %d\n",im->lignes,im->colonnes);
    for(int i = 0;i<im->lignes;i++){
        for(int j=0;j<im->colonnes;j++){
            printf("%d ",im->image[i][j]);
        }
        printf("\n");
    }
}

void afficher_hist(histogramme h){
    int taille = h.taille;
    for(int i = 0;i<taille;i++){
        if(h.tab[i]>0)
        printf("Valeur : %d | %d\n",i,h.tab[i]);
    }
}


int main(int argc,char** argv){
    FILE* filename;
    /*char buffer[512];*/
    if((filename = fopen("Data/IMG_5389.txt","r+")) == NULL){
        perror("fopen");
        exit(1);
    }
    /*printf("Fichier ouvert\n");*/

    /*int lignes, colonnes, dimension;

    if (fscanf(filename, "%d %d %d", &lignes, &colonnes, &dimension) != 3)
    {
        fprintf(stderr, "Image non valide.\n");
        exit(EXIT_FAILURE);
    }
    printf("\n%3d %3d %d\n",lignes,colonnes,dimension);

    image3D_ptr Im;
    if(dimension == 3){
         Im = creer_image3D(lignes,colonnes);
        lire_image3D(filename,Im);
    }

    image2D_ptr im_2;
    histogramme hist;
    int nb_bits = 4;
    im_2 = RGB_to_GREY(Im,&hist,2);
    */
   int nb_bits = 6;
   CouleurNom ***lut = build_lut(nb_bits);
     if(!lut){
        fprintf(stderr, "Echec de build_lut.\n");
        return 1;
     }
   image2D_ptr im = pre_traitement(filename,nb_bits);
    image2D_ptr img = seuillage(im,COL_JAUNE,nb_bits);
    afficherImage(img);

    
   
    

    fclose(filename);
    /*else if(dimension == 2){
        image2D Im = creer_image2D(lignes,colonnes);
    }*/

}

