#Projet de Traitement d'Images et de Commandes Vocales pour Robotique

Description

Ce projet implémente un système permettant le traitement d'images et de commandes vocales pour un robot mobile. Il comprend des modules pour :

La quantification et le seuillage d'images.

La détection et l'étiquetage d'objets dans des images binaires.

L'interprétation et la conversion de commandes vocales en instructions pour le robot.

Structure du Projet

Le projet est organisé en plusieurs fichiers :

1. Traitement d'Images

traitement_images.c & traitement_images.h : Contient les fonctions de traitement d'images, notamment la lecture, l'étiquetage et la détection d'objets.

Fonctionnalités :

Lecture et manipulation d'images en niveaux de gris.

Segmentation et étiquetage des objets.

Détection et classification des formes (carré, balle).

2. Traitement Vocal

traitement_vocal.c & traitement_vocal.h : Contient les fonctions de reconnaissance et de conversion de commandes vocales.

Fonctionnalités :

Tokenisation et filtrage des commandes.

Transformation des phrases en instructions robotisées.

Interaction avec le module de pilotage vocal.

3. Gestion de la Configuration et des Logs

config.c & config.h : Gère la configuration du système et la journalisation des événements.

Fonctionnalités :

Gestion des paramètres de quantification et des logs.

Lecture et modification des fichiers de configuration.

4. Interface Utilisateur

interface.c & interface.h : Module d'interaction avec l'utilisateur.

Fonctionnalités :

Affichage et navigation dans l'interface.

Exécution des traitements d'images et de commandes vocales.

5. Compilation

Makefile : Automatisation de la compilation.

Installation et Compilation

Prérequis

Un environnement Linux avec un compilateur C (gcc).

Python 3 (pour la conversion d’images).

Compilation

Exécutez la commande suivante dans le terminal :

make

Exécution du Programme

L'exécution se fait uniquement via l'interface utilisateur à partir de l'exécutable :

exec/tst_interface.out

Toutes les interactions utilisateur sont gérées dans l'interface.

Génération et Consultation de la Documentation

Pour générer la documentation :

make doc

La documentation est consultable dans le fichier index.html du répertoire documentation.

Contributions

Les contributions sont les bienvenues ! Vous pouvez proposer des améliorations en ouvrant une pull request.

Auteurs

Yoann Smets et son équipe (UPSSITECH - Robotique)

Licence

Ce projet est sous licence MIT.
