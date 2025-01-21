#include <stdlib.h>

#include <stdio.h>
#include "interface.h"

int readInterface(char* nomFichier) {
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        // fprintf(stderr,"Erreur lors de l'ouverture du fichier %s dans lire l'interface\n",nomFichier);
        exit(1);
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        printf("%s", ligne);
    }

    // Fermer le fichier
    fclose(fichier);
    printf("\n");
    return 0;
}

int convert_interface_to_int(const char *str) {
    char *pos = strrchr(str, '/');
    if (pos != NULL) {

        // Convertir la chaîne après '/' en entier
        char *endptr;
        long result = strtol(pos + 1, &endptr, 10);
        
        // Vérifier si la conversion a réussi
        if (*endptr == '\0') {  // Aucun caractère non numérique après le nombre
            return (int)result;
        } else {
            return 0;
        }
    }
    
    return 0;
}

int switchInterface(char * currentInterface){
    char nextInterface[10];
    if (!scanf("%1s", nextInterface)) return 1;

        if (strstr(nextInterface, "q") || strstr(nextInterface, "Q")){
            return 1;
        }

        if (strstr(nextInterface, "0")){ // Si 0 est selec pour reculer dans l'interface
            if (strlen(currentInterface) > 12)remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
            readInterface(currentInterface);
        } else {
            strcat(currentInterface, nextInterface);

            if (!file_exists(currentInterface)){
                remove_last_char(currentInterface);
                readInterface(currentInterface);
                printf("\t\t\tChoix Incorrect\n");
            } 
            else readInterface(currentInterface);
        }

    while (getchar() != '\n'); // Vide la pile du scanf si jamais l'utilisateur tape plusieurs char
    return 0;
}

int switchInterfaceBis(char * currentInterface, char* nextInterface){
    if (strstr(nextInterface, "q") || strstr(nextInterface, "Q")){
        return 1;
    }

    if (strstr(nextInterface, "0")){ // Si 0 est selec pour reculer dans l'interface
        if (strlen(currentInterface) > 12)remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
        readInterface(currentInterface);
    } else {
        strcat(currentInterface, nextInterface);

        if (!file_exists(currentInterface)){
            remove_last_char(currentInterface);
            readInterface(currentInterface);
            printf("\t\t\tChoix Incorrect\n");
        } 
        else readInterface(currentInterface);
    }

    return 0;
}

void actionByInterface(int * currentInterfaceButitsAnInteger, char* currentInterface){
    switch (*currentInterfaceButitsAnInteger)
    {
    case 13:
        char choiceLangue[3] = "\0";
        if (!scanf("%1s", choiceLangue)) exit(1);
        printf("\n\t%s\n", choiceLangue);


        if (strstr(choiceLangue, "1")){
            change_config("Langue", "FR");
            strcpy(currentInterface,"Interface/FR/1");
            *currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);
            readInterface(currentInterface);
        }

        else if (strstr(choiceLangue, "2")){
            change_config("Langue", "EN");
            strcpy(currentInterface,"Interface/EN/1");
            *currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);
            readInterface(currentInterface);
        }
        
        else{
            if (switchInterfaceBis(currentInterface, choiceLangue)) exit(1);
        }

        while (getchar() != '\n');
        break;
    
    default:
        break;
    }
}