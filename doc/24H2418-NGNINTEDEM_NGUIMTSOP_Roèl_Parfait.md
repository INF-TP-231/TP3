# 💾 README Personnel — Bloc I : Gestion des Entrées/Sorties (I/O) PPM

## 👤 Informations Personnelles & Contexte

| **Champ** | **Détails** |
| :--- | :--- |
| **Nom** | **NGNINTEDEM NGUIMTSOP Roèl Parfait** |
| **Matricule** | **24H2418** |
| **Bloc attribué** | **Bloc I — Lecture et Écriture PPM (I/O)** |
| **Fichiers concernés** | `ppm_io.c`, `ppm_io.h` |
| **Projet** | PPM Viewer – Application de Traitement d’Images (Format PPM P3) |
| **Cours** | INF231 — Techniques de Conception d’Algorithmes et Structures de Données |
| **Année académique** | 2025–2026 |
| **Date** | Octobre 2025 |

---

## 🧩 Description de ma Partie

Le **Bloc I** est le **fondement** du projet. Il assure la passerelle entre le système de fichiers et la structure de données interne (`Image*`).

Mon travail consiste à :

1.  **Lire** (charger) des images PPM (P3) de manière robuste.
2.  **Écrire** (sauvegarder) des images PPM (P3) depuis la mémoire.
3.  **Gérer la mémoire** associée à la structure d'image de manière sécurisée (allocation/libération).

Ces fonctions sont capitales, car **tous les autres blocs** (filtres, redimensionnement, etc.) dépendent du succès des fonctions de lecture et de la gestion de la mémoire.

---

## ⚙️ Fonctionnalités Implémentées & Robustesse

L'implémentation est concentrée sur la **fiabilité** du parsing et la **sécurité mémoire**.

### 🔹 1. Fonctionnalités de Base

| Fonction | Rôle & Entrée/Sortie | Contrat d'Erreur |
| :--- | :--- | :--- |
| **`load_ppm`** | Charge un fichier PPM P3 $\to$ retourne `Image*` alloué en mémoire. | Retourne `NULL` si échec (fichier introuvable, format invalide, etc.). |
| **`save_ppm`** | Sauvegarde `Image*` $\to$ crée/écrase le fichier PPM P3. | Retourne `0` (échec) ou `1` (succès). |
| **`create_image`** | Alloue la structure `Image` (métadonnées + tableau de `Pixel*`). | Retourne `NULL` si l'allocation dynamique échoue. |
| **`free_image`** | **Libère toute la mémoire** (`Pixel` et `Image` structure). | **Crucial** pour éviter les fuites mémoire. |

### 2. Gestion de la Robustesse

| Utilitaire/Technique | Objectif | Description |
| :--- | :--- | :--- |
| **`skip_comments_and_spaces`** | **Parsing Robuste** | Ignore les lignes de commentaires (`#`) et tous les espaces/sauts de ligne non essentiels lors de la lecture des en-têtes et des données. |
| **`clamp_pixel`** | **Validation des Données** | Assure que les valeurs RGB lues ou manipulées sont toujours restreintes (clampées) entre $0$ et la valeur maximale (`max\_value`) du fichier. |
| **Gestion d'Erreur Explicite** | **Debug Facile** | Messages d'erreur détaillés sur `stderr` en cas de format non-P3, de fichier corrompu, ou d'erreur d'allocation. |

---

## 🧠 Algorithme et Contrat (I/O)

### Approche Algorithmique de `load_ppm`

1.  Ouvrir le fichier et vérifier le **Magic Number** (`P3`).
2.  Utiliser `skip_comments_and_spaces` pour trouver la largeur, la hauteur et la valeur max.
3.  Appeler `create_image` pour allouer l'espace. Si échec, retourner `NULL`.
4.  Parcourir les pixels un par un, lire leurs composantes R, G, B et stocker dans la structure allouée.
5.  Fermer le fichier et retourner `Image*`.

### Contrat du Module (`ppm_io.h`)

| Entrées (Inputs) | Sorties (Outputs) |
| :--- | :--- |
| Chemin du fichier à lire/écrire (`const char* filename`). | Structure `Image*` allouée en mémoire **OU** fichier `.ppm` généré. |
| Paramètres de l'image (largeur, hauteur, max\_value) pour la création. | Codes de retour `NULL`/`0` en cas d'erreur bloquante. |

---

## 🧾 Tests Réalisés & Limitations

| Test | Description | Résultat Vérifié |
| :--- | :--- | :--- |
| **Lecture Standard** | Chargement de fichiers PPM P3 valides. | `Image*` correctement rempli et conforme. |
| **Cas des Commentaires** | Lecture de fichiers avec commentaires variés (en-tête, entre les pixels). | Les commentaires sont ignorés sans planter le parsing. |
| **Erreur de Format** | Tentative de charger un fichier non-PPM ou P6. | Message d'erreur et retour `NULL`. |
| **Erreur I/O** | Tentative de charger un fichier inexistant ou protégé en écriture. | Gestion de l'erreur `fopen` et retour `NULL`/`0`. |
| **Fuite Mémoire** | Vérification avec un outil (ex: Valgrind) après `load_ppm` puis `free_image`. | **Aucune fuite détectée.** |

### ⚠️ Limitation Actuelle

* **Format Supporté :** Seul le format **P3 (ASCII/texte)** est géré. Le support du format binaire **P6** n'est pas implémenté dans cette version.

---

