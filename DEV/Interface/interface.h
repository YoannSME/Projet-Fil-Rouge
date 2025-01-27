#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include "../Configuration/config.h"
#include "../Image/traitement_images.h"
#include "../Couleur/analyse_couleur.h"
#include "../commande_vocale/parser.h"

#include "../Utils/utils.h"
#define PATH_INTERFACE "Interface/"

int readInterface(char* nomFichier);
int file_exists(const char *filename);
int convert_interface_to_int(const char *str);
int switchInterface(char * currentInterface);
int switchInterfaceBis(char * currentInterface, char * nextInterface);
void actionByInterface(int* currentInterfaceButitsAnInteger, char* currentInterface);

#endif