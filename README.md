🕹️ Cub3D
Cub3D est un projet de l'école 42 Lausanne inspiré du moteur de rendu de Wolfenstein 3D. Il s'agit d'un mini-FPS en vue subjective, développé en C avec la bibliothèque MiniLibX, utilisant la technique du raycasting pour générer un environnement 3D à partir d'une carte en 2D.

<p align="center"> <img src="https://github.com/Mehdo0/cube3d/blob/main/.asset/cube3d.gif" width="720" alt="Aperçu du gameplay de Cub3D"/> </p>
🎯 Objectif du projet
L'objectif principal de Cub3D est de créer un moteur de rendu 3D simplifié en utilisant la technique du raycasting. Ce projet permet de :

Comprendre les bases du rendu 3D sans utiliser de moteur graphique avancé.

Manipuler des concepts mathématiques tels que les vecteurs, les angles et les projections.

Gérer les entrées utilisateur pour le déplacement et la rotation du joueur.

Implémenter un parsing robuste pour lire et valider des fichiers de configuration.
LinkedIn

🧠 Fonctionnalités clés
Rendu 3D via raycasting : simulation de la projection de rayons pour déterminer la distance aux murs et afficher une perspective 3D.

Gestion des textures : application de textures aux murs, sols et plafonds pour un rendu réaliste.

Déplacements fluides : gestion des mouvements avant/arrière et des rotations gauche/droite avec détection des collisions.

Parsing de la carte : lecture de fichiers .cub contenant la configuration de la carte, les textures et les couleurs.

Minimap : affichage d'une carte en 2D pour visualiser la position du joueur et l'environnement.

Optimisations : correction de la distorsion en "fish-eye" et amélioration des performances de rendu.

🛠️ Compilation et exécution
Cloner le dépôt :

bash
Copier
Modifier
git clone https://github.com/Mehdo0/cube3d.git
cd cube3d
Compiler le projet :

bash
Copier
Modifier
make
Exécuter le programme :

bash
Copier
Modifier
./cub3D maps/map.cub
Assurez-vous que le fichier map.cub est correctement configuré et présent dans le dossier maps/.

📁 Structure du projet
src/ : fichiers sources contenant la logique principale du jeu.

includes/ : fichiers d'en-tête définissant les structures et prototypes de fonctions.

maps/ : fichiers de configuration .cub définissant les cartes du jeu.

textures/ : images utilisées pour texturer les murs, sols et plafonds.

Makefile : fichier de compilation pour construire le projet.

🧪 Exemples de cartes
Le projet inclut plusieurs exemples de fichiers .cub dans le dossier maps/. Chaque fichier définit :

Les chemins vers les textures pour chaque direction (Nord, Sud, Est, Ouest).

Les couleurs du sol et du plafond.

La disposition de la carte avec des caractères représentant les murs (1), les espaces vides (0) et la position initiale du joueur (N, S, E, W).
Medium

🚀 Défis rencontrés
Parsing complexe : gestion des erreurs et validation des fichiers .cub avec des structures de données appropriées.

Gestion des collisions : implémentation d'une détection précise pour éviter que le joueur ne traverse les murs.

Optimisation du rendu : réduction de la distorsion visuelle et amélioration des performances pour un affichage fluide.

Utilisation de MiniLibX : apprentissage et utilisation efficace d'une bibliothèque graphique minimaliste.

📚 Ressources utiles
Tutoriel sur le raycasting de Lodev

Documentation de MiniLibX

Guide complet sur Cub3D

📸 Aperçu du gameplay
<p align="center"> <img src="https://github.com/Mehdo0/cube3d/blob/main/.asset/cube3d.gif" width="720" alt="Aperçu du gameplay de Cub3D"/> </p>
📬 Contact
Pour toute question ou suggestion, n'hésitez pas à me contacter :

GitHub : Mehdo0

Email : mehdi@example.com

Ce projet a été réalisé dans le cadre du cursus de l'école 42 Lausanne. Il m'a permis de renforcer mes compétences en programmation bas niveau, en mathématiques appliquées et en développement de moteurs graphiques simples.
