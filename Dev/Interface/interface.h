#include <stdlib.h>
#include <stdio.h>
#include "../Configuration/config.h"

int readInterface(char nomFichier[100]);
int file_exists(const char *filename);
int convert_to_int_after_slash(const char *str);
int switchInterface(char * currentInterface);
void actionByInterface(int currentInterfaceButitsAnInteger);