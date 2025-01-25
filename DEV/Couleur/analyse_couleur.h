#ifndef ANALYSE_COULEUR
#define ANALYSE_COULEUR

#include "../Utils/utils.h"

typedef enum {
    COL_ROUGE,
    COL_BLEU,
    COL_JAUNE,
    COL_ORANGE,
    COL_BLANC,
    COL_INCONNU,
    COL_GRIS,
    COL_VERT
} CouleurNom;

typedef char int8b;


void quantification(int valeur,int8b *,int8b*,int8b*);
void rgb_to_hsv(int8b r, int8b g, int8b b, float *h, float *s, float *v, int max_val);
CouleurNom conversion_couleur(int valeur);
void association_couleur(CouleurNom couleur);
#endif


