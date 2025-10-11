/*
 * ============================================================================
 * BLOC 1 : Lecture et Écriture de fichiers PPM
 * ============================================================================
 * Fichier : ppm_io.h
 * Auteur  : Assogo Manga Georges Mathurin
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier définit les structures de données pour manipuler des images
 *   au format PPM (Portable PixMap) version P3, ainsi que les prototypes
 *   des fonctions de lecture, écriture et gestion de mémoire.
 * ============================================================================
 */

#ifndef PPM_IO_H
#define PPM_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ============================================================================
 * STRUCTURES DE DONNÉES
 * ============================================================================ */

/**
 * Structure représentant un pixel RGB
 * 
 * Champs :
 *   - r : composante rouge (0-255)
 *   - g : composante verte (0-255)
 *   - b : composante bleue (0-255)
 */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Pixel;

/**
 * Structure représentant une image PPM complète
 * 
 * Champs :
 *   - width     : largeur de l'image en pixels
 *   - height    : hauteur de l'image en pixels
 *   - max_value : valeur maximale pour chaque composante RGB (généralement 255)
 *   - pixels    : tableau 2D de pixels [height][width]
 */
typedef struct {
    int width;
    int height;
    int max_value;
    Pixel** pixels;
} Image;

/* ============================================================================
 * PROTOTYPES DES FONCTIONS
 * ============================================================================ */

/**
 * Charge une image PPM depuis un fichier
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM à charger
 * 
 * Retour :
 *   - Pointeur vers l'image chargée en cas de succès
 *   - NULL en cas d'erreur (fichier introuvable, format invalide, etc.)
 * 
 * Notes :
 *   - Supporte uniquement le format P3 (texte)
 *   - Ignore les commentaires commençant par '#'
 *   - Alloue dynamiquement la mémoire pour l'image
 */
Image* load_ppm(const char* filename);

/**
 * Sauvegarde une image PPM dans un fichier
 * 
 * Paramètres :
 *   - filename : chemin du fichier de destination
 *   - img      : pointeur vers l'image à sauvegarder
 * 
 * Retour :
 *   - 1 en cas de succès
 *   - 0 en cas d'échec
 */
int save_ppm(const char* filename, Image* img);

/**
 * Crée une nouvelle image vide avec les dimensions spécifiées
 * 
 * Paramètres :
 *   - width     : largeur de l'image
 *   - height    : hauteur de l'image
 *   - max_value : valeur maximale des composantes RGB
 * 
 * Retour :
 *   - Pointeur vers la nouvelle image
 *   - NULL en cas d'échec d'allocation mémoire
 */
Image* create_image(int width, int height, int max_value);

/**
 * Libère toute la mémoire associée à une image
 * 
 * Paramètres :
 *   - img : pointeur vers l'image à libérer
 * 
 * Notes :
 *   - Libère le tableau 2D de pixels ainsi que la structure Image
 *   - Ne fait rien si img est NULL
 */
void free_image(Image* img);

/**
 * Restreint les valeurs RGB d'un pixel entre 0 et max_value
 * 
 * Paramètres :
 *   - p         : pixel à clamper
 *   - max_value : valeur maximale autorisée
 * 
 * Retour :
 *   - Pixel avec valeurs clampées
 */
Pixel clamp_pixel(Pixel p, int max_value);

/**
 * Ignore les commentaires et espaces dans un fichier PPM
 * 
 * Paramètres :
 *   - fp : pointeur vers le fichier ouvert
 * 
 * Notes :
 *   - Fonction utilitaire pour le parsing
 *   - Ignore tout caractère entre '#' et fin de ligne
 */
void skip_comments_and_spaces(FILE* fp);

#endif // PPM_IO_H
