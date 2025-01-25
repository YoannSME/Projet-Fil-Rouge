#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LABELS 10
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
        Im->image[i] = calloc(colonnes, sizeof(int));
        if (Im->image[i] == NULL)
        {
            Erreur("Erreur malloc image2D");
        }
    }

    return Im;
}

image2D_ptr copier_image(image2D_ptr image_origine)
{
    image2D_ptr image_copie = creer_image2D(image_origine->lignes, image_origine->colonnes);
    for (int i = 0; i < image_origine->lignes; i++)
    {
        for (int j = 0; j < image_origine->colonnes; j++)
        {
            image_copie->image[i][j] = image_origine->image[i][j];
        }
    }
    return image_copie;
}

image2D_ptr additionner_deux_images(image2D_ptr image1, image2D_ptr image2)
{
    if ((image1->lignes != image2->lignes) || (image1->colonnes != image2->colonnes))
    {
        fprintf(stderr, "Les images n'ont pas la même dimension\n");
        return image1;
    }

    for (int i = 0; i < image1->lignes; i++)
    {
        for (int j = 0; j < image1->colonnes; j++)
        {
            image1->image[i][j] = image1->image[i][j] | image2->image[i][j];
        }
    }

    return image1;
}
void initialiser_image(image2D_ptr image, int valeur)
{
    for (int i = 0; i < image->lignes; i++)
    {
        for (int j = 0; j < image->colonnes; j++)
        {
            image->image[i][j] = valeur;
        }
    }
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
}

image2D_ptr lire_image2D(FILE *filename)
{
    int v1;
    int lignes, colonnes;
    if (fscanf(filename, "%d %d", &lignes, &colonnes) != 2)
        Erreur("Erreur lire image2D");

    image2D_ptr im = creer_image2D(lignes, colonnes);

    for (int i = 0; i < lignes; i++)
    {

        for (int j = 0; j < colonnes; j++)
        {

            if (fscanf(filename, "%d", &v1) != 1)
            {
                Erreur("Echec de la lecture de la valeur dans le fichier");
            }
            im->image[i][j] = v1;
        }
    }
   
    return im;
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
    image2D_ptr im_retour = creer_image2D(img->lignes, img->colonnes);
    CouleurNom couleur_actuelle;

    for (int i = 0; i < img->lignes; i++)
    {
        for (int j = 0; j < img->colonnes; j++)
        {
            couleur_actuelle = conversion_couleur(img->image[i][j]);
            if (couleur_actuelle == couleur)
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

void DFS_iteratif_8(image2D_ptr binaire,
                    image2D_ptr labels,
                    int start_i,
                    int start_j,
                    int label)
{

    PILE pile = init_PILE();

    Element debut;
    debut.x = start_i;
    debut.y = start_j;
    pile = emPILE(pile, debut);

    labels->image[start_i][start_j] = label;

    int di[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int dj[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    int nbVoisins = 8;

    // Parcours en profondeur
    while (!PILE_estVide(pile))
    {

        Element courant;
        pile = dePILE(pile, &courant);

        int i = courant.x;
        int j = courant.y;

        // 8 voisinage
        for (int k = 0; k < nbVoisins; k++)
        {
            int ni = i + di[k];
            int nj = j + dj[k];

            if (ni >= 0 && ni < binaire->lignes &&
                nj >= 0 && nj < binaire->colonnes)
            {
                // pixel pas encore  labellisé
                if (binaire->image[ni][nj] == 1 &&
                    labels->image[ni][nj] == 0)
                {
                    labels->image[ni][nj] = label;
                    Element voisin;
                    voisin.x = ni;
                    voisin.y = nj;
                    pile = emPILE(pile, voisin);
                }
            }
        }
    }
    free(pile);
}

int labelliserImage_8voisinage(image2D_ptr binaire,
                               image2D_ptr labels)
{
    int currentLabel = 0;

    for (int i = 0; i < binaire->lignes; i++)
    {
        for (int j = 0; j < binaire->colonnes; j++)
        {
            if (binaire->image[i][j] == 1 &&
                labels->image[i][j] == 0 && compter_voisins(binaire, i, j) >= 8)
            {
                currentLabel++;
                DFS_iteratif_8(binaire, labels, i, j, currentLabel);
            }
        }
    }

    return currentLabel;
}

void calculer_boites_englobantes(image2D_ptr labels, image2D_ptr im_binaire, boite_englobante *boites, int nbLabels)
{
    // Init possibilité de l'enlever plus tard (debug)
    for (int k = 0; k < nbLabels; k++)
    {
        boites[k].lig_haut = labels->lignes;
        boites[k].lig_bas = 0;
        boites[k].col_gauche = labels->colonnes;
        boites[k].col_droite = 0;
        boites[k].aire = 0;
        boites[k].image = im_binaire;
    }

    for (int i = 0; i < labels->lignes; i++)
    {
        for (int j = 0; j < labels->colonnes; j++)
        {
            int lab = labels->image[i][j]; // 1..nbLabels
            if (lab > 0 && lab <= nbLabels)
            {
                int idx = lab - 1;
                if (i < boites[idx].lig_haut)
                    boites[idx].lig_haut = i;
                if (i > boites[idx].lig_bas)
                    boites[idx].lig_bas = i;
                if (j < boites[idx].col_gauche)
                    boites[idx].col_gauche = j;
                if (j > boites[idx].col_droite)
                    boites[idx].col_droite = j;
                boites[idx].aire++;
            }
        }
    }
}
void filtrage_boites(tab_boite_englobante *boites)
{
    if (boites == NULL || boites->tabBoites == NULL || boites->taille <= 0)
    {
        printf("Aucune boîte à traiter.\n");
        return;
    }

    for (int i = boites->taille - 1; i >= 0; i--)
    {
        boite_englobante b = boites->tabBoites[i];
       

        if (b.aire < 100)
        {
            boites->tabBoites[i] = boites->tabBoites[boites->taille - 1];
            boites->taille--;
        }
        else
        {
            boites->tabBoites[i] = creer_boiteEnglobante(
                b.image, b.lig_haut, b.lig_bas, b.col_gauche, b.col_droite);
        }
    }
}

void entourer_objet(boite_englobante b)
{
    for (int j = b.col_gauche; j <= b.col_droite; j++)
    {
        b.image->image[b.lig_haut][j] = 1;
        b.image->image[b.lig_bas][j] = 1;
    }

    for (int i = b.lig_haut; i <= b.lig_bas; i++)
    {
        b.image->image[i][b.col_gauche] = 1;
        b.image->image[i][b.col_droite] = 1;
    }
}

boite_englobante creer_boiteEnglobante(image2D_ptr image, int lig_haut, int lig_bas, int col_gauche, int col_droite)
{
    boite_englobante bteEnglobante;

    int delta = 3;
    bteEnglobante.image = image;
    bteEnglobante.lig_haut = max(lig_haut - 1 - delta, 0);
    bteEnglobante.lig_bas = min(lig_bas + 1 + delta, image->lignes - 1);
    bteEnglobante.col_gauche = max(col_gauche - 1 - delta, 0);
    bteEnglobante.col_droite = min(col_droite + 1 + delta, image->colonnes - 1);

    bteEnglobante.aire = (bteEnglobante.col_droite - bteEnglobante.col_gauche + 1) *
                         (bteEnglobante.lig_bas - bteEnglobante.lig_haut + 1);

    // Recalcul du centre
    bteEnglobante.centre_objet[0] = bteEnglobante.col_gauche + (bteEnglobante.col_droite - bteEnglobante.col_gauche) / 2;
    bteEnglobante.centre_objet[1] = bteEnglobante.lig_haut +
                                    (bteEnglobante.lig_bas - bteEnglobante.lig_haut) / 2;

    bteEnglobante.objet = reconnaissance_objet(bteEnglobante);

    return bteEnglobante;
}

Objet reconnaissance_objet(boite_englobante bte)
{
    int nb_pixel = 0;
    for (int i = bte.lig_haut; i <= bte.lig_bas; i++)
    {
        for (int j = bte.col_gauche; j <= bte.col_droite; j++)
        {
            if (bte.image->image[i][j] == 1)
                nb_pixel++;
        }
    }
    if (nb_pixel >= 0.9 * bte.aire)
    {
        return CARRE;
    }
    else if (nb_pixel >= 0.5 * bte.aire)
    {
        return BALLE;
    }
    else
    {
        return NONE;
    }
}

void association_objet(Objet objet){
    switch(objet){
        case CARRE:
            printf("CARRE\n");
            break;
        case BALLE:
            printf("BALLE\n");
            break;
        default:
            printf("AUCUN OBJET\n");
            break;
    }
}

tab_boite_englobante traitement_images(image2D_ptr image_pretraitee, CouleurNom couleur)
{

    image2D_ptr imSeuillee = seuillage(image_pretraitee, couleur);

    image2D_ptr image_etiquettee = creer_image2D(imSeuillee->lignes, imSeuillee->colonnes);

    tab_boite_englobante tabBoiteEnglobante;
    int nb_objets = labelliserImage_8voisinage(imSeuillee, image_etiquettee);
   
    if (nb_objets == 0)
    {
        tabBoiteEnglobante.tabBoites = NULL;
        tabBoiteEnglobante.taille = 0;
        free_image2D(image_etiquettee);
        free_image2D(imSeuillee);
        return tabBoiteEnglobante;
    }
    tabBoiteEnglobante.tabBoites = malloc(nb_objets * sizeof(boite_englobante));

    if (tabBoiteEnglobante.tabBoites == NULL)
    {
        Erreur("Erreur malloc tabBoiteEnglobante");
    }

    tabBoiteEnglobante.taille = nb_objets;
    calculer_boites_englobantes(image_etiquettee, imSeuillee, tabBoiteEnglobante.tabBoites, nb_objets);

    filtrage_boites(&tabBoiteEnglobante);
    for (int i = 0; i < tabBoiteEnglobante.taille; i++)
    {

        entourer_objet(tabBoiteEnglobante.tabBoites[i]);
        boite_englobante b = tabBoiteEnglobante.tabBoites[i];
        //printf("Coordoonnées de la boite englobante : %d %d %d %d - aire %d - centre objet : %d %d\n", b.lig_haut, b.lig_bas, b.col_gauche, b.col_droite, b.aire, b.centre_objet[0], b.centre_objet[1]);
        //association_objet(b.objet);
    }

    free_image2D(image_etiquettee);

    return tabBoiteEnglobante;
}

tab_boite_englobante traiter_image_selon_forme(image2D_ptr image_pretraitee, Objet objet)
{

    // Tableau de toutes les boites englobantes de la première image selon col bleu
    tab_boite_englobante tab_retour;
    tab_retour.tabBoites = malloc(30 * sizeof(boite_englobante)); //max 10 objets
    tab_retour.taille = 0;
    if (tab_retour.tabBoites == NULL)
    {
        Erreur("Erreur malloc tab_boite_englobante");
    }
    CouleurNom couleur[] = {COL_BLEU, COL_JAUNE, COL_ORANGE};
    image2D_ptr image_retour = creer_image2D(image_pretraitee->lignes, image_pretraitee->colonnes);
   
    int i = 0;
    do
    {
        tab_boite_englobante tab_couleur_courante = traitement_images(image_pretraitee, couleur[i]);
        if(tab_couleur_courante.taille>0){
        image_retour = additionner_deux_images(image_retour, tab_couleur_courante.tabBoites[0].image);
        for (int i = 0; i < tab_couleur_courante.taille; i++)
        {
            if (tab_couleur_courante.tabBoites[i].objet == objet)
            {
                tab_retour.tabBoites[i].couleurObjet = couleur[i];
                tab_retour.tabBoites[tab_retour.taille] = tab_couleur_courante.tabBoites[i];
                tab_retour.taille++;
            }
            
        }
        }
        free_tab_boites_englobantes(tab_couleur_courante);
        i++;
    }while (i < 3);
    
    tab_retour.tabBoites[0].image = image_retour;
    return tab_retour;
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
    im = NULL;
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
void free_tab_boites_englobantes(tab_boite_englobante tab)
{
    if (tab.tabBoites != NULL)
    {
        free_boite_englobante(tab.tabBoites[0]);
        free(tab.tabBoites);
    }
}

void free_boite_englobante(boite_englobante boite)
{
    if (boite.image != NULL)
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