/*
 * ============================================================================
 * BLOC 2 : Implémentation du parseur de commandes
 * ============================================================================
 * Fichier : command_parser.c
 * Auteur  : [Nom Personne 2]
 * Date    : Octobre 2025
 * ============================================================================
 */

#include "command_parser.h"

/* ============================================================================
 * AFFICHAGE DE L'AIDE
 * ============================================================================ */

/**
 * Affiche la liste complète des commandes disponibles
 */
void print_help(void) {
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("                    COMMANDES DISPONIBLES                          \n");
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("\n");
    printf("  size <fichier.ppm>\n");
    printf("      → Affiche la taille de l'image (largeur x hauteur)\n");
    printf("\n");
    printf("  dom <R|G|B> <valeur> <fichier.ppm>\n");
    printf("      → Foncer/éclaircir les pixels avec dominante donnée\n");
    printf("      → <valeur> > 0 : foncer | <valeur> < 0 : éclaircir\n");
    printf("      → Sortie automatique : fichier_dom.ppm\n");
    printf("\n");
    printf("  gris <fichier.ppm>\n");
    printf("      → Convertir l'image en niveaux de gris\n");
    printf("      → Sortie automatique : fichier_gris.ppm\n");
    printf("\n");
    printf("  neg <fichier.ppm> <fichier_sortie.ppm>\n");
    printf("      → Créer le négatif de l'image\n");
    printf("\n");
    printf("  cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>\n");
    printf("      → Découper une région rectangulaire\n");
    printf("      → Indices commencent à 1\n");
    printf("\n");
    printf("  fil <fichier.ppm> <fichier_sortie.ppm>\n");
    printf("      → Appliquer un filtre médian 3x3\n");
    printf("\n");
    printf("  help\n");
    printf("      → Afficher cette aide\n");
    printf("\n");
    printf("  quit\n");
    printf("      → Quitter l'application\n");
    printf("\n");
    printf("═══════════════════════════════════════════════════════════════════\n");
    printf("\n");
}

/* ============================================================================
 * PARSING DE COMMANDES
 * ============================================================================ */

/**
 * Parse une ligne de commande et extrait ses paramètres
 */
Command parse_command(const char* input) {
    Command cmd;
    
    // Initialiser la structure à zéro
    memset(&cmd, 0, sizeof(Command));
    cmd.type = CMD_UNKNOWN;
    
    // Buffer pour le nom de la commande
    char command[20];
    
    // Extraire le premier mot (nom de la commande)
    int n = sscanf(input, "%19s", command);
    
    if (n != 1) {
        // Aucune commande trouvée
        return cmd;
    }
    
    /* ========================================================================
     * COMMANDE : size
     * Syntaxe : size <fichier.ppm>
     * ======================================================================== */
    if (strcmp(command, "size") == 0) {
        cmd.type = CMD_SIZE;
        sscanf(input, "%*s %255s", cmd.filename);
    }
    
    /* ========================================================================
     * COMMANDE : dom
     * Syntaxe : dom <R|G|B> <valeur> <fichier.ppm>
     * ======================================================================== */
    else if (strcmp(command, "dom") == 0) {
        cmd.type = CMD_DOM;
        int parsed = sscanf(input, "%*s %c %d %255s", 
                           &cmd.color, &cmd.value, cmd.filename);
        
        // Valider la couleur
        if (parsed != 3 || (cmd.color != 'R' && cmd.color != 'G' && cmd.color != 'B')) {
            cmd.type = CMD_UNKNOWN;
        }
    }
    
    /* ========================================================================
     * COMMANDE : gris
     * Syntaxe : gris <fichier.ppm>
     * ======================================================================== */
    else if (strcmp(command, "gris") == 0) {
        cmd.type = CMD_GRIS;
        sscanf(input, "%*s %255s", cmd.filename);
    }
    
    /* ========================================================================
     * COMMANDE : neg
     * Syntaxe : neg <fichier.ppm> <fichier_sortie.ppm>
     * ======================================================================== */
    else if (strcmp(command, "neg") == 0) {
        cmd.type = CMD_NEG;
        int parsed = sscanf(input, "%*s %255s %255s", 
                           cmd.filename, cmd.output_filename);
        
        if (parsed != 2) {
            cmd.type = CMD_UNKNOWN;
        }
    }
    
    /* ========================================================================
     * COMMANDE : cut
     * Syntaxe : cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>
     * ======================================================================== */
    else if (strcmp(command, "cut") == 0) {
        cmd.type = CMD_CUT;
        int parsed = sscanf(input, "%*s %255s %d %d %d %d %255s", 
                           cmd.filename, &cmd.l1, &cmd.l2, 
                           &cmd.c1, &cmd.c2, cmd.output_filename);
        
        if (parsed != 6) {
            cmd.type = CMD_UNKNOWN;
        }
    }
    
    /* ========================================================================
     * COMMANDE : fil
     * Syntaxe : fil <fichier.ppm> <fichier_sortie.ppm>
     * ======================================================================== */
    else if (strcmp(command, "fil") == 0) {
        cmd.type = CMD_FIL;
        int parsed = sscanf(input, "%*s %255s %255s", 
                           cmd.filename, cmd.output_filename);
        
        if (parsed != 2) {
            cmd.type = CMD_UNKNOWN;
        }
    }
    
    /* ========================================================================
     * COMMANDE : quit
     * Syntaxe : quit
     * ======================================================================== */
    else if (strcmp(command, "quit") == 0) {
        cmd.type = CMD_QUIT;
    }
    
    /* ========================================================================
     * COMMANDE : help
     * Syntaxe : help
     * ======================================================================== */
    else if (strcmp(command, "help") == 0) {
        cmd.type = CMD_HELP;
    }
    
    /* ========================================================================
     * COMMANDE INCONNUE
     * ======================================================================== */
    else {
        cmd.type = CMD_UNKNOWN;
    }
    
    return cmd;
}