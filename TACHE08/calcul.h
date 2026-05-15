#ifndef CALCUL_H_
#define CALCUL_H_

#include "sequence_point.h"
/* ===== Types ===== */



typedef struct {
    double x;
    double y;
} Vecteur;

/*operation*/

/* somme */
Point somme_points(Point A, Point B);
Vecteur somme_vecteurs(Vecteur u, Vecteur v);

/* vecteur à partir de deux points */
Vecteur vecteur_points(Point A, Point B);

/* multiplication par un réel */
Point   mult_point(Point P, double k);
Vecteur mult_vecteur(Vecteur v, double k);

/* produit scalaire */
double produit_scalaire(Vecteur u, Vecteur v);

/* norme */
double norme(Vecteur v);

/* distance entre deux points */
double distance(Point A, Point B);
Vecteur normaliser(Vecteur v);
Vecteur orthogonal(Vecteur v);
double distance_point_vecteur(Point P, Point A, Point B);
Point  C_2(bezier_2 B, double t);
Point  C_3(bezier_3 B, double t);
bezier_3 conversion_bezier_2_vers_bezier_3(bezier_2 B);
bezier_2 approx_bezier_2(Tableau_Point T,int j1,int j2);
double distance_point_bezier_2(Point P, bezier_2 B, double t);
double distance_point_bezier_3(Point P, bezier_3 B, double t);
bezier_3 approx_bezier_3(Tableau_Point T,int j1,int j2);
#endif
