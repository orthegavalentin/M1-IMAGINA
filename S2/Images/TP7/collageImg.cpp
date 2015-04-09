#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "image_ppm.h"

using namespace std;

void drawCarre(OCTET *ImgOut, int xHG, int yHG, int taille, OCTET *ImgPetite){
	for(int i=xHG; i< xHG+taille;i++){
		for(int j=yHG; j<yHG+taille;j++){
			ImgOut[i*512+j] = ImgPetite[i*8+j];
		}
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

	OCTET *ImgIn, *ImgOut, *ImgPetite;

	ifstream stream("tabMoy.txt");
	string ligne;
	int numLigne=0;
	int tabMoy[1292][2];
	while (getline(stream, ligne)) {
		std::istringstream iss(ligne);
		int moyenne,numImage;
		iss >> moyenne >> numImage;
		tabMoy[numLigne][0]=moyenne;
		tabMoy[numLigne][1]=numImage;
		numLigne++;
	}

	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;

	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);

	for(int i=0; i<nH;i+=8){
		for(int j=0; j<nW;j+=8){
			//ImgOut[i*nW+j] = ImgIn[i*nW+j];
			drawCarre(ImgOut,i,j,8,ImgPetite);
		}
	}

	ecrire_image_pgm(cNomImgEcrite, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
}