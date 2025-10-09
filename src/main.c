/*
 * ============================================================================
 * BLOC 2 : Point d'entrée principal de l'application
 * ============================================================================
 * Fichier : main.c
 * Auteur  : [Nom Personne 2]
 * Date    : Octobre 2025
 * 
 * Description :
 *   Ce fichier contient la fonction main() qui gère la boucle principale
 *   de l'application, l'affichage de l'invite de commande et l'exécution
 *   des différentes opérations sur les images PPM.
 * ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include "ppm_io.h"
#include "command_parser.h"
#include "operations.h"
#include "filters.h"
#include "crop.h"
#include "median.h"

/* ============================================================================
 * EXÉCUTION DES COMMANDES
 * ============================================================================ */

/**
 * Exécute une commande parsée en appelant la fonction appropriée
 * 
 * Paramètres :
 *   - cmd : pointeur vers la structure Command contenant la commande et ses paramètres
 */
void execute_command(Command* cmd) {
    switch (cmd->type) {
        /* ====================================================================
         * Afficher la taille
         * ==================================================================== */
        case CMD_SIZE:
            command_size(cmd->filename);
            break;
        
        /* ====================================================================
         * Foncer/éclaircir dominante
         * ==================================================================== */
        case CMD_DOM:
            command_dom(cmd->filename, cmd->color, cmd->value);
            break;
        
        /* ====================================================================
         * Convertir en niveaux de gris
         * ==================================================================== */
        case CMD_GRIS:
            command_gris(cmd->filename);
            break;
        
        /* ====================================================================
         * Créer le négatif
         * ==================================================================== */
        case CMD_NEG:
            command_neg(cmd->filename, cmd->output_filename);
            break;
        
        /* ====================================================================
         * Découper une région
         * ==================================================================== */
        case CMD_CUT:
            command_cut(cmd->filename, cmd->l1, cmd->l2, 
                       cmd->c1, cmd->c2, cmd->output_filename);
            break;
        
        /* ====================================================================
         * Appliquer filtre médian
         * ==================================================================== */
        case CMD_FIL:
            command_fil(cmd->filename, cmd->output_filename);
            break;
        
        /* ====================================================================
         * Afficher l'aide
         * ==================================================================== */
        case CMD_HELP:
            print_help();
            break;
        
        /* ====================================================================
         * Commande inconnue
         * ==================================================================== */
        case CMD_UNKNOWN:
            printf("Commande inconnue. Tapez 'help' pour voir les commandes disponibles.\n");
            break;
        
        /* ====================================================================
         * Autres cas (quit, etc.)
         * ==================================================================== */
        default:
            break;
    }
}

/* ============================================================================
 * FONCTION PRINCIPALE
 * ============================================================================ */

/**
 * Point d'entrée du programme
 */
int main(void) {
    // Bannière de bienvenue
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════════════╗\n");
    printf("║                                                                   ║\n");
    printf("║              APPLICATION DE TRAITEMENT D'IMAGES PPM               ║\n");
    printf("║                                                                   ║\n");
    printf("║                  Université de Yaoundé 1 - INF231                 ║\n");
    printf("║                   Année académique 2025-2026                      ║\n");
    printf("║                                                                   ║\n");
    printf("╚═══════════════════════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("Tapez 'help' pour voir les commandes disponibles.\n");
    printf("\n");
    
    // Buffer pour lire les commandes
    char input[512];
    
    // Boucle principale
    while (1) {
        // Afficher l'invite de commande
        printf("ppmviewer > ");
        fflush(stdout);
        
        // Lire la ligne de commande
        if (!fgets(input, sizeof(input), stdin)) {
            // EOF ou erreur de lecture
            break;
        }
        
        // Enlever le retour à la ligne
        input[strcspn(input, "\n")] = '\0';
        
        // Ignorer les lignes vides
        if (strlen(input) == 0) {
            continue;
        }
        
        // Parser la commande
        Command cmd = parse_command(input);
        
        // Vérifier si c'est la commande quit
        if (cmd.type == CMD_QUIT) {
            printf("\n");
            printf("═══════════════════════════════════════════════════════════════════\n");
            printf("           Merci d'avoir utilisé PPM Viewer.            \n");
            printf("═══════════════════════════════════════════════════════════════════\n");
            printf("\n");
            break;
        }
        
        // Exécuter la commande
        execute_command(&cmd);
    }
    
    return 0;
}