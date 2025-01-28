#ifndef TRAITEMENT_VOCAL
#define TRAITEMENT_VOCAL
#define MAX_BUFFER_SIZE 1024
#define PATH_DICT_AVANCER "dictAvancer.txt"


typedef struct s_token
{
    char mots[256][512];
    int nbMots;
} token;

token recuperer_dictionnaire(char *filename);
int extraireNombre(char *chaine);
int est_dans_dictionnaire(char *mot, token motsDictionnaire);
void envoyer_au_robot(token requete_commande);
token filtrer_mots(token requeteTexte);
token transformation_requete_commande(token requeteTexte);
token creer_token();
void init_dictionnaires();
token tokeniser_phrase_courante();


#endif