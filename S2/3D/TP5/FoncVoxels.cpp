#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h> 

#include "FoncVoxels.h"

using namespace std;

bool switcher = true;

void displayVoxel(Point centre, double length){
	double t = length/2;
	if(switcher){
		glColor3f(1.0, 0.37, 0);
		switcher=false;
	}
	else{
		glColor3f(0.5, 0.5, 0.5);
		switcher=true;
	}
	glBegin(GL_QUADS);

	glVertex3f(centre.getX()+t,centre.getY()+t,centre.getZ()+t);
	glVertex3f(centre.getX()+t,centre.getY()+t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()-t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()-t,centre.getZ()+t);

	glVertex3f(centre.getX()+t,centre.getY()+t,centre.getZ()-t);
	glVertex3f(centre.getX()-t,centre.getY()+t,centre.getZ()-t);
	glVertex3f(centre.getX()-t,centre.getY()-t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()-t,centre.getZ()-t);

	glVertex3f(centre.getX()-t,centre.getY()+t,centre.getZ()-t);
	glVertex3f(centre.getX()-t,centre.getY()+t,centre.getZ()+t);
	glVertex3f(centre.getX()-t,centre.getY()-t,centre.getZ()+t);
	glVertex3f(centre.getX()-t,centre.getY()-t,centre.getZ()-t);

	glVertex3f(centre.getX()-t,centre.getY()+t,centre.getZ()+t);
	glVertex3f(centre.getX()+t,centre.getY()+t,centre.getZ()+t);
	glVertex3f(centre.getX()+t,centre.getY()-t,centre.getZ()+t);
	glVertex3f(centre.getX()-t,centre.getY()-t,centre.getZ()+t);

	glVertex3f(centre.getX()-t,centre.getY()+t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()+t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()+t,centre.getZ()+t);
	glVertex3f(centre.getX()-t,centre.getY()+t,centre.getZ()+t);

	glVertex3f(centre.getX()-t,centre.getY()-t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()-t,centre.getZ()-t);
	glVertex3f(centre.getX()+t,centre.getY()-t,centre.getZ()+t);
	glVertex3f(centre.getX()-t,centre.getY()-t,centre.getZ()+t);

	glEnd();
}

void displaySphereVolumic(Point centre, Point vraiCentre, double diametre, double vraiDiametre, int resolution){
	if (resolution==1){
		double somme = pow(centre.getX()-vraiCentre.getX(),2) + pow(centre.getY()-vraiCentre.getY(),2) + pow(centre.getZ()-vraiCentre.getZ(),2);
		if(somme <= pow(vraiDiametre/2,2)){
			displayVoxel(centre,diametre);
		}
	}
	else{
		centre.setX(centre.getX()-(diametre/4));
		centre.setY(centre.getY()+(diametre/4));
		centre.setZ(centre.getZ()-(diametre/4));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setY(centre.getY()-(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()-(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setZ(centre.getZ()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setY(centre.getY()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()-(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
	}
}

void displayCylinderVolumic(Point ptOrigin, Point centre, Vector axisVector, double diametre, double vraiDiametre, int resolution){
	
	Point ptProj;
	ptProj = centre.projectOnLine(axisVector, ptOrigin);
	if (resolution==1){
		double somme = pow(centre.getX(),2) + pow(centre.getY(),2);
		if(somme*axisVector.getZ() <= pow(vraiDiametre/2,2) && (ptProj.getZ() == centre.getZ() || ptProj.getZ() == -centre.getZ())){
			displayVoxel(centre,diametre);
		}
	}
	else{
		centre.setX(centre.getX()-(diametre/4));
		centre.setY(centre.getY()+(diametre/4));
		centre.setZ(centre.getZ()-(diametre/4));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()+(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setY(centre.getY()-(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()-(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setZ(centre.getZ()+(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()+(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setY(centre.getY()+(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()-(diametre/2));
		displayCylinderVolumic(ptOrigin, centre, axisVector, diametre/2, vraiDiametre, resolution-1);
	}
}

bool isCircle(Point centre, Point vraiCentre, double diametre, double vraiDiametre){
	double somme = pow(centre.getX()-vraiCentre.getX(),2) + pow(centre.getY()-vraiCentre.getY(),2) + pow(centre.getZ()-vraiCentre.getZ(),2);

	return somme <= pow(vraiDiametre/2,2);
}

bool isCylindre(Point ptOrigin, Point centre, Vector axisVector, double diametre, double vraiDiametre){
	Point ptProj;
	ptProj = centre.projectOnLine(axisVector, ptOrigin);
	double somme = pow(centre.getX(),2) + pow(centre.getY(),2);

	return somme*axisVector.getZ() <= pow(vraiDiametre/2,2) && (ptProj.getZ() == centre.getZ() || ptProj.getZ() == -centre.getZ());
}

void displayIntersectionSphereCylinder(Point centreSphere, double rayonSphere, Point axisOriginCylinder, Vector axisVectorCylinder, double rayonCylinder, double resolution){
	if (resolution==1){
		if(isCircle(/*TODO*/) && isCylindre(/*TODO*/)){
			displayVoxel(centre,diametre);
		}
	}
	else{
		centre.setX(centre.getX()-(diametre/4));
		centre.setY(centre.getY()+(diametre/4));
		centre.setZ(centre.getZ()-(diametre/4));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setY(centre.getY()-(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()-(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setZ(centre.getZ()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setY(centre.getY()+(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
		centre.setX(centre.getX()-(diametre/2));
		displaySphereVolumic(centre, vraiCentre, diametre/2, vraiDiametre, resolution-1);
	}
}