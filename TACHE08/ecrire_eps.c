
#include "sequence_point.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "calcul.h"


void ecrire_contour_bezier3_eps(Liste_bezier_3 contour, FILE *f, unsigned int H)
{
    //c
    for (unsigned int k = 0; k < contour.taille; k++) {
        bezier_3 b = contour.bez3[k];

        if (k == 0) {
            fprintf(f, "%f %f moveto\n", b.c0.x, H - b.c0.y);
        }

        fprintf(f, "%f %f %f %f %f %f curveto\n",
                b.c1.x, H - b.c1.y,
                b.c2.x, H - b.c2.y,
                b.c3.x, H - b.c3.y);
    }
    fprintf(f, "closepath\n");
}
void ecrire_contour_bezier2_eps(Liste_bezier_2 contour, FILE *f, unsigned int H)
{
    
    for (unsigned int k = 0; k < contour.taille; k++) {
        bezier_2 b1 = contour.bez2[k];
        bezier_3  b=conversion_bezier_2_vers_bezier_3(b1);
        if (k == 0) {
            fprintf(f, "%f %f moveto\n", b.c0.x, H - b.c0.y);
        }

        fprintf(f, "%f %f %f %f %f %f curveto\n",
                b.c1.x, H - b.c1.y,
                b.c2.x, H - b.c2.y,
                b.c3.x, H - b.c3.y); 
    }
    fprintf(f, "closepath\n");
}
char *nom_eps(const char *nom_pbm, const char *suffixe, int d)
{
    size_t len = strlen(nom_pbm);
    char *base = malloc(len + 1);
    if (!base) return NULL;

    strcpy(base, nom_pbm);

    char *dot = strrchr(base, '.');
    if (dot != NULL)
        *dot = '\0';

    int taille = snprintf(NULL, 0, "%s%s%d.eps", base, suffixe, d) + 1;

    char *nom = malloc(taille);
    if (!nom) {
        free(base);
        return NULL;
    }

    snprintf(nom, taille, "%s%s%d.eps", base, suffixe, d);

    free(base);
    return nom;
}