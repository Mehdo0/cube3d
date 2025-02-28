# TODO - Projet Cub3D

Ce document liste les étapes clés à réaliser pour mener à bien le projet Cub3D.

## 1. Initialisation du projet
- [ ] Créer la structure du projet (dossiers `src`, `include`, `lib`, etc.)
- [ ] Mettre en place un Makefile pour faciliter la compilation
- [ ] Configurer les dépendances (MiniLibX, bibliothèques standard, etc.)

## 2. Parsing et gestion de la configuration
- [ ] Lire et valider le fichier de configuration (`.cub`)
- [ ] Extraire les informations : résolution, chemins vers les textures, couleurs du sol/plafond, et la carte
- [ ] Gérer les erreurs et cas particuliers dans la configuration

## 3. Initialisation de la fenêtre et gestion des événements
- [ ] Créer la fenêtre avec MiniLibX en respectant la résolution définie
- [ ] Mettre en place les hooks pour la gestion des entrées clavier et la fermeture de la fenêtre

## 4. Implémentation du raycasting
- [ ] Calculer les intersections des rayons avec les murs
- [ ] Déterminer la distance entre la caméra et chaque mur pour un rendu 3D correct
- [ ] Calculer la hauteur de la projection murale pour chaque colonne de pixels
- [ ] Appliquer les textures sur les murs en fonction de l'orientation

## 5. Gestion des mouvements et des collisions
- [ ] Implémenter les déplacements (avant, arrière, strafe) et la rotation
- [ ] Mettre en place la détection et la gestion des collisions avec les murs

## 6. Rendu du sol et du plafond
- [ ] Implémenter le rendu pour le sol et le plafond
- [ ] Optimiser l'affichage pour maintenir de bonnes performances

## 7. Fonctionnalités supplémentaires (optionnel)
- [ ] Gérer les sprites (objets interactifs, ennemis, etc.)
- [ ] Ajouter des éléments bonus ou des effets visuels supplémentaires (ombras, lumières, etc.)

## 8. Tests, débogage et optimisation
- [ ] Réaliser des tests unitaires et fonctionnels pour chaque module
- [ ] Déboguer les problèmes d'affichage et de collision
- [ ] Optimiser les performances et la gestion de la mémoire

## 9. Documentation et finalisation
- [ ] Rédiger une documentation détaillée et un README.md complet
- [ ] Commenter le code pour faciliter sa maintenance
- [ ] Effectuer une relecture finale pour vérifier la conformité aux normes du projet 42

