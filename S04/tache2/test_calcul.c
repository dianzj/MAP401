#include "calcul.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(void)
{
    srand(time(NULL));

    Point A, B;
    Vecteur u, v;

    for (int k = 1; k <= 10; k++) {

        /* generation aleatoire */
        A.x = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        A.y = ((double)rand() / RAND_MAX) * 20.0 - 10.0;

        B.x = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        B.y = ((double)rand() / RAND_MAX) * 20.0 - 10.0;

        u.x = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        u.y = ((double)rand() / RAND_MAX) * 20.0 - 10.0;

        v.x = ((double)rand() / RAND_MAX) * 20.0 - 10.0;
        v.y = ((double)rand() / RAND_MAX) * 20.0 - 10.0;

        printf("===== GENERATION %d =====\n", k);

        printf("A = (%.2f , %.2f)\n", A.x, A.y);
        printf("B = (%.2f , %.2f)\n", B.x, B.y);

        printf("u = (%.2f , %.2f)\n", u.x, u.y);
        printf("v = (%.2f , %.2f)\n\n", v.x, v.y);

        printf("A + B = (%.2f , %.2f)\n",
               somme_points(A, B).x,
               somme_points(A, B).y);

        printf("u + v = (%.2f , %.2f)\n",
               somme_vecteurs(u, v).x,
               somme_vecteurs(u, v).y);

        printf("vecteur AB = (%.2f , %.2f)\n",
               vecteur_points(A, B).x,
               vecteur_points(A, B).y);

        printf("2.5 * A = (%.2f , %.2f)\n",
               mult_point(A, 2.5).x,
               mult_point(A, 2.5).y);

        printf("-3 * u = (%.2f , %.2f)\n",
               mult_vecteur(u, -3.0).x,
               mult_vecteur(u, -3.0).y);

        printf("u · v = %.2f\n", produit_scalaire(u, v));
        printf("||u|| = %.2f\n", norme(u));
        printf("distance(A,B) = %.2f\n", distance(A, B));

        printf("normaliser(u) = (%.4f , %.4f)\n",
               normaliser(u).x,
               normaliser(u).y);

        printf("orthogonal(u) = (%.2f , %.2f)\n\n",
               orthogonal(u).x,
               orthogonal(u).y);
    }

    return 0;
}
