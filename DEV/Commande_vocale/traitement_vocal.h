#ifndef TRAITEMENT_VOCAL_H
#define TRAITEMENT_VOCAL_H
#define MAX_BUFFER_SIZE 1024
#define PATH_DICT_AVANCER "dictAvancer.txt"

typedef struct s_token
{
    char mots[256][512];
    int nbMots;
} token;

extern token dict_avancer;
extern token dict_reculer;
extern token dict_droite;
extern token dict_gauche;

extern char instructions_a_executer[MAX_BUFFER_SIZE];

extern int nb_dict;



token recuperer_dictionnaire(char *filename);
int extraireNombre(char *chaine);
int est_dans_dictionnaire(char *mot, token motsDictionnaire);
void envoyer_au_robot(token requete_commande);
token filtrer_mots(token requeteTexte);
token transformation_requete_commande(token requeteTexte);
token creer_token();
void init_dictionnaires();
token tokeniser_phrase_courante(char buffer[MAX_BUFFER_SIZE]);
char* recuperer_commande_vocale();
void appeler_pilotage_vocal();
void appeler_pilotage_manuel();




#endif