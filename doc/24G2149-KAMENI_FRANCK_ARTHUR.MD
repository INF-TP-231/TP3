🧩 README – Bloc 5 : Implémentation du découpage d’images

Fichier : crop.c
Auteur : Kameni Franck Arthur
Date : Octobre 2025

🎯 Objectif du module

Le fichier crop.c implémente la commande CUT, dont le rôle est de découper une sous-région rectangulaire d’une image PPM existante pour créer une nouvelle image contenant uniquement cette zone.

Cette fonctionnalité est essentielle dans un projet de traitement d’images, car elle permet de :

isoler une partie d’intérêt (ex. un visage, un objet) ;

réduire la taille d’une image avant d’autres opérations ;

simplifier les traitements sur une zone spécifique.

🧠 Processus de raisonnement et étapes de conception
1. Chargement de l’image source

La première étape consiste à charger l’image depuis un fichier .ppm via la fonction :

Image* img = load_ppm(filename);


Cette fonction renvoie un pointeur vers une structure Image contenant :

la largeur (width)

la hauteur (height)

la valeur maximale (max_value)

le tableau de pixels (pixels)

Une vérification immédiate garantit que le chargement a réussi ; sinon, le programme signale une erreur.

2. Validation des paramètres d’entrée

Avant de manipuler les pixels, on vérifie la validité des indices fournis :

if (l1 < 1 || l2 > img->height || l1 >= l2)
if (c1 < 1 || c2 > img->width  || c1 >= c2)


Cette étape de sécurisation des bornes évite :

des accès mémoire invalides ;

des erreurs d’indexation ;

la création d’images de taille nulle ou négative.

En cas d’erreur, un message explicite précise la contrainte correcte :

Contrainte requise : 1 <= l1 < l2 <= hauteur
Contrainte requise : 1 <= c1 < c2 <= largeur

3. Calcul des dimensions de la nouvelle image

L’image découpée doit contenir tous les pixels compris entre les coordonnées données (inclusives).
La hauteur et la largeur sont donc calculées ainsi :

new_height = l2 - l1 + 1;
new_width  = c2 - c1 + 1;


Le +1 est crucial car les bornes sont inclusives (par exemple, découper de 1 à 3 donne bien 3 lignes).

4. Création de l’image résultat

Une nouvelle image vide est allouée :

Image* cropped = create_image(new_width, new_height, img->max_value);


Cette fonction prépare la structure mémoire et initialise le tableau de pixels à la taille exacte du découpage.

Si cette allocation échoue, le programme libère l’image d’origine et quitte proprement.

5. Copie des pixels de la région spécifiée

Cette partie représente le cœur du traitement :

for (int i = 0; i < new_height; i++) {
    for (int j = 0; j < new_width; j++) {
        int src_row = (l1 - 1) + i;
        int src_col = (c1 - 1) + j;
        cropped->pixels[i][j] = img->pixels[src_row][src_col];
    }
}


Le décalage (l1 - 1) et (c1 - 1) provient du passage d’une base 1 (utilisateur) à une base 0 (index mémoire C).
Chaque pixel de la région choisie est copié dans la nouvelle image, ligne par ligne, colonne par colonne.

6. Sauvegarde et libération mémoire

L’image découpée est enregistrée sur disque via :

save_ppm(output, cropped);


Une fois la sauvegarde terminée, les deux structures (img et cropped) sont libérées pour éviter toute fuite mémoire :

free_image(img);
free_image(cropped);


Le programme confirme le succès de l’opération par :

opération effectuée

🧩 Schéma logique simplifié
          ┌───────────────┐
          │ Image source  │
          └───────┬───────┘
                  │
          Charger le fichier
                  │
        Valider l1, l2, c1, c2
                  │
          Calculer dimensions
                  │
          Créer nouvelle image
                  │
         Copier pixels sélectionnés
                  │
         Sauvegarder et libérer
                  ▼
          ┌──────────────────┐
          │ Image découpée   │
          └──────────────────┘

🧾 Exemple d’utilisation
cut input.ppm 50 150 30 120 output.ppm


→ Découpe les lignes 50 à 150 et les colonnes 30 à 120 de input.ppm
→ Crée une nouvelle image output.ppm