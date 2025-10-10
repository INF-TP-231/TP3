# 👩‍💻 Bloc 3 — PPM Viewer (Traitement d’Images PPM)

## 🧾 Informations personnelles

- **Nom complet :** YVANA EMILIA LALANE LARCIER  
- **Matricule :** 24G2439  
- **Bloc :** 3  
- **Fichiers concernés :** `operations.c`, `operations.h`  
- **Commandes implémentées :** `size` et `dom`  
- **Cours :** INF231 – Techniques de Conception d’Algorithmes et Structures de Données  
- **Institution :** Université de Yaoundé I — Département d’Informatique  
- **Année académique :** 2025–2026  

---

## 🎯 Objectif du Bloc 3

Le **Bloc 3** du projet **PPM Viewer** est consacré à la gestion des **opérations de base** sur les images PPM.  
Il comprend deux fonctionnalités principales :

1. **`size`** — Affiche les dimensions de l’image (largeur × hauteur).  
2. **`dom`** — Applique une **dominante de couleur** (Rouge, Vert ou Bleu).

---

## ⚙️ Commandes Détaillées

### 🧮 Commande `size`

#### 🔹 Description
Affiche la largeur et la hauteur d’une image PPM donnée en paramètre.

#### 🔹 Prototype
```c
void sizePPM(const char *filename);
Fonctionnement

Lecture du fichier PPM à l’aide du module ppm_io.c.

Extraction des valeurs width et height.

Affichage du résultat sous la forme :
Taille de l'image : largeur = 640 px, hauteur = 480 px

🔹 Exemple
ppmviewer > size tests/test.ppm
Taille de l'image : largeur = 4 px, hauteur = 4 px
🎨 Commande dom
🔹 Description

Applique une dominante de couleur (R, G ou B) à l’image en modifiant la composante correspondante.

🔹 Prototype
void applyDominantColor(const char *filename, char channel, int value);

🔹 Fonctionnement

Chargement de l’image depuis le fichier .ppm.

Parcours des pixels et ajustement de la composante couleur sélectionnée :

'R' → Rouge

'G' → Vert

'B' → Bleu

Application de la valeur de modification value (positive ou négative).

Enregistrement du résultat dans un nouveau fichier suffixé _dom.ppm.

🔹 Exemple
ppmviewer > dom R 40 tests/test.ppm
Dominante rouge appliquée avec +40 → tests/test_dom.ppm généré.


🧩 Structure du Code
operations.h

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "ppm_io.h"

void sizePPM(const char *filename);
void applyDominantColor(const char *filename, char channel, int value);

#endif

operations.c

Lecture des métadonnées d’image (largeur, hauteur).

Application de la dominante de couleur.

Gestion des erreurs (fichier introuvable, canal invalide, débordement RGB).

🧠 Difficultés Rencontrées

Prévention des dépassements de valeur (>255 ou <0) sur les composantes RGB.

Gestion des entrées utilisateurs invalides (canal inconnu ou fichier manquant).

Respect du format PPM P3 lors de la sauvegarde du fichier de sortie.

✅ Tests Réalisés

Tous les tests ont été effectués sur tests/test.ppm.

Commande	Résultat attendu
size tests/test.ppm	Affiche 4×4
dom R 50 tests/test.ppm	Image plus rouge
dom G -30 tests/test.ppm	Teinte verte atténuée
dom B 70 tests/test.ppm	Image plus bleutée

