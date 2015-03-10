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

	int aR = 0;
	int bR = 255;
	int aG = 0;
	int bG = 255;
	int aB = 0;
	int bB = 255;
	bool picR = false;
	bool bTrouveR = false;
	bool picG = false;
	bool bTrouveG = false;
	bool picB = false;
	bool bTrouveB = false;
	
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
		if(nbR != 0){
			picR = true;
		}
		if(nbR == 0 && !picR){
			aR=i+1;
		} else if (nbR == 0 && picR && !bTrouveR){
			bR=i-1;
			bTrouveR = true;
		}

		if(nbG != 0){
			picG = true;
		}
		if(nbG == 0 && !picG){
			aG=i+1;
		} else if (nbG == 0 && picG && !bTrouveG){
			bG=i-1;
			bTrouveG = true;
		}

		if(nbB != 0){
			picB = true;
		}
		if(nbB == 0 && !picB){
			aB=i+1;
		} else if (nbB == 0 && picB && !bTrouveB){
			bB=i-1;
			bTrouveB = true;
		}
	}

	for (int i=0; i < nTaille3; i+=3){
		ImgOut[i]=(255*(ImgIn[i] - aR))/(bR-aR);
		ImgOut[i+1]=(255*(ImgIn[i+1] - aG))/(bG-aG);
		ImgOut[i+2]=(255*(ImgIn[i+2] - aB))/(bB-aB);
	}

	cout << "aR : " << aR << ", bR : " << bR << endl;
	cout << "aG : " << aG << ", bG : " << bG << endl;
	cout << "aB : " << aB << ", bB : " << bB << endl;


	ecrire_image_ppm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
