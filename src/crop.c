/*
 * ============================================================================
 * BLOC 5 : Implémentation du découpage d'images
 * ============================================================================
 * Fichier : crop.c
 * Auteur  : Kameni Franck Arthur
 * Date    : Octobre 2025
 * ============================================================================
 */

#include "crop.h"

/* ============================================================================
 * COMMANDE CUT
 * ============================================================================ */

/**
 * Découpe une région rectangulaire d'une image
 */
void command_cut(const char* filename, int l1, int l2, int c1, int c2, const char* output) {
    // Charger l'image source
    Image* img = load_ppm(filename);
    
    // Vérifier si le chargement a réussi
    if (!img) {
        printf("fichier non trouvé\n");
        return;
    }
    
    /* ========================================================================
     * VALIDATION DES PARAMÈTRES
     * ======================================================================== */
    
    // Vérifier les contraintes sur les lignes
    if (l1 < 1 || l2 > img->height || l1 >= l2) {
        printf("Erreur : paramètres de lignes invalides (l1=%d, l2=%d, hauteur=%d)\n", 
               l1, l2, img->height);
        printf("Contrainte requise : 1 <= l1 < l2 <= %d\n", img->height);
        free_image(img);
        return;
    }
    
    // Vérifier les contraintes sur les colonnes
    if (c1 < 1 || c2 > img->width || c1 >= c2) {
        printf("Erreur : paramètres de colonnes invalides (c1=%d, c2=%d, largeur=%d)\n", 
               c1, c2, img->width);
        printf("Contrainte requise : 1 <= c1 < c2 <= %d\n", img->width);
        free_image(img);
        return;
    }
    
    /* ========================================================================
     * CALCUL DES DIMENSIONS DE LA NOUVELLE IMAGE
     * ======================================================================== */
    
    // Les indices sont inclusifs, donc on ajoute 1
    int new_height = l2 - l1 + 1;
    int new_width = c2 - c1 + 1;
    
    /* ========================================================================
     * CRÉATION DE LA NOUVELLE IMAGE
     * ======================================================================== */
    
    // Créer l'image découpée
    Image* cropped = create_image(new_width, new_height, img->max_value);
    
    if (!cropped) {
        printf("Erreur : impossible de créer l'image découpée\n");
        free_image(img);
        return;
    }
    
    /* ========================================================================
     * COPIE DE LA RÉGION SPÉCIFIÉE
     * ======================================================================== */
    
    // Copier les pixels de la région spécifiée
    // Conversion des indices de base-1 vers base-0
    for (int i = 0; i < new_height; i++) {
        for (int j = 0; j < new_width; j++) {
            // Position dans l'image source (conversion base-1 -> base-0)
            int src_row = (l1 - 1) + i;
            int src_col = (c1 - 1) + j;
            
            // Copier le pixel
            cropped->pixels[i][j] = img->pixels[src_row][src_col];
        }
    }
    
    /* ========================================================================
     * SAUVEGARDE
     * ======================================================================== */
    
    // Sauvegarder l'image découpée
    if (save_ppm(output, cropped)) {
        printf("opération effectuée\n");
    } else {
        printf("erreur lors de la sauvegarde\n");
    }
    
    // Libérer la mémoire
    free_image(img);
    free_image(cropped);
}
