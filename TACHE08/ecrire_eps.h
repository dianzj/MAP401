
#ifndef ECRIRE_EPS_H
#define ECRIRE_EPS_H
#include "sequence_point.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void ecrire_contour_bezier3_eps(Liste_bezier_3 contour, FILE *f, unsigned int H);
void ecrire_contour_bezier2_eps(Liste_bezier_2 contour, FILE *f, unsigned int H);
char *nom_eps(const char *nom_pbm, const char *suffixe, int d);
#endif // ECRIRE_EPS_H