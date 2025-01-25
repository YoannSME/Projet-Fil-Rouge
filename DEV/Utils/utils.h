#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>  // Nécessaire pour le type FILE
#include <stdlib.h>

#define PATH_LOGFILE "/log/Logs_traitement_images"


#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define max3(a, b, c) ((a) > (b) ? ((a) > (c) ? (a) : (c)) : ((b) > (c) ? (b) : (c)))
#define min3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
typedef struct{
  int x;
  int y;
}coo;
typedef coo Element;
typedef char int8b;
typedef struct s_Cellule{
  Element val;
  struct s_Cellule *suiv;
}Cellule;

typedef Cellule* PILE;


extern int8b nb_bits;


/* mettre votre code ci-après */
PILE init_PILE();
void Erreur(char *message);

void init_logfile();
void write_logfile(char* message,...);
void close_logfile();


int PILE_estVide(PILE p);
PILE emPILE(PILE p, Element e);
PILE dePILE(PILE p, Element *e);





#endif