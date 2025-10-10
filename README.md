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

## 👥 Équipe de Développement (Groupe TPE3)

### Répartition des Tâches

| **Bloc** | **Membre** | **Fichiers** | **Responsabilité** |
|----------|------------|--------------|-------------------|
| **Bloc 1** | [] | `ppm_io.c`, `ppm_io.h` | Lecture/Écriture fichiers PPM, gestion mémoire |
| **Bloc 2** | [Nom Personne 2] | `command_parser.c`, `command_parser.h`, `main.c` | Parsing de commandes, boucle principale |
| **Bloc 3** | [Nom Personne 3] | `operations.c`, `operations.h` | Commandes `size` et `dom` (dominante) |
| **Bloc 4** | [Nom Personne 4] | `filters.c`, `filters.h` | Commandes `gris` (niveaux de gris) et `neg` (négatif) |
| **Bloc 5** | [Nom Personne 5] | `crop.c`, `crop.h` | Commande `cut` (découpage d'images) |
| **Bloc 6** | [Nom Personne 6] | `median.c`, `median.h` | Commande `fil` (filtre médian) |

> **Note :** Remplacez `[Nom Personne X]` par les vrais noms des membres de votre équipe.

---

## 📖 Description du Projet

Application en langage C permettant de manipuler des images au format **PPM (Portable PixMap) version P3**. Le programme offre une interface en ligne de commande interactive pour effectuer diverses opérations de traitement d'images.

### Format PPM P3

Le format PPM P3 stocke des images non compressées avec :
- **En-tête** : Version (P3), largeur, hauteur, valeur maximale des couleurs
- **Pixels** : Valeurs RGB (Red, Green, Blue) en texte brut
- **Commentaires** : Lignes commençant par `#` (ignorées lors de la lecture)

**Exemple de fichier PPM :**
```
P3
# Commentaire - Image de test
4 4
255
255 0 0   0 255 0   0 0 255   255 255 0
255 0 255 0 255 255 128 128 128 255 255 255
0 0 0     64 64 64  192 192 192 32 32 32
200 50 50 50 200 50 50 50 200  100 100 100
```

---

## 🏗️ Architecture du Projet

```
ppmviewer/
│
├── src/                        # Code source
│   ├── main.c                  # Point d'entrée et boucle principale
│   ├── ppm_io.c/.h            # Lecture/écriture fichiers PPM
│   ├── command_parser.c/.h    # Parsing des commandes
│   ├── operations.c/.h        # Opérations dominante et size
│   ├── filters.c/.h           # Filtres noir&blanc et négatif
│   ├── crop.c/.h              # Découpage d'images
│   └── median.c/.h            # Filtre médian
│
├── tests/                      # Fichiers de test
│   └── test.ppm               # Image de test 4x4
│
├── obj/                        # Fichiers objets compilés (généré)
│
├── Makefile                    # Fichier de compilation
├── README.md                   # Cette documentation
└── doc                         # Dossier contenant les README personnalisés 
```

---

## ⚙️ Prérequis et Installation

### Prérequis

- **Compilateur GCC** (compatible C99)
- **Make** (pour la compilation)
- **Système d'exploitation** : Linux, macOS, ou Windows (avec MinGW/Cygwin)

### Installation

```bash
# 1. Cloner le dépôt GitHub
git clone <votre-lien-github>
cd ppmviewer

# 2. Compiler le projet
make

# 3. Vérifier la compilation
./ppmviewer
```

---

## 🚀 Utilisation

### Lancement du Programme

```bash
./ppmviewer
```

**Sortie :**
```
╔═══════════════════════════════════════════════════════════════════╗
║                                                                   ║
║              APPLICATION DE TRAITEMENT D'IMAGES PPM               ║
## PPM Viewer — Traitement d'images PPM (P3)

Application en C pour manipuler des images au format PPM (P3). Interface en ligne de commande interactive.

### Objectif

Fournir des outils simples pour analyser et transformer des images PPM : taille, dominante, niveaux de gris, négatif, découpage et filtre médian.

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
