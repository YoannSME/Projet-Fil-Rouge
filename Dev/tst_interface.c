#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "interface.h"
#include "config.h"

int main() {
    char* Langue = find_in_config("config", "Langue");
    printf("%s", Langue);
    char* Langue2 = find_in_config("config", "moncul");
    printf("%s", Langue2);

    // readInterface(strcat(Langue, "/test"));

    return 1;
}