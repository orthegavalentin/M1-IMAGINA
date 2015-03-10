#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

//Ressort l'histogramme d'une image pgm
int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille, nR, nG, nB, nbR, nbG, nbB;
	
	if (argc != 3) {
		printf("Usage: ImageIn.ppm ImageOut.ppm \n"); 
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

	int aR = 14;
	int bR = 186;
	int aG = 9;
	int bG = 168;
	int aB = 7;
	int bB = 176;
	
	for(int i = 0; i< 256; i++){
		nbR=0;
		nbG=0;
		nbB=0;
		for(int j=0; j < nTaille3; j+=3){
			nR = ImgIn[j];
			nG = ImgIn[j+1];
			nB = ImgIn[j+2];
			if(nR==i){
				nbR++;
			}if(nG==i){
				nbG++;
			}if(nB==i){
				nbB++;
			}
		}
	}

	for(int j=0; j < nTaille3; j+=3){
		if(ImgIn[j] < aR){
			ImgOut[j] = aR;
		}
		else if (ImgIn[j] > bR){
			ImgOut[j] = bR;
		}
		else{
			ImgOut[j] = ImgIn[j];
		}
		if(ImgIn[j+1] < aG){
			ImgOut[j+1] = aG;
		}
		else if (ImgIn[j+1] > bG){
			ImgOut[j+1] = bG;
		}
		else{
			ImgOut[j+1] = ImgIn[j+1];
		}
		if(ImgIn[j+2] < aB){
			ImgOut[j+2] = aB;
		}
		else if (ImgIn[j+2] > bB){
			ImgOut[j+2] = bB;
		}
		else{
			ImgOut[j+2] = ImgIn[j+2];
		}
	}


	// for (int i=0; i < nTaille3; i+=3){
	// 	ImgOut[i]=(255*ImgIn[i] - aR)/(bR-aR);
	// 	ImgOut[i+1]=(255*ImgIn[i+1] - aG)/(bG-aG);
	// 	ImgOut[i+2]=(255*ImgIn[i+2] - aB)/(bB-aB);
	// }


	ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
