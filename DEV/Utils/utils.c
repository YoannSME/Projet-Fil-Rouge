#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>
#define VOISINAGE_8

static FILE* logfile = NULL;
void Erreur(char *message)
{
    fprintf(stderr, "%s.\n", message);
    exit(EXIT_FAILURE);
}



void write_logfile(char* message,...)
{
    if (logfile == NULL) {
        Erreur("Le fichier de log n'a pas été initialisé");
    }
    va_list args;
    va_start(args, message);
    vfprintf(logfile, message, args);
    va_end(args);
    fprintf(logfile, "\n");
}



void close_logfile()
{
    if (logfile != NULL) {
        fclose(logfile);
        logfile = NULL;
    }
}

void init_logfile(){
    FILE* file = fopen("log/Logs_traitement_images.txt", "w");
    if(file == NULL){
        Erreur("Impossible d'ouvrir le fichier");
    }
    logfile = file;
    
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







