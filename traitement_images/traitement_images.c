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

CouleurNom conversion_couleur(int valeur, int nb_bits)
{ // couleur 24 bits
    unsigned char r = (valeur >> (2 * nb_bits)) & ((1 << nb_bits) - 1);
    unsigned char g = (valeur >> nb_bits) & ((1 << nb_bits) - 1);
    unsigned char b = valeur & ((1 << nb_bits) - 1);

    unsigned int max_val = (1 << nb_bits) - 1;
    float thr80 = 0.8f * max_val; // "haut"
    float thr20 = 0.2f * max_val; // "bas"

    // Convertir r,g,b en float pour comparer
    float rf = (float)r, gf = (float)g, bf = (float)b;

    // BLANC : r,g,b > ~80% du max
    if (rf > thr80 && gf > thr80 && bf > thr80)
    {
        return COL_BLANC;
    }

    // GRIS : r,g,b assez proches, ni trop clair ni trop sombre
    {
        float diff_rg = fabsf(rf - gf);
        float diff_rb = fabsf(rf - bf);
        float diff_gb = fabsf(gf - bf);
        float moy = (rf + gf + bf) / 3.0f;
        // ex. on veut diff < 0.2*max, et moy entre 0.2*max et 0.8*max
        if (diff_rg < 0.2f * max_val &&
            diff_rb < 0.2f * max_val &&
            diff_gb < 0.2f * max_val &&
            moy > thr20 && moy < thr80)
        {
            return COL_GRIS;
        }
    }

    // ROUGE
    if (r > 0.6f * max_val && r > g + 0.2f * max_val && r > b + 0.2f * max_val)
    {
        return COL_ROUGE;
    }

    // JAUNE : r,g forts, b faible
    if (r > 0.4f * max_val && g > 0.4f * max_val && b < 0.3f * max_val)
    {
        return COL_JAUNE;
    }

    // ORANGE : r très fort, g moyen, b faible
    if (r > 0.4f * max_val && g > 0.3f * max_val && b < 0.2f * max_val)
    {
        return COL_ORANGE;
    }

    // BLEU : b nettement plus grand que r et g
    if (b > 0.6f * max_val && b > r + 0.2f * max_val && b > g + 0.2f * max_val)
    {
        return COL_BLEU;
    }

    if (g > 0.8f * max_val && g > r + 0.2f * max_val && g > b + 0.2f * max_val)
    {
        return COL_VERT;
    }
    return COL_INCONNU;
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
                im_retour->image[i][j] = 255;
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
