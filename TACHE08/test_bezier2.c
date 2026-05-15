#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "calcul.h"
#include "sequence_point.h"
#include "calcul_contour.h"

int egal_double(double a, double b){
    return fabs(a - b) < 1e-6;
}

int egal_point(Point A, Point B){
    return egal_double(A.x, B.x) && egal_double(A.y, B.y);
}

void afficher_point(char *nom, Point P){
    printf("%s=(%f,%f)\n", nom, P.x, P.y);
}

int main(){
    Tableau_Point T;
    bezier_2 B2;

    T.taille = 10;
    T.tab = malloc(sizeof(Point) * T.taille);
    if (T.tab == NULL){
        printf("erreur allocation\n");
        return 1;
    }

    /* =========================
       Test 1 : cas n = 1
       ========================= */
    printf("cas n==1\n");

    T.tab[0].x = 10.0; T.tab[0].y = 10.0;
    T.tab[1].x = 20.0; T.tab[1].y = 20.0;

    B2 = approx_bezier_2(T, 0, 1);

    printf("valeur de approx_bezier_2 pour les points (10,10) et (20,20)\n");
    afficher_point("B2.c0", B2.c0);
    afficher_point("B2.c1", B2.c1);
    afficher_point("B2.c2", B2.c2);

    printf("valeur par calcul\n");
    Point A0, A1, A2;
    A0 = T.tab[0];
    A1.x = (T.tab[0].x + T.tab[1].x) / 2.0;
    A1.y = (T.tab[0].y + T.tab[1].y) / 2.0;
    A2 = T.tab[1];

    afficher_point("A0", A0);
    afficher_point("A1", A1);
    afficher_point("A2", A2);

    if (egal_point(B2.c0, A0) &&
        egal_point(B2.c1, A1) &&
        egal_point(B2.c2, A2)){
        printf("test n==1 : OK\n\n");
    } else {
        printf("test n==1 : ECHEC\n\n");
    }

    /* =========================
       Test 2 : cas n >= 2
       On prend une vraie Bézier 2
       ========================= */
    printf("cas n>=2\n");

    bezier_2 Q;
    Q.c0.x = 0.0; Q.c0.y = 0.0;
    Q.c1.x = 2.0; Q.c1.y = 4.0;
    Q.c2.x = 6.0; Q.c2.y = 2.0;

    int n = 5;
    T.taille = n + 1;

    for (int i = 0; i <= n; i++){
        double t = (double)i / (double)n;
        T.tab[i] = C_2(Q, t);
    }

    B2 = approx_bezier_2(T, 0, n);

    printf("points de controle attendus\n");
    afficher_point("Q.c0", Q.c0);
    afficher_point("Q.c1", Q.c1);
    afficher_point("Q.c2", Q.c2);

    printf("points de controle obtenus\n");
    afficher_point("B2.c0", B2.c0);
    afficher_point("B2.c1", B2.c1);
    afficher_point("B2.c2", B2.c2);

    if (egal_point(B2.c0, Q.c0) &&
        egal_point(B2.c1, Q.c1) &&
        egal_point(B2.c2, Q.c2)){
        printf("test n>=2 : OK\n\n");
    } else {
        printf("test n>=2 : ECHEC\n\n");
    }

    /* =========================
       Test 3 : exemple du cours
       ========================= */
    printf("cas exemple du cours\n");

    T.taille = 9;

    T.tab[0].x = 0.0; T.tab[0].y = 0.0;
    T.tab[1].x = 1.0; T.tab[1].y = 0.0;
    T.tab[2].x = 1.0; T.tab[2].y = 1.0;
    T.tab[3].x = 1.0; T.tab[3].y = 2.0;
    T.tab[4].x = 2.0; T.tab[4].y = 2.0;
    T.tab[5].x = 3.0; T.tab[5].y = 2.0;
    T.tab[6].x = 3.0; T.tab[6].y = 3.0;
    T.tab[7].x = 4.0; T.tab[7].y = 3.0;
    T.tab[8].x = 5.0; T.tab[8].y = 3.0;

    B2 = approx_bezier_2(T, 0, 8);

    Point C0_cours, C1_cours, C2_cours;
    C0_cours.x = 0.0; C0_cours.y = 0.0;
    C1_cours.x = 2600.0 / 1680.0; C1_cours.y = 4120.0 / 1680.0;
    C2_cours.x = 5.0; C2_cours.y = 3.0;

    printf("valeurs obtenues\n");
    afficher_point("B2.c0", B2.c0);
    afficher_point("B2.c1", B2.c1);
    afficher_point("B2.c2", B2.c2);

    printf("valeurs du cours\n");
    afficher_point("C0_cours", C0_cours);
    afficher_point("C1_cours", C1_cours);
    afficher_point("C2_cours", C2_cours);

    if (egal_point(B2.c0, C0_cours) &&
        egal_point(B2.c1, C1_cours) &&
        egal_point(B2.c2, C2_cours)) {
        printf("test exemple du cours : OK\n");
    } else {
        printf("test exemple du cours : ECHEC\n");
    }

    free(T.tab);
    return 0;
}