#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille;
	
	if (argc != 3) {
		printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	OCTET *ImgIn, *ImgOut, *ImgInt;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgInt, OCTET, nTaille);

	int seuil = 20;
	bool tab[nTaille];
	int nbPixels=0;
	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if(ImgIn[i*nW+j]<seuil){
				tab[i*nW+j]=true;		//pixel noir
			}
			else{
				tab[i*nW+j]=false;
			}
		}
	}


	for (int i=0; i < nH; i++){
		for (int j=0; j < nW; j++){
			if(tab[i*nW+j]){
				if(tab[(i-1)*nW+j]==false){
					ImgOut[i*nW+j]=(ImgIn[(i-1)*nW+j+1]+ImgIn[(i-1)*nW+j]+ImgIn[(i-1)*nW+j-1])/3;
				} else if(tab[(i-+1)*nW+j]==false){
					ImgOut[i*nW+j]=(ImgIn[(i+1)*nW+j+1]+ImgIn[(i+1)*nW+j]+ImgIn[(i+1)*nW+j-1])/3;
				} else if(tab[i*nW+j-1]==false){
					ImgOut[i*nW+j]=(ImgIn[(i+1)*nW+j-1]+ImgIn[i*nW+j-1]+ImgIn[(i-1)*nW+j-1])/3;
				} else if(tab[i*nW+j+1]==false){
					ImgOut[i*nW+j]=(ImgIn[(i+1)*nW+j+1]+ImgIn[i*nW+j+1]+ImgIn[(i-1)*nW+j+1])/3;
				}
			}else{
				ImgOut[i*nW+j]=ImgIn[i*nW+j];
			}
		}
	}


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
