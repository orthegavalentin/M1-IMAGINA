#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h> 
#include <string>
#include <sstream>
#include <fstream> 

using namespace std;

void drawFile(){
	std::ifstream fichier("max.off");
	std::string ligne;
	int nbLignes=0;
	int nbSommets=0;
	int nbFaces=0;
	int nbAretes=0;
	double* tabSommets;
	int* tabFaces;
	while (std::getline(fichier, ligne)){
        //cout << ligne << endl;
		nbLignes++;
		if (nbLignes == 1 && ligne=="OFF"){
			cout << "Fichier OFF détecté" << endl;
		}
		if (nbLignes == 2){
			std::istringstream iss(ligne);
			int nbS,nbF,nbA;
			iss >> nbS >> nbF >> nbA;
			nbSommets=nbS;
			nbFaces=nbF;
			nbAretes=nbA;
		}
		tabSommets = new double[nbSommets*3];
		tabFaces = new int[nbFaces*3];

		if (nbLignes>2 && nbLignes<=nbSommets+2){
			std::istringstream iss(ligne);
			double pt1, pt2, pt3;
			iss >> pt1 >> pt2 >> pt3;
			tabSommets[(nbLignes-3)]=pt1;
			tabSommets[(nbLignes-3)+1]=pt2;
			tabSommets[(nbLignes-3)+2]=pt3;
		}
		if (nbLignes>nbSommets+2){
			std::istringstream iss(ligne);
			int nb, p1, p2, p3;
			iss >> nb >> p1 >> p2 >> p3;
			tabFaces[nbLignes-(nbSommets+2)]=p1;
			tabFaces[nbLignes-(nbSommets+2)+1]=p2;
			tabFaces[nbLignes-(nbSommets+2)+2]=p3;
		}
	}

	for (int i = 0; i < nbSommets*3; i+=3){
		glBegin(GL_TRIANGLES);

		glVertex3f(tabSommets[tabFaces[i]],tabSommets[tabFaces[i+1]],tabSommets[tabFaces[i+2]]);

		glEnd();
	}

	

}