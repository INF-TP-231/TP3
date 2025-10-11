/*
 * ============================================================================
 * BLOC 6 : Filtre médian pour réduction de bruit
 * ============================================================================
 * Fichier : median.h
 * Auteur  : Ngnintedem Nguimtsop Roèl Parfait
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier définit les fonctions pour appliquer un filtre médian 3x3
 *   sur une image PPM. Le filtre médian est efficace pour réduire le bruit
 *   tout en préservant les contours de l'image.
 * ============================================================================
 */

#ifndef MEDIAN_H
#define MEDIAN_H

#include "ppm_io.h"

/* ============================================================================
 * PROTOTYPES DES COMMANDES
 * ============================================================================ */

/**
 * Commande fil : applique un filtre médian 3x3 à une image
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM source
 *   - output   : chemin du fichier PPM de sortie
 * 
 * Algorithme :
 *   Pour chaque pixel de l'image :
 *   1. Collecter les valeurs R, G, B des 8 voisins + pixel central (fenêtre 3x3)
 *   2. Calculer la médiane de chaque composante séparément
 *   3. Remplacer le pixel par (médiane_R, médiane_G, médiane_B)
 * 
 * Gestion des bords :
 *   - Les pixels aux bords n'ont pas 8 voisins complets
 *   - La médiane est calculée avec les voisins disponibles uniquement
 * 
 * Sortie :
 *   - Crée le fichier spécifié avec l'image filtrée
 *   - Affiche "fichier non trouvé" si le fichier source n'existe pas
 *   - Affiche "opération effectuée" en cas de succès
 * 
 * Exemple :
 *   ppmviewer > fil image_bruitee.ppm image_propre.ppm
 *   opération effectuée
 * 
 * Notes :
 *   - Le filtre médian préserve mieux les contours que la moyenne
 *   - Efficace contre le bruit "sel et poivre"
 */
void command_fil(const char* filename, const char* output);

/* ============================================================================
 * FONCTIONS UTILITAIRES
 * ============================================================================ */

/**
 * Calcule la médiane d'un tableau de valeurs
 * 
 * Paramètres :
 *   - values : tableau de valeurs (unsigned char)
 *   - count  : nombre de valeurs dans le tableau
 * 
 * Retour :
 *   - Valeur médiane
 * 
 * Algorithme :
 *   1. Trier le tableau
 *   2. Retourner l'élément central
 * 
 * Notes :
 *   - Pour un nombre pair d'éléments, retourne values[count/2]
 *   - Le tableau est modifié (trié) par cette fonction
 */
unsigned char get_median(unsigned char* values, int count);

/**
 * Applique le filtre médian à un pixel donné
 * 
 * Paramètres :
 *   - img : pointeur vers l'image
 *   - row : ligne du pixel (0-based)
 *   - col : colonne du pixel (0-based)
 * 
 * Retour :
 *   - Nouveau pixel avec valeurs médianes
 * 
 * Algorithme :
 *   1. Collecter les valeurs RGB des voisins dans un rayon de 1
 *   2. Vérifier que chaque voisin est dans les limites de l'image
 *   3. Calculer la médiane pour R, G, B séparément
 *   4. Retourner le pixel filtré
 */
Pixel apply_median_filter(Image* img, int row, int col);

/**
 * Fonction de comparaison pour qsort (tri de unsigned char)
 * 
 * Paramètres :
 *   - a : pointeur vers premier élément
 *   - b : pointeur vers second élément
 * 
 * Retour :
 *   - Négatif si a < b
 *   - Zéro si a == b
 *   - Positif si a > b
 */
int compare_uchar(const void* a, const void* b);

#endif // MEDIAN_H
