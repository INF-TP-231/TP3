# 🧑‍💻 README Personnel — Bloc 4 : Filtres (Gris & Négatif)

## 👤 Informations Personnelles

| **Champ** | **Détails** |
|------------|-------------|
| **Nom** | **AKANA SIGNING JOSIAS AARON** |
| **Matricule** | **24H2358** |
| **Groupe TPE** | **TPE3** |
| **Bloc attribué** | **Bloc 4 — Filtres** |
| **Fichiers concernés** | `filters.c`, `filters.h` |
| **Projet** | PPM Viewer – Application de Traitement d’Images (format PPM P3) |
| **Cours** | INF231 — Techniques de Conception d’Algorithmes et Structures de Données |
| **Superviseur** | Prof. **MELATAGIA** |
| **Année académique** | 2025–2026 |
| **Date de remise** | Vendredi 10 Octobre 2025, 20h00 |

---

## 🧩 Description de ma Partie

Le **Bloc 4** du projet gère les **filtres d’image** permettant de transformer les couleurs des pixels.  
Il comprend l’implémentation de deux fonctions principales :

1. **Conversion en niveaux de gris (`gris`)**
2. **Création du négatif d’une image (`neg`)**

Ces fonctionnalités sont regroupées dans les fichiers :
- `filters.c` — implémentation des fonctions
- `filters.h` — prototypes et documentation

---

## 🎨 Fonctionnalités Détails

### 🔹 1. Filtre Gris — `gris <fichier.ppm>`

**Objectif :**  
Transformer une image couleur en **niveaux de gris** selon la moyenne des composantes RGB de chaque pixel.

**Principe de calcul :**

\[
gris = (R + G + B) / 3
\]

Chaque pixel devient :


R = G = B = gris

**Sortie générée :**  
`<nom>_gris.ppm`

**Exemple :**
```bash
ppmviewer > gris test.ppm
✅ Image test_gris.ppm générée avec succès !


🔹 2. Filtre Négatif — neg <fichier.ppm> <fichier_sortie.ppm>

Objectif :
Inverser les couleurs de l’image (effet « négatif photographique »).

Principe de calcul :

R′=255−R,G′=255−G,B′=255−B
R
′
=255−R,G
′
=255−G,B
′
=255−B

Sortie générée :
Un nouveau fichier image contenant le négatif de l’original.

Exemple :
ppmviewer > neg test.ppm neg_test.ppm
✅ Image neg_test.ppm générée avec succès !

⚙️ Approche et Algorithme
Étapes générales d’un filtre :

Lecture du fichier PPM via les fonctions du module ppm_io.

Parcours des pixels ligne par ligne.

Application de la transformation (gris ou négatif).

Écriture du résultat dans un nouveau fichier PPM.

Libération de la mémoire.

Exemple simplifié de code (filtre gris)

for (int i = 0; i < hauteur; i++) {
    for (int j = 0; j < largeur; j++) {
        Pixel *p = &image[i][j];
        int gray = (p->r + p->g + p->b) / 3;
        p->r = p->g = p->b = gray;
    }
}
🧠 Compétences Mobilisées

Manipulation de structures dynamiques pour stocker les pixels.

Gestion de fichiers texte PPM (P3).

Optimisation de boucles pour traitement rapide.

Modularité du code (séparation claire entre modules ppm_io et filters).

Bonne pratique du langage C (allocation mémoire, en-têtes, prototypes).

🧾 Tests Réalisés
Test	Image d’entrée	Commande	Résultat attendu
Niveaux de gris	tests/test.ppm	gris test.ppm	test_gris.ppm contenant l’image en gris
Négatif	tests/test.ppm	neg test.ppm test_neg.ppm	Image aux couleurs inversées
Erreur fichier manquant	gris image404.ppm	Message d’erreur géré proprement	
