#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string.h>
#include <time.h>
#include <time.h>

int init();
int updateLog(const char *message);
int file_exists(const char *filename);
int read_config(char *nomFichier);
char* find_in_config(char *nomFichier, char *configtofind);
void remove_last_char(char *chaine);
int change_config(char *nomFichier, char *configtochange, const char *new_val_optional);
int make_file(const char *nomFichier);
int add_row_to_file(const char *nomFichier, const char *ligne);
int rename_file(const char *ancienNom, const char *nouveauNom);
int remove_file(const char *nomFichier);