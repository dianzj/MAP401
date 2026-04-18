#include <stdio.h>
#include "calcul_contour.h"
#include "sequence_point.h"
#include "image.h"
#include "calcul.h"

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
    int nb_contour = 0;
    
    Image img = lire_fichier_image(argv[1]); 
    
    
    //Liste_Point contour = calcul_contour(img,nb_contour,1);
    
    //Tableau_Point T = sequence_points_liste_vers_tableau(contour);
    //supprimer_liste_Point(contour);
    
    //free(T.tab);
    //Ensemble_Contours contour_simplifie;
    Ensemble_Contours cont = calcul_contour(img,&nb_contour);  
    for(int i = 0; i < 2; i++) {
    
    
    FILE *f=NULL;   
    if(i==0){
        char *nom = nom_eps(argv[1], "_fill_d1.eps");
        f = fopen(nom, "w");
        free(nom);}
    else if(i==1){
        char *nom = nom_eps(argv[1], "_fill_d2.eps");
        f = fopen(nom, "w");
        free(nom);
    }
    int L = largeur_image(img);
    int H = hauteur_image(img); 
    int taille=0; 
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0  %d %d\n", L,H);
    
    fprintf(f, "0 setlinewidth\n");
    for(int j=0;j<cont.nb;j++){
        Tableau_Point T = sequence_points_liste_vers_tableau(cont.tab[j]);
        Liste_Point contour= simplification_douglas_peucker(T, 0, (int)T.taille-1, (double)i+1);
        free(T.tab);
        taille+=contour.taille;
        Cellule_Liste_Point *el = contour.first;
        
        

        fprintf(f," %f %f  moveto\n", el->data.x ,H- el->data.y );
        //double x0=el->data.x ;
        //double y0=H-el->data.y;

        while(el->suiv != NULL)
        {   
            
            el = el->suiv;
            fprintf(f, " %f %f  lineto\n",el->data.x,H-el->data.y);
            }
            fprintf(f, "closepath\n");

            
        
    //ecrire_contour(contour,*nb_contour);
    
    
    
    supprimer_liste_Point(contour);
    }
    
    fprintf(f, " fill\n");
    fprintf(f, "showpage\n");
    fclose(f);
      
    printf("Pour d=%d on a:\n Nombre de point :%d\n Nombre de contours : %d\n Nombre de segments : %d\n",i+1, taille, nb_contour, taille-nb_contour);    
        }  
    supprimer_ensemble_contours(&cont);
    supprimer_image(&img);
    
    return 0;
}