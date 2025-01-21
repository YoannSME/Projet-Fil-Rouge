#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include "../Configuration/config.h"
#define PATH_INTERFACE "Interface/"

int readInterface(char nomFichier[100]);
int file_exists(const char *filename);
int convert_to_int_after_slash(const char *str);
int switchInterface(char * currentInterface);
void actionByInterface(int currentInterfaceButitsAnInteger);

#endif