#include <stdlib.h>

#include <stdio.h>
#include "interface.h"

int readInterface(char nomFichier[100]) {
    FILE *fichier;  // Pointeur vers le fichier
    char ligne[256];  // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        fprintf(stderr,"Erreur lors de l'ouverture du fichier %s dans lire l'interface\n",nomFichier);
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

int convert_to_int_after_slash(const char *str) {
    char *pos = strchr(str, '/');
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
    scanf("%1s", nextInterface);

        if (strstr(nextInterface, "q")){
            printf("\n\n\t\t\tAu revoir\n\n\n\n");
            return 1;
        }

        if (strstr(nextInterface, "0")){ // Si 0 est selec pour reculer dans l'interface
            if (strlen(currentInterface) > 4)remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
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

void actionByInterface(int currentInterfaceButitsAnInteger){
    switch (currentInterfaceButitsAnInteger)
    {
    case 1:
        break;
    
    default:
        break;
    }
}