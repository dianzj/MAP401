#ifndef CALCUL_H_
#define CALCUL_H_

/* ===== Types ===== */

typedef struct {
    double x;
    double y;
} Point;

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

#endif
