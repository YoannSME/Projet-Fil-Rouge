#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Interface/interface.h"

int main() {
    printf("\n\n\n\n");
    
    char Langue[10];
    int currentInterfaceButitsAnInteger = 1;
   // char currentInterface[256];
    

    if (init()){
        printf("Erreur lors de l'initialisation !\n");
        return -1;
    }

    if (find_in_config("Langue", Langue)) return 1;
    
    //snprintf(currentInterface, sizeof(currentInterface), "Interface/%.*s%s", (int)(strlen(Langue)), Langue, "/1"); // J'avoue c'est ChatGPT qui m'a fait cette ligne, j'y arriver pas (Du à \0 qui se trouvait à la fait de la chaine langue)
     char currentInterface[256] = "Interface/FR/1";
    readInterface(currentInterface);

    for(;;)
    {
        
        if(switchInterface(currentInterface)) return 0;

        currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);

        actionByInterface(&currentInterfaceButitsAnInteger, currentInterface);

    }
    
    
    printf("\n\n\n\n");
    return 0;
}