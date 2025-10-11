/*
 * ============================================================================
 * BLOC 3 : Opérations sur les dominantes et affichage de taille
 * ============================================================================
 * Fichier : operations.h
 * Auteur  : Yvana Emilia Lalane Larcier 
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier définit les fonctions pour :
 *   - Afficher la taille d'une image (commande size)
 *   - Foncer/éclaircir les pixels ayant une dominante donnée (commande dom)
 *   
 *   La dominante d'un pixel est la composante RGB ayant la valeur la plus élevée.
 * ============================================================================
 */

#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "ppm_io.h"

/* ============================================================================
 * PROTOTYPES DES COMMANDES
 * ============================================================================ */

/**
 * Commande size : affiche les dimensions d'une image
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM
 * 
 * Sortie :
 *   - Affiche "largeur x hauteur" si le fichier existe
 *   - Affiche "fichier non trouvé" sinon
 * 
 * Exemple :
 *   ppmviewer > size image.ppm
 *   100 x 205
 */
void command_size(const char* filename);

/**
 * Commande dom : foncer ou éclaircir les pixels avec une dominante donnée
 * 
 * Paramètres :
 *   - filename : chemin du fichier PPM
 *   - color    : couleur dominante à traiter ('R', 'G' ou 'B')
 *   - value    : valeur à ajouter/soustraire
 *                > 0 : foncer (ajouter)
 *                < 0 : éclaircir (soustraire)
 * 
 * Sortie :
 *   - Crée un fichier "filename_dom.ppm" avec l'image modifiée
 *   - Affiche "fichier non trouvé" si le fichier n'existe pas
 *   - Affiche "opération effectuée ; filename_dom.ppm créé" en cas de succès
 * 
 * Exemple :
 *   ppmviewer > dom R 10 image.ppm
 *   opération effectuée ; image_dom.ppm créé
 * 
 * Notes :
 *   - Seuls les pixels ayant la dominante spécifiée sont modifiés
 *   - Les valeurs RGB sont clampées entre 0 et max_value
 */
void command_dom(const char* filename, char color, int value);

/* ============================================================================
 * FONCTIONS UTILITAIRES
 * ============================================================================ */

/**
 * Détermine quelle composante RGB est dominante dans un pixel
 * 
 * Paramètres :
 *   - p : pixel à analyser
 * 
 * Retour :
 *   - 0 si Rouge est dominant
 *   - 1 si Vert est dominant
 *   - 2 si Bleu est dominant
 * 
 * Notes :
 *   - En cas d'égalité, priorité à Rouge > Vert > Bleu
 */
int get_dominant_color(Pixel p);

/**
 * Ajuste un pixel selon sa dominante
 * 
 * Paramètres :
 *   - p         : pixel à modifier
 *   - dominant  : couleur dominante ciblée ('R', 'G' ou 'B')
 *   - value     : valeur à ajouter (peut être négative)
 *   - max_value : valeur maximale pour clamping
 * 
 * Retour :
 *   - Pixel modifié si sa dominante correspond
 *   - Pixel inchangé sinon
 * 
 * Notes :
 *   - Les trois composantes RGB sont modifiées
 *   - Les valeurs sont clampées entre 0 et max_value
 */
Pixel adjust_pixel_by_dominant(Pixel p, char dominant, int value, int max_value);

#endif // OPERATIONS_H
