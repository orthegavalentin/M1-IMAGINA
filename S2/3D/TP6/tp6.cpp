#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h> 
#include <string>
#include <sstream>
#include <fstream> 

using namespace std;

void drawFile(){
	std::ifstream fichier("triceratops.off");
	std::string ligne;
	int nbLignes=0;
	int nbSommets=0;
	int nbFaces=0;
	int nbAretes=0;
	double* tabSommets;
	int* tabFaces;

	while (std::getline(fichier, ligne)){
		nbLignes++;
		if (nbLignes == 1 && ligne=="OFF"){
			//cout << "Fichier OFF détecté" << endl;
		}
		if (nbLignes == 2){
			std::istringstream iss(ligne);
			int nbS,nbF,nbA;
			iss >> nbS >> nbF >> nbA;
			nbSommets=nbS;
			nbFaces=nbF;
			nbAretes=nbA;
			tabSommets = new double[nbSommets*3];
			tabFaces = new int[nbFaces*3];
		}


		if (nbLignes>2 && nbLignes<=nbSommets+2){
			std::istringstream iss(ligne);
			double pt1, pt2, pt3;
			iss >> pt1 >> pt2 >> pt3;
			tabSommets[3*(nbLignes-3)]=pt1;
			tabSommets[3*(nbLignes-3)+1]=pt2;
			tabSommets[3*(nbLignes-3)+2]=pt3;
		}
		if (nbLignes>nbSommets+2){
			std::istringstream iss(ligne);
			int nb, p1, p2, p3;
			iss >> nb >> p1 >> p2 >> p3;
			tabFaces[3*(nbLignes-(nbSommets+3))]=p1;
			tabFaces[3*(nbLignes-(nbSommets+3))+1]=p2;
			tabFaces[3*(nbLignes-(nbSommets+3))+2]=p3;
		}
	}

	for (int i = 0; i < nbFaces*3; i+=3){

		glBegin(GL_LINE_LOOP);

		glVertex3d(tabSommets[3*tabFaces[i]], tabSommets[3*tabFaces[i]+1] , tabSommets[3*tabFaces[i]+2]);
		glVertex3d(tabSommets[3*tabFaces[i+1]], tabSommets[3*tabFaces[i+1]+1] , tabSommets[3*tabFaces[i+1]+2]);
		glVertex3d(tabSommets[3*tabFaces[i+2]], tabSommets[3*tabFaces[i+2]+1] , tabSommets[3*tabFaces[i+2]+2]);

		// cout << tabSommets[3*tabFaces[i]] << " " << tabSommets[3*tabFaces[i]+1] << " " << tabSommets[3*tabFaces[i]+2] << " \t\t";
		// cout << tabSommets[3*tabFaces[i+1]] << " " << tabSommets[3*tabFaces[i+1]+1] << " " << tabSommets[3*tabFaces[i+1]+2] << " \t\t";
		// cout << tabSommets[3*tabFaces[i+2]] << " " << tabSommets[3*tabFaces[i+2]+1] << " " << tabSommets[3*tabFaces[i+2]+2] << endl;

		glEnd();
	}


	// cout << tabSommets[3*tabFaces[0]] << " " << tabSommets[3*tabFaces[0]+1] << " " << tabSommets[3*tabFaces[0]+2] << endl;
	// cout << tabSommets[3*tabFaces[0+1]] << " " << tabSommets[3*tabFaces[0+1]+1] << " " << tabSommets[3*tabFaces[0+1]+2] << endl;
	// cout << tabSommets[3*tabFaces[0+2]] << " " << tabSommets[3*tabFaces[0+2]+1] << " " << tabSommets[3*tabFaces[0+2]+2] << endl;
	// cout << endl;

	// for(int i = 0; i< nbFaces*3;i+=3){
	// 	cout << tabFaces[i] << " " << tabFaces[i+1] << " " << tabFaces[i+2] << "  ";
	// }
	
}