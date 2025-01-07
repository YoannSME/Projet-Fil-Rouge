#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))

#include "traitement_images.h"

void Erreur(char *message)
{
    fprintf(stderr, "%s.\n", message);
    exit(EXIT_FAILURE);
}



image3D_ptr creer_image3D(int lignes, int colonnes)
{
    image3D_ptr Im = malloc(sizeof(struct s_image3D));
    if (Im == NULL)
    {
        Erreur("Erreur malloc image3D");
    }
    Im->lignes = lignes;
    Im->colonnes = colonnes;

    
    Im->image = malloc(lignes * sizeof(*Im->image));
    if (Im->image == NULL)
    {
        Erreur("Erreur malloc image3D");
    }
    for (int i = 0; i < lignes; i++)
    {
        Im->image[i] = malloc(colonnes * sizeof(*Im->image[i]));

        if (Im->image[i] == NULL)
        {
            Erreur("Erreur malloc image3D");
        }
        

        for (int j = 0; j < colonnes; j++)
        {
            Im->image[i][j] = malloc(3 * sizeof(**Im->image[i]));
            if (Im->image[i][j] == NULL)
            {
                Erreur("Erreur malloc image3D");
            }
            
        }
    }

    return Im;
}

image2D_ptr creer_image2D(int lignes, int colonnes)
{
    image2D_ptr Im = malloc(sizeof(struct s_image2D));
    if (Im == NULL)
    {
        Erreur("Erreur malloc image2D");
    }
    Im->lignes = lignes;
    Im->colonnes = colonnes;

    Im->image = (int **)malloc(sizeof(int *) * lignes);
    if (Im->image == NULL)
    {
        Erreur("Erreur malloc image2D");
    }

    for (int i = 0; i < lignes; i++)
    {
        Im->image[i] = malloc(colonnes * sizeof(int));
        if (Im->image[i] == NULL)
        {
            Erreur("Erreur malloc image2D");
        }
    }

    return Im;
}

void lire_image3D(FILE *filename, image3D_ptr im)
{
    int v1;
    int lignes, colonnes;
    lignes = im->lignes;
    colonnes = im->colonnes;
    for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < lignes; i++)
        {

            for (int j = 0; j < colonnes; j++)
            {

                fscanf(filename, "%d", &v1);
                im->image[i][j][k] = v1;
            }
        }
    }
    printf("\n");
}



int quantification(int8b r_8b, int8b g_8b, int8b b_8b, int nb_bits)
{
    if (nb_bits < 1 || nb_bits > NB_BITS_MAX)
    {
        Erreur("Quantification : NB_BITS INVALIDE");
    }

    int8b r = r_8b >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
    int8b g = g_8b >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
    int8b b = b_8b >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
    return r << (2 * nb_bits) | g << (nb_bits) | b;
}

image2D_ptr pre_traitement(FILE *filename, int nb_bits)
{
    int8b val;
    int8b pix;
    int lignes, colonnes, dimension;
    fscanf(filename, "%d %d %d", &lignes, &colonnes, &dimension);
    image2D_ptr im_retour = creer_image2D(lignes, colonnes);

    for (int k = 0; k < dimension; k++)
    {
        for (int i = 0; i < lignes; i++)
        {
            for (int j = 0; j < colonnes; j++)
            {
                fscanf(filename, "%hhd", &val);
                pix = val >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
                switch (k)
                {
                case 0:
                    im_retour->image[i][j] = pix << (2 * nb_bits);
                    break;
                case 1:
                    im_retour->image[i][j] |= pix << nb_bits;
                    break;

                case 2:
                    im_retour->image[i][j] |= pix;
                    break;

                default:
                    break;
                }
            }
        }
    }

    return im_retour;
}

const char *nom_couleur(CouleurNom c)
{
    switch (c)
    {
    case COL_ROUGE:
        return "ROUGE";
    case COL_BLEU:
        return "BLEU";
    case COL_JAUNE:
        return "JAUNE";
    case COL_ORANGE:
        return "ORANGE";
    case COL_BLANC:
        return "BLANC";
    case COL_GRIS:
        return "GRIS";
    case COL_VERT:
        return "VERT";
    default:
        return "INCONNU";
    }
}

void rgb_to_hsv(int8b r, int8b g, int8b b, float *h, float *s, float *v, int max_val)
{
    float rf = (float)r / max_val;
    float gf = (float)g / max_val;
    float bf = (float)b / max_val;

    // Trouver max et min
    float maxC = (rf > gf) ? ((rf > bf) ? rf : bf) : ((gf > bf) ? gf : bf);
    float minC = (rf < gf) ? ((rf < bf) ? rf : bf) : ((gf < bf) ? gf : bf);
    float delta = maxC - minC;

    // Calcul de V (Valeur)
    *v = maxC;

    // Calcul de S (Saturation)
    *s = (maxC < 1e-6) ? 0 : (delta / maxC);

    // Calcul de H (Teinte)
    if (delta == 0)
    {
        *h = 0; // Gris ou blanc

    }
    else if (maxC == rf)
    {
        *h = 60 * ((gf - bf) / delta);
        if (*h < 0)
            *h += 360; // Corriger les valeurs négatives
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
CouleurNom conversion_couleur(int valeur, int nb_bits)
{                                                              // couleur 24 bits
    int8b r = (valeur >> (2 * nb_bits)) & ((1 << nb_bits) - 1); // Valeur rouge : les N premiers bits
    int8b g = (valeur >> nb_bits) & ((1 << nb_bits) - 1);       // Valeur verte : les N bits du milieu
    int8b b = valeur & ((1 << nb_bits) - 1);                    // Valeur bleu : les N bits de fin

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
        (s >= 0.5) &&            
        (v >= 0.4))
    {
        return COL_BLEU;
    }

    if ((h >= 3 && h <= 28) && // Teinte orange
        (s >= 0.3) &&          
        (v >= 0.3))
        return COL_ORANGE;

    return COL_INCONNU; ///
}

image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur, int nb_bits)
{

    image2D_ptr im_retour = creer_image2D(img->lignes, img->colonnes);
    CouleurNom couleur_actuelle;
    for (int i = 0; i < img->lignes; i++)
    {
        for (int j = 0; j < img->colonnes; j++)
        {
            couleur_actuelle = conversion_couleur(img->image[i][j], nb_bits);
            if (strcmp(nom_couleur(couleur_actuelle), nom_couleur(couleur)) == 0)
            {
                im_retour->image[i][j] = 1;
            }
            else
            {
                im_retour->image[i][j] = 0;
            }
        }
    }
    return im_retour;
}

int compter_voisins(const image2D_ptr image, int x, int y) {
    int lignes = image->lignes;
    int colonnes = image->colonnes;
    int voisins = 0;

    // Parcourir les 8 voisins
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue; // Ignorer le pixel central
            int nx = x + dx;
            int ny = y + dy;

            // Vérifier si le voisin est dans les limites de l'image et est un pixel de l'objet
            if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes && image->image[nx][ny] == 1) {
                voisins++;
            }
        }
    }

    return voisins;
}


image2D_ptr encadrer(const image2D_ptr image_binarise,int nb_bits) {
    int delta = 3; // Élargissement du cadre
    int lignes = image_binarise->lignes;
    int colonnes = image_binarise->colonnes;

    // Initialiser les limites avec des valeurs impossibles
    int col_gauche = colonnes, col_droite = -1;
    int lig_haut = lignes, lig_bas = -1;
    int cpt = 0;

    // Seuil minimal pour qu'un pixel soit considéré comme faisant partie d'un objet
    int seuil_voisins =6;
    if(nb_bits ==2){
        seuil_voisins =8;
    }

    // Parcourir l'image pour trouver les limites de l'objet
    for (int i = 0; i < lignes; i++) {
        for (int j = 0; j < colonnes; j++) {
            if (image_binarise->image[i][j] == 1) {
                // Vérifier si le pixel a suffisamment de voisins
                if (compter_voisins(image_binarise, i, j) >= seuil_voisins) {
                    cpt++; // Compteur de pixels de l'objet

                    // Mise à jour des limites
                    if (j < col_gauche) col_gauche = j; // Colonne gauche
                    if (j > col_droite) col_droite = j; // Colonne droite
                    if (i < lig_haut) lig_haut = i;     // Ligne supérieure
                    if (i > lig_bas) lig_bas = i;       // Ligne inférieure
                }
            }
        }
    }

    // Si aucun pixel significatif n'a été trouvé, retourner l'image inchangée
    if (col_gauche > col_droite || lig_haut > lig_bas || cpt < 20) {
        printf("Aucun objet détecté ou objet trop petit.\n");
        return image_binarise;
    }

    // Élargir les limites avec delta
    lig_haut = max(lig_haut - 1 - delta, 0);
    lig_bas = min(lig_bas + 1 + delta, lignes - 1);
    col_gauche = max(col_gauche - 1 - delta, 0);
    col_droite = min(col_droite + 1 + delta, colonnes - 1);

    // Tracer le cadre sur l'image
    for (int j = col_gauche; j <= col_droite; j++) {
        image_binarise->image[lig_haut][j] = 1; // Ligne du haut
        image_binarise->image[lig_bas][j] = 1;  // Ligne du bas
    }
    for (int i = lig_haut; i <= lig_bas; i++) {
        image_binarise->image[i][col_gauche] = 1; // Colonne gauche
        image_binarise->image[i][col_droite] = 1; // Colonne droite
    }

    return image_binarise;
}



void free_image3D(image3D_ptr im)
{
    for (int i = 0; i < im->lignes; i++)
    {
        for (int j = 0; j < im->colonnes; j++)
        {
            free(im->image[i][j]);
        }
        free(im->image[i]);
    }
    free(im->image);
    free(im);
}

void free_image2D(image2D_ptr im)
{
    for (int i = 0; i < im->lignes; i++)
    {
        free(im->image[i]);
    }
    free(im->image);
    free(im);
}
void free_histogramme(histogramme hist)
{
    free(hist.tab);
}
