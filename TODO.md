# TODO : Implémentation du Raycasting avec l'algorithme DDA

## Contexte
Nous disposons d'une map sous forme de grille, par exemple :

1111111111111111111
10W1001001001000001
1011000001000001001
1001001001111101111
1001111000001001001
1000000000000001001
1001111111111001001
1111000000000001011
1000000001000000001
1111111111111111111


- **'1'** représente un mur.
- **'0'** représente un espace vide.
- **'N', 'W', 'S', 'E'** indiquent la position (et la direction initiale) du joueur.

La map est déjà parsée.

## Étapes d'implémentation

### 1. Initialisation des structures
- **Map** : Créer une structure ou utiliser un tableau 2D / un tableau de chaînes pour stocker la map.
- **Joueur** : Créer une structure `Player` incluant :
  - **Position** (`posX`, `posY`), par exemple en `float`.
  - **Vecteur direction** (`dirX`, `dirY`) qui indique où regarde le joueur.
  - **Vecteur plan** (`planeX`, `planeY`) qui définit la largeur du champ de vision.
  
*Vulgarisation* : Imagine que le joueur est un personnage posé sur la grille. Sa position te dit où il se trouve, son vecteur direction te montre dans quelle direction il regarde (comme pointer du doigt) et le vecteur plane détermine la largeur de sa fenêtre de vision (ce qu'il voit à gauche et à droite).

---

### 2. Définir la fenêtre de rendu
- Choisir une résolution pour l'écran (ex. : 640x480).
- Déterminer que chaque colonne verticale de l'écran correspond à un rayon à tracer.

---

### 3. Calcul des directions des rayons
Pour chaque colonne **x** de l'écran :
- **Calculer `cameraX`** : une valeur allant de -1 (bord gauche) à +1 (bord droit).
- **Calculer la direction du rayon** :
  - `rayDirX = dirX + planeX * cameraX`
  - `rayDirY = dirY + planeY * cameraX`
  
*Explication mathématique* : On part du vecteur central (dir) et on y ajoute une partie du vecteur plane (qui détermine la largeur de la vision) proportionnel à la position sur l'écran. Cela permet de couvrir tout le champ de vision.

---

### 4. Implémenter l'algorithme DDA pour chaque rayon
#### 4.1. Déterminer la case de départ
- Calculer la case dans laquelle se trouve le joueur :
  - `mapX = (int) posX`
  - `mapY = (int) posY`

#### 4.2. Calculer les distances d'incrémentation (`deltaDistX` et `deltaDistY`)
- Ces valeurs représentent la distance parcourue par le rayon pour traverser une case en X ou en Y.
- Formules :
  - \(\Delta_{distX} = \sqrt{1 + \left(\frac{rayDirY}{rayDirX}\right)^2}\)
  - \(\Delta_{distY} = \sqrt{1 + \left(\frac{rayDirX}{rayDirY}\right)^2}\)
  
*Explication vulgarisée* : Ces formules nous indiquent combien le rayon doit avancer (en "distance réelle") pour passer d'un bord de case à l'autre, en tenant compte de sa direction.

#### 4.3. Déterminer les pas (stepX et stepY)
- Si `rayDirX < 0` alors `stepX = -1`, sinon `+1`.
- Pareil pour `rayDirY` et `stepY`.

#### 4.4. Calculer les distances initiales jusqu'aux bords (`sideDistX` et `sideDistY`)
- Ces valeurs indiquent la distance entre la position du joueur et le premier bord vertical et horizontal de la case.
- Exemple :
  - Si `rayDirX < 0` :
    - `sideDistX = (posX - mapX) * deltaDistX`
  - Sinon :
    - `sideDistX = (mapX + 1.0 - posX) * deltaDistX`
  
*Remarque* : Le même principe s'applique pour `sideDistY`.

#### 4.5. Boucle DDA
- **Tant que** le rayon n’a pas rencontré un mur :
  - **Comparer** `sideDistX` et `sideDistY` :
    - Si `sideDistX < sideDistY` :
      - `sideDistX += deltaDistX`
      - `mapX += stepX`
      - `side = 0` (indique que le mur touché est vertical)
    - Sinon :
      - `sideDistY += deltaDistY`
      - `mapY += stepY`
      - `side = 1` (mur horizontal)
  - **Vérifier** si la case [mapX][mapY] contient un mur (`'1'`). Si oui, sortir de la boucle.
  
*Vulgarisation* : L'algorithme "saute" de case en case, en choisissant toujours le bord le plus proche du rayon, jusqu'à ce qu'il rencontre un mur.

---

### 5. Calcul de la distance au mur et de la hauteur de la tranche murale
- **Distance perpendiculaire** (pour éviter l'effet fisheye) :
  - Si `side == 0` :
    - `perpWallDist = sideDistX - deltaDistX`
  - Sinon :
    - `perpWallDist = sideDistY - deltaDistY`
- **Hauteur du mur** :
  - `lineHeight = (int)(screenHeight / perpWallDist)`
  
*Math* : Plus le mur est proche, plus la distance est petite et donc la hauteur (calculée par division) est grande, ce qui crée l'effet de perspective.

---

### 6. Rendu de la scène
- Pour chaque colonne, dessiner la tranche murale (la "vertical stripe") avec la hauteur calculée.
- Optionnel : ajouter un rendu pour le sol et le plafond.

---

### 7. Gestion des entrées utilisateur
- Implémenter la rotation et le déplacement du joueur en mettant à jour :
  - Sa position (`posX`, `posY`)
  - Ses vecteurs `dir` et `plane` (en appliquant une rotation via la matrice de rotation 2D)
- Recalculer le rendu après chaque mise à jour.

---

### 8. Intégrer dans une boucle principale
- Créer une boucle qui :
  - Pour chaque frame, pour chaque colonne de l'écran, calcule la direction du rayon et exécute l'algorithme DDA.
  - Dessine la scène (murs, sol, plafond).
  - Gère les entrées utilisateur.
  - Rafraîchit l'écran.

---

## Notes supplémentaires
- **Compréhension mathématique** :  
  Les formules pour \(\Delta_{distX}\) et \(\Delta_{distY}\) viennent du théorème de Pythagore appliqué à la direction du rayon. Elles traduisent l'idée suivante : pour avancer d'une case en X (ou Y), on doit aussi avancer proportionnellement en Y (ou X) selon l'inclinaison du rayon.
  
- **Vulgarisation** :  
  Pense à l'algorithme DDA comme à un jeu de "saute-mouton" sur une grille. Tu commences là où se trouve le joueur et tu sautes de case en case (en choisissant la direction la plus courte à parcourir) jusqu'à ce que tu tombes sur un mur. À ce moment, tu mesures la distance parcourue pour savoir à quelle "taille" afficher ce mur à l'écran.

---

Ce plan te guide étape par étape pour intégrer le raycasting avec l'algorithme DDA dans ton code, en alliant explications simples et formules mathématiques pour t'aider à comprendre le fonctionnement sous-jacent.
