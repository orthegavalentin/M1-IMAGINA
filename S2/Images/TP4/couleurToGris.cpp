#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

int moyenne(int R, int V, int B){
	return (R+V+B)/3;
}

//convertit un image ppm (couleur) en pgm (gris)
int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille;
	
	if (argc != 3) {
		printf("Usage: ImageIn.ppm ImageOut.pgm \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);


	for (int i=0; i < nTaille; i++){
		ImgOut[i]= moyenne(ImgIn[i*3], ImgIn[(i*3)+1], ImgIn[(i*3)+2]);
	}


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
}

