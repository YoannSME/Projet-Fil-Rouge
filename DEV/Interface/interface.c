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
            if (strlen(currentInterface) > 14)remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
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

int switchInterfaceBis(char * currentInterface, char * nextInterface){
    if (strstr(nextInterface, "q") || strstr(nextInterface, "Q")){
        return 1;
    }

    if (strstr(nextInterface, "0")){ // Si 0 est selec pour reculer dans l'interface
        if (strlen(currentInterface) > 14)remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
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

void actionByInterface(int * currentInterfaceButitsAnInteger, char* currentInterface){
    printf("\n%s\n", currentInterface);
    switch (*currentInterfaceButitsAnInteger)
    {
    case 131: 
        change_config("Langue", "FR");
        strcpy(currentInterface,"Interface/FR/1");
        *currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);
        readInterface(currentInterface);
        break;
    case 132:
        change_config("Langue", "EN");
        strcpy(currentInterface,"Interface/EN/1");
        *currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);
        readInterface(currentInterface);
        break;
    case 1211:
        printf("\n\t\t\tConfiguration : \n\n");
        read_config("Configuration/config");
        char langue[10];
        find_in_config("Langue", langue);

        char choice[50];
        if (strstr(langue, "FR")) printf("Quelle configuration voulez vous changer ?\n");
        else if (strstr(langue, "EN")) printf("Wich configuration do you want to change ?\n");
        else break;

        if (!scanf("%s", choice)) exit(1);
        change_config(choice, NULL);
        switchInterfaceBis(currentInterface, "0");
        break;
    case 1111:
        printf("\n\t\t\tLa je dois lancer le programme de Jules\n");
        break;
    
    case 14:
    initialisationLogfileTraitementImage();
        etablir_nbBits(3);
        char chemin[512] = { "img_down"};
        char entree[1024];
        char sortie[1024];

        snprintf(entree, sizeof(entree), "Data/%.500s.txt", chemin);
        snprintf(sortie, sizeof(sortie), "sortie/%.500s_v2.txt", chemin);
        FILE *fichier_entree = fopen(entree, "r");
        FILE *fichier_sortie = fopen(sortie, "w");//Seulement utile pour visualiser l'image avec : python3 conversion.py
        image2D_ptr image_pretraitee = pre_traitement(fichier_entree);
        tab_boite_englobante tab = traitement_images(image_pretraitee, COL_JAUNE);
        if(tab.taille>0 ) afficherImage(tab.tabBoites[0].image,fichier_sortie);
        /*tab_boite_englobante tab = traiter_image_selon_forme(image_pretraitee,BALLE);
        afficherImage(tab.tabBoites[0].image,fichier_sortie);*/
        

        free_tab_boites_englobantes(tab);
        free_image2D(image_pretraitee);
        fclose(fichier_entree);
        fclose(fichier_sortie);
        close_logfile();
        
        break;

    default:
        break;
    }
}