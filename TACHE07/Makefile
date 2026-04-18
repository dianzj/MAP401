#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2024/2025
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond � toutes les d�pendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commancant par @ n'est pas affichee a l'ecran)
#############################################################################


#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'�dition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES =   ecr_im_bezier2 test_bezier3


#############################################################################
# definition des regles
#############################################################################

########################################################
# la r�gle par d�faut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation separee de la forme
#	module.o : module.c module.h
#		$(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation separee de modules
# n'ayant pas de fichier .h ET/OU dependant d'autres modules

calcul_contour.o: calcul_contour.c calcul_contour.h sequence_point.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<	
image.o : image.c image.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<	
calcul.o : calcul.c calcul.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module calcul"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<		

ecr_im_bezier2.o : ecr_im_bezier2.c calcul.h image.h sequence_point.h calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<
test_bezier3.o : test_bezier3.c calcul.h image.h sequence_point.h calcul_contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<	
########################################################
# regles explicites de creation des executables


ecr_im_bezier2: ecr_im_bezier2.o calcul.o image.o sequence_point.o calcul_contour.o
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)
test_bezier3: test_bezier3.o calcul.o image.o sequence_point.o calcul_contour.o
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) -o $@ $^ $(LDOPTS)
# regle pour "nettoyer" le r�pertoire
clean:
	rm -fR $(EXECUTABLES) *.o 
