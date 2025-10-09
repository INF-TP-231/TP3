# ==============================================================================
# MAKEFILE - PPM VIEWER
# ==============================================================================
# Projet     : Application de traitement d'images PPM
# Cours      : INF231 - Université de Yaoundé 1
# Année      : 2025-2026
# Superviseur: Prof. Melatagia
# ==============================================================================

# ==============================================================================
# CONFIGURATION DU COMPILATEUR
# ==============================================================================

# Compilateur C
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99 -g -O2

# Options de l'éditeur de liens
LDFLAGS = 

# ==============================================================================
# STRUCTURE DES RÉPERTOIRES
# ==============================================================================

# Répertoire des fichiers sources (.c et .h)
SRC_DIR = src

# Répertoire des fichiers objets (.o)
OBJ_DIR = obj

# Répertoire des fichiers de test
TEST_DIR = tests

# ==============================================================================
# FICHIERS DU PROJET
# ==============================================================================

# Liste des fichiers sources (.c)
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/ppm_io.c \
          $(SRC_DIR)/command_parser.c \
          $(SRC_DIR)/operations.c \
          $(SRC_DIR)/filters.c \
          $(SRC_DIR)/crop.c \
          $(SRC_DIR)/median.c

# Liste des fichiers objets (.o) générés à partir des sources
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/ppm_io.o \
          $(OBJ_DIR)/command_parser.o \
          $(OBJ_DIR)/operations.o \
          $(OBJ_DIR)/filters.o \
          $(OBJ_DIR)/crop.o \
          $(OBJ_DIR)/median.o

# Liste des fichiers headers (.h)
HEADERS = $(SRC_DIR)/ppm_io.h \
          $(SRC_DIR)/command_parser.h \
          $(SRC_DIR)/operations.h \
          $(SRC_DIR)/filters.h \
          $(SRC_DIR)/crop.h \
          $(SRC_DIR)/median.h

# Nom de l'exécutable final
EXECUTABLE = ppmviewer

# ==============================================================================
# RÈGLES DE COMPILATION
# ==============================================================================

# Règle par défaut : compile tout le projet
all: $(EXECUTABLE)
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║                    COMPILATION RÉUSSIE !                       ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "✓ Exécutable : ./$(EXECUTABLE)"
	@echo ""
	@echo "Pour lancer le programme :"
	@echo "    ./$(EXECUTABLE)"
	@echo ""
	@echo "Ou utilisez :"
	@echo "    make run"
	@echo ""

# Créer l'exécutable en liant tous les fichiers objets
$(EXECUTABLE): $(OBJECTS)
	@echo ""
	@echo "⚙️  Création de l'exécutable..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ $(EXECUTABLE) créé avec succès"

# Compiler chaque fichier .c en fichier .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "✓ $@ créé"

# Créer le répertoire obj s'il n'existe pas
$(OBJ_DIR):
	@echo "Création du répertoire $(OBJ_DIR)/"
	@mkdir -p $(OBJ_DIR)

# ==============================================================================
# RÈGLES DE NETTOYAGE
# ==============================================================================

# Nettoyer les fichiers compilés
clean:
	@echo ""
	@echo "Nettoyage en cours..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(EXECUTABLE)
	@rm -f $(TEST_DIR)/*_dom.ppm
	@rm -f $(TEST_DIR)/*_gris.ppm
	@rm -f $(TEST_DIR)/*_neg.ppm
	@rm -f $(TEST_DIR)/*_cut.ppm
	@rm -f $(TEST_DIR)/*_fil.ppm
	@echo "✓ Fichiers nettoyés"
	@echo ""

# Nettoyer et recompiler
rebuild: clean all

# ==============================================================================
# RÈGLES D'EXÉCUTION
# ==============================================================================

# Lancer le programme
run: $(EXECUTABLE)
	@echo ""
	@echo "Lancement de $(EXECUTABLE)..."
	@echo ""
	@./$(EXECUTABLE)

# ==============================================================================
# RÈGLES DE TEST
# ==============================================================================

# Tester toutes les commandes
test: $(EXECUTABLE)
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║                      TESTS AUTOMATIQUES                        ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Test 1 : Afficher la taille"
	@echo "size $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE)
	@echo ""
	@echo "Test 2 : Convertir en niveaux de gris"
	@echo "gris $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE)
	@echo ""
	@echo "Test 3 : Dominante rouge (foncer)"
	@echo "dom R 20 $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE)
	@echo ""
	@echo "Test 4 : Créer le négatif"
	@echo "neg $(TEST_DIR)/test.ppm $(TEST_DIR)/test_neg.ppm" | ./$(EXECUTABLE)
	@echo ""
	@echo "Test 5 : Découper une région"
	@echo "cut $(TEST_DIR)/test.ppm 1 2 1 2 $(TEST_DIR)/test_cut.ppm" | ./$(EXECUTABLE)
	@echo ""
	@echo "Test 6 : Appliquer filtre médian"
	@echo "fil $(TEST_DIR)/test.ppm $(TEST_DIR)/test_fil.ppm" | ./$(EXECUTABLE)
	@echo ""
	@echo "✓ Tests terminés"
	@echo ""

# ==============================================================================
# RÈGLES D'AIDE
# ==============================================================================

# Afficher l'aide
help:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║              MAKEFILE - PPM VIEWER - AIDE                      ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Commandes disponibles :"
	@echo ""
	@echo "  make              Compile le projet"
	@echo "  make all          Même chose que 'make'"
	@echo "  make clean        Supprime les fichiers compilés"
	@echo "  make rebuild      Nettoie et recompile tout"
	@echo "  make run          Compile et lance le programme"
	@echo "  make test         Lance des tests automatiques"
	@echo "  make help         Affiche cette aide"
	@echo "  make info         Affiche les infos du projet"
	@echo ""
	@echo "Exemples :"
	@echo ""
	@echo "  make && ./ppmviewer        Compile et lance manuellement"
	@echo "  make run                   Compile et lance automatiquement"
	@echo "  make clean && make         Recompile proprement"
	@echo ""

# Afficher les informations du projet
info:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║              INFORMATIONS DU PROJET                            ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Projet        : PPM Viewer"
	@echo "Cours         : INF231 - Techniques de Conception d'Algorithmes"
	@echo "Université    : Yaoundé 1"
	@echo "Année         : 2025-2026"
	@echo ""
	@echo "Compilateur   : $(CC)"
	@echo "Options       : $(CFLAGS)"
	@echo "Exécutable    : $(EXECUTABLE)"
	@echo ""
	@echo "Fichiers sources :"
	@for src in $(SOURCES); do echo "  - $$src"; done
	@echo ""
	@echo "Fichiers headers :"
	@for hdr in $(HEADERS); do echo "  - $$hdr"; done
	@echo ""

# ==============================================================================
# RÈGLES SPÉCIALES
# ==============================================================================

# Déclarer les règles qui ne correspondent pas à des fichiers
.PHONY: all clean rebuild run test help info

# ==============================================================================
# FIN DU MAKEFILE
# ==============================================================================# ==============================================================================
# MAKEFILE - PPM VIEWER
# ==============================================================================
# Projet      : Application de traitement d'images PPM
# Cours       : INF231 - Technique de Conception d'Algorithmes et Structures 
#               de Données
# Institution : Université de Yaoundé 1 - Département d'Informatique
# Niveau      : Licence 2 Informatique
# Année       : 2025-2026
# Superviseur : Prof. MELATAGIA
# ==============================================================================

# ==============================================================================
# CONFIGURATION DU COMPILATEUR
# ==============================================================================

# Compilateur C
CC = gcc

# Options de compilation
# -Wall      : Active tous les avertissements
# -Wextra    : Active des avertissements supplémentaires
# -std=c99   : Utilise le standard C99
# -g         : Inclut les informations de débogage
# -O2        : Optimisation niveau 2
CFLAGS = -Wall -Wextra -std=c99 -g -O2

# Options de l'éditeur de liens
LDFLAGS = 

# ==============================================================================
# STRUCTURE DES RÉPERTOIRES
# ==============================================================================

# Répertoire des fichiers sources (.c et .h)
SRC_DIR = src

# Répertoire des fichiers objets (.o)
OBJ_DIR = obj

# Répertoire des fichiers de test
TEST_DIR = tests

# ==============================================================================
# FICHIERS DU PROJET
# ==============================================================================

# Liste des fichiers sources (.c)
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/ppm_io.c \
          $(SRC_DIR)/command_parser.c \
          $(SRC_DIR)/operations.c \
          $(SRC_DIR)/filters.c \
          $(SRC_DIR)/crop.c \
          $(SRC_DIR)/median.c

# Liste des fichiers objets (.o) générés à partir des sources
OBJECTS = $(OBJ_DIR)/main.o \
          $(OBJ_DIR)/ppm_io.o \
          $(OBJ_DIR)/command_parser.o \
          $(OBJ_DIR)/operations.o \
          $(OBJ_DIR)/filters.o \
          $(OBJ_DIR)/crop.o \
          $(OBJ_DIR)/median.o

# Liste des fichiers headers (.h)
HEADERS = $(SRC_DIR)/ppm_io.h \
          $(SRC_DIR)/command_parser.h \
          $(SRC_DIR)/operations.h \
          $(SRC_DIR)/filters.h \
          $(SRC_DIR)/crop.h \
          $(SRC_DIR)/median.h

# Nom de l'exécutable final
EXECUTABLE = ppmviewer

# ==============================================================================
# RÈGLES DE COMPILATION
# ==============================================================================

# Règle par défaut : compile tout le projet
all: $(EXECUTABLE)
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║                    COMPILATION RÉUSSIE !                       ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "✓ Exécutable créé : ./$(EXECUTABLE)"
	@echo ""
	@echo "Pour lancer le programme :"
	@echo "    ./$(EXECUTABLE)"
	@echo ""
	@echo "Ou utilisez :"
	@echo "    make run"
	@echo ""

# Créer l'exécutable en liant tous les fichiers objets
$(EXECUTABLE): $(OBJECTS)
	@echo ""
	@echo "Liaison des fichiers objets..."
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ $(EXECUTABLE) créé avec succès"

# Compiler chaque fichier .c en fichier .o
# La règle dépend aussi des headers pour recompiler si un .h change
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(OBJ_DIR)
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "✓ $@ créé"

# Créer le répertoire obj s'il n'existe pas
$(OBJ_DIR):
	@echo "Création du répertoire $(OBJ_DIR)/"
	@mkdir -p $(OBJ_DIR)

# ==============================================================================
# RÈGLES DE NETTOYAGE
# ==============================================================================

# Nettoyer les fichiers compilés
clean:
	@echo ""
	@echo "Nettoyage en cours..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(EXECUTABLE)
	@rm -f $(TEST_DIR)/*_dom.ppm
	@rm -f $(TEST_DIR)/*_gris.ppm
	@rm -f $(TEST_DIR)/*_neg.ppm
	@rm -f $(TEST_DIR)/*_cut.ppm
	@rm -f $(TEST_DIR)/*_fil.ppm
	@echo "✓ Fichiers compilés et images générées supprimés"
	@echo ""

# Nettoyer et recompiler tout
rebuild: clean all
	@echo "✓ Recompilation complète terminée"

# ==============================================================================
# RÈGLES D'EXÉCUTION
# ==============================================================================

# Lancer le programme
run: $(EXECUTABLE)
	@echo ""
	@echo "Lancement de $(EXECUTABLE)..."
	@echo ""
	@./$(EXECUTABLE)

# ==============================================================================
# RÈGLES DE TEST
# ==============================================================================

# Tester toutes les commandes
test: $(EXECUTABLE)
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║              TESTS AUTOMATIQUES - INF231 TP1                   ║"
	@echo "║              Superviseur: Prof. MELATAGIA                      ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@if [ ! -f "$(TEST_DIR)/test.ppm" ]; then \
		echo "Erreur : $(TEST_DIR)/test.ppm introuvable"; \
		echo "   Créez d'abord un fichier de test PPM"; \
		exit 1; \
	fi
	@echo "Test 1 : Affichage de la taille d'une image"
	@echo "Commande : size $(TEST_DIR)/test.ppm"
	@echo "size $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE) | grep -v "ppmviewer" | grep -v "Application" | grep -v "Tapez"
	@echo ""
	@echo "Test 2 : Conversion en niveaux de gris"
	@echo "Commande : gris $(TEST_DIR)/test.ppm"
	@echo "gris $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE) | grep "opération"
	@echo ""
	@echo "Test 3 : Foncer pixels à dominante rouge (+20)"
	@echo "Commande : dom R 20 $(TEST_DIR)/test.ppm"
	@echo "dom R 20 $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE) | grep "opération"
	@echo ""
	@echo "Test 4 : Éclaircir pixels à dominante verte (-15)"
	@echo "Commande : dom G -15 $(TEST_DIR)/test.ppm"
	@echo "dom G -15 $(TEST_DIR)/test.ppm" | ./$(EXECUTABLE) | grep "opération"
	@echo ""
	@echo "Test 5 : Création du négatif"
	@echo "Commande : neg $(TEST_DIR)/test.ppm $(TEST_DIR)/test_neg.ppm"
	@echo "neg $(TEST_DIR)/test.ppm $(TEST_DIR)/test_neg.ppm" | ./$(EXECUTABLE) | grep "opération"
	@echo ""
	@echo "Test 6 : Découpage d'une région"
	@echo "Commande : cut $(TEST_DIR)/test.ppm 1 2 1 2 $(TEST_DIR)/test_cut.ppm"
	@echo "cut $(TEST_DIR)/test.ppm 1 2 1 2 $(TEST_DIR)/test_cut.ppm" | ./$(EXECUTABLE) | grep "opération"
	@echo ""
	@echo "Test 7 : Application du filtre médian"
	@echo "Commande : fil $(TEST_DIR)/test.ppm $(TEST_DIR)/test_fil.ppm"
	@echo "fil $(TEST_DIR)/test.ppm $(TEST_DIR)/test_fil.ppm" | ./$(EXECUTABLE) | grep "opération"
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║                   RÉSUMÉ DES TESTS                             ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Fichiers générés à vérifier :"
	@ls -lh $(TEST_DIR)/*_gris.ppm $(TEST_DIR)/*_dom.ppm $(TEST_DIR)/*_neg.ppm $(TEST_DIR)/*_cut.ppm $(TEST_DIR)/*_fil.ppm 2>/dev/null || echo "Aucun fichier généré"
	@echo ""
	@echo "✓ Tous les tests ont été exécutés"
	@echo ""

# ==============================================================================
# RÈGLES D'AIDE
# ==============================================================================

# Afficher l'aide
help:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║          MAKEFILE - PPM VIEWER - GUIDE D'UTILISATION           ║"
	@echo "║          INF231 - Prof. MELATAGIA                              ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "COMMANDES DISPONIBLES :"
	@echo ""
	@echo "  make              Compile le projet complet"
	@echo "  make all          Identique à 'make'"
	@echo "  make clean        Supprime tous les fichiers compilés"
	@echo "  make rebuild      Nettoie et recompile tout le projet"
	@echo "  make run          Compile (si nécessaire) et lance le programme"
	@echo "  make test         Lance une batterie de tests automatiques"
	@echo "  make help         Affiche ce guide d'utilisation"
	@echo "  make info         Affiche les informations du projet"
	@echo "  make archive      Crée une archive .tar.gz du projet"
	@echo ""
	@echo "EXEMPLES D'UTILISATION :"
	@echo ""
	@echo "  # Compilation initiale"
	@echo "  make"
	@echo ""
	@echo "  # Lancer le programme"
	@echo "  make run"
	@echo ""
	@echo "  # Après modification du code"
	@echo "  make rebuild"
	@echo ""
	@echo "  # Tester toutes les fonctionnalités"
	@echo "  make test"
	@echo ""
	@echo "  # Préparer pour soumission"
	@echo "  make clean"
	@echo "  make archive"
	@echo ""

# Afficher les informations du projet
info:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║              INFORMATIONS DU PROJET                            ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "IDENTIFICATION :"
	@echo "   Projet       : PPM Viewer - Traitement d'images"
	@echo "   Cours        : INF231 - Technique de Conception d'Algorithmes"
	@echo "   Niveau       : Licence 2 Informatique"
	@echo "   Institution  : Université de Yaoundé 1"
	@echo "   Département  : Informatique"
	@echo "   Année        : 2025-2026"
	@echo "   Superviseur  : Prof. MELATAGIA"
	@echo ""
	@echo "CONFIGURATION TECHNIQUE :"
	@echo "   Compilateur  : $(CC)"
	@echo "   Standard     : C99"
	@echo "   Options      : $(CFLAGS)"
	@echo "   Exécutable   : $(EXECUTABLE)"
	@echo ""
	@echo "STRUCTURE DU PROJET :"
	@echo "   Sources      : $(SRC_DIR)/"
	@echo "   Objets       : $(OBJ_DIR)/"
	@echo "   Tests        : $(TEST_DIR)/"
	@echo ""
	@echo "FICHIERS SOURCES :"
	@for src in $(SOURCES); do echo "   ✓ $$src"; done
	@echo ""
	@echo "FICHIERS HEADERS :"
	@for hdr in $(HEADERS); do echo "   ✓ $$hdr"; done
	@echo ""
	@echo "STATISTIQUES :"
	@echo "   Fichiers .c  : $$(echo $(SOURCES) | wc -w)"
	@echo "   Fichiers .h  : $$(echo $(HEADERS) | wc -w)"
	@echo "   Total lignes : $$(cat $(SOURCES) $(HEADERS) 2>/dev/null | wc -l)"
	@echo ""

# ==============================================================================
# RÈGLES POUR LA SOUMISSION
# ==============================================================================

# Créer une archive pour la soumission sur GitHub
archive: clean
	@echo ""
	@echo "Création de l'archive pour soumission..."
	@tar -czf ppmviewer_INF231_$(shell date +%Y%m%d_%H%M%S).tar.gz \
		--exclude='*.tar.gz' \
		--exclude='.git' \
		--exclude='$(OBJ_DIR)' \
		--exclude='*_dom.ppm' \
		--exclude='*_gris.ppm' \
		--exclude='*_neg.ppm' \
		--exclude='*_cut.ppm' \
		--exclude='*_fil.ppm' \
		.
	@echo "✓ Archive créée : ppmviewer_INF231_$(shell date +%Y%m%d_%H%M%S).tar.gz"
	@echo ""
	@echo "Vous pouvez maintenant :"
	@echo "   1. Commit et push sur GitHub"
	@echo "   2. Soumettre le lien sur le formulaire Google"
	@echo ""

# Vérifier que le projet est prêt pour la soumission
check-submission:
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════════╗"
	@echo "║           VÉRIFICATION AVANT SOUMISSION                        ║"
	@echo "╚════════════════════════════════════════════════════════════════╝"
	@echo ""
	@echo "Vérification des fichiers requis..."
	@echo ""
	@if [ -f "README.md" ]; then \
		echo "✓ README.md présent"; \
	else \
		echo "README.md manquant"; \
	fi
	@if [ -f "Makefile" ]; then \
		echo "✓ Makefile présent"; \
	else \
		echo "Makefile manquant"; \
	fi
	@if [ -f "$(TEST_DIR)/test.ppm" ]; then \
		echo "✓ Fichier de test présent"; \
	else \
		echo "Fichier de test manquant (recommandé)"; \
	fi
	@echo ""
	@echo "Vérification de la compilation..."
	@make clean > /dev/null 2>&1
	@if make all > /dev/null 2>&1; then \
		echo "✓ Le projet compile sans erreur"; \
	else \
		echo "Erreurs de compilation détectées"; \
	fi
	@echo ""
	@echo "Date limite : Vendredi 10 Octobre 2025 à 20H00"
	@echo ""

# ==============================================================================
# RÈGLES SPÉCIALES
# ==============================================================================

# Déclarer les règles qui ne correspondent pas à des fichiers
.PHONY: all clean rebuild run test help info archive check-submission

# Message de copyright
.DEFAULT_GOAL := all

# ==============================================================================
# FIN DU MAKEFILE
# ==============================================================================
# Projet supervisé par Prof. MELATAGIA 
# Université de Yaoundé 1 - Département d'Informatique
# INF231 - Année académique 2025-2026
# ==============================================================================