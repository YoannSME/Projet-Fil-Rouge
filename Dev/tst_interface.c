#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "config.h"

int main() {
    printf("\n\n");


    // char* Langue = find_in_config("config", "Langue");
    // if ( Langue == NULL ) return 1;

    change_config("config", "moncul");

    // readInterface(strcat(Langue, "/test"));
    // read_config("config");



    printf("\n\n");
    return 0;
}