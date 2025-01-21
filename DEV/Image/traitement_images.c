#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "traitement_images.h"

int debug = 0;
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

                if (fscanf(filename, "%d", &v1) != 1)
                {
                    Erreur("Echec de la lecture de la valeur dans le fichier");
                }
                im->image[i][j][k] = v1;
            }
        }
    }
    printf("\n");
}

image2D_ptr pre_traitement(FILE *filename)
{
    int8b val;
    int8b pix;
    int lignes, colonnes, dimension;
    if (fscanf(filename, "%d %d %d", &lignes, &colonnes, &dimension) != 3)
        Erreur("Erreur lecture de 3 valeurs dans le fichier");
    image2D_ptr im_retour = creer_image2D(lignes, colonnes);
    for (int k = 0; k < dimension; k++)
    {
        for (int i = 0; i < lignes; i++)
        {
            for (int j = 0; j < colonnes; j++)
            {
                if (fscanf(filename, "%hhd", &val) != 1)
                    Erreur("Erreur lecture de la valeur");
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

image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur)
{
    //image2D_ptr im_retour = creer_image2D(img->lignes, img->colonnes);
    CouleurNom couleur_actuelle;

    for (int i = 0; i < img->lignes; i++)
    {
        for (int j = 0; j < img->colonnes; j++)
        {
            couleur_actuelle = conversion_couleur(img->image[i][j]);
            if (couleur_actuelle == couleur)
            {
                img->image[i][j] = 1;
            }
            else
            {
                img->image[i][j] = 0;
            }
        }
    }
    return img;
}

int compter_voisins(const image2D_ptr image, int x, int y)
{
    int lignes = image->lignes;
    int colonnes = image->colonnes;
    int voisins = 0;

    // Parcourir les 8 voisins (-1,-1) haut gauche, (-1,0) haut, (-1,1) haut droite ect..
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx == 0 && dy == 0)
                continue; // Ignorer le pixel central
            int nx = x + dx;
            int ny = y + dy;

            if (nx >= 0 && nx < lignes && ny >= 0 && ny < colonnes && image->image[nx][ny] == 1)
            {
                voisins++;
            }
        }
    }

    return voisins;
}

image2D_ptr detecter_Objet(image2D_ptr image_binarise, boite_englobante *bteEnglobante)
{
    int delta = 3;
    int lignes = image_binarise->lignes;
    int colonnes = image_binarise->colonnes;

    // Initialiser les limites ac vals aléatoires
    int col_gauche = colonnes, col_droite = -1;
    int lig_haut = lignes, lig_bas = -1;
    int cpt = 0;

    // Seuil minimal pour qu'un pixel soit considéré comme faisant partie d'un objet
    int seuil_voisins = 6;

    for (int i = 0; i < lignes; i++)
    {
        for (int j = 0; j < colonnes; j++)
        {
            if (image_binarise->image[i][j] == 1)
            {
                if (compter_voisins(image_binarise, i, j) >= seuil_voisins)
                {
                    cpt++; // Compteur de pixels de l'objet

                    if (j < col_gauche)
                        col_gauche = j;
                    if (j > col_droite)
                        col_droite = j;
                    if (i < lig_haut)
                        lig_haut = i;
                    if (i > lig_bas)
                        lig_bas = i;
                }
            }
        }
    }

    if (col_gauche > col_droite || lig_haut > lig_bas || cpt < 100)
    {
        printf("Aucun objet détecté ou objet trop petit.\n");
        bteEnglobante->image = image_binarise;
        bteEnglobante->objet = INDEFINI;
        return image_binarise;
    }

    // Élargir les limites avec delta
    lig_haut = max(lig_haut - 1 - delta, 0);
    lig_bas = min(lig_bas + 1 + delta, lignes - 1);
    col_gauche = max(col_gauche - 1 - delta, 0);
    col_droite = min(col_droite + 1 + delta, colonnes - 1);

    for (int j = col_gauche; j <= col_droite; j++)
    {
        image_binarise->image[lig_haut][j] = 1; // Ligne du haut
        image_binarise->image[lig_bas][j] = 1;  // Ligne du bas
    }
    for (int i = lig_haut; i <= lig_bas; i++)
    {
        image_binarise->image[i][col_gauche] = 1; // Colonne gauche
        image_binarise->image[i][col_droite] = 1; // Colonne droite
    }
    creer_boiteEnglobante(bteEnglobante, lig_haut, lig_bas, col_gauche, col_droite, image_binarise);
    bteEnglobante->objet = reconnaissance_objet(*bteEnglobante);

    return image_binarise;
}

void creer_boiteEnglobante(boite_englobante *bteEnglobante, int lig_haut, int lig_bas, int col_gauche, int col_droite, image2D_ptr im)
{
    bteEnglobante->lig_haut = lig_haut;
    bteEnglobante->lig_bas = lig_bas;
    bteEnglobante->col_gauche = col_gauche;
    bteEnglobante->col_droite = col_droite;

    bteEnglobante->aire = (col_droite - col_gauche + 1) * (lig_bas - lig_haut + 1);
    bteEnglobante->image = im;
    bteEnglobante->centre_objet[0] = (col_droite - col_gauche) / 2;
    bteEnglobante->centre_objet[1] = (lig_bas - lig_haut) / 2;
}

Objet reconnaissance_objet(boite_englobante bte)
{
    int lig_haut, lig_bas, col_haut, col_bas;
    lig_haut = bte.lig_haut;
    lig_bas = bte.lig_bas;
    col_haut = bte.col_gauche;
    col_bas = bte.col_droite;
    int nb_pixel = 0;
    for (int i = lig_haut; i <= lig_bas; i++)
    {
        for (int j = col_haut; j <= col_bas; j++)
        {
            if (bte.image->image[i][j] == 1)
                nb_pixel++;
        }
    }
    if (nb_pixel >= 0.9 * bte.aire)
    {
        return CARRE;
    }
    else if (nb_pixel >= 0.4 * bte.aire)
    {
        return BALLE;
    }
    else
    {
        return INDEFINI;
    }
}

boite_englobante traitement_image(char image_entree[], char image_sortie[], CouleurNom couleur)
{
    FILE *filename, *fileout;
    filename = fopen(image_entree, "r");
    if (!filename)
    {
        fprintf(stderr, "Impossible d’ouvrir le fichier %s\n", image_entree);
    }
    fileout = fopen(image_sortie, "w");
    if (!fileout)
    {
        fprintf(stderr, "Impossible de créer le fichier %s\n", image_sortie);
        fclose(filename);
    }
    image2D_ptr image;
    boite_englobante boite_englobante;
    image = pre_traitement(filename);
    image = seuillage(image, couleur);
    image = detecter_Objet(image, &boite_englobante);

    if (boite_englobante.objet != INDEFINI)
    {
        if (boite_englobante.objet == BALLE)
            printf("BALLE\n");
        else if (boite_englobante.objet == CARRE)
            printf("CARRE\n");
        fprintf(stderr, "Coordonnées boite englobante : %d %d %d %d - Aire = %d - Centre objet = %d %d\n", boite_englobante.lig_haut, boite_englobante.col_gauche, boite_englobante.lig_bas, boite_englobante.col_droite, boite_englobante.aire, boite_englobante.centre_objet[0], boite_englobante.centre_objet[1]);
    }
    afficherImage(image, fileout);

    fclose(fileout);
    fclose(filename);
    
    return boite_englobante;
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

void free_boite_englobante(boite_englobante boite){
    if(boite.image != NULL)
    free_image2D(boite.image);
}

void afficherImage(image2D_ptr im, FILE *fileout)
{
    fprintf(fileout, "%d %d\n", im->lignes, im->colonnes);
    for (int i = 0; i < im->lignes; i++)
    {
        for (int j = 0; j < im->colonnes; j++)
        {
           
            fprintf(fileout, "%d ", im->image[i][j]);
        }
        fprintf(fileout, "\n");
    }
}