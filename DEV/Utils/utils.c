#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char nb_bits = 3;

void Erreur(char *message)
{
    fprintf(stderr, "%s.\n", message);
    exit(EXIT_FAILURE);
}

void etablir_nbBits(unsigned char nb){
    if(nb<3 ||nb>7){
        fprintf(stderr,"Nombre de bits de quantifications invalide, {3-7});
        exit(1);
    }
    nb_bits = nb;
}

