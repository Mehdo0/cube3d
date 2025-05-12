# Cub3D  

Cub3D est un projet de l'école 42 inspiré du moteur de rendu de **Wolfenstein 3D**. Il s'agit d'un **mini-FPS** en **vue subjective**, développé en **C** avec la bibliothèque **MiniLibX**, utilisant la technique du **raycasting** pour générer un environnement 3D à partir d'une carte en 2D.   

## Fonctionnalités  
- Rendu 3D en **raycasting**  
- Gestion des textures pour les murs et le sol/plafond  
- Déplacements fluides avec gestion des collisions  
- Support du clavier pour la navigation  
- Lecture d'une carte au format `.cub`  

Ce projet permet de se familiariser avec la programmation bas niveau, la manipulation des mathématiques 2D/3D et l'optimisation des performances.  

## Compilation et Exécution  
```sh
make
./cub3D maps/map.cub

