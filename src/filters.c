/*
 * ============================================================================
 * BLOC 4 : Implémentation des filtres de transformation
 * ============================================================================
 * Fichier : filters.c
 * Auteur  : Akana Signing Josias Aaron
 * Date    : Octobre 2025
 * ============================================================================
 */

#include "filters.h"
#include <string.h>

/* ============================================================================
 * FONCTIONS DE TRANSFORMATION DE PIXELS
 * ============================================================================ */

/**
 * Convertit un pixel en niveau de gris
 * Utilise la méthode de la moyenne arithmétique
 */
Pixel to_grayscale(Pixel p) {
    // Calculer la moyenne des trois composantes
    // Note : on additionne d'abord en entier pour éviter l'overflow
    unsigned char avg = ((int)p.r + (int)p.g + (int)p.b) / 3;
    
    // Créer le pixel en niveau de gris
    Pixel result;
    result.r = avg;
    result.g = avg;
    result.b = avg;
    
    return result;
}

/**
 * Crée le négatif d'un pixel (inversion des couleurs)
 */
Pixel to_negative(Pixel p, int max_value) {
    // Inverser chaque composante
    Pixel result;
    result.r = (unsigned char)(max_value - p.r);
    result.g = (unsigned char)(max_value - p.g);
    result.b = (unsigned char)(max_value - p.b);
    
    return result;
}

/* ============================================================================
 * COMMANDE GRIS
 * ============================================================================ */

/**
 * Convertit une image en niveaux de gris
 */
void command_gris(const char* filename) {
    // Charger l'image source
    Image* img = load_ppm(filename);
    
    // Vérifier si le chargement a réussi
    if (!img) {
        printf("fichier non trouvé\n");
        return;
    }
    
    // Appliquer la conversion en niveaux de gris sur tous les pixels
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->pixels[i][j] = to_grayscale(img->pixels[i][j]);
        }
    }
    
    // Créer le nom du fichier de sortie
    char output[512];
    strcpy(output, filename);
    
    // Trouver l'extension .ppm et la remplacer par _gris.ppm
    char* ext = strstr(output, ".ppm");
    if (ext != NULL) {
        strcpy(ext, "_gris.ppm");
    } else {
        // Si pas d'extension .ppm, ajouter _gris.ppm à la fin
        strcat(output, "_gris.ppm");
    }
    
    // Sauvegarder l'image modifiée
    if (save_ppm(output, img)) {
        printf("opération effectuée ; %s créé\n", output);
    } else {
        printf("erreur lors de la sauvegarde\n");
    }
    
    // Libérer la mémoire
    free_image(img);
}

/* ============================================================================
 * COMMANDE NEG
 * ============================================================================ */

/**
 * Crée le négatif d'une image
 */
void command_neg(const char* filename, const char* output) {
    // Charger l'image source
    Image* img = load_ppm(filename);
    
    // Vérifier si le chargement a réussi
    if (!img) {
        printf("fichier non trouvé\n");
        return;
    }
    
    // Appliquer le négatif sur tous les pixels
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->pixels[i][j] = to_negative(img->pixels[i][j], img->max_value);
        }
    }
    
    // Sauvegarder l'image modifiée
    if (save_ppm(output, img)) {
        printf("opération effectuée\n");
    } else {
        printf("erreur lors de la sauvegarde\n");
    }
    
    // Libérer la mémoire
    free_image(img);
}
