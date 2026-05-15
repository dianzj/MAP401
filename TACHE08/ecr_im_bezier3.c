#include <stdio.h>
#include "calcul_contour.h"
#include "sequence_point.h"
#include "image.h"
#include "calcul.h"
#include "ecrire_eps.h"
#include <stdlib.h>
#include <string.h>

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
    printf("calcul des contours\n");
    Ensemble_Contours cont = calcul_contour(img,&nb_contour);  
    
    
    printf(" veuillez entrez la distance seuille\n");
    int d;
    scanf("%d", &d);
     
    FILE *f=NULL;   
    
    char *nom = nom_eps(argv[1], "_bez3_fill_d",d);
    
    f = fopen(nom, "w");
    if (f == NULL) {
        printf("Erreur ouverture fichier\n");
        free(nom);
        return 1;
        supprimer_ensemble_contours(&cont);
        supprimer_image(&img);
    }
    
    free(nom);
    
    int L = largeur_image(img);
    int H = hauteur_image(img); 
    
    fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
    fprintf(f, "%%%%BoundingBox: 0 0  %d %d\n", L,H);
    
    fprintf(f, "0 setlinewidth\n");
    //int taille=0;
    int nb_bez=0;
    int tl_init=0;
    //int tl_simpl=0;
    for(int j=0;j<cont.nb;j++){
        //Tableau_Point T = sequence_points_liste_vers_tableau(cont.tab[j]);
        //printf("executer\n");
        Tableau_Point T = sequence_points_liste_vers_tableau(cont.tab[j]);
        supprimer_liste_Point(cont.tab[j]);
        tl_init+=T.taille;
        Liste_bezier_3 contour= simplification_douglas_peucker_bezier3(T, 0, (int)T.taille-1, (double)d);
        //tl_simpl+=contour.taille;
        free(T.tab);
        nb_bez+=contour.taille;
        
        ecrire_contour_bezier3_eps(contour, f, H);
        free(contour.bez3);

    }
    free(cont.tab);
    fprintf(f, " fill\n");
    fprintf(f, "showpage\n");
    fclose(f);   
    supprimer_image(&img);
    printf(" nombre de contour: %d\n nombre segments de l’image initiale : %d \n Pour d=%d on a:\n %d bezier\n ",nb_contour,tl_init-nb_contour,d,nb_bez);
return 0;
}