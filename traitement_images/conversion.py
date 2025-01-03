import os
import numpy as np
import matplotlib.pyplot as plt

# Chemin WSL
PATH = r"C:\Users\isaac\OneDrive\Bureau\1A SRI\PFR-1\PFR1_traitement_images\traitement_images"

# Demande du nom du fichier
nom_fichier = 'image.txt'
fichier_complet = os.path.join(PATH, nom_fichier)

# Vérification si le fichier existe
if not os.path.exists(fichier_complet):
    print(f"Erreur : fichier {fichier_complet} introuvable.")
    exit(1)

# Ouverture et lecture du fichier
with open(fichier_complet, "r") as fichier:
    # Lecture des dimensions
    ligne_dim = fichier.readline().strip()
    hauteur, largeur = map(int, ligne_dim.split())

    # Création d'une matrice NumPy
    image_lue = np.zeros((hauteur, largeur), dtype=int)

    # Chargement des pixels
    for i in range(hauteur):
        ligne = fichier.readline().strip()
        if not ligne:  # Vérifie les lignes manquantes
            raise ValueError(f"Ligne {i+1} manquante dans le fichier.")
        
        liste_valeur = ligne.split()
        if len(liste_valeur) != largeur:
            raise ValueError(f"Ligne {i+1} invalide : {len(liste_valeur)} colonnes au lieu de {largeur}.")
        
        image_lue[i] = [int(val) for val in liste_valeur]

# Affichage de l'image
plt.imshow(image_lue, cmap='gray', vmin=0, vmax=1)
plt.title(nom_fichier)

# Affichage ou sauvegarde
plt.show()