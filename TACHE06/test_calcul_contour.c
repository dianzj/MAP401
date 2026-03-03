#include <stdio.h>
#include "calcul_contour.h"
#include "sequence_point.h"
#include "image.h"
#include <stdlib.h>
#include <string.h>
char *nom_eps(const char *nom_pbm, const char *suffixe)
{
    char *nom = malloc(strlen(nom_pbm) + 20);
    if (!nom) return NULL;

    strcpy(nom, nom_pbm);

    char *dot = strrchr(nom, '.');
    if (dot != NULL)
        *dot = '\0';   // supprime ".pbm"

    strcat(nom, suffixe); // "_fill.eps" ou "_stroke.eps"
    return nom;
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Usage: %s <image_file.pbm>\n", argv[0]);
        return 1;
    }
    int *nb_contour = malloc(sizeof(int));
    *nb_contour = 0;
    Image img = lire_fichier_image(argv[1]);
    
    
    Liste_Point contour = calcul_contour(img,nb_contour);
    
    for(int i = 0; i < 2; i++) {
     FILE *f=NULL;   
    if(i==0){
        char *nom = nom_eps(argv[1], "_fill.eps");
        f = fopen(nom, "w");
        free(nom);}
    else if(i==1){
        char *nom = nom_eps(argv[1], "_stroke.eps");
        f = fopen(nom, "w");
        free(nom);
    }
    int L = largeur_image(img);
    int H = hauteur_image(img);  
    
    Cellule_Liste_Point *el = contour.first;
    double x=el->data.x ;
    double y=el->data.y; 
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0  %d %d\n", L,H);
  
    fprintf(f, "0 setlinewidth\n");

    fprintf(f," %f %f  moveto\n", el->data.x ,H- el->data.y );
    double x0=el->data.x ;
    double y0=H-el->data.y;

    while(el->suiv != NULL)
    {   
        
        el = el->suiv;
        x=el->data.x;
        y=H-el->data.y;
       
        if(x==x0 && y==y0 && el->suiv != NULL){
            x0=el->suiv->data.x ;
            y0=H-el->suiv->data.y;
            fprintf(f, " %f %f  moveto\n", x0,y0);
            el=el->suiv;
        }
        else{
            fprintf(f, " %f %f  lineto\n", x,y);}
         
    }
    if(i==0){
        fprintf(f, " fill\n");
        fprintf(f, "showpage\n");
        fclose(f);}
    else if(i==1){
    fprintf(f, " stroke\n");
    fprintf(f, "showpage\n");
    fclose(f);}
    }
      
    ecrire_contour(contour,*nb_contour);
    
    supprimer_liste_Point(contour);
    supprimer_image(&img);
    free(nb_contour);
    return 0;
}