/*
 * ============================================================================
 * BLOC 5 : Découpage d'images
 * ============================================================================
 * Fichier : crop.h
 * Auteur  : [Nom Personne 5]
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier définit la fonction pour découper une région rectangulaire
 *   d'une image PPM et la sauvegarder dans un nouveau fichier.
 * ============================================================================
 */

#ifndef CROP_H
#define CROP_H

#include "ppm_io.h"

/* ============================================================================
 * PROTOTYPES DES COMMANDES
 * ============================================================================ */

/**
 * Commande cut : découpe une région rectangulaire d'une image
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM source
 *   - l1       : ligne de début (incluse, indexation commence à 1)
 *   - l2       : ligne de fin (incluse)
 *   - c1       : colonne de début (incluse, indexation commence à 1)
 *   - c2       : colonne de fin (incluse)
 *   - output   : chemin du fichier PPM de sortie
 * 
 * Contraintes :
 *   - l1 < l2 <= hauteur de l'image
 *   - c1 < c2 <= largeur de l'image
 *   - Les indices commencent à 1 (pas 0)
 * 
 * Sortie :
 *   - Crée une nouvelle image contenant uniquement la région spécifiée
 *   - Dimensions de l'image résultante : (l2-l1+1) x (c2-c1+1)
 *   - Affiche "fichier non trouvé" si le fichier source n'existe pas
 *   - Affiche "Erreur : paramètres invalides" si les contraintes ne sont pas respectées
 *   - Affiche "opération effectuée" en cas de succès
 * 
 * Exemple :
 *   Image source : 100x100 pixels
 *   Commande : cut image.ppm 10 50 20 80 region.ppm
 *   Résultat : image de 41x61 pixels (lignes 10 à 50, colonnes 20 à 80)
 * 
 * Notes :
 *   - La région découpée inclut les lignes l1 et l2, ainsi que les colonnes c1 et c2
 *   - Les paramètres utilisent une indexation à base 1 (première ligne = 1)
 *   - Conversion en indexation à base 0 faite en interne
 */
void command_cut(const char* filename, int l1, int l2, int c1, int c2, const char* output);

#endif // CROP_H