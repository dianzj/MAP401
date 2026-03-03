#ifndef CALCUL_CONTOUR_H
#define CALCUL_CONTOUR_H

#include "sequence_point.h"
#include "image.h"

typedef enum {Nord, Est, Sud, Ouest} Orientation;

/* Trouver le premier pixel noir du contour */
Point trouver_pixel_depart(Image I);

/* Avancer d'une case dans la direction donnée */
Point avancer(Point p0, Orientation orient);

/* Récupérer la valeur du pixel à gauche */
Pixel valeur_pixel_gauche(Image I, Point p0, Orientation orient);

/* Récupérer la valeur du pixel à droite */
Pixel valeur_pixel_droite(Image I, Point p0, Orientation orient);

/* Déterminer la nouvelle orientation */
Orientation sens(Image I, Point p0, Orientation orient);

/* Calculer le contour de l'image */
void supprimer_ensemble_contours(Ensemble_Contours *ensemble);
Ensemble_Contours calcul_contour(Image I, int *nb_contour);
void sauver_image_pbm(Image I, const char *nom_f);
Liste_Point simplification_douglas_peucker (Tableau_Point T, int j1, int j2, double d);
#endif
    