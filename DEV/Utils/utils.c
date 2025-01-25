#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define VOISINAGE_8
char nb_bits;
static FILE* logfile = NULL;
void Erreur(char *message)
{
    fprintf(stderr, "%s.\n", message);
    exit(EXIT_FAILURE);
}

void etablir_nbBits(int nb){
    nb_bits = nb;
}

void write_logfile(char* message)
{
    if (logfile == NULL) {
        Erreur("Le fichier de log n'a pas été initialisé");
    }
    fprintf(logfile, "%s\n", message);
}

void init_logfile()
{
    logfile = openFile("/log/Logs_traitement_images", "w");
}

void close_logfile()
{
    if (logfile != NULL) {
        fclose(logfile);
        logfile = NULL;
    }
}

FILE* openFile(char* chemin, char* mode){
    FILE* file = fopen(chemin, mode);
    if(file == NULL){
        Erreur("Impossible d'ouvrir le fichier");
    }
    return file;
}



int PILE_estVide(PILE p){
  if(p==NULL){
    return 1;
  }else{
    return 0;
  }
}

PILE emPILE(PILE p,Element e){
  Cellule* cell = (Cellule*)malloc(sizeof(Cellule));    
  if(cell==NULL){
    perror("malloc element");
    return p;
  }
  cell->val = e;
  if(PILE_estVide(p)){
    cell->suiv = NULL;
  }
  else{
    cell->suiv = p;
  }
  p = cell;
  return p;
}


PILE dePILE(PILE p,Element *e){
  if(!PILE_estVide(p)){
    PILE paux = p;
    *e = p->val;
    p = p->suiv;
    free(paux);

  }
  else{
    printf("Erreur, pile vide\n");
  }
  return p;
}

PILE init_PILE(){
  PILE p = NULL;
  return p;
}







