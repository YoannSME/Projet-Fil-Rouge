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
    if(argc<2){
        fprintf(stderr,"Usage");
        exit(1);
    }
    /*char buffer[512];*/
    char chemin[512] = "Data/IMG_";
    
    strcat(chemin,argv[1]);
    strcat(chemin,".txt");
    if((filename = fopen(chemin,"r+")) == NULL){
        perror("fopen");
        exit(1);
    }
 
   int nb_bits = 4;
   CouleurNom ***lut = build_lut(nb_bits);
     if(!lut){
        fprintf(stderr, "Echec de build_lut.\n");
        return 1;
     }
   image2D_ptr im = pre_traitement(filename,nb_bits);
    image2D_ptr img = seuillage(im,COL_ORANGE,nb_bits);
    afficherImage(img);

    
   
    

    fclose(filename);
    /*else if(dimension == 2){
        image2D Im = creer_image2D(lignes,colonnes);
    }*/

}

