# 24H2072 - NSANGOU NKANJONE MANUEL DECENCY

Résumé
------
Ce document décrit le travail réalisé par Nsangou N. M. Decency (matricule 24H2072) sur le projet PPM Viewer. Il est responsable du Bloc 2 : parsing des commandes et boucle principale (`command_parser.c` et `main.c`).

Travail réalisé
---------------
- Implémentation du parseur de commandes interactif : lecture de la ligne d'entrée, découpage en tokens, validation des arguments et gestion des erreurs.
- Conception de la boucle principale (interface REPL) dans `main.c` : affichage de l'invite `ppmviewer >`, dispatch des commandes vers les modules appropriés, et gestion des commandes `help` et `quit`.
- Gestion des chemins relatifs et absolus pour les fichiers PPM fournis en argument.
- Normalisation minimale des entrées (trim, gestion des espaces multiples, insensibilité à la casse pour les commandes clés).
- Mise en place de messages d'erreur clairs pour : fichier introuvable, format PPM invalide, paramètres invalides pour `cut`, et commande inconnue.
- Tests manuels et cas de bord : entrées vides, arguments manquants, valeurs numériques hors bornes, et noms de fichiers avec espaces.

Fichiers modifiés / ajoutés
--------------------------
- `src/command_parser.c`  — fonctions de parsing, validation et help
- `src/command_parser.h`  — prototypes et structures publiques
- `src/main.c`            — boucle principale et initialisation

Fonctions et responsabilités clés
---------------------------------
- `read_line()` — lit une ligne depuis stdin en gérant la taille dynamique.
- `tokenize_line(char *line, char ***tokens, int *count)` — sépare la ligne en tokens.
- `dispatch_command(int argc, char **argv)` — valide la commande et appelle la fonction correspondante (size, dom, gris, neg, cut, fil, help, quit).
- `parse_int(const char *s, int *out)` — conversion sûre d'entier avec détection d'erreur.
- `print_help()` — affiche la liste des commandes et leur syntaxe.

Contrat (inputs / outputs)
--------------------------
- Inputs : ligne de commande tapée par l'utilisateur ; fichiers PPM P3 en entrée.
- Outputs : messages à l'écran (succès / erreurs) et fichiers PPM générés (`*_gris.ppm`, `*_dom.ppm`, etc.).
- Modes d'erreur : mauvaise syntaxe → message et retour à l'invite ; fichier manquant → message d'erreur ; paramètres invalides → message spécifique.

Tests effectués
---------------
- Cas happy-path pour chaque commande (`size`, `dom`, `gris`, `neg`, `cut`, `fil`).
- Tests d'erreur : commande inconnue, arguments manquants, `cut` avec indices hors bornes, valeur non numérique pour `dom`.
- Test de robustesse : lignes contenant plusieurs espaces, tabulations, et commentaires précédant l'entrée.

Notes & limitations
-------------------
- Le parseur ne gère pas encore les guillemets pour les chemins contenant des espaces de façon complète (workaround : utiliser des noms sans espaces ou échappement).
- Certaines validations plus poussées (par ex. vérification avancée du format PPM au parsing) sont déléguées à `ppm_io.c`.

Comment tester localement
-------------------------
1. Compiler :

```bash
make
```

2. Lancer l'application :

```bash
./ppmviewer
```

3. Exemples de commandes à tester :

```
size tests/test.ppm
gris tests/test.ppm
dom R 20 tests/test.ppm
neg tests/test.ppm tests/test_neg.ppm
cut tests/test.ppm 1 2 1 2 tests/region.ppm
fil tests/test.ppm tests/test_fil.ppm
help
quit
```

---

Fichier généré automatiquement par l'équipe — Octobre 2025
