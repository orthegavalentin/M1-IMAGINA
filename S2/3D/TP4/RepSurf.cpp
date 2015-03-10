#include <iostream>
#include <stdio.h>
#include <math.h>

#include "RepSurf.h"

using namespace std;

Point*** calcSommetsCylindre(float rayon, float hauteur, int nbMeri){
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
	return tabPts;
}

Point*** calcSommetsCone(float rayon, float hauteur, float tailleCouvHaut, int nbMeri){
	Point*** tabPts = new Point**[nbMeri+2];

	tabPts[nbMeri] = new Point*[nbMeri];
	tabPts[nbMeri+1] = new Point*[nbMeri];
	for (int i = 0; i < nbMeri; ++i){
		tabPts[i]= new Point*[4];

		double theta = 2.0 * M_PI * ((double) i / (double) nbMeri);

		tabPts[i][0] = new Point(
			(double) rayon * cos(theta) * tailleCouvHaut,
			(double) rayon * sin(theta) * tailleCouvHaut,
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
	return tabPts;
}



static void fghCircleTable(double **sint,double **cost,const int n){
	int i;
	const int size = abs(n);
	const double angle = 2*M_PI/(double)( ( n == 0 ) ? 1 : n );
	*sint = (double *) calloc(sizeof(double), size+1);
	*cost = (double *) calloc(sizeof(double), size+1);
	
	(*sint)[0] = 0.0;
	(*cost)[0] = 1.0;
	for (i=1; i<size; i++){
		(*sint)[i] = sin(angle*i);
		(*cost)[i] = cos(angle*i);
	}
	(*sint)[size] = (*sint)[0];
	(*cost)[size] = (*cost)[0];
}

void calcSommetsCercle(float radius, int slices, int stacks){
	stacks+=1;
	int i,j;
	double z0,z1;
	double r0,r1;
	double *sint1,*cost1;
	double *sint2,*cost2;
	fghCircleTable(&sint1,&cost1,-slices);
	fghCircleTable(&sint2,&cost2,stacks*2);

	z0 = 1.0;
	z1 = cost2[(stacks>0)?1:0];
	r0 = 0.0;
	r1 = sint2[(stacks>0)?1:0];
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(0,0,1);
	glVertex3d(0,0,radius);
	for (j=slices; j>=0; j--){
		glNormal3d(cost1[j]*r1, sint1[j]*r1, z1 );
		glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
	}
	glEnd();

	for( i=1; i<stacks-1; i++ ){
		z0 = z1; z1 = cost2[i+1];
		r0 = r1; r1 = sint2[i+1];
		glBegin(GL_QUAD_STRIP);
		for(j=0; j<=slices; j++){
			glNormal3d(cost1[j]*r1, sint1[j]*r1, z1 );
			glVertex3d(cost1[j]*r1*radius, sint1[j]*r1*radius, z1*radius);
			glNormal3d(cost1[j]*r0, sint1[j]*r0, z0 );
			glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
		}
		glEnd();
	}

	z0 = z1;
	r0 = r1;
	glBegin(GL_TRIANGLE_FAN);
	glNormal3d(0,0,-1);
	glVertex3d(0,0,-radius);
	for (j=0; j<=slices; j++){
		glNormal3d(cost1[j]*r0, sint1[j]*r0, z0 );
		glVertex3d(cost1[j]*r0*radius, sint1[j]*r0*radius, z0*radius);
	}
	glEnd();

	free(sint1);
	free(cost1);
	free(sint2);
	free(cost2);
}









// Point*** calcSommetsCercle(float rayon, int nbMeri, int nbPara){
// 	Point*** tabPts = new Point**[nbMeri*nbPara];
// 	//nbMeri et nbPara en variable globale pour les modifier avec + et -;
// 	//https://github.com/LuaDist/freeglut/blob/5462d9195ca3114697d381b2f1599b63bca4e4b6/src/freeglut_geometry.c

// 	//https://www.opengl.org/resources/libraries/glut/spec3/node81.html
// 	//http://www.cburch.com/cs/490/sched/feb8/index.html

// 	// glutSolidSphere(rayon,nbMeri,nbPara+1);
// 	glColor3f(1.0, 0.37, 0);
// 	glutWireSphere(rayon+0.1,nbMeri,nbPara+1);
// 	return tabPts;
// }