#include "calcul.h"
#include <stdio.h>
#include <math.h>

#include "sequence_point.h"
/* somme */
Point somme_points(Point A, Point B){
    Point C;
    C.x = A.x + B.x;
    C.y = A.y + B.y;
    return C;
}
/* somme */
Vecteur somme_vecteurs(Vecteur u, Vecteur v){
    Vecteur w;
    w.x = u.x + v.x;
    w.y = u.y + v.y;
    return w;
}

/* vecteur à partir de deux points */
Vecteur vecteur_points(Point A, Point B){
    Vecteur v;
    v.x = B.x - A.x;
    v.y = B.y - A.y;
    return v;
}

/* multiplication par un réel */
Point   mult_point(Point A, double k){
    Point B;
    B.x = A.x * k;
    B.y = A.y * k;
    return B;
}
/* multiplication par un réel */
Vecteur mult_vecteur(Vecteur v, double k){
    Vecteur w;
    w.x = v.x * k;
    w.y = v.y * k;
    return w;
}

/* produit scalaire */
double produit_scalaire(Vecteur u, Vecteur v){
    return u.x * v.x + u.y * v.y;
}

/* norme */
double norme(Vecteur v){
    return sqrt(produit_scalaire(v, v));
}

/* distance entre deux points */
double distance(Point A, Point B){
    Vecteur v = vecteur_points(A, B);
    return norme(v);
}



/*retourne le vecteur normalisé*/
Vecteur normaliser(Vecteur v){
    double n = norme(v);
    Vecteur u;
    if (n == 0){
        u.x = 0.0;
        u.y = 0.0;
    } else {
        u.x = v.x / n;
        u.y = v.y / n;
    }
    return u;
}

Vecteur orthogonal(Vecteur v){
    Vecteur u;
    u.x = -v.y;
    u.y = v.x;
    return u;
}


double distance_point_vecteur(Point P, Point A, Point B){
    Vecteur AB = vecteur_points(A, B);
    Vecteur AP = vecteur_points(A, P);
    double n = norme(AB);
    if (n == 0){
        //printf("Le segment [AB] est réduit à un point.\n");
        return distance(P, A);
    } else {
        double t = produit_scalaire(AP, AB) / (n * n);
        if (t < 0){
            return distance(P, A);
        } else if (t > 1){
            return distance(P, B);
        } else {
            Point C;
            C.x = A.x + t * AB.x;
            C.y = A.y + t * AB.y;
            return distance(P, C);
        }
    }
}