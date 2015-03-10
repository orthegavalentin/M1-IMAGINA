#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

//Ressort l'histogramme d'une image pgm
int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille, cPixel, nb;
	
	if (argc != 3) {
		printf("Usage: ImageIn.pgm ImageOut.pgm \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgEcrite);
	
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);

	int a = 0;
	int b = 255;
	bool pic = false;
	bool bTrouve = false;
	
	for(int i = 0; i< 256; i++){
		nb=0;
		for(int j = 0;j<nH;j++){
			for(int k = 0;k<nW;k++){
				cPixel = ImgIn[j*nW+k];
				if(cPixel==i){
					nb++;
				}
			}	
		}
		if(nb != 0){
			pic = true;
		}
		if(nb == 0 && !pic){
			a=i;
		} else if (nb == 0 && pic && !bTrouve){
			b=i-1;
			bTrouve = true;
		}
	}

	for(int j = 0;j<nH;j++){
		for(int k = 0;k<nW;k++){
			ImgOut[j*nW+k]=(255*ImgIn[j*nW+k] - a)/(b-a);
		}
	}

	cout << "a : " << a << ", b : " << b << endl;


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
