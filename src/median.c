/*
 * ============================================================================
 * BLOC 6 : Implémentation du filtre médian
 * ============================================================================
 * Fichier : median.c
 * Auteur  : [Nom Personne 6]
 * Date    : Octobre 2025
 * ============================================================================
 */

#include "median.h"
#include <stdlib.h>

/* ============================================================================
 * FONCTION DE COMPARAISON POUR TRI
 * ============================================================================ */

/**
 * Compare deux unsigned char pour qsort
 */
int compare_uchar(const void* a, const void* b) {
    unsigned char val_a = *(unsigned char*)a;
    unsigned char val_b = *(unsigned char*)b;
    
    return (int)val_a - (int)val_b;
}

/* ============================================================================
 * CALCUL DE LA MÉDIANE
 * ============================================================================ */

/**
 * Calcule la médiane d'un tableau de valeurs
 */
unsigned char get_median(unsigned char* values, int count) {
    // Cas particulier : tableau vide
    if (count == 0) {
        return 0;
    }
    
    // Cas particulier : un seul élément
    if (count == 1) {
        return values[0];
    }
    
    // Trier le tableau en ordre croissant
    qsort(values, count, sizeof(unsigned char), compare_uchar);
    
    // Retourner l'élément médian
    // Pour un nombre pair d'éléments, on prend celui juste après le milieu
    return values[count / 2];
}

/* ============================================================================
 * APPLICATION DU FILTRE MÉDIAN À UN PIXEL
 * ============================================================================ */

/**
 * Applique le filtre médian 3x3 à un pixel donné
 */
Pixel apply_median_filter(Image* img, int row, int col) {
    // Tableaux pour stocker les valeurs RGB des voisins
    // Maximum 9 valeurs (pixel central + 8 voisins)
    unsigned char r_values[9];
    unsigned char g_values[9];
    unsigned char b_values[9];
    int count = 0;
    
    /* ========================================================================
     * COLLECTE DES VALEURS DES VOISINS
     * ======================================================================== */
    
    // Parcourir une fenêtre 3x3 centrée sur le pixel
    // dr et dc varient de -1 à +1
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            // Calculer les coordonnées du voisin
            int neighbor_row = row + dr;
            int neighbor_col = col + dc;
            
            // Vérifier que le voisin est dans les limites de l'image
            if (neighbor_row >= 0 && neighbor_row < img->height &&
                neighbor_col >= 0 && neighbor_col < img->width) {
                
                // Ajouter les valeurs RGB du voisin
                r_values[count] = img->pixels[neighbor_row][neighbor_col].r;
                g_values[count] = img->pixels[neighbor_row][neighbor_col].g;
                b_values[count] = img->pixels[neighbor_row][neighbor_col].b;
                count++;
            }
        }
    }
    
    /* ========================================================================
     * CALCUL DES MÉDIANES
     * ======================================================================== */
    
    // Créer le pixel résultant avec les valeurs médianes
    Pixel result;
    result.r = get_median(r_values, count);
    result.g = get_median(g_values, count);
    result.b = get_median(b_values, count);
    
    return result;
}

/* ============================================================================
 * COMMANDE FIL
 * ============================================================================ */

/**
 * Applique un filtre médian 3x3 à toute l'image
 */
void command_fil(const char* filename, const char* output) {
    // Charger l'image source
    Image* img = load_ppm(filename);
    
    // Vérifier si le chargement a réussi
    if (!img) {
        printf("fichier non trouvé\n");
        return;
    }
    
    /* ========================================================================
     * CRÉATION DE L'IMAGE FILTRÉE
     * ======================================================================== */
    
    // Créer une nouvelle image pour le résultat
    // (on ne modifie pas l'image source en place)
    Image* filtered = create_image(img->width, img->height, img->max_value);
    
    if (!filtered) {
        printf("Erreur : impossible de créer l'image filtrée\n");
        free_image(img);
        return;
    }
    
    /* ========================================================================
     * APPLICATION DU FILTRE À TOUS LES PIXELS
     * ======================================================================== */
    
    // Parcourir tous les pixels de l'image
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            // Appliquer le filtre médian au pixel (i, j)
            filtered->pixels[i][j] = apply_median_filter(img, i, j);
        }
    }
    
    /* ========================================================================
     * SAUVEGARDE
     * ======================================================================== */
    
    // Sauvegarder l'image filtrée
    if (save_ppm(output, filtered)) {
        printf("opération effectuée\n");
    } else {
        printf("erreur lors de la sauvegarde\n");
    }
    
    // Libérer la mémoire
    free_image(img);
    free_image(filtered);
}