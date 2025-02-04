#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LABELS 30
#include "traitement_images.h"
#include <math.h>

int8b nb_bits;
int debug = 0;

void etablir_nbBits(int8b nb)
{
    nb_bits = nb;
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
                {
                    printf("Valeur %d\n", val);
                    Erreur("Erreur lecture de la valeur");
                }
                pix = val >> (NB_BITS_MAX - nb_bits) & ((1 << nb_bits) - 1); // On récupère les nb_bits de poids fort du pixel courant
                switch (k)
                {
                case 0:
                    im_retour->image[i][j] = pix << (2 * nb_bits); // BITS de poids fort pour la couleur rouge tout à gauche
                    break;
                case 1:
                    im_retour->image[i][j] |= pix << nb_bits; // BITS de poids fort pour la couleur verte toute au milieu
                    break;

                case 2:
                    im_retour->image[i][j] |= pix; // BITS de poids fort pour la couleur bleu tout à droite
                    break;

                default:
                    break;
                }
            }
        }
    }
    write_logfile("=====Image pré-traitée=====\n");
    return im_retour;
}

image2D_ptr seuillage(const image2D_ptr img, CouleurNom couleur)
{
    // Possibilité d'enlever cette ligne et de modifier directement l'image pour diviser par 2 l'utilisation de mémoire au PFR2
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
    write_logfile("=====Image seuillée=====\n");
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

// Algorithme de parcourir en profondeur selon le 8 voisinage
// Récupère
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
    write_logfile("=====Image étiquetée, %d objets trouvés=====\n", currentLabel);
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
                // Récupère les limites de l'objet courante
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
        // Si l'aire de la boite englobante est inférieure à 100, ce n'est pas un objet
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
    write_logfile("=====Boites englobantes filtrées, %d objets restants après filtrage=====\n", boites->taille);
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

/*Cette fonction vient calculer la distance entre les coins de l'image et le premier pixel blanc sur ce coin
//Si l'objet est un carré, la distance sera très proche de 4*delta, delta étant une "marge" pour la boite englobante
*/
int calculer_pixels_noirs(boite_englobante bte)
{

    int hauteur = bte.lig_bas - bte.lig_haut + 1;
    int largeur = bte.col_droite - bte.col_gauche + 1;
    int taille = (hauteur < largeur) ? hauteur : largeur;
    int diag1, diag2, diag3, diag4;

    diag1 = diag2 = diag3 = diag4 = 0;

    int stop_diag1 = 0;
    int stop_diag2 = 0;
    int stop_diag3 = 0;
    int stop_diag4 = 0;

    for (int i = 0; i < taille; i++)
    {
        // Haut-gauche à bas-droit
        if (!stop_diag1)
        {
            int ligne1 = bte.lig_haut + i;
            int colonne1 = bte.col_gauche + i;
            if (bte.image->image[ligne1][colonne1] == 0)
            {
                (diag1)++;
            }
            else
            {
                stop_diag1 = 1;
            }
        }

        // Haut-droit à bas-gauche
        if (!stop_diag2)
        {
            int ligne2 = bte.lig_haut + i;
            int colonne2 = bte.col_droite - i;
            if (bte.image->image[ligne2][colonne2] == 0)
            {
                (diag2)++;
            }
            else
            {
                stop_diag2 = 1;
            }
        }

        // Bas-gauche à haut-droit
        if (!stop_diag3)
        {
            int ligne3 = bte.lig_bas - i;
            int colonne3 = bte.col_gauche + i;
            if (bte.image->image[ligne3][colonne3] == 0)
            {
                (diag3)++;
            }
            else
            {
                stop_diag3 = 1;
            }
        }

        // Bas-droit à haut-gauche
        if (!stop_diag4)
        {
            int ligne4 = bte.lig_bas - i;
            int colonne4 = bte.col_droite - i;
            if (bte.image->image[ligne4][colonne4] == 0)
            {
                (diag4)++;
            }
            else
            {
                stop_diag4 = 1;
            }
        }
    }
    return diag1 + diag2 + diag3 + diag4;
}
Objet reconnaissance_objet(boite_englobante bte)
{
    int diag = calculer_pixels_noirs(bte);
    int delta = 12;
    if (diag <= delta + 6)
    {
        return CARRE;
    }
    else // Possibilité d'améliorer ça pour une évolutivité mais dans ce PFR1 seulement des balles rondes et carrés seront utilisées
    {
        return BALLE;
    }
}

char *association_objet(Objet objet)
{
    switch (objet)
    {
    case CARRE:
        return "CARRE";

    case BALLE:
        return "BALLE";

    default:
        return "INCONNU";
    }
}

tab_boite_englobante traitement_images(image2D_ptr image_pretraitee, CouleurNom couleur)
{

    write_logfile("=====DEBUT DU TRAITEMENT D'UNE IMAGE SELON SA COULEUR=====\n");
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
    write_logfile("=====Boites englobantes calculées=====\n");
    for (int i = 0; i < tabBoiteEnglobante.taille; i++)
    {

        entourer_objet(tabBoiteEnglobante.tabBoites[i]);
        boite_englobante b = tabBoiteEnglobante.tabBoites[i];
        write_logfile("=====Coordonnées de la boite englobante : CG = %d %d - CD = %d %d - BG = %d %d  - BD = %d %d  - aire = %d\n", b.lig_haut, b.col_gauche, b.lig_haut, b.col_droite, b.lig_bas, b.col_gauche, b.lig_bas, b.col_droite, b.aire);
        write_logfile("=====Objet reconnu : %s\n", association_objet(b.objet));
    }

    free_image2D(image_etiquettee);
    write_logfile("=====FIN DU TRAITEMENT D'UNE IMAGE SELON SA COULEUR=====\n");
    return tabBoiteEnglobante;
}

tab_boite_englobante traiter_image_selon_forme(image2D_ptr image_pretraitee, Objet objet)
{
    write_logfile("=====DEBUT DU TRAITEMENT D'UNE IMAGE SELON SA FORME=====\n");

    tab_boite_englobante tab_retour;
    tab_retour.tabBoites = malloc(MAX_LABELS * sizeof(boite_englobante));
    tab_retour.taille = 0;
    if (tab_retour.tabBoites == NULL)
    {
        Erreur("Erreur malloc tab_boite_englobante");
        return tab_retour; // Retourne une structure vide en cas d'erreur
    }

    CouleurNom couleur[] = {COL_BLEU, COL_JAUNE, COL_ORANGE};
    image2D_ptr image_retour = creer_image2D(image_pretraitee->lignes, image_pretraitee->colonnes);
    initialiser_image(image_retour, 0);

    for (int i = 0; i < 3; i++)
    {
        tab_boite_englobante tab_couleur_courante = traitement_images(image_pretraitee, couleur[i]);
        if (tab_couleur_courante.taille > 0)
        {
            for (int j = 0; j < tab_couleur_courante.taille; j++)
            {
                if (tab_couleur_courante.tabBoites[j].objet == objet)
                {

                    // Copie des données dans tab_retour
                    tab_retour.tabBoites[tab_retour.taille] = tab_couleur_courante.tabBoites[j];
                    tab_retour.tabBoites[tab_retour.taille].couleurObjet = couleur[i];
                    tab_retour.taille++;

                    // Ajout des images des boîtes englobantes
                    image_retour = additionner_deux_images(image_retour, tab_couleur_courante.tabBoites[j].image);
                    tab_retour.tabBoites[0].image = image_retour;

                    boite_englobante b = tab_couleur_courante.tabBoites[j];
                    write_logfile("=====Coordonnées de la boite englobante : CG = %d - CD = %d - BG = %d - BD = %d - aire = %d\n",
                                  b.lig_haut, b.col_gauche, b.lig_bas, b.col_droite, b.aire);
                    write_logfile("=====Objet reconnu : %s\n", association_objet(b.objet));
                }
            }
        }
        free_tab_boites_englobantes(tab_couleur_courante);
    }
    if (tab_retour.taille < 1)
        free_image2D(image_retour);
    write_logfile("=====FIN DU TRAITEMENT D'UNE IMAGE SELON SA FORME=====\n");
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
    if (im == NULL)
        return;
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

void appel_traitement_image_selon_couleur(char entree[], char sortie[], CouleurNom couleur)
{
    initialisationLogfileTraitementImage();
    FILE *fichier_entree = fopen(entree, "r");
    FILE *fichier_sortie = fopen(sortie, "w"); // Seulement utile pour visualiser l'image avec : python3 conversion.py
    image2D_ptr image_pretraitee = pre_traitement(fichier_entree);
    tab_boite_englobante tab = traitement_images(image_pretraitee, couleur);
    printf("%d Objets détectés\n",tab.taille);
    if (tab.taille > 0)
        afficherImage(tab.tabBoites[0].image, fichier_sortie);

    free_tab_boites_englobantes(tab);
    free_image2D(image_pretraitee);
    fclose(fichier_entree);
    fclose(fichier_sortie);
    close_logfile();
}

void appel_traitement_image_selon_forme(char entree[], char sortie[], Objet objet)
{
    initialisationLogfileTraitementImage();
    FILE *fichier_entree = fopen(entree, "r");
    FILE *fichier_sortie = fopen(sortie, "w"); // Seulement utile pour visualiser l'image avec : python3 conversion.py
    image2D_ptr image_pretraitee = pre_traitement(fichier_entree);
    tab_boite_englobante tab = traiter_image_selon_forme(image_pretraitee, objet);
    printf("%d Objets détectés\n",tab.taille);
    if (tab.taille > 0){
        afficherImage(tab.tabBoites[0].image, fichier_sortie);
         free_tab_boites_englobantes(tab);
        
    }
    else{
        free(tab.tabBoites);
    }
    free_image2D(image_pretraitee);
    fclose(fichier_entree);
    fclose(fichier_sortie);
    close_logfile();
}

void initialisationLogfileTraitementImage()
{
    init_logfile();
    write_logfile("Fichier initialisé\n");
}