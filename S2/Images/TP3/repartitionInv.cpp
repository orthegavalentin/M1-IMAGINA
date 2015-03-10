#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

//Ressort l'histogramme d'une image pgm
int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	char cNomImgBLue[250], cNomImgBEcrite[250];
	int nH, nW, nHR, nWR, nHB, nWB, nTaille, nTaille2, cPixel, nb, proba;
	float repartition;
	
	if (argc != 5) {
		printf("Usage: ImageIn.pgm ImageBIn.pgm ImageOut.pgm ImageBOut.pgm \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgBLue);
	sscanf (argv[3],"%s",cNomImgEcrite);
	sscanf (argv[4],"%s",cNomImgBEcrite);
	
	OCTET *ImgIn, *ImgBIn, *ImgOut, *ImgBOut;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	nHR = nH;
	nWR = nW;
	lire_nb_lignes_colonnes_image_pgm(cNomImgBLue, &nH, &nW);
	nTaille2 = nH * nW;
	nHB = nH;
	nWB = nW;

	cout << nTaille << " " << nTaille2 << endl;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	allocation_tableau(ImgBIn, OCTET, nTaille2);
	lire_image_pgm(cNomImgLue, ImgIn, nHR * nWR);
	lire_image_pgm(cNomImgBLue, ImgBIn, nHB * nWB);
	allocation_tableau(ImgOut, OCTET, nTaille);
	allocation_tableau(ImgBOut, OCTET, nTaille2);

	proba=nTaille;
	repartition = 0;

	float ddp = 0;

	for(int i = 0; i< 256; i++){
		nb=0;
		for(int j = 0;j<nHR;j++){
			for(int k = 0;k<nWR;k++){
				cPixel = ImgIn[j*nWR+k];
				if(cPixel==i){
					nb++;
				}
			}
		}
		ddp = (float) nb / (float) nTaille;
		proba = proba - nb;
		repartition = (float) proba / (float) nTaille;
		cout << i << " " << ddp << " " << repartition << "\n";


		for(int j = 0;j<nHR;j++){
			for(int k = 0;k<nWR;k++){
				if (ImgIn[j*nWR+k]==i){
					ImgOut[j*nWR+k]= repartition * 255;
				}
			}
		}
		for(int j = 0;j<nHB;j++){
			for(int k = 0;k<nWB;k++){
				if (ImgBIn[j*nWB+k]==i){
					ImgBOut[j*nWB+k]= repartition * 255;
				}
			}
		}

	}
	// for (int i=0; i < nH; i++){
	// 	for (int j=0; j < nW; j++){
	// 		ImgOut[i*nW+j]=ImgIn[i*nW+j];
	// 	}
	// }


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nHR, nWR);
	ecrire_image_pgm(cNomImgBEcrite, ImgBOut,  nHB, nWB);
	free(ImgIn);
	free(ImgBIn);
	return 1;

}
