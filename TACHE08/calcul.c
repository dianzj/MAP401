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
Point  C_2(bezier_2 B, double t){
	Point P;
	P.x=(B.c0.x)*(1-t)*(1-t) + 2*(B.c1.x)*(1-t)*t + (B.c2.x)*t*t;
	P.y=(B.c0.y)*(1-t)*(1-t) + 2*(B.c1.y)*(1-t)*t + (B.c2.y)*t*t;  
	return P;
}
Point  C_3(bezier_3 B, double t){
	Point P;
	P.x=(B.c0.x)*(1-t)*(1-t)*(1-t) + 3*(B.c1.x)*(1-t)*(1-t)*t + 3*(B.c2.x)*(1-t)*t*t + (B.c3.x)*t*t*t;
	P.y=(B.c0.y)*(1-t)*(1-t)*(1-t) + 3*(B.c1.y)*(1-t)*(1-t)*t + 3*(B.c2.y)*(1-t)*t*t + (B.c3.y)*t*t*t;
	return P;
}
bezier_3 conversion_bezier_2_vers_bezier_3(bezier_2 B){
	bezier_3 B3;
	B3.c0=B.c0;
	B3.c1.x=(B.c0.x + 2*B.c1.x)/3;
	B3.c1.y=(B.c0.y + 2*B.c1.y)/3;
	B3.c2.x=(2*B.c1.x + B.c2.x)/3;
	B3.c2.y=(2*B.c1.y + B.c2.y)/3;
	B3.c3=B.c2;
	return B3;
}

bezier_2 approx_bezier_2(Tableau_Point T,int j1,int j2){
    bezier_2 B2;
    if(T.taille<2){
        printf("La liste doit contenir au moins 2 points pour approximer une courbe de Bézier de degré 2.\n");
    }
    B2.c0=T.tab[j1];
    B2.c2=T.tab[j2];
    int n = j2 - j1;
    double nd=(double)n;
    if (n==1){
        B2.c1.x=0.5*(B2.c0.x+B2.c2.x);
        B2.c1.y=0.5*(B2.c0.y+B2.c2.y);
    }
    else{
        double alpha=(3*nd)/((nd*nd)-1);
        double beta=(1-2*nd)/(2*(nd+1));
       
        double x=0.0;
        double y=0.0;
        B2.c1.x=beta*(B2.c0.x+B2.c2.x);
        B2.c1.y=beta*(B2.c0.y+B2.c2.y);
        for(int i=j1+1;i<j2;i++){
           x=x+T.tab[i].x;
           y=y+T.tab[i].y;
        }
        
        B2.c1.x=B2.c1.x +x*alpha;
        B2.c1.y=B2.c1.y+y*alpha;


    }
    return B2;
    
}
double distance_point_bezier_2(Point P, bezier_2 B, double t){
    Point C = C_2(B, t);
    return distance(P, C);
}
double distance_point_bezier_3(Point P, bezier_3 B, double t){
    Point C = C_3(B, t);
    return distance(P, C);
}
bezier_3 approx_bezier_3(Tableau_Point T,int j1,int j2){
    bezier_3 B3;
    if(T.taille<2){
        printf("La liste doit contenir au moins 2 points pour approximer une courbe de Bézier de degré 3.\n");
        bezier_3 B3 = {0};
        return B3;

    }
    B3.c0=T.tab[j1];
    B3.c3=T.tab[j2];
    int n = j2 - j1;
    double nd=(double)n;
    if(n==1 || n==2){
        bezier_2 B2=approx_bezier_2(T,j1,j2);
        B3=conversion_bezier_2_vers_bezier_3(B2);
        return B3;
    }

    if(n>=3){
        double num=-15*nd*nd*nd+5*nd*nd+2*nd+4;
        double alpha=num/(3*(nd+2)*(nd*nd*3+1));
        num=10*nd*nd*nd-15*nd*nd+nd+2;
        double beta=num/(3*(nd+2)*(nd*nd*3+1));
        double lambda=70*nd/(3*(nd*nd-1)*(nd*nd-4)*(3*nd*nd+1));
       
        double x1=0.0;
        double y1=0.0;
        double x2=0.0;
        double y2=0.0;
        B3.c1.x=alpha*B3.c0.x+beta*B3.c3.x;
        B3.c1.y=alpha*B3.c0.y+beta*B3.c3.y;
        B3.c2.x=beta*B3.c0.x+alpha*B3.c3.x;
        B3.c2.y=beta*B3.c0.y+alpha*B3.c3.y;
        
        for(int i=j1+1;i<j2;i++){
           double k=(double)(i-j1);
           
           double fi= 6*k*k*k*k - 8*nd*k*k*k + 6*k*k - 4*nd*k + nd*nd*nd*nd-nd*nd;
           x1=x1+lambda*(fi*T.tab[i].x);
           y1=y1+ lambda*(fi*T.tab[i].y);

           k=nd-k;
           fi= 6*k*k*k*k - 8*nd*k*k*k + 6*k*k - 4*nd*k + nd*nd*nd*nd-nd*nd;
           x2=x2+lambda*(fi*T.tab[i].x);
           y2=y2+ lambda*(fi*T.tab[i].y);
        }
        
        B3.c1.x=B3.c1.x +x1;
        B3.c1.y=B3.c1.y+y1;
        B3.c2.x=B3.c2.x +x2;
        B3.c2.y=B3.c2.y+y2;


    }
    return B3;
}