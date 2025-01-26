#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Image/traitement_images.h"

typedef char int8b;
int main(void){
  

    //printf("val = %d\n",quantification(r,g,b,2));
    int taille = 1<<(9);
    printf("taille = %d\n",taille);
    
    int nb_bits = 4;
    int nombre_bits = (1<<(nb_bits-1))| ((1<<nb_bits)-1); //
    int rouge = nombre_bits<<2*nb_bits;
    int vert = nombre_bits<<nb_bits;
    int bleu = nombre_bits;
    printf("nombre_bits = %d\n",nombre_bits);

    printf("rouge = %d, vert = %d, bleu  = %d\n",rouge,vert,bleu);


    char buffer[512];
    printf("Image ? :\n");
    if(scanf("%s",buffer)==-1){
        perror("Erreur de lecture");
        exit(1);
    }
    printf("buffer = %s\n",buffer);

    return 0;
}