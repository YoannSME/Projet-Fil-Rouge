#include <stdlib.h>
#include <stdio.h>


int read_config(char *nomFichier);
char* find_in_config(char *nomFichier, char *configtofind);
void remove_last_char(char *chaine);
int change_config(char *nomFichier, char *configtochange);
int make_file(const char *nomFichier);
int add_row_to_file(const char *nomFichier, const char *ligne);
int rename_file(const char *ancienNom, const char *nouveauNom);
int remove_file(const char *nomFichier);