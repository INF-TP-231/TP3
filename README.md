# 🖼️ PPM Viewer - Application de Traitement d'Images

> **Note :** Ce projet est une application en langage C pour manipuler des images au format PPM (Portable PixMap) version P3. Il offre une interface en ligne de commande interactive pour effectuer diverses opérations de traitement d'images.
---

## 📋 Informations du Projet

| **Champ** | **Détails** |
|-----------|-------------|
| **Projet** | PPM Viewer - Traitement d'images au format PPM P3 |
| **Cours** | INF231 - Technique de Conception d'Algorithmes et Structures de Données |
| **Niveau** | Licence 2 Informatique |
| **Institution** | Université de Yaoundé 1 |
| **Département** | Informatique |
| **Superviseur** | **Prof. MELATAGIA** |
| **Année Académique** | 2025-2026 |
| **Date de Soumission** | Vendredi 10 Octobre 2025, 20H00 |

---

## PPM Viewer — Traitement d'images PPM (P3)

Application en C pour manipuler des images au format PPM (P3). Interface en ligne de commande interactive.

### Objectif

Fournir des outils simples pour analyser et transformer des images PPM : taille, dominante, niveaux de gris, négatif, découpage et filtre médian.

### Équipe et répartition des tâches

| Bloc | Membre (matricule) | Fichiers | Responsabilité |
|------|--------------------|----------|----------------|
| Bloc 1 | ASSOGO MANGA GEORGES MATHURIN (24G2280) | `ppm_io.c`, `ppm_io.h` | Lecture/Écriture fichiers PPM, gestion mémoire |
| Bloc 2 | Nsangou Nkanjone Manuel Decency (24H2072) | `command_parser.c`, `command_parser.h`, `main.c` | Parsing de commandes, boucle principale |
| Bloc 3 | YVANA EMILIA LALANE LARCIER (24G2439) | `operations.c`, `operations.h` | Commandes `size` et `dom` (dominante) |
| Bloc 4 | AKANA SIGNING JOSIAS AARON (24H2358) | `filters.c`, `filters.h` | Commandes `gris` (niveaux de gris) et `neg` (négatif) |
| Bloc 5 | KAMENI FRANCK ARTHUR (24G2149) | `crop.c`, `crop.h` | Commande `cut` (découpage d'images) |
| Bloc 6 | NGNINTEDEM NGUIMTSOP Roèl Parfait (24H2418) | `median.c`, `median.h` | Commande `fil` (filtre médian) |

### Prérequis

- gcc (C99)
- make
- Système : Linux / macOS (ou Windows avec MinGW)

### Compiler

À la racine du dépôt :

```bash
make
```

Cibles utiles :

- `make run` — compile et lance l'exécutable
- `make clean` — supprime objets et exécutable
- `make test` — lance une suite de tests simples (besoin de `tests/test.ppm`)

### Utilisation (interface interactive)

Lancer :

```bash
./ppmviewer
```

Commandes (dans l'invite `ppmviewer >`) :

- `size <fichier.ppm>` — affiche largeur × hauteur
- `dom <R|G|B> <valeur> <fichier.ppm>` — ajuste la dominante (positif pour foncer, négatif pour éclaircir), génère `<nom>_dom.ppm`
- `gris <fichier.ppm>` — convertit en niveaux de gris, génère `<nom>_gris.ppm`
- `neg <fichier.ppm> <fichier_sortie.ppm>` — génère le négatif
- `cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>` — découpe la région (indices 1-based)
- `fil <fichier.ppm> <fichier_sortie.ppm>` — applique un filtre médian 3×3
- `help` — affiche l'aide
- `quit` — quitte l'application

### Tests

Placez un fichier PPM P3 de test dans `tests/test.ppm` puis :

```bash
make test
```

Les images générées par les commandes de test sont déposées dans `tests/` avec suffixes `_gris.ppm`, `_dom.ppm`, etc.

### Structure du dépôt

- `src/` : code source
- `tests/` : images de test
- `Makefile` : règles de compilation et tests
- `doc/` : documentation (actuellement `.gitkeep`)

### Notes

- Le projet supporte uniquement le format PPM P3 (texte).
- Indices pour `cut` commencent à 1.
- Pour conserver le dossier `doc/` dans Git, un fichier `.gitkeep` a été ajouté.

### Licence

Projet académique — usage et modifications autorisés pour les besoins du cours INF231.

---

Date de préparation : Octobre 2025

>>>>>>> 5456253 (Commit demandé : mise à jour README, ajout docs et fichiers personnels)
### Prérequis

- gcc (C99)
- make
- Système : Linux / macOS (ou Windows avec MinGW)

### Compiler

À la racine du dépôt :

```bash
make
```

Cibles utiles :

- `make run` — compile et lance l'exécutable
- `make clean` — supprime objets et exécutable
- `make test` — lance une suite de tests simples (besoin de `tests/test.ppm`)

### Utilisation (interface interactive)

Lancer :

```bash
./ppmviewer
```

Commandes (dans l'invite `ppmviewer >`) :

- `size <fichier.ppm>` — affiche largeur × hauteur
- `dom <R|G|B> <valeur> <fichier.ppm>` — ajuste la dominante (positif pour foncer, négatif pour éclaircir), génère `<nom>_dom.ppm`
- `gris <fichier.ppm>` — convertit en niveaux de gris, génère `<nom>_gris.ppm`
- `neg <fichier.ppm> <fichier_sortie.ppm>` — génère le négatif
- `cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>` — découpe la région (indices 1-based)
- `fil <fichier.ppm> <fichier_sortie.ppm>` — applique un filtre médian 3×3
- `help` — affiche l'aide
- `quit` — quitte l'application

### Tests

Placez un fichier PPM P3 de test dans `tests/test.ppm` puis :

```bash
make test
```

Les images générées par les commandes de test sont déposées dans `tests/` avec suffixes `_gris.ppm`, `_dom.ppm`, etc.

### Structure du dépôt

- `src/` : code source
- `tests/` : images de test
- `Makefile` : règles de compilation et tests
- `doc/` : documentation (actuellement `.gitkeep`)

### Notes

- Le projet supporte uniquement le format PPM P3 (texte).
- Indices pour `cut` commencent à 1.
- Pour conserver le dossier `doc/` dans Git, un fichier `.gitkeep` a été ajouté.

### Licence

Projet académique — usage et modifications autorisés pour les besoins du cours INF231.

---

Date de préparation : Octobre 2025
