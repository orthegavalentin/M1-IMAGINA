#include <stdio.h>
#include <iostream>
#include "image_ppm.h"

using namespace std;

int main(int argc, char* argv[]){

	char cNomImgLue[250];
	int nH, nW, nTaille, nLigne, x;
	char colLigne;
	
	if (argc != 4) {
		printf("Usage: ImageIn.pgm c/l nLigne \n"); 
		exit (1) ;
	}
	
	sscanf (argv[1],"%s",cNomImgLue);
	sscanf (argv[2],"%c",&colLigne);
	sscanf (argv[3],"%d",&nLigne);
	
	OCTET *ImgIn;
	
	lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
	nTaille = nH * nW;
  
	allocation_tableau(ImgIn, OCTET, nTaille);
	lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	
	if(colLigne == 'l'){
		for(int i = 0; i< nW; i++){
			x = ImgIn[nLigne*nW+i];
			cout << i << " " << x << "\n";
		}
	} else if(colLigne == 'c'){
		for(int i = 0; i< nW; i++){
			x = ImgIn[i*nW+nLigne];
			cout << i << " " << x << "\n";
		}
	}
		
		
	
	free(ImgIn);
	return 1;

}
