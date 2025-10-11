/*
 * ============================================================================
 * BLOC 3 : Implémentation des opérations dominante et size
 * ============================================================================
 * Fichier : operations.c
 * Auteur  : Yvana Emilia Lalane Larcier
 * Date    : Octobre 2025
 * ============================================================================
 */

#include "operations.h"
#include <string.h>

/* ============================================================================
 * FONCTIONS UTILITAIRES
 * ============================================================================ */

/**
 * Détermine la couleur dominante d'un pixel
 * Priorité en cas d'égalité : Rouge > Vert > Bleu
 */
int get_dominant_color(Pixel p) {
    // Vérifier si Rouge est dominant ou égal
    if (p.r >= p.g && p.r >= p.b) {
        return 0; // Rouge dominant
    }
    // Vérifier si Vert est dominant
    else if (p.g >= p.r && p.g >= p.b) {
        return 1; // Vert dominant
    }
    // Sinon, Bleu est dominant
    else {
        return 2; // Bleu dominant
    }
}

/**
 * Ajuste un pixel selon sa dominante
 */
Pixel adjust_pixel_by_dominant(Pixel p, char dominant, int value, int max_value) {
    // Déterminer la dominante actuelle du pixel
    int dom = get_dominant_color(p);
    
    // Vérifier si le pixel a la bonne dominante
    int has_dominant = 0;
    
    if (dominant == 'R' && dom == 0) {
        has_dominant = 1;
    }
    else if (dominant == 'G' && dom == 1) {
        has_dominant = 1;
    }
    else if (dominant == 'B' && dom == 2) {
        has_dominant = 1;
    }
    
    // Si le pixel n'a pas la bonne dominante, le retourner inchangé
    if (!has_dominant) {
        return p;
    }
    
    // Appliquer la modification à toutes les composantes
    int r = (int)p.r + value;
    int g = (int)p.g + value;
    int b = (int)p.b + value;
    
    // Clamper les valeurs entre 0 et max_value
    if (r < 0) r = 0;
    if (r > max_value) r = max_value;
    
    if (g < 0) g = 0;
    if (g > max_value) g = max_value;
    
    if (b < 0) b = 0;
    if (b > max_value) b = max_value;
    
    // Créer le pixel modifié
    Pixel result;
    result.r = (unsigned char)r;
    result.g = (unsigned char)g;
    result.b = (unsigned char)b;
    
    return result;
}

/* ============================================================================
 * COMMANDE SIZE
 * ============================================================================ */

/**
 * Affiche les dimensions d'une image
 */
void command_size(const char* filename) {
    // Charger l'image
    Image* img = load_ppm(filename);
    
    // Vérifier si le chargement a réussi
    if (!img) {
        printf("fichier non trouvé\n");
        return;
    }
    
    // Afficher la taille au format "largeur x hauteur"
    printf("%d x %d\n", img->width, img->height);
    
    // Libérer la mémoire
    free_image(img);
}

/* ============================================================================
 * COMMANDE DOM
 * ============================================================================ */

/**
 * Foncer/éclaircir les pixels avec une dominante donnée
 */
void command_dom(const char* filename, char color, int value) {
    // Charger l'image
    Image* img = load_ppm(filename);
    
    // Vérifier si le chargement a réussi
    if (!img) {
        printf("fichier non trouvé\n");
        return;
    }
    
    // Appliquer la transformation sur tous les pixels
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->pixels[i][j] = adjust_pixel_by_dominant(
                img->pixels[i][j], 
                color, 
                value, 
                img->max_value
            );
        }
    }
    
    // Créer le nom du fichier de sortie
    char output[512];
    strcpy(output, filename);
    
    // Trouver l'extension .ppm et la remplacer par _dom.ppm
    char* ext = strstr(output, ".ppm");
    if (ext != NULL) {
        strcpy(ext, "_dom.ppm");
    } else {
        // Si pas d'extension .ppm, ajouter _dom.ppm à la fin
        strcat(output, "_dom.ppm");
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
