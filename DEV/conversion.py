import os
import numpy as np
import matplotlib.pyplot as plt

PATH = os.getcwd()
PATH+="/sortie"

lst_fichier = os.listdir(PATH)

cpt = 0
for nom_fichier in lst_fichier:
    # Ignorer tout fichier non .txt
    if not nom_fichier.endswith(".txt"):
        continue
    
    fichier_complet = os.path.join(PATH, nom_fichier)

    # Vérification si le fichier existe
    if not os.path.exists(fichier_complet):
        print(f"Erreur : fichier {fichier_complet} introuvable.")
        continue

    # Lecture du fichier texte
    with open(fichier_complet, "r", encoding="utf-8") as fichier:
        # Lecture des dimensions
        ligne_dim = fichier.readline().strip()
        if( not ligne_dim ):
            continue
        hauteur, largeur = map(int, ligne_dim.split())
        

        # Création d'une matrice NumPy
        image_lue = np.zeros((hauteur, largeur), dtype=int)

        # Chargement des pixels
        for i in range(hauteur):
            ligne = fichier.readline().strip()
            if not ligne:
                raise ValueError(f"Ligne {i+1} manquante dans le fichier {nom_fichier}.")
            
            liste_valeur = ligne.split()
            if len(liste_valeur) != largeur:
                raise ValueError(
                    f"Ligne {i+1} invalide : {len(liste_valeur)} colonnes au lieu de {largeur} dans {nom_fichier}."
                )
            
            image_lue[i] = [int(val) for val in liste_valeur]

    # Création d'une nouvelle figure
    plt.figure()
    plt.imshow(image_lue, cmap='gray', vmin=0, vmax=1)
    plt.title(nom_fichier)

    # Nom de sortie .png basé sur le nom du fichier .txt
    base_name = os.path.splitext(nom_fichier)[0]
    output_name = f"{base_name,cpt}.png"  # ou "_output.png", etc.
    output_path = os.path.join(PATH, output_name)
    cpt+=1

    # Sauvegarde de l'image
    plt.savefig(output_path)
    plt.close()  # on ferme la figure
