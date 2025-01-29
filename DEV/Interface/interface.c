#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "interface.h"

int readInterface(char *nomFichier)
{
    FILE *fichier;   // Pointeur vers le fichier
    char ligne[256]; // Tampon pour lire chaque ligne

    // Ouvrir le fichier en mode lecture
    fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        // fprintf(stderr,"Erreur lors de l'ouverture du fichier %s dans lire l'interface\n",nomFichier);
        exit(1);
    }

    // Lire le fichier ligne par ligne et afficher le contenu
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        printf("%s", ligne);
    }

    // Fermer le fichier
    fclose(fichier);
    printf("\n");
    return 0;
}

int convert_interface_to_int(const char *str)
{
    char *pos = strrchr(str, '/');
    if (pos != NULL)
    {

        // Convertir la chaîne après '/' en entier
        char *endptr;
        long result = strtol(pos + 1, &endptr, 10);

        // Vérifier si la conversion a réussi
        if (*endptr == '\0')
        { // Aucun caractère non numérique après le nombre
            return (int)result;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}

int switchInterface(char *currentInterface)
{
    char nextInterface[10];
    if (!scanf("%1s", nextInterface))
        return 1;

    if (strstr(nextInterface, "q") || strstr(nextInterface, "Q"))
    {
        return 1;
    }

    if (strstr(nextInterface, "0"))
    { // Si 0 est selec pour reculer dans l'interface
        if (strlen(currentInterface) > 14)
            remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
        readInterface(currentInterface);
    }
    else
    {
        strcat(currentInterface, nextInterface);

        if (!file_exists(currentInterface))
        {
            remove_last_char(currentInterface);
            readInterface(currentInterface);
            printf("\t\t\tChoix Incorrect\n");
        }
        else
            readInterface(currentInterface);
    }

    while (getchar() != '\n')
        ; // Vide la pile du scanf si jamais l'utilisateur tape plusieurs char
    return 0;
}

int switchInterfaceBis(char *currentInterface, char *nextInterface)
{
    if (strstr(nextInterface, "q") || strstr(nextInterface, "Q"))
    {
        return 1;
    }

    if (strstr(nextInterface, "0"))
    { // Si 0 est selec pour reculer dans l'interface
        if (strlen(currentInterface) > 14)
            remove_last_char(currentInterface); // si on en pas à la racine de l'interface on recule
        readInterface(currentInterface);
    }
    else
    {
        strcat(currentInterface, nextInterface);

        if (!file_exists(currentInterface))
        {
            remove_last_char(currentInterface);
            readInterface(currentInterface);
            printf("\t\t\tChoix Incorrect\n");
        }
        else
            readInterface(currentInterface);
    }

    while (getchar() != '\n')
        ; // Vide la pile du scanf si jamais l'utilisateur tape plusieurs char
    return 0;
}

void actionByInterface(int *currentInterfaceButitsAnInteger, char *currentInterface)
{

    char langue[10];
    find_in_config("Langue", langue);
    // printf("\n%s\n", currentInterface);
    switch (*currentInterfaceButitsAnInteger)
    {
    case 131:
        change_config("Langue", "FR");
        strcpy(currentInterface, "Interface/FR/1");
        *currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);
        readInterface(currentInterface);
        break;
    case 132:
        change_config("Langue", "EN");
        strcpy(currentInterface, "Interface/EN/1");
        *currentInterfaceButitsAnInteger = convert_interface_to_int(currentInterface);
        readInterface(currentInterface);
        break;
    case 1211:
        printf("\n\t\t\tConfiguration : \n\n");
        read_config("Configuration/config");

        char choice[50];
        if (strstr(langue, "FR"))
            printf("Quelle configuration voulez vous changer ?\n");
        else if (strstr(langue, "EN"))
            printf("Wich configuration do you want to change ?\n");
        else
            break;

        if (!scanf("%s", choice))
            exit(1);
        change_config(choice, NULL);
        switchInterfaceBis(currentInterface, "0");
        break;
    case 1111:
        appeler_pilotage_vocal();
        switchInterfaceBis(currentInterface, "0");
        readInterface(currentInterface);
        break;

    case 1121:
        make_file("commande/transcription.txt");
        add_row_to_file("commande/transcription.txt", "forward(5)");
        switchInterfaceBis(currentInterface, "0");
        break;
    case 1122:
        make_file("commande/transcription.txt");
        add_row_to_file("commande/transcription.txt", "turn(90)");
        switchInterfaceBis(currentInterface, "0");
        break;
    case 1123:
        make_file("commande/transcription.txt");
        add_row_to_file("commande/transcription.txt", "turn(-90)");
        switchInterfaceBis(currentInterface, "0");
        break;
    case 1124:
        make_file("commande/transcription.txt");
        add_row_to_file("commande/transcription.txt", "backward(5)");
        switchInterfaceBis(currentInterface, "0");
        break;
    case 1129:
        appeler_pilotage_manuel();
        switchInterfaceBis(currentInterface,"0");
        readInterface(currentInterface);
        break;

    case 14:

        char retour[1];
        find_in_config("Quantification", retour);
        etablir_nbBits(atoi(retour));

        char chemin[512];
        char entree[1024];
        char sortie[1024];
        printf("\n\t\t\tEntrez le nom de l'image à traiter : ");

        if (scanf("%s", chemin) == -1)
            Erreur("Erreur de lecture chemin");
        snprintf(entree, sizeof(entree), "Data/%s.txt", chemin);
        if (!file_exists(entree))
        {
            printf("Le fichier %s n'existe pas\n", entree);
            readInterface(currentInterface);
            break;
        }
        snprintf(sortie, sizeof(sortie), "sortie/%.500s_v2.txt", chemin);
        clock_t
            temps_initial, /* Temps initial en micro-secondes */
            temps_final;   /* Temps final en micro-secondes */
        float
            temps_cpu;
        /* Temps total en secondes */
        temps_initial = clock();
        printf("Vous voulez traiter une image selon :\n1 - sa couleur\n2 - sa forme\n choix = " );
        int choix;
        do{
            if(scanf("%d", &choix)!=1)Erreur("ERREUR");
        }while(choix != 1 && choix != 2);
        if(choix == 1){
            printf("Quelle couleur ? \n1 - Bleu \n2 - Orange \n3 - Jaune\n choix = ");
            if(scanf("%d", &choix)!=1)Erreur("ERREUR, choix invalide {BLEU-1,ORANGE-2,JAUNE-3}");
            CouleurNom couleur;
            if(choix ==1){
                couleur = COL_BLEU;
            }
            if(choix ==2){
                couleur = COL_ORANGE;
            }
            else{
                couleur = COL_JAUNE;
            }
            appel_traitement_image_selon_couleur(entree, sortie, couleur);
        }
        else{
            printf("Quelle forme ? :\n1 - BALLE\n2 - CARRE\n choix = ");
            if(scanf("%d", &choix)!=1)Erreur("ERREUR, choix objet invalide {Balle-1 ,CARRE-2}");
            Objet objet;
            if(choix == 2){
                objet = CARRE;
                printf("objet carre\n");
            }
            else{
                objet = BALLE;
            }
            appel_traitement_image_selon_forme(entree,sortie,objet);
        }
        temps_final = clock();
        temps_cpu = (temps_final - temps_initial) * 1e-5;
        printf("TEMPS CPU : %f\n", temps_cpu);
        
        if(system("python3 conversion.py")==-1){
            Erreur("system conversion.py");
        }
        printf("L'image traitée peut être visualisée dans le dossier sortie.\n");

        readInterface(currentInterface);
        break;

    default:
        break;
    }
}