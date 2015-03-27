#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

//Ressort l'histogramme d'une image pgm
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

	int seuil = 10;
	// int nbPixelNoir = 0;
	// bool pixelNoir = true;

	//while(pixelNoir == true){
		//nbPixelNoir = 0;
		for (int i=0; i < nH; i++){
			for (int j=0; j < nW; j++){
				if(ImgIn[i*nW+j]<seuil){
					int somme = 0;
					//nbPixelNoir++;
					somme += (int)ImgIn[i*nW+j+1];
					somme += (int)ImgIn[i*nW+j-1];
					somme += (int)ImgIn[(i-1)*nW+j];
					somme += (int)ImgIn[(i+1)*nW+j];
					if(somme != 0){
						int moyenne = somme / 4;
						ImgOut[i*nW+j]=moyenne;
					}
				}
				else{
					ImgOut[i*nW+j]=ImgIn[i*nW+j];			
				}
			}
		}
		// if (nbPixelNoir > 0){
		// 	pixelNoir = true;
		// }
		// else{
		// 	pixelNoir = false;
		// }
	//}


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
