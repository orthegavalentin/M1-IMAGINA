#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h> 
#include <string>

using namespace std;

void drawCylindre(float rayon, float hauteur, int nbMeri){
	rayon /= 5;
	hauteur /= 5;
	Point*** tabPts = new Point**[nbMeri+2];

	tabPts[nbMeri] = new Point*[nbMeri];
	tabPts[nbMeri+1] = new Point*[nbMeri];
	for (int i = 0; i < nbMeri; ++i){
		tabPts[i]= new Point*[4];

		double theta = 2.0 * M_PI * ((double) i / (double) nbMeri);

		tabPts[i][0] = new Point(
			(double) rayon * cos(theta),
			(double) rayon * sin(theta),
			(double) hauteur / 2.0);
		tabPts[i][1] = new Point(
			(double) rayon * cos(theta),
			(double) rayon * sin(theta),
			(double) - hauteur / 2.0);
	}
	for (int i = 0; i < nbMeri; i++){
		if (i == nbMeri-1){
			tabPts[i][2] = tabPts[0][1];
			tabPts[i][3] = tabPts[0][0];
		}
		else {
			tabPts[i][2] = tabPts[i+1][1];
			tabPts[i][3] = tabPts[i+1][0];	
		}
	}
	for (int i = 0; i < nbMeri; i++){
		tabPts[nbMeri][i] = tabPts[i][0];
		tabPts[nbMeri+1][i] = tabPts[i][1];
	}

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < nbMeri; i++){
		for (int j = 0; j < 2; j++){
			glVertex3f(
				tabPts[i][j]->getX(),
				tabPts[i][j]->getY(),
				tabPts[i][j]->getZ());
		}
	}
	glEnd();

	for (int i = nbMeri; i < nbMeri+2; i++){
		glBegin(GL_LINE_LOOP);
		for (int j = 0; j < nbMeri; j++){
			glVertex3f(
				tabPts[i][j]->getX(),
				tabPts[i][j]->getY(),
				tabPts[i][j]->getZ());
		}
		glEnd();
	}

	for (int i = nbMeri; i < nbMeri+2; i++){
		for (int j = 0; j < nbMeri; j++){
			glBegin(GL_LINES);
			glVertex3f(
				tabPts[i][0]->getX(),
				tabPts[i][0]->getY(),
				tabPts[i][0]->getZ());
			glVertex3f(
				tabPts[i][j]->getX(),
				tabPts[i][j]->getY(),
				tabPts[i][j]->getZ());
			glEnd();
		}
	}
}