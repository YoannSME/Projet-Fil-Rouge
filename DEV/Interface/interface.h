#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include "../Configuration/config.h"
#define PATH_INTERFACE "Interface/"

int readInterface(char* nomFichier);
int file_exists(const char *filename);
int convert_interface_to_int(const char *str);
int switchInterface(char * currentInterface);
int switchInterfaceBis(char * currentInterface, char * nextInterface);
void actionByInterface(int* currentInterfaceButitsAnInteger, char* currentInterface);

#endif