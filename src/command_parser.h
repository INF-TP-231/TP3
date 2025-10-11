/*
 * ============================================================================
 * BLOC 2 : Parsing et gestion des commandes utilisateur
 * ============================================================================
 * Fichier : command_parser.h
 * Auteur  : Nsangou Nkanjone Manuel Decency 
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier définit les types de commandes supportées par l'application
 *   ainsi que les structures et fonctions pour parser les entrées utilisateur.
 * ============================================================================
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <string.h>
#include <stdio.h>

/* ============================================================================
 * ÉNUMÉRATIONS
 * ============================================================================ */

/**
 * Types de commandes disponibles
 * 
 * Valeurs :
 *   - CMD_SIZE    : Afficher la taille d'une image
 *   - CMD_DOM     : Foncer/éclaircir pixels avec dominante
 *   - CMD_GRIS    : Convertir en niveaux de gris
 *   - CMD_NEG     : Créer le négatif
 *   - CMD_CUT     : Découper une région
 *   - CMD_FIL     : Appliquer filtre médian
 *   - CMD_QUIT    : Quitter l'application
 *   - CMD_HELP    : Afficher l'aide
 *   - CMD_UNKNOWN : Commande non reconnue
 */
typedef enum {
    CMD_SIZE,
    CMD_DOM,
    CMD_GRIS,
    CMD_NEG,
    CMD_CUT,
    CMD_FIL,
    CMD_QUIT,
    CMD_HELP,
    CMD_UNKNOWN
} CommandType;

/* ============================================================================
 * STRUCTURES
 * ============================================================================ */

/**
 * Structure contenant une commande parsée avec tous ses paramètres
 * 
 * Champs :
 *   - type             : type de la commande (voir CommandType)
 *   - filename         : nom du fichier d'entrée
 *   - output_filename  : nom du fichier de sortie (si applicable)
 *   - color            : couleur dominante (R, G ou B) pour CMD_DOM
 *   - value            : valeur d'ajustement pour CMD_DOM
 *   - l1, l2, c1, c2   : coordonnées pour CMD_CUT
 */
typedef struct {
    CommandType type;
    char filename[256];
    char output_filename[256];
    char color;          // Pour dom (R, G, B)
    int value;           // Pour dom
    int l1, l2, c1, c2;  // Pour cut
} Command;

/* ============================================================================
 * PROTOTYPES DES FONCTIONS
 * ============================================================================ */

/**
 * Parse une ligne de commande saisie par l'utilisateur
 * 
 * Paramètres :
 *   - input : chaîne contenant la commande à parser
 * 
 * Retour :
 *   - Structure Command remplie avec les paramètres extraits
 *   - Le champ 'type' vaut CMD_UNKNOWN si la commande est invalide
 * 
 * Exemples :
 *   "size image.ppm"              -> CMD_SIZE
 *   "dom R 10 image.ppm"          -> CMD_DOM
 *   "cut img.ppm 1 50 1 100 o.ppm" -> CMD_CUT
 */
Command parse_command(const char* input);

/**
 * Affiche l'aide avec la liste des commandes disponibles
 * 
 * Sortie :
 *   - Affiche sur stdout la syntaxe de toutes les commandes
 */
void print_help(void);

#endif // COMMAND_PARSER_H
