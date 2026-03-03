#include "calcul.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void input_point(const char* name, Point* p) {
    printf("Entrez les coordonnées du point %s (x y) : ", name);
    scanf("%lf %lf", &p->x, &p->y);
}
int main() {
    Point A, B, P;
    input_point("A", &A);
    input_point("B", &B);
    input_point("P", &P);
    double d = distance_point_vecteur(P, A, B);
    printf("Distance entre le point P et le segment [AB] : %f\n", d);
    return 0;
}