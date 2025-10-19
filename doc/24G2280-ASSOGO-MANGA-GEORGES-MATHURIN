Cahier de suivi individuel — INF231 (TP3)
===============================================

#ASSOGO MANGA GEORGES MATHURIN <br>

#Matricule:24G2280 <br>

#Exercice attribué: ppm_io.c ppm_io.h: lecture et écriture des images<br>

## 1. Description générale
- Le module ppm_io est responsable de la lecture (read) et de l’écriture (write) des fichiers image au format PPM (Portable Pixmap — type P3, ASCII).  
- Il constitue la porte d’entrée et de sortie du système de traitement d’images utilisé dans le projet.
- Il permet de charger une image en mémoire dans une structure dédiée puis de sauvegarder les modifications après traitement par les autres modules.


## 2. Fonctions principales
| Fonction | Rôle |
|----------|------|
| PPMImage* ppm_read(const char *filename) | Lit un fichier .ppm, vérifie son intégrité et charge ses données en mémoire |
| int ppm_write(const char *filename, const PPMImage *img) | Sauvegarde l’image en mémoire vers un fichier .ppm valide |
| void ppm_free(PPMImage *img) | Libère correctement la mémoire associée à l’image |


## 3. Structure de données utilisée
Définie dans ppm_io.h :


```c
typedef struct {   
int width;   
int height;   
int max_value;  
unsigned char *data; // Données brutes : RGBRGBRGB...
} PPMImage;
