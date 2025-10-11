/*
 * ============================================================================
 * BLOC 1 : Implémentation des fonctions de lecture/écriture PPM
 * ============================================================================
 * Fichier : ppm_io.c
 * Auteur  : Assogo Manga Georges Mathurin
 * Date    : Octobre 2025
 * ============================================================================
 */

#include "ppm_io.h"

/* ============================================================================
 * FONCTIONS UTILITAIRES
 * ============================================================================ */

/**
 * Ignore les commentaires et espaces blancs dans un fichier PPM
 */
void skip_comments_and_spaces(FILE* fp) {
    int c;
    
    while ((c = fgetc(fp)) != EOF) {
        if (c == '#') {
            // Commentaire détecté : ignorer jusqu'à la fin de ligne
            while ((c = fgetc(fp)) != EOF && c != '\n') {
                // Continue à lire jusqu'au '\n'
            }
        } else if (!isspace(c)) {
            // Caractère non-blanc trouvé : remettre dans le buffer
            ungetc(c, fp);
            break;
        }
    }
}

/**
 * Restreint les valeurs RGB entre 0 et max_value
 */
Pixel clamp_pixel(Pixel p, int max_value) {
    if (p.r > max_value) p.r = max_value;
    if (p.g > max_value) p.g = max_value;
    if (p.b > max_value) p.b = max_value;
    
    // Pas besoin de vérifier < 0 car unsigned char
    return p;
}

/* ============================================================================
 * GESTION DE LA MÉMOIRE
 * ============================================================================ */

/**
 * Crée une nouvelle image avec allocation dynamique
 */
Image* create_image(int width, int height, int max_value) {
    // Allouer la structure Image
    Image* img = (Image*)malloc(sizeof(Image));
    if (!img) {
        fprintf(stderr, "Erreur : échec d'allocation pour Image\n");
        return NULL;
    }
    
    // Initialiser les champs
    img->width = width;
    img->height = height;
    img->max_value = max_value;
    
    // Allouer le tableau de pointeurs (lignes)
    img->pixels = (Pixel**)malloc(height * sizeof(Pixel*));
    if (!img->pixels) {
        fprintf(stderr, "Erreur : échec d'allocation pour les lignes\n");
        free(img);
        return NULL;
    }
    
    // Allouer chaque ligne (colonnes)
    for (int i = 0; i < height; i++) {
        img->pixels[i] = (Pixel*)malloc(width * sizeof(Pixel));
        if (!img->pixels[i]) {
            fprintf(stderr, "Erreur : échec d'allocation pour la ligne %d\n", i);
            // Libérer les lignes déjà allouées
            for (int j = 0; j < i; j++) {
                free(img->pixels[j]);
            }
            free(img->pixels);
            free(img);
            return NULL;
        }
    }
    
    return img;
}

/**
 * Libère toute la mémoire d'une image
 */
void free_image(Image* img) {
    if (!img) return;
    
    // Libérer chaque ligne
    if (img->pixels) {
        for (int i = 0; i < img->height; i++) {
            if (img->pixels[i]) {
                free(img->pixels[i]);
            }
        }
        free(img->pixels);
    }
    
    // Libérer la structure
    free(img);
}

/* ============================================================================
 * LECTURE D'IMAGE PPM
 * ============================================================================ */

/**
 * Charge une image PPM depuis un fichier
 */
Image* load_ppm(const char* filename) {
    // Ouvrir le fichier en lecture
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        return NULL;
    }
    
    // Lire le numéro magique (P3)
    char magic[3];
    if (fscanf(fp, "%2s", magic) != 1) {
        fclose(fp);
        return NULL;
    }
    
    // Vérifier que c'est bien P3
    if (strcmp(magic, "P3") != 0) {
        fprintf(stderr, "Erreur : format non supporté (attendu P3, reçu %s)\n", magic);
        fclose(fp);
        return NULL;
    }
    
    // Lire la largeur
    skip_comments_and_spaces(fp);
    int width;
    if (fscanf(fp, "%d", &width) != 1) {
        fclose(fp);
        return NULL;
    }
    
    // Lire la hauteur
    skip_comments_and_spaces(fp);
    int height;
    if (fscanf(fp, "%d", &height) != 1) {
        fclose(fp);
        return NULL;
    }
    
    // Lire la valeur maximale
    skip_comments_and_spaces(fp);
    int max_value;
    if (fscanf(fp, "%d", &max_value) != 1) {
        fclose(fp);
        return NULL;
    }
    
    // Créer l'image
    Image* img = create_image(width, height, max_value);
    if (!img) {
        fclose(fp);
        return NULL;
    }
    
    // Lire tous les pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int r, g, b;
            
            skip_comments_and_spaces(fp);
            if (fscanf(fp, "%d", &r) != 1) {
                free_image(img);
                fclose(fp);
                return NULL;
            }
            
            skip_comments_and_spaces(fp);
            if (fscanf(fp, "%d", &g) != 1) {
                free_image(img);
                fclose(fp);
                return NULL;
            }
            
            skip_comments_and_spaces(fp);
            if (fscanf(fp, "%d", &b) != 1) {
                free_image(img);
                fclose(fp);
                return NULL;
            }
            
            // Stocker le pixel
            img->pixels[i][j].r = (unsigned char)r;
            img->pixels[i][j].g = (unsigned char)g;
            img->pixels[i][j].b = (unsigned char)b;
        }
    }
    
    fclose(fp);
    return img;
}

/* ============================================================================
 * ÉCRITURE D'IMAGE PPM
 * ============================================================================ */

/**
 * Sauvegarde une image PPM dans un fichier
 */
int save_ppm(const char* filename, Image* img) {
    if (!img) return 0;
    
    // Ouvrir le fichier en écriture
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Erreur : impossible d'ouvrir %s en écriture\n", filename);
        return 0;
    }
    
    // Écrire l'en-tête
    fprintf(fp, "P3\n");
    fprintf(fp, "# Created by PPM Viewer - INF231\n");
    fprintf(fp, "%d %d\n", img->width, img->height);
    fprintf(fp, "%d\n", img->max_value);
    
    // Écrire les pixels
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            fprintf(fp, "%d %d %d ", 
                    img->pixels[i][j].r, 
                    img->pixels[i][j].g, 
                    img->pixels[i][j].b);
        }
        fprintf(fp, "\n");
    }
    
    fclose(fp);
    return 1;
}
