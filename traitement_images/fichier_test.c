#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "traitement_images.h"

typedef __int8_t int8b;
int quantification(int8b r_8b,int8b g_8b,int8b b_8b, int nb_bits){
    if(nb_bits<1 || nb_bits>NB_BITS_MAX){
        perror("Quantification : NB_BITS INVALIDE");
        exit(1);
    }

    unsigned char r = r_8b>>(NB_BITS_MAX-nb_bits)&((1<<nb_bits)-1);
    unsigned char g = g_8b>>(NB_BITS_MAX-nb_bits)&((1<<nb_bits)-1);
    unsigned char b = b_8b>>(NB_BITS_MAX-nb_bits)&((1<<nb_bits)-1);
    return r<<(2*nb_bits)|g<<(nb_bits)|b;
    
}
int main(void){
    int r = 255;
    int g = 128;
    int b = 64;

    //printf("val = %d\n",quantification(r,g,b,2));
    int taille = 1<<(9);
    printf("taille = %d\n",taille);
    
    int nb_bits = 2;
    int nombre_bits = ((1<<nb_bits-1) | (1<<nb_bits)-1); //
    int rouge = nombre_bits<<2*nb_bits;
    int vert = nombre_bits<<nb_bits;
    int bleu = nombre_bits;
    printf("nombre_bits = %d\n",nombre_bits);

    printf("rouge = %d, vert = %d, bleu  = %d\n",rouge,vert,bleu);

    return 0;
}