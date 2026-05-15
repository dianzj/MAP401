#include <stdlib.h> /* utilisation des fonctions malloc et free */
#include <stdio.h>  /* utilisation des fonctions printf et fprintf */
#include "sequence_point.h"
#include "calcul_contour.h"
#include "image.h"
#include "calcul.h"
Point trouver_pixel_depart(Image I){
    UINT i, j;
    UINT L=largeur_image(I);
    UINT H=hauteur_image(I);
    Point p={-1,-1};
    int trouve=0;
    for (i=1; i<=H && trouve==0; i++){
        for (j=1; j<=L && trouve==0; j++){
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i-1) == BLANC){

                p.x=j;
                p.y=i;
                trouve=1;
            }
        }
    }
    return p;
}
Point avancer(Point p0, Orientation orient)
{
    switch (orient) {
        case Est:   p0.x += 1; break;
        case Ouest: p0.x -= 1; break;
        case Nord:  p0.y -= 1; break;
        case Sud:   p0.y += 1; break;
    }
    return p0;
}

Pixel valeur_pixel_gauche(Image I, Point p0, Orientation orient)
{
    int x = (int)p0.x;
    int y = (int)p0.y;

    switch (orient) {
        case Est:   return get_pixel_image(I, x+1, y);     // NE
        case Ouest: return get_pixel_image(I, x,   y+1);   // SW
        case Nord:  return get_pixel_image(I, x,   y);     // NW
        case Sud:   return get_pixel_image(I, x+1, y+1);   // SE
    }
    return BLANC;
}

Pixel valeur_pixel_droite(Image I, Point p0, Orientation orient)
{
    int x = (int)p0.x;
    int y = (int)p0.y;

    switch (orient) {
        case Est:   return get_pixel_image(I, x+1, y+1);   // SE
        case Ouest: return get_pixel_image(I, x,   y);     // NW
        case Nord:  return get_pixel_image(I, x+1, y);     // NE
        case Sud:   return get_pixel_image(I, x,   y+1);   // SW
    }
    return BLANC;
}


Orientation sens(Image I, Point p0, Orientation orient){
    Pixel p_pixel_d=valeur_pixel_droite(I,p0,orient);
    Pixel p_pixel_g=valeur_pixel_gauche(I,p0,orient);
    if (p_pixel_g==NOIR) {
        switch (orient)
        {
        case Est:
            orient=Nord;
            break;
        case Ouest:
            orient=Sud;
            break;
        case Nord:
            orient=Ouest;
            break;
        case Sud:
            orient=Est;
            break;             
               
        
        default:
            break;
        }
    } else if (p_pixel_d==BLANC)
    {
        switch (orient)
        {
        case Est:
            orient=Sud;
            break;
        case Ouest:
            orient=Nord;
            break;
        case Nord:
            orient=Est;
            break;
        case Sud:
            orient=Ouest;
            break;             
               
        
        default:
            break;
        }
    }
    return orient;
}
Image creer_image_contour(Image I){
    UINT L=largeur_image(I);
    UINT H=hauteur_image(I);
    Image I_contour=creer_image(L,H);
    
    
    for (unsigned int i=1; i<=H ; i++){
        for (unsigned int j=1; j<=L ; j++){
            if (get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i-1) == BLANC){
                set_pixel_image(I_contour, j, i, NOIR);               
            }
        }
    }
    return I_contour;
}
void supprimer_ensemble_contours(Ensemble_Contours *ensemble){
    for (int i = 0; i < ensemble->nb; i++){
        supprimer_liste_Point(ensemble->tab[i]);
    }
    free(ensemble->tab);
}
Ensemble_Contours calcul_contour(Image I,int *nb_contour){
    Image I_contour=creer_image_contour(I);
    *nb_contour=0;
    int boucle=0;
    Ensemble_Contours ensemble;
    ensemble.nb=0;
    ensemble.tab = NULL;
    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);
    int capacite = 8;
    ensemble.tab = malloc(capacite * sizeof(Liste_Point));
    if (ensemble.tab == NULL){
        supprimer_image(&I_contour);
        *nb_contour = 0;
        return ensemble;
    }
    Point p={-1,-1};
    //Point p=trouver_pixel_depart(I_contour);
    for (UINT i=1; i<=H ; i++){
        for (UINT j=1; j<=L; j++){
            if (get_pixel_image(I_contour, j, i) == NOIR && get_pixel_image(I_contour, j, i-1) == BLANC){
                Liste_Point p_liste=creer_liste_Point_vide();
                boucle=0;
                p.x=j;
                p.y=i;
                
                Orientation orient=Est;
                Point p0;
                p0.x=p.x-1;
                p0.y=p.y-1;
                
                while (boucle==0){
                    
                    
                    p_liste=ajouter_element_liste_Point(p_liste,p0);
                    
                    set_pixel_image(I_contour, p0.x+1, p0.y+1, BLANC);
                    
                    p0 = avancer(p0, orient);
                    
                    
                    orient = sens(I, p0, orient);
                    
                    if (p0.x == p.x-1 && p0.y == p.y-1 && orient == Est) {
                        boucle = 1;
                    }    
            
            
                
                }
                
                //ensemble.nb=ensemble.nb+1;
                p_liste=ajouter_element_liste_Point(p_liste,p0);
                if (ensemble.nb == capacite){
                    capacite *= 2;
                    Liste_Point *tmp = realloc(ensemble.tab, capacite * sizeof(Liste_Point));
                    if (tmp == NULL){
                        supprimer_liste_Point(p_liste);
                        supprimer_ensemble_contours(&ensemble);
                        supprimer_image(&I_contour);
                        *nb_contour = 0;
                        return ensemble;
                    }
                    ensemble.tab = tmp;
                }
                
                ensemble.tab[ensemble.nb]=p_liste;
                ensemble.nb++;
                
            }//if get_pixel_image(I, j, i) == NOIR && get_pixel_image(I, j, i-1) == BLANC
       
        }
    }
    *nb_contour=ensemble.nb;
    
    supprimer_image(&I_contour);
    return ensemble;
}




void sauver_image_pbm(Image I, const char *nom_f)
{
    FILE *f = fopen(nom_f, "w");
    if (f == NULL) ERREUR_FATALE("sauver_image_pbm : ouverture impossible\n");

    UINT L = largeur_image(I);
    UINT H = hauteur_image(I);

    fprintf(f, "P1\n");
    fprintf(f, "%u %u\n", L, H);

    for (UINT y = 1; y <= H; y++) {
        for (UINT x = 1; x <= L; x++) {
            Pixel p = get_pixel_image(I, (int)x, (int)y);
            fprintf(f, "%d ", (p == NOIR) ? 1 : 0);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}

Liste_Point simplification_douglas_peucker(Tableau_Point T,int j1,int j2,double d)
{
    Liste_Point L = creer_liste_Point_vide();

    Point pj1 = T.tab[j1];
    Point pj2 = T.tab[j2];

    
    if (j2 <= j1 + 1) {
        L = ajouter_element_liste_Point(L, pj1);
        L = ajouter_element_liste_Point(L, pj2);
        return L;
    }

    
    double dmax = 0.0;
    int k = j1;

    for (int i = j1 + 1; i < j2; i++) {
        double di = distance_point_vecteur(T.tab[i], pj1, pj2);
        if (di > dmax) {
            dmax = di;
            k = i;
        }
    }

    
    if (dmax <= d) {
        L = ajouter_element_liste_Point(L, pj1);
        L = ajouter_element_liste_Point(L, pj2);
        return L;
    }
    
    Liste_Point L1 = simplification_douglas_peucker(T, j1, k, d);
    Liste_Point L2 = simplification_douglas_peucker(T, k, j2, d);


    L2 = supprimer_premier_element_liste_Point(L2);

    L = concatener_liste_Point(L1, L2);

    return L;
}
Liste_bezier_2 simplification_douglas_peucker_bezier2(Tableau_Point T,int j1,int j2,double d) {
    int n=j2-j1;
    if (T.tab == NULL || j1 < 0 || j2 < 0 || j1 >= (int)T.taille || j2 >= (int)T.taille || j1 >= j2) {
        printf("simplification_douglas_peucker_bezier2 : indices invalides\n");
        Liste_bezier_2 Lb;
        Lb.taille=0;
        Lb.bez2=NULL;
        return Lb;
    }
    bezier_2 B;
    
    B=approx_bezier_2(T,j1,j2);
    double dmax=0.0;
    int k=j1;
    
    for (int j=j1+1;j<j2;j++){
        int i=j-j1;
        double t=(double)i/(double)n;
        double dj=distance_point_bezier_2(T.tab[j], B, t);
        if (dj>dmax){
            dmax=dj;
            k=j;
        }
           
    }
    if(dmax<=d){
        Liste_bezier_2 Lb;
        Lb.taille=1;
        Lb.bez2=malloc(sizeof(bezier_2));
        Lb.bez2[0]=B;
        return Lb;
    }
    else{
        Liste_bezier_2 Lb1=simplification_douglas_peucker_bezier2(T, j1, k, d);
        Liste_bezier_2 Lb2=simplification_douglas_peucker_bezier2(T, k, j2, d);
        Liste_bezier_2 Lb;
        Lb.taille=Lb1.taille+Lb2.taille;
        Lb.bez2=malloc(Lb.taille*sizeof(bezier_2));
        for (unsigned int i=0;i<Lb1.taille;i++){
            Lb.bez2[i]=Lb1.bez2[i];
        }
        for (unsigned int i=0;i<Lb2.taille;i++){
            Lb.bez2[Lb1.taille+i]=Lb2.bez2[i];
        }
        free(Lb1.bez2);
        free(Lb2.bez2);
        return Lb;
    }
}

Liste_bezier_3 simplification_douglas_peucker_bezier3(Tableau_Point T,int j1,int j2,double d) {
    int n=j2-j1;
    if (T.tab == NULL || j1 < 0 || j2 < 0 || j1 >= (int)T.taille || j2 >= (int)T.taille || j1 >= j2) {
        printf("simplification_douglas_peucker_bezier3 : indices invalides\n");
        Liste_bezier_3 Lb;
        Lb.taille=0;
        Lb.bez3=NULL;
        return Lb;
    }
    bezier_3 B;
    
    B=approx_bezier_3(T,j1,j2);
    double dmax=0.0;
    int k=j1;
    
    for (int j=j1+1;j<j2;j++){
        int i=j-j1;
        double t=(double)i/(double)n;
        double dj=distance_point_bezier_3(T.tab[j], B, t);
        if (dj>dmax){
            dmax=dj;
            k=j;
        }
           
    }
    if(dmax<=d){
        Liste_bezier_3 Lb;
        Lb.taille=1;
        Lb.bez3=malloc(sizeof(bezier_3));
        Lb.bez3[0]=B;
        return Lb;
    }
    else{
        Liste_bezier_3 Lb1=simplification_douglas_peucker_bezier3(T, j1, k, d);
        Liste_bezier_3 Lb2=simplification_douglas_peucker_bezier3(T, k, j2, d);
        Liste_bezier_3 Lb;
        Lb.taille=Lb1.taille+Lb2.taille;
        Lb.bez3=malloc(Lb.taille*sizeof(bezier_3));
        for (unsigned int i=0;i<Lb1.taille;i++){
            Lb.bez3[i]=Lb1.bez3[i];
        }
        for (unsigned int i=0;i<Lb2.taille;i++){
            Lb.bez3[Lb1.taille+i]=Lb2.bez3[i];
        }
        free(Lb1.bez3);
        free(Lb2.bez3);
        return Lb;
    }
}