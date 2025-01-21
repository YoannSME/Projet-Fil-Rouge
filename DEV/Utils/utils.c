#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char nb_bits;

void Erreur(char *message)
{
    fprintf(stderr, "%s.\n", message);
    exit(EXIT_FAILURE);
}

void etablir_nbBits(int nb){
    nb_bits = nb;
}

