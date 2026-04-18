#include <stdio.h>
#include "calcul_contour.h"
#include "sequence_point.h"
#include "image.h"
#include "calcul.h"

#include <stdlib.h>
#include <string.h>
char *nom_eps(const char *nom_pbm, const char *suffixe, int d)
{
    size_t len = strlen(nom_pbm);
    char *base = malloc(len + 1);
    if (!base) return NULL;

    strcpy(base, nom_pbm);

    char *dot = strrchr(base, '.');
    if (dot != NULL)
        *dot = '\0';

    int taille = snprintf(NULL, 0, "%s%s%d.eps", base, suffixe, d) + 1;

    char *nom = malloc(taille);
    if (!nom) {
        free(base);
        return NULL;
    }

    snprintf(nom, taille, "%s%s%d.eps", base, suffixe, d);

    free(base);
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
    printf("calcul des contours\n");
    Ensemble_Contours cont = calcul_contour(img,&nb_contour);  
    
    
    printf(" veuillez entrez la distance seuille\n");
    int d;
    scanf("%d", &d);
     
    FILE *f=NULL;   
    
    char *nom = nom_eps(argv[1], "_fill_d",d);
    
    f = fopen(nom, "w");
    if (f == NULL) {
    printf("Erreur ouverture fichier\n");
    free(nom);
    return 1;
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
    int tl_simpl=0;
    for(int j=0;j<cont.nb;j++){
        //Tableau_Point T = sequence_points_liste_vers_tableau(cont.tab[j]);
        //printf("executer\n");
        Tableau_Point T = sequence_points_liste_vers_tableau(cont.tab[j]);
        supprimer_liste_Point(cont.tab[j]);
        tl_init+=T.taille;
        Liste_bezier_2 contour= simplification_douglas_peucker_bezier2(T, 0, (int)T.taille-1, (double)d);
        tl_simpl+=contour.taille*3-contour.taille;
        free(T.tab);
        nb_bez+=contour.taille;
        
        for(unsigned int k=0;k<contour.taille;k++){
            bezier_2 cont2=contour.bez2[k];
            bezier_3  b=conversion_bezier_2_vers_bezier_3(cont2);
            if( k==0){
                fprintf(f," %f %f  moveto\n",b.c0.x,H-b.c0.y );
            }
            fprintf(f," %f %f %f %f %f %f  curveto\n", b.c1.x,H-b.c1.y, b.c2.x,H-b.c2.y,b.c3.x,H-b.c3.y );

        }
        fprintf(f, "closepath\n");
        free(contour.bez2);

    }
    free(cont.tab);
    fprintf(f, " fill\n");
    fprintf(f, "showpage\n");
    fclose(f);   
    supprimer_image(&img);
    printf(" nombre de contour: %d\n nombre segments de l’image initiale : %d \n Pour d=%d on a:\n nomre de segments de l image simplifiés: %d\n Nombre de bezier %d\n ",nb_contour,tl_init-nb_contour,d,tl_simpl,nb_bez);
return 0;
}