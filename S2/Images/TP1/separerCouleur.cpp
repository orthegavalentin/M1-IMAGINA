#include <stdio.h>
#include "image_ppm.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]){
	char cNomImgLue[250], cNomImgEcriteR[250], cNomImgEcriteG[250], cNomImgEcriteB[250];
	int nH, nW, nTaille, nR, nG, nB, S;

	if (argc != 5) {
		printf("Usage: ImageIn.ppm ImageOut.ppm R.ppm G.ppm B.ppm \n"); 
		exit (1) ;
	}

	sscanf (argv[1],"%s",cNomImgLue) ;
	sscanf (argv[2],"%s",cNomImgEcriteR);
	sscanf (argv[3],"%s",cNomImgEcriteG);
	sscanf (argv[4],"%s",cNomImgEcriteB);

	OCTET *ImgIn, *ImgOutR, *ImgOutG, *ImgOutB;

	lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	int nTaille3 = nTaille * 3;
	allocation_tableau(ImgIn, OCTET, nTaille3);
	lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOutR, OCTET, nTaille3);
	allocation_tableau(ImgOutG, OCTET, nTaille3);
	allocation_tableau(ImgOutB, OCTET, nTaille3);

	for (int i=0; i < nTaille3; i+=3){
		nR = ImgIn[i];
		nG = ImgIn[i+1];
		nB = ImgIn[i+2];
		ImgOutR[i]=nR;
		ImgOutR[i+1]=0; 
		ImgOutR[i+2]=0;
		ImgOutG[i]=0;
		ImgOutG[i+1]=nG; 
		ImgOutG[i+2]=0;
		ImgOutB[i]=0;
		ImgOutB[i+1]=0;
		ImgOutB[i+2]=nB;
	}

	ecrire_image_ppm(cNomImgEcriteR, ImgOutR,  nH, nW);
	ecrire_image_ppm(cNomImgEcriteG, ImgOutG,  nH, nW);
	ecrire_image_ppm(cNomImgEcriteB, ImgOutB,  nH, nW);
	free(ImgIn);
	return 1;
}
