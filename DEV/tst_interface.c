#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Interface/interface.h"

int main() {
    printf("\n\n\n\n");
    char Langue[10];
    int currentInterfaceButitsAnInteger = 1;
    int OldcurrentInterfaceButitsAnInteger = 1;

    if (init()){
        printf("Erreur lors de l'initialisation !\n");
        return -1;
    }

    if (find_in_config("Langue", Langue)) return 1;
    printf("\n%s\n", Langue);

    char currentInterface[256] = "Interface/FR/1";
    //strcat(currentInterface, Langue);

    readInterface(currentInterface);

    for(;;)
    {
        
        if(switchInterface(currentInterface)) return 0;

        currentInterfaceButitsAnInteger = convert_to_int_after_slash(currentInterface);

        if (OldcurrentInterfaceButitsAnInteger != currentInterfaceButitsAnInteger){
            actionByInterface(currentInterfaceButitsAnInteger);
            OldcurrentInterfaceButitsAnInteger = currentInterfaceButitsAnInteger;
        }
    }
    
    
    printf("\n\n\n\n");
    return 0;
}