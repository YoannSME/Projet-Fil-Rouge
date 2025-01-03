#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traitement_images.h"


void afficherImage(image2D im){
    for(int i = 0;i<im->lignes;i++){
        for(int j=0;j<im->colonnes;j++){
            printf("%3d",im->image[i][j]);
        }
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
    if((filename = fopen(argv[1],"r+")) == NULL){
        perror("fopen");
        exit(1);
    }
    /*printf("Fichier ouvert\n");*/

     int lignes, colonnes, dimension;

    if (fscanf(filename, "%d %d %d", &lignes, &colonnes, &dimension) != 3)
    {
        fprintf(stderr, "Image non valide.\n");
        exit(EXIT_FAILURE);
    }
    printf("\n%3d %3d %d\n",lignes,colonnes,dimension);

    image3D Im;
    if(dimension == 3){
         Im = creer_image3D(lignes,colonnes);
        lire_image3D(filename,Im);
    }

    image2D im_2;
    histogramme hist;
    int nb_bits = 4;
    im_2 = RGB_to_GREY(Im,&hist,2);
    afficher_hist(hist);

    fclose(filename);
    /*else if(dimension == 2){
        image2D Im = creer_image2D(lignes,colonnes);
    }*/



    




}