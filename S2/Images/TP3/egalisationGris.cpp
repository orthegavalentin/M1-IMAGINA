#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

//Ressort l'histogramme d'une image pgm
int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille, cPixel, nb, proba;
	float repartition;
	
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

	proba=0;
	repartition = 0;

	float ddp = 0;

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
		ddp = (float) nb / (float) nTaille;
		proba = proba + nb;
		repartition = (float) proba / (float) nTaille;
		cout << i << " " << ddp << " " << repartition << "\n";


		for(int j = 0;j<nH;j++){
			for(int k = 0;k<nW;k++){
				if (ImgIn[j*nW+k]==i){
					ImgOut[j*nW+k]= repartition * 255;					
				}
			}
		}
	}

	// for (int i=0; i < nH; i++){
	// 	for (int j=0; j < nW; j++){
	// 		ImgOut[i*nW+j]=ImgIn[i*nW+j];
	// 	}
	// }


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
