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
| **Bloc 1** | [Nom Personne 1] | `ppm_io.c`, `ppm_io.h` | Lecture/Écriture fichiers PPM, gestion mémoire |
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
║                                                                   ║
║                  Université de Yaoundé 1 - INF231                 ║
║                   Année académique 2025-2026                      ║
║                                                                   ║
╚═══════════════════════════════════════════════════════════════════╝

Tapez 'help' pour voir les commandes disponibles.

ppmviewer > 
```

---

## 📖 Commandes Disponibles

### 1. **`size` - Afficher la taille d'une image**

**Syntaxe :**
```
size <fichier.ppm>
```

**Exemple :**
```
ppmviewer > size tests/test.ppm
4 x 4
```

**Description :** Affiche les dimensions de l'image au format `largeur x hauteur`.

---

### 2. **`dom` - Foncer/Éclaircir les pixels à dominante**

**Syntaxe :**
```
dom <couleur> <valeur> <fichier.ppm>
```

**Paramètres :**
- `<couleur>` : `R` (rouge), `G` (vert), ou `B` (bleu)
- `<valeur>` : 
  - Positive → foncer l'image (ajouter)
  - Négative → éclaircir l'image (soustraire)

**Exemple :**
```
ppmviewer > dom R 20 tests/test.ppm
opération effectuée ; tests/test_dom.ppm créé
```

**Description :** Modifie uniquement les pixels dont la dominante correspond à la couleur spécifiée. La dominante est la composante RGB ayant la valeur la plus élevée.

**Fichier de sortie :** `<nom_original>_dom.ppm`

---

### 3. **`gris` - Convertir en niveaux de gris**

**Syntaxe :**
```
gris <fichier.ppm>
```

**Exemple :**
```
ppmviewer > gris tests/test.ppm
opération effectuée ; tests/test_gris.ppm créé
```

**Description :** Convertit l'image en noir et blanc en calculant la moyenne des composantes RGB de chaque pixel :
```
nouvelle_valeur = (R + G + B) / 3
```

**Fichier de sortie :** `<nom_original>_gris.ppm`

---

### 4. **`neg` - Créer le négatif**

**Syntaxe :**
```
neg <fichier.ppm> <fichier_sortie.ppm>
```

**Exemple :**
```
ppmviewer > neg tests/test.ppm tests/test_neg.ppm
opération effectuée
```

**Description :** Crée le négatif de l'image en inversant chaque couleur :
```
nouvelle_valeur = 255 - ancienne_valeur
```

---

### 5. **`cut` - Découper une région**

**Syntaxe :**
```
cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>
```

**Paramètres :**
- `<l1>`, `<l2>` : Lignes de début et fin (indices commencent à 1)
- `<c1>`, `<c2>` : Colonnes de début et fin (indices commencent à 1)

**Contraintes :**
- `l1 < l2 ≤ hauteur`
- `c1 < c2 ≤ largeur`

**Exemple :**
```
ppmviewer > cut tests/test.ppm 1 2 1 2 tests/region.ppm
opération effectuée
```

**Description :** Extrait une région rectangulaire de l'image et la sauvegarde dans un nouveau fichier.

---

### 6. **`fil` - Appliquer le filtre médian**

**Syntaxe :**
```
fil <fichier.ppm> <fichier_sortie.ppm>
```

**Exemple :**
```
ppmviewer > fil tests/test.ppm tests/test_filtré.ppm
opération effectuée
```

**Description :** Applique un filtre médian 3×3 pour réduire le bruit. Pour chaque pixel, remplace ses valeurs RGB par la médiane des valeurs correspondantes de ses 8 voisins + lui-même.

**Utilité :** Efficace contre le bruit "sel et poivre" tout en préservant les contours.

---

### 7. **`help` - Afficher l'aide**

**Syntaxe :**
```
help
```

**Description :** Affiche la liste complète des commandes disponibles avec leur syntaxe.

---

### 8. **`quit` - Quitter l'application**

**Syntaxe :**
```
quit
```

**Description :** Ferme l'application proprement.

---

## 💻 Commandes Make

### Compilation

```bash
# Compiler le projet
make

# Recompiler complètement (après modifications)
make rebuild

# Nettoyer les fichiers compilés
make clean
```

### Exécution et Tests

```bash
# Lancer le programme
make run

# Lancer les tests automatiques
make test

# Vérifier que le projet est prêt pour soumission
make check-submission
```

### Documentation

```bash
# Afficher l'aide du Makefile
make help

# Afficher les informations du projet
make info
```

### Soumission

```bash
# Créer une archive pour soumission
make archive
```

---

## 📝 Exemple de Session Complète

```
$ ./ppmviewer

Application de traitement d'images PPM réalisée par Equipe INF231.
Tapez 'help' pour voir les commandes disponibles.

ppmviewer > size tests/test.ppm
4 x 4

ppmviewer > cut tests/test.ppm 1 2 1 2 tests/region.ppm
opération effectuée

ppmviewer > dom R 10 tests/region.ppm
opération effectuée ; tests/region_dom.ppm créé

ppmviewer > gris tests/test.ppm
opération effectuée ; tests/test_gris.ppm créé

ppmviewer > neg tests/test.ppm tests/test_neg.ppm
opération effectuée

ppmviewer > fil tests/test_gris.ppm tests/test_filtré.ppm
opération effectuée

ppmviewer > quit

═══════════════════════════════════════════════════════════════════
           Merci d'avoir utilisé PPM Viewer. Au revoir!            
═══════════════════════════════════════════════════════════════════
```

---

## 🧪 Tests

### Tests Automatiques

```bash
make test
```

**Sortie attendue :**
```
╔════════════════════════════════════════════════════════════════╗
║              TESTS AUTOMATIQUES - INF231 TP1                   ║
║              Superviseur: Prof. MELATAGIA Yves                 ║
╚════════════════════════════════════════════════════════════════╝

📝 Test 1 : Affichage de la taille d'une image
✓ Réussi

📝 Test 2 : Conversion en niveaux de gris
✓ Réussi

📝 Test 3 : Foncer pixels à dominante rouge (+20)
✓ Réussi

📝 Test 4 : Éclaircir pixels à dominante verte (-15)
✓ Réussi

📝 Test 5 : Création du négatif
✓ Réussi

📝 Test 6 : Découpage d'une région
✓ Réussi

📝 Test 7 : Application du filtre médian
✓ Réussi

✓ Tous les tests ont été exécutés
```

### Créer vos propres tests

Pour tester avec vos propres images PPM :

1. Créez un fichier `.ppm` au format P3
2. Placez-le dans le dossier `tests/`
3. Utilisez les commandes sur ce fichier

---

## 🔧 Détails d'Implémentation

### Structures de Données Principales

```c
// Structure pour un pixel RGB
typedef struct {
    unsigned char r;  // Rouge (0-255)
    unsigned char g;  // Vert (0-255)
    unsigned char b;  // Bleu (0-255)
} Pixel;

// Structure pour une image complète
typedef struct {
    int width;           // Largeur en pixels
    int height;          // Hauteur en pixels
    int max_value;       // Valeur max (généralement 255)
    Pixel** pixels;      // Tableau 2D de pixels
} Image;
```

### Gestion de la Mémoire

- **Allocation dynamique** pour les tableaux de pixels
- **Libération automatique** via `free_image()`
- **Clamping des valeurs** RGB entre 0 et max_value pour éviter les débordements

### Algorithmes Clés

#### Dominante d'un Pixel
```c
// Retourne 0 (Rouge), 1 (Vert), ou 2 (Bleu)
int get_dominant_color(Pixel p) {
    if (p.r >= p.g && p.r >= p.b) return 0;
    if (p.g >= p.b) return 1;
    return 2;
}
```

#### Filtre Médian
```c
// Pour chaque pixel :
// 1. Collecter valeurs RGB des 9 pixels (3×3)
// 2. Trier chaque composante séparément
// 3. Prendre la médiane (valeur centrale)
```

---

## 📅 Organisation du Travail

### Méthodologie

1. **Développement modulaire** : Chaque bloc est indépendant
2. **Tests unitaires** : Chaque personne teste son module
3. **Intégration progressive** : Fusion des modules au fur et à mesure
4. **Tests d'intégration** : Vérification globale avant soumission

---

## 🐛 Gestion des Erreurs

L'application gère plusieurs types d'erreurs :

| **Erreur** | **Message** | **Action** |
|------------|-------------|-----------|
| Fichier introuvable | `fichier non trouvé` | Vérifier le chemin |
| Format PPM invalide | Erreur lors du chargement | Vérifier le format P3 |
| Paramètres `cut` invalides | `Erreur : paramètres invalides` | Respecter les contraintes |
| Commande inconnue | `Commande inconnue` | Taper `help` |
| Échec allocation mémoire | Message d'erreur système | Vérifier la mémoire disponible |

---

## 📌 Notes Importantes

### Conventions

- **Indices de `cut`** : Commencent à 1 (pas 0)
- **Nommage automatique** : `dom` et `gris` créent automatiquement les noms de fichiers
- **Chemins relatifs** : Supportés (ex: `../images/photo.ppm`)
- **Commentaires PPM** : Les lignes commençant par `#` sont ignorées

### Limitations

- Supporte uniquement le format **P3** (pas P6)
- Images en texte brut uniquement (pas de compression)
- Valeur maximale RGB fixée à 255

### Optimisations Possibles

- Support du format P6 (binaire)
- Parallélisation du filtre médian
- Interface graphique (GUI)
- Support de formats additionnels (PNG, JPEG)

---

## 📚 Références

### Documentation Format PPM
- [Adobe - PPM File Format](https://www.adobe.com/ca_fr/creativecloud/file-types/image/raster/ppm-file.html)
- [Netpbm - PPM Specification](http://netpbm.sourceforge.net/doc/ppm.html)

### Cours et Ressources
- **INF231** : Technique de Conception d'Algorithmes et Structures de Données
- **Superviseur** : Prof. MELATAGIA 
- **Institution** : Université de Yaoundé 1

---

## 📞 Contact et Support

### En cas de problème

1. **Vérifier la documentation** : Relire ce README
2. **Tester avec `make test`** : Vérifier que tout fonctionne
3. **Consulter les logs** : Messages d'erreur détaillés


### Membres de l'Équipe

| **Nom** | **Rôle** | **Matricule** |
|---------|----------|-------------|
| [Kameni Franck Arthur] | Bloc 1 - IO | [24G2149] |
| [Nom 2] | Bloc 2 - Parser | [] |
| [Nom 3] | Bloc 3 - Operations | [] |
| [Nom 4] | Bloc 4 - Filters | [] |
| [Nom 5] | Bloc 5 - Crop | [] |
| [Nom 6] | Bloc 6 - Median | [] |

> **Note :** Remplacez par les vrais noms et contacts de votre équipe.

---

## 📄 Licence

Projet académique réalisé dans le cadre du cours **INF231** à l'**Université de Yaoundé 1**, sous la supervision du **Prof. MELATAGIA**.

**Année académique** : 2025-2026

© 2025 - Tous droits réservés aux étudiants du groupe TPE3.

---
---

<div align="center">

**Projet réalisé avec 💻 et ☕**

**Université de Yaoundé 1 - Département d'Informatique**

</div>