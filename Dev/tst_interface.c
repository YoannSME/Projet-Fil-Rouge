#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "config.h"

int main() {
    printf("\n\n\n\n");
    char nextInterface[50];
    char currentInterface[100];
    int currentInterfaceButitsAInteger = 0;

    char* Langue = find_in_config("config", "Langue");
    if ( Langue == NULL ) return 1;

    strcpy(currentInterface, Langue);
    strcat(currentInterface, "/1");
    readInterface(currentInterface);

    while(1)
    {
        while (getchar() != '\n');
        scanf("%1s", nextInterface);

        if (strstr(nextInterface, "0")){
            if (strlen(currentInterface) > 4) remove_last_char(currentInterface);
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

    }
    
    
    printf("\n\n");
    return 0;
}