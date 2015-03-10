#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include "image_ppm.h"

using namespace std;

void drawCarre(OCTET *ImgOut, int xHG, int yHG, int taille, int couleur){
	for(int i=xHG; i< xHG+taille;i++){
		for(int j=yHG; j<yHG+taille;j++){
			ImgOut[i*512+j] = couleur;
		}
	}
}

void divRecursive(OCTET *ImgIn, OCTET *ImgOut,int x,int y, int nTaille, int nH, int nW, int seuil, int seuilFusion){
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

	// int buff;
	// if(std::abs(moyenne1 - moyenne2) <= seuilFusion){
	// 	buff=moyenne1;
	// 	moyenne1 = (buff+moyenne2)/2;
	// 	moyenne2 = moyenne1;
	// }
	// if(std::abs(moyenne3 - moyenne4) <= seuilFusion){
	// 	buff=moyenne3;
	// 	moyenne3 = (buff+moyenne4)/2;
	// 	moyenne4 = moyenne3;
	// }

	if (moyenne1 <= (256-seuilFusion)){
		drawCarre(ImgOut, x,y,nH/2,0);
	} else {
		drawCarre(ImgOut, x,y,nH/2,moyenne1);
	}
	if (moyenne2 <= (256-seuilFusion)){
		drawCarre(ImgOut, x,y+(nH/2),nH/2,0);
	} else {
		drawCarre(ImgOut, x,y+(nH/2),nH/2,moyenne2);
	}
	if (moyenne3 <= (256-seuilFusion)){
		drawCarre(ImgOut, x+(nH/2),y,nH/2,0);
	} else {
		drawCarre(ImgOut, x+(nH/2),y,nH/2,moyenne3);
	}
	if (moyenne4 <= (256-seuilFusion)){
		drawCarre(ImgOut, x+(nH/2),y+(nW/2),nH/2,0);
	} else {
		drawCarre(ImgOut, x+(nH/2),y+(nW/2),nH/2,moyenne4);
	}

	//drawCarre(ImgOut, x,y,nH/2,moyenne1);
	//drawCarre(ImgOut, x,y+(nH/2),nH/2,moyenne2);
	//drawCarre(ImgOut, x+(nH/2),y,nH/2,moyenne3);
	//drawCarre(ImgOut, x+(nH/2),y+(nW/2),nH/2,moyenne4);

	float variance1 = 0.0;
	float variance2 = 0.0;
	float variance3 = 0.0;
	float variance4 = 0.0;

	for (int i=x; i < x+nH; i++){
		for (int j=y; j < y+nW; j++){
			if (j<y+(nW/2) && i<x+(nH/2)){
				variance1 += pow(ImgIn[i*512+j] - moyenne1,2);
			}
			else if (j>=y+(nW/2) && i<x+(nH/2)){
				variance2 += pow(ImgIn[i*512+j] - moyenne2,2);
			}
			else if (j<y+(nW/2) && i>=x+(nH/2)){
				variance3 += pow(ImgIn[i*512+j] - moyenne3,2);
			}
			else if (j>=y+(nW/2) && i>=x+(nH/2)){
				variance4 += pow(ImgIn[i*512+j] - moyenne4,2);
			}
		}
	}
	variance1 /= (nTaille/4);
	variance2 /= (nTaille/4);
	variance3 /= (nTaille/4);
	variance4 /= (nTaille/4);
	//cout << "Variances : " << variance1 << " " << variance2 << " " << variance3 << " " << variance4 << endl;


	if(sqrt(variance1) > seuil){
		divRecursive(ImgIn, ImgOut,x,y,nTaille/4,nH/2,nW/2,seuil,seuilFusion);
	}
	if(sqrt(variance2) > seuil){
		divRecursive(ImgIn, ImgOut,x,y+(nW/2),nTaille/4,nH/2,nW/2,seuil,seuilFusion);
	}
	if(sqrt(variance3) > seuil){
		divRecursive(ImgIn, ImgOut,x+(nH/2),y,nTaille/4,nH/2,nW/2,seuil,seuilFusion);
	}
	if(sqrt(variance4) > seuil){
		divRecursive(ImgIn, ImgOut,x+(nH/2),y+(nW/2),nTaille/4,nH/2,nW/2,seuil,seuilFusion);
	}
}

int main(int argc, char* argv[]){

	char cNomImgLue[250], cNomImgEcriteM[250];
	int nH, nW, nTaille;
	
	if (argc != 3) {
		printf("Usage: ImageIn.pgm ImageOutMoy.pgm \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%s",cNomImgEcriteM);
	
	OCTET *ImgIn, *ImgOut;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
	
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);

	int seuil = 10;
	int seuilFusion = 100;
	divRecursive(ImgIn, ImgOut,0,0, nTaille, nH, nW, seuil, seuilFusion);

	ecrire_image_pgm(cNomImgEcriteM, ImgOut,  nH, nW);
	free(ImgIn);
	return 1;
}

//Q1 : > 16.4444 3516.71 4263.54 4474.51