#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "config.h"

int main() {
    printf("\n\n\n\n");
    char nextInterface[10];
    char currentInterface[100];
    int currentInterfaceButitsAInteger = 0;

    if (init()){
        printf("Erreur lors de l'initialisation !\n");
        return -1;
    }

    char* Langue = find_in_config("config", "Langue");
    if ( Langue == NULL ) return 1;

    strcpy(currentInterface, Langue);
    strcat(currentInterface, "/1");
    readInterface(currentInterface);

    while(1)
    {
        scanf("%1s", nextInterface);

        if (strstr(nextInterface, "0")){ // Si 0 est selec pour reculer dans l'interface
            if (strlen(currentInterface) > 4) remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
            else{
                printf("\n\n\t\t\tAu revoir\n\n\n\n");
                return 0;
            }
        } else {
            strcat(currentInterface, nextInterface);
            if (!file_exists(currentInterface)) remove_last_char(currentInterface);
        }
        currentInterfaceButitsAInteger = convert_to_int_after_slash(currentInterface);
        readInterface(currentInterface);

        switch (currentInterfaceButitsAInteger)
        {
        case 1:
            printf("Yeah\n");
            break;
        
        default:
            break;
        }

        while (getchar() != '\n'); // Vide la pile du scanf si jamais l'utilisateur tape plusieurs char
    }
    
    
    printf("\n\n");
    return 0;
}