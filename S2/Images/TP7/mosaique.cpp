#include <stdio.h>
#include <iostream>
#include <string>
#include "image_ppm.h"

using namespace std;

int moyenneImg(OCTET *Img){
	int somme=0;
	for (int i=0; i < 8; i++){
		for (int j=0; j < 8; j++){
			somme+=Img[i*8+j];
		}
	}
	return somme/64;
}

void drawCarre(OCTET *ImgOut, int xHG, int yHG, int taille, int couleur){
	for(int i=xHG; i< xHG+taille;i++){
		for(int j=yHG; j<yHG+taille;j++){
			ImgOut[i*512+j] = couleur;
		}
	}
}

void divRecursive(OCTET *ImgIn, OCTET *ImgOut,int x,int y, int nTaille, int nH, int nW, int nbDiv){
	if (nbDiv>1){
		int somme1=0;
		int somme2=0;
		int somme3=0;
		int somme4=0;

		for (int i=x; i < x+nH; i++){
			for (int j=y; j < y+nW; j++){
				if (j<y+(nW/2) && i<x+(nH/2)){
					somme1 += ImgIn[i*512+j];
				}
				else if (j>=y+(nW/2) && i<x+(nH/2)){
					somme2 += ImgIn[i*512+j];
				}
				else if (j<y+(nW/2) && i>=x+(nH/2)){
					somme3 += ImgIn[i*512+j];
				}
				else if (j>=y+(nW/2) && i>=x+(nH/2)){
					somme4 += ImgIn[i*512+j];
				}
			}
		}

		int moyenne1 = somme1/(nTaille/4);
		int moyenne2 = somme2/(nTaille/4);
		int moyenne3 = somme3/(nTaille/4);
		int moyenne4 = somme4/(nTaille/4);

		drawCarre(ImgOut, x,y,nH/2,moyenne1);
		drawCarre(ImgOut, x,y+(nH/2),nH/2,moyenne2);
		drawCarre(ImgOut, x+(nH/2),y,nH/2,moyenne3);
		drawCarre(ImgOut, x+(nH/2),y+(nW/2),nH/2,moyenne4);

		divRecursive(ImgIn, ImgOut,x,y,nTaille/4,nH/2,nW/2,nbDiv-1);
		divRecursive(ImgIn, ImgOut,x,y+(nW/2),nTaille/4,nH/2,nW/2,nbDiv-1);
		divRecursive(ImgIn, ImgOut,x+(nH/2),y,nTaille/4,nH/2,nW/2,nbDiv-1);
		divRecursive(ImgIn, ImgOut,x+(nH/2),y+(nW/2),nTaille/4,nH/2,nW/2,nbDiv-1);
	}
}

//http://qmos.qlamb.com/telechargement.php

int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcrite[250];
	int nH, nW, nTaille;

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

	//for (int i = 1; i < 647; ++i){
		
		OCTET *ImgMoz;
		allocation_tableau(ImgMoz, OCTET, 64);
		lire_image_pgm("1.pgm", ImgMoz, 64);
	//}


	divRecursive(ImgIn, ImgOut,0,0, nTaille, nH, nW,7);


	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;

}
