#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

    /*printf("Image allouée\n.");*/
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
        /*printf("Image[i] allouée\n.");*/

        for (int j = 0; j < colonnes; j++)
        {
            Im->image[i][j] = malloc(3 * sizeof(**Im->image[i]));
            if (Im->image[i][j] == NULL)
            {
                Erreur("Erreur malloc image3D");
            }
            /*printf("Image[col] allouée\n.");*/
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

image2D_ptr RGB_to_GREY(image3D_ptr im, histogramme *hist, int nb_bits)

{
    int taille = 1 << (nb_bits * 3);
    printf("taille = %d\n", taille);
    hist->tab = (int *)calloc(taille, sizeof(int));
    hist->taille = taille;
    if (hist->tab == NULL)
    {
        Erreur("Malloc histogramme RGB_to_GREY");
    }
    int8b r, g, b;
    int8b somme = 0;
    image2D_ptr im_retour = creer_image2D(im->lignes, im->colonnes);
    for (int i = 0; i < im->lignes; i++)
    {
        for (int j = 0; j < im->colonnes; j++)
        {
            r = im->image[i][j][R];
            g = im->image[i][j][G];
            b = im->image[i][j][B];
            somme = quantification(r, g, b, nb_bits);
            // im_retour->image[i][j] = r*COEFF_R+g*COEFF_G+b*COEFF_B;
            im_retour->image[i][j] = somme;
            hist->tab[somme]++;
        }
    }

    return im_retour;
}

int quantification(int8b r_8b, int8b g_8b, int8b b_8b, int nb_bits)
{
    if (nb_bits < 1 || nb_bits > NB_BITS_MAX)
    {
        Erreur("Quantification : NB_BITS INVALIDE");
    }

    unsigned char r = r_8b >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
    unsigned char g = g_8b >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
    unsigned char b = b_8b >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1);
    return r << (2 * nb_bits) | g << (nb_bits) | b;
}

image2D_ptr pre_traitement(FILE *filename, int nb_bits)
{
    int8b val;
    unsigned char pix;
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

void rgb_to_hsv(char r, char g, char b, float *h, float *s, float *v, int max_val)
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
    if (delta < 1e-6)
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
    *h = *h / 2;
}
CouleurNom conversion_couleur(int valeur, int nb_bits)
{                                                              // couleur 24 bits
    char r = (valeur >> (2 * nb_bits)) & ((1 << nb_bits) - 1); // Valeur rouge : les N premiers bits
    char g = (valeur >> nb_bits) & ((1 << nb_bits) - 1);       // Valeur verte : les N bits du milieu
    char b = valeur & ((1 << nb_bits) - 1);                    // Valeur bleu : les N bits de fin

    int max_val = ((1 << nb_bits - 1) | (1 << nb_bits) - 1);
    float h, s, v;
    rgb_to_hsv(r, g, b, &h, &s, &v, max_val);
    if ((h >= 13 && h <= 24) && // Teinte jaune
        (s >= 0.44) &&          // Saturation suffisante
        (v >= 0.3))
    {
        return COL_JAUNE;
    }
    if ((h >= 100 && h <= 140) && // Teinte bleue
        (s >= 0.4) &&             // Saturation élevée
        (v >= 0.3))
        return COL_BLEU;
    if ((h >= 7 && h <= 13) && // Teinte orange
        (s >= 0.5) &&           // Saturation suffisante
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

CouleurNom ***build_lut(unsigned int nb_bits)
{
    unsigned int size = 1 << nb_bits; // 4,8,16
    // Allouer la table 3D
    // On va faire un triple pointeur LUT[size][size][size]
    // En C, on peut faire un malloc "en dur" ou un malloc triple-niveaux,
    // ou un bloc 1D. Pour la démonstration, faisons triple-niveaux simple.

    // 1) Créer un pointeur de pointeurs de pointeurs
    CouleurNom ***lut = malloc(size * sizeof(*lut));
    if (!lut)
        return NULL;

    for (unsigned int r = 0; r < size; r++)
    {
        lut[r] = malloc(size * sizeof(*(lut[r])));
        if (!lut[r])
            return NULL;

        for (unsigned int g = 0; g < size; g++)
        {
            lut[r][g] = malloc(size * sizeof(*(lut[r][g])));
            if (!lut[r][g])
                return NULL;
        }
    }

    // 2) Remplir la table
    for (unsigned int r = 0; r < size; r++)
    {
        for (unsigned int g = 0; g < size; g++)
        {
            for (unsigned int b = 0; b < size; b++)
            {
                unsigned char val = r << (2 * nb_bits) | g << (nb_bits) | b;
                lut[r][g][b] = conversion_couleur(val, nb_bits);
            }
        }
    }

    return lut;
}

// Libérer la LUT
void free_lut(CouleurNom ***lut, unsigned int nb_bits)
{
    unsigned int size = 1 << nb_bits;
    for (unsigned int r = 0; r < size; r++)
    {
        for (unsigned int g = 0; g < size; g++)
        {
            free(lut[r][g]);
        }
        free(lut[r]);
    }
    free(lut);
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
