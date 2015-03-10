#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

using namespace std;

//Ressort l'histogramme d'une image couleur ppm
int main(int argc, char* argv[]){
	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille, nR, nG, nB, nbR, nbG, nbB;

	if (argc != 2) {
		printf("Usage: ImageIn.ppm \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;

	OCTET *ImgIn;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

	for(int a = 0; a<256; a++){
		nbR=0;
		nbG=0;
		nbB=0;
		for (int i=0; i < nTaille3; i+=3){
			nR = ImgIn[i];
			nG = ImgIn[i+1];
			nB = ImgIn[i+2];
			if(nR==a){
				nbR++;
			}
			if (nG==a){
				nbG++;
			}
			if (nB==a){
				nbB++;
			}
		}
		cout << a << "\t" << nbR << "\t" << nbG << "\t" << nbB << "\n";
	}
	

	free(ImgIn);
	return 1;
}
/* Afficher sous gnuplot
	plot 'histoBaboon.dat' using 2 with lines lt 1, 'histoBaboon.dat' using 3 with lines lt 2, 'histoBaboon.dat' using 4 with lines lt 3
*/