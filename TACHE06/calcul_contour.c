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
    
    
    for (int i=1; i<=H ; i++){
        for (int j=1; j<=L ; j++){
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
    
    
    
    while(trouver_pixel_depart(I_contour).x!=-1 && trouver_pixel_depart(I_contour).y!=-1){
        Liste_Point p_liste=creer_liste_Point_vide();
        boucle=0;
        Point p=trouver_pixel_depart(I_contour);
        if (p.x<0 || p.y<0){
        
        
        return ensemble;
        } 
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
        ensemble.nb=ensemble.nb+1;
        p_liste=ajouter_element_liste_Point(p_liste,p0);
        ensemble.tab = realloc(ensemble.tab, (ensemble.nb) * sizeof(Liste_Point));
        ensemble.tab[ensemble.nb-1]=p_liste;
       
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

    /* ==== CAS DE BASE ==== */
    if (j2 <= j1 + 1) {
        L = ajouter_element_liste_Point(L, pj1);
        L = ajouter_element_liste_Point(L, pj2);
        return L;
    }

    /* ==== Recherche du point le plus éloigné ==== */
    double dmax = 0.0;
    int k = j1;

    for (int i = j1 + 1; i < j2; i++) {
        double di = distance_point_vecteur(T.tab[i], pj1, pj2);
        if (di > dmax) {
            dmax = di;
            k = i;
        }
    }

    /* ==== Si la distance max est inférieure au seuil ==== */
    if (dmax <= d) {
        L = ajouter_element_liste_Point(L, pj1);
        L = ajouter_element_liste_Point(L, pj2);
        return L;
    }

    /* ==== Sinon : diviser pour régner ==== */
    Liste_Point L1 = simplification_douglas_peucker(T, j1, k, d);
    Liste_Point L2 = simplification_douglas_peucker(T, k, j2, d);

    /* IMPORTANT : enlever le premier point de L2 (doublon Pk) */
    L2 = supprimer_premier_element_liste_Point(L2);

    L = concatener_liste_Point(L1, L2);

    return L;
}