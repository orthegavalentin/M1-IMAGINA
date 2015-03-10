#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

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
	allocation_tableau(ImgOut, OCTET, nTaille3);




	for (int i=0; i < nTaille3; i+=3){
		ImgOut[i]=(float) (ImgIn[i]+ImgIn[i+3]+ImgIn[i-3]+ImgIn[i+(nW*3)]+ImgIn[i-(nW*3)]+ImgIn[i+(nW*3)-3]+ImgIn[i+(nW*3)+3]+ImgIn[i-(nW*3)+3]+ImgIn[i-(nW*3)-3])/9;
		ImgOut[i+1]=(float) (ImgIn[i+1]+ImgIn[i+4]+ImgIn[i-2]+ImgIn[i+(nW*3)+1]+ImgIn[i-(nW*3)+1]+ImgIn[i+(nW*3)-2]+ImgIn[i+(nW*3)+4]+ImgIn[i-(nW*3)+4]+ImgIn[i-(nW*3)-2])/9;
		ImgOut[i+2]=(float) (ImgIn[i+2]+ImgIn[i+5]+ImgIn[i-1]+ImgIn[i+(nW*3)+2]+ImgIn[i-(nW*3)+2]+ImgIn[i+(nW*3)-1]+ImgIn[i+(nW*3)+5]+ImgIn[i-(nW*3)+5]+ImgIn[i-(nW*3)-1])/9;
	}

	ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
}

