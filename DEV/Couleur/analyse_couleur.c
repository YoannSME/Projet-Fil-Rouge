#include "analyse_couleur.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void quantification(int valeur,int8b *r, int8b *g, int8b *b)
{
    *r = (valeur >> (2 * nb_bits)) & ((1 << nb_bits) - 1); // Valeur rouge : les N premiers bits
    *g = (valeur >> nb_bits) & ((1 << nb_bits) - 1);       // Valeur verte : les N bits du milieu
    *b = valeur & ((1 << nb_bits) - 1);  
    
}


void rgb_to_hsv(int8b r, int8b g, int8b b, float *h, float *s, float *v, int max_val) //REPRESENTATION HSV POUR CAPTER L'OMBRE (MERCI LE COURS DE TRAITEMENT D'IMAGE)
{
    float rf = (float)r / max_val;
    float gf = (float)g / max_val;
    float bf = (float)b / max_val;

   
    float maxC = max3(rf,gf,bf);
    float minC = min3(rf,gf,bf);
    float delta = maxC - minC;

    // Calcul de V (Valeur)
    *v = maxC;

    // Calcul de S (Saturation)
    if(maxC<1e-6)*s=0;
    else *s=(delta/maxC);
        

    // Calcul de H (Teinte)
    if (delta == 0)
    {
        *h = 0; // Gris ou blanc

    }
    else if (maxC == rf)
    {
        *h = 60 * ((gf - bf) / delta);
        if (*h < 0)
            *h += 360;
    }
    else if (maxC == gf)
    {
        *h = 60 * (((bf - rf) / delta) + 2);
    }
    else
    {
        *h = 60 * (((rf - gf) / delta) + 4);
    }
}



CouleurNom conversion_couleur(int valeur)
{                                                              
    int8b r,g,b;
    quantification(valeur,&r,&g,&b);

    int max_val = (1 << (nb_bits - 1)) | ((1 << nb_bits) - 1);
    float h, s, v;
    rgb_to_hsv(r, g, b, &h, &s, &v, max_val);

    if ((h >= 39 && h <= 70) && // Teinte jaune
        (s >= 0.6) &&           
        (v >= 0.4))
    {
        return COL_JAUNE;
    }
    if ((h >= 200 && h <= 275) && // Teinte bleue
        (s >= 0.6) &&            
        (v >= 0.15))
    {
        return COL_BLEU;
    }

    if ((h >= 7 && h <= 28) && // Teinte orange
        (s >= 0.5) &&          
        (v >= 0.3))
        return COL_ORANGE;

    return COL_INCONNU; ///
}

void association_couleur(CouleurNom couleur){
    switch (couleur)
    {
    case COL_BLEU:
        printf("BLEU\n");
        break;
    case COL_JAUNE:
        printf("JAUNE\n");
        break;
    default:
        printf("ERREUR\n");
        break;
    }
}

