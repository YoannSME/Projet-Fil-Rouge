#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "traitement_vocal.h"


token dict_avancer;
token dict_reculer;
token dict_droite;
token dict_gauche;

int nb_dict = 4;

void init_dictionnaires(){
    dict_avancer = recuperer_dictionnaire("dictAvancer.txt");
    dict_reculer = recuperer_dictionnaire("dictReculer.txt");
    dict_droite = recuperer_dictionnaire("dictDroite.txt");
    dict_gauche = recuperer_dictionnaire("dictGauche.txt");
}
token creer_token()
{
    token token;
    token.nbMots = 0;
    return token;
}

FILE *ouvrir_fichier(char filename[], char *mode)
{
    FILE *file = fopen(filename, mode);
    if (file == NULL)
    {
        fprintf(stderr, "Erreur ouverture du fichier %s\n", filename);
        exit(1);
    }
    return file;
}
token tokeniser_phrase_courante()
{   
    FILE* fichier = ouvrir_fichier("phrase.txt","r");
    char buffer[MAX_BUFFER_SIZE];
    fgets(buffer, MAX_BUFFER_SIZE, fichier);

    buffer[strcspn(buffer, "\n")] = '\0';

    token phraseTokenise = creer_token();
    phraseTokenise.nbMots = 0;
    int i = 0;
    while (buffer[i] != '\0')
    {
        if (buffer[i] == ' ')
            i++;
        else
        {
            int j = 0;
            while (buffer[i] != ' ' && buffer[i] != '\0')
            {
                phraseTokenise.mots[phraseTokenise.nbMots][j] = buffer[i];
                i++;
                j++;
            }
            phraseTokenise.mots[phraseTokenise.nbMots][j] = '\0';
            phraseTokenise.nbMots += 1;
        }
    }
    fclose(fichier);
    return phraseTokenise;
}

int extraireNombre(char *chaine)
{
    int nombre = 0;
    int estDansUnNombre = 0;

    while (*chaine)
    {
        if (*chaine >= '0' && *chaine <= '9')
        {
            nombre = nombre * 10 + (*chaine - '0');
            estDansUnNombre = 1;
        }
        else if (estDansUnNombre)
        {
            break;
        }
        chaine++;
    }

    return estDansUnNombre ? nombre : -1;
}

token recuperer_dictionnaire(char *filename)
{
    FILE *fichierDictionnaire = ouvrir_fichier(filename, "r");
    token motsDictionnaire = creer_token();
    while (fgets(motsDictionnaire.mots[motsDictionnaire.nbMots], MAX_BUFFER_SIZE, fichierDictionnaire) != NULL)
    {
        motsDictionnaire.mots[motsDictionnaire.nbMots][strcspn(motsDictionnaire.mots[motsDictionnaire.nbMots], "\n")] = '\0';
        motsDictionnaire.nbMots++;
    }
    fclose(fichierDictionnaire);
    return motsDictionnaire;
}

int est_dans_dictionnaire(char *mot, token motsDictionnaire)
{

    for (int i = 0; i < motsDictionnaire.nbMots; i++)
    {
        if (strcmp(mot, motsDictionnaire.mots[i]) == 0)
            return 1;
    }
    return 0;
}

token filtrer_mots(token requeteTexte)
{
    token texte_filtre = creer_token();
    char nb_char[10];
    int taille_requete = requeteTexte.nbMots;
    for (int i = 0; i < taille_requete; i++)
    {
        char *mot_courant = requeteTexte.mots[i];

      
        if (est_dans_dictionnaire(mot_courant, dict_avancer) ||
            est_dans_dictionnaire(mot_courant, dict_reculer) ||
            est_dans_dictionnaire(mot_courant, dict_droite) ||
            est_dans_dictionnaire(mot_courant, dict_gauche))
        {
            strcpy(texte_filtre.mots[texte_filtre.nbMots], mot_courant);
            texte_filtre.nbMots++;
        }
        else{
            int nb = extraireNombre(mot_courant);
            if(nb!=-1){
                snprintf(nb_char,sizeof(nb_char),"%d",nb);
                strcpy(texte_filtre.mots[texte_filtre.nbMots], nb_char);
            texte_filtre.nbMots++;
            }
        }
    }

    return texte_filtre;
}

token transformation_requete_commande(token requeteTexte)
{

    token requete_commande = creer_token();

    int distance_defaut = 100;
    int angle_defaut = 90;
    int taille_requete = requeteTexte.nbMots;
    for (int i = 0; i < taille_requete; i++)
    {
        char *mot_courant = requeteTexte.mots[i];

        int distance;
        if (est_dans_dictionnaire(mot_courant, dict_avancer))
        {

            if ((i + 1) < taille_requete && (sscanf(requeteTexte.mots[i + 1], "%d", &distance) == 1))
            {

                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "forward(%d)", distance);
            }
            else
            {
                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "forward(%d)", distance_defaut);
            }
            requete_commande.nbMots += 1;
        }
        else if (est_dans_dictionnaire(mot_courant, dict_reculer))
        {
            if ((i + 1) < taille_requete && (sscanf(requeteTexte.mots[i + 1], "%d", &distance) == 1))
            {

                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "backward(%d)", distance);
            }
            else
            {
                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "backward(%d)", distance_defaut);
            }
            requete_commande.nbMots += 1;
        }
        else if (est_dans_dictionnaire(mot_courant, dict_droite))
        {
            if ((i + 1) < taille_requete && (sscanf(requeteTexte.mots[i + 1], "%d", &distance) == 1))
            {

                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "right(%d)", distance);
            }
            else
            {
                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "right(%d)", angle_defaut);
            }
            requete_commande.nbMots += 1;
        }
        else if (est_dans_dictionnaire(mot_courant, dict_gauche))
        {
            if ((i + 1) < taille_requete && (sscanf(requeteTexte.mots[i + 1], "%d", &distance) == 1))
            {

                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "left(%d)", distance);
            }
            else
            {
                snprintf(requete_commande.mots[requete_commande.nbMots], MAX_BUFFER_SIZE, "left(%d)", angle_defaut);
            }
            requete_commande.nbMots += 1;
        }
    }
    return requete_commande;
}


void envoyer_au_robot(token requete_commande){
    FILE* fichier = ouvrir_fichier("requete_commande.txt","w");
    for(int i = 0;i<requete_commande.nbMots;i++){
        fprintf(fichier,"%s ",requete_commande.mots[i]);
    }
    fclose(fichier);
}

int main(void)
{
    init_dictionnaires();
    token phrase = tokeniser_phrase_courante();
    for (int i = 0; i < phrase.nbMots; i++)
    {
        printf("Mot = %s\n", phrase.mots[i]);
    }


    token mots_filtrees = filtrer_mots(phrase);
    for (int i = 0; i < mots_filtrees.nbMots; i++)
    {
        printf("mot filtree = %s\n", mots_filtrees.mots[i]);
    }
    token requete = transformation_requete_commande(mots_filtrees);

    envoyer_au_robot(requete);

    return 0;
}