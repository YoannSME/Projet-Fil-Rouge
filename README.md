# Projet de Traitement d'Images et de Commandes Vocales pour Robotique

## Présentation du Projet

### Description du Projet :

Ce projet implémente un système permettant le traitement d'images et de commandes vocales pour un robot mobile. Il comprend des modules pour :

- La quantification et le seuillage d'images.
- La détection et l'étiquetage d'objets dans des images binaires.
- L'interprétation et la conversion de commandes vocales en instructions pour le robot.

## Table des Matières

1. [Table des Matières](#table-des-matières)
2. [Fonctionnalités Principales](#fonctionnalités-principales)
3. [Utilisation](#utilisation)
4. [Exemple d'Utilisation](#exemple-dutilisation)
5. [Compilation](#compilation)
6. [Documentation](#documentation)
7. [Contributions](#contributions)

## Fonctionnalités Principales :

1. **Traitement d'Images** :

   - Lecture et manipulation d'images en niveaux de gris.
   - Segmentation et étiquetage des objets.
   - Détection et classification des formes (carré, balle).

2. **Traitement Vocal** :

   - Tokenisation et filtrage des commandes vocales.
   - Transformation des phrases en instructions robotisées.
   - Interaction avec le module de pilotage vocal.

3. **Gestion de la Configuration et des Logs** :

   - Gestion des paramètres de quantification et des logs.
   - Lecture et modification des fichiers de configuration.

4. **Interface Utilisateur** :

   - Affichage et navigation dans l'interface.
   - Exécution des traitements d'images et de commandes vocales.

## Utilisation

L'exécution du programme se fait uniquement via l'interface utilisateur à partir de l'exécutable suivant :

```bash
exec/tst_interface.out
```

L'utilisateur navigue ensuite dans l'interface pour sélectionner les différentes options.

## Compilation

Pour compiler le programme, exécutez la commande suivante :

```bash
make
```

Pour supprimer les exécutables/fichiers objets, exécutez la commande suivante :
```bash
make clean
```


## Documentation

Vous pouvez générer la documentation avec la commande :

```bash
make doc
```

La documentation est consultable dans le fichier `index.html` du répertoire `documentation`.

## Contributions

**Équipe de développement :**

- GROUPE 3 PFR
- APEDOH Senam Amenyo  Jules
- LETEURTRE Martin
- SICHI Axel
- SMETS Yoann

**Cliente :**
FERRANE Isabelle

