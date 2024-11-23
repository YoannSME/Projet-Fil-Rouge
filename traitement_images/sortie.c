#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traitement_images.h"


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
    printf("%3d %3d %d\n",lignes,colonnes,dimension);

    if(dimension == 3){
        image3D Im = creer_image3D(lignes,colonnes);
        lire_image3D(filename,Im);


    }
    /*else if(dimension == 2){
        image2D Im = creer_image2D(lignes,colonnes);
    }*/


    




}