#include <stdio.h>
#include <iostream>
#include <string>
#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]){

	char cNomImgLue[250];
	int nH, nW, nTaille;

	// if (argc != 2) {
	// 	printf("Usage: ImageIn.pgm \n"); 
	// 	exit (1) ;
	// }

	sscanf (argv[1],"%s",cNomImgLue);

	OCTET *ImgIn;

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

	int somme=0;
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			somme+=ImgIn[i*nW+j];
		}
	}
	cout << somme/nTaille << endl;
	
	free(ImgIn);
	return 1;
}