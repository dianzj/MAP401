#include <stdio.h>
#include "image.h"
int main(int argc, char *argv[])
{
    
    if(argc != 2) {
        printf("Usage: %s <image_file.pbm>\n", argv[0]);
        return 1;
    }
    Image img = lire_fichier_image(argv[1]);
    ecrire_image(img);
    printf("\nNegatif de l'image:\n");
    Image neg_img = negatif_image(img);
    ecrire_image(neg_img);
    printf("\n");
    supprimer_image(&neg_img);
    
    return 0;
}
