/*
 * ============================================================================
 * BLOC 4 : Filtres de transformation d'images (Niveaux de gris et Négatif)
 * ============================================================================
 * Fichier : filters.h
 * Auteur  : Akana Signing Josias Aaron
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier définit les fonctions pour appliquer des filtres simples
 *   aux images PPM :
 *   - Conversion en niveaux de gris (noir et blanc)
 *   - Création du négatif (inversion des couleurs)
 * ============================================================================
 */

#ifndef FILTERS_H
#define FILTERS_H

#include "ppm_io.h"

/* ============================================================================
 * PROTOTYPES DES COMMANDES
 * ============================================================================ */

/**
 * Commande gris : convertit une image en niveaux de gris
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM à convertir
 * 
 * Sortie :
 *   - Crée un fichier "filename_gris.ppm" avec l'image en noir et blanc
 *   - Affiche "fichier non trouvé" si le fichier n'existe pas
 *   - Affiche "opération effectuée ; filename_gris.ppm créé" en cas de succès
 * 
 * Algorithme :
 *   Pour chaque pixel, calcule la moyenne des composantes RGB :
 *   nouvelle_valeur = (R + G + B) / 3
 *   Puis applique cette valeur aux trois composantes
 * 
 * Exemple :
 *   ppmviewer > gris image.ppm
 *   opération effectuée ; image_gris.ppm créé
 */
void command_gris(const char* filename);

/**
 * Commande neg : crée le négatif d'une image
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM source
 *   - output   : chemin du fichier PPM de sortie
 * 
 * Sortie :
 *   - Crée le fichier spécifié avec l'image négative
 *   - Affiche "fichier non trouvé" si le fichier source n'existe pas
 *   - Affiche "opération effectuée" en cas de succès
 * 
 * Algorithme :
 *   Pour chaque composante RGB :
 *   nouvelle_valeur = max_value - ancienne_valeur
 * 
 * Exemple :
 *   ppmviewer > neg image.ppm image_neg.ppm
 *   opération effectuée
 */
void command_neg(const char* filename, const char* output);

/* ============================================================================
 * FONCTIONS UTILITAIRES
 * ============================================================================ */

/**
 * Convertit un pixel en niveau de gris
 * 
 * Paramètres :
 *   - p : pixel à convertir
 * 
 * Retour :
 *   - Pixel avec R = G = B = moyenne(R, G, B)
 * 
 * Formule :
 *   gris = (R + G + B) / 3
 */
Pixel to_grayscale(Pixel p);

/**
 * Crée le négatif d'un pixel
 * 
 * Paramètres :
 *   - p         : pixel à inverser
 *   - max_value : valeur maximale (généralement 255)
 * 
 * Retour :
 *   - Pixel avec chaque composante inversée
 * 
 * Formule :
 *   R' = max_value - R
 *   G' = max_value - G
 *   B' = max_value - B
 */
Pixel to_negative(Pixel p, int max_value);

#endif // FILTERS_H
