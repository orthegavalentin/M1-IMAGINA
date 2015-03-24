#include <iostream>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h> 

#include "FoncVoxels.h"

using namespace std;

bool switcher = true;

void displayVoxel(Point centre, double length){
	double t = length/2;
	// if(switcher){
	// 	glColor3f(1.0, 0.37, 0);
	// 	switcher=false;
	// }
	// else{
	// 	glColor3f(0.5, 0.5, 0.5);
	// 	switcher=true;
	// }
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

void displaySphereVolumic(Point centre, Point vraiCentre, double diametre, double vraiDiametre, int resolution){
	if (resolution==1){
		double somme = pow(centre.getX()-vraiCentre.getX(),2) + pow(centre.getY()-vraiCentre.getY(),2) + pow(centre.getZ()-vraiCentre.getZ(),2);
		// if(somme <= pow(vraiDiametre/2,2)){
		if(isCircle(centre, vraiCentre, diametre, vraiDiametre)){
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
		// if(somme*axisVector.getZ() <= pow(vraiDiametre/2,2) && (ptProj.getZ() == centre.getZ() || ptProj.getZ() == -centre.getZ())){
		if(isCylindre(ptOrigin, centre, axisVector, diametre, vraiDiametre)){
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



void displayIntersectionSphereCylinder(Point centreS, Point vraiCentreS, double diametreS, double vraiDiametreS, Point ptOriginC, Point centreC, Vector axisVectorC, double diametreC, double vraiDiametreC, double resolution){
	if (resolution==1){
		if(isCircle(centreS, vraiCentreS, diametreS, vraiDiametreS) && isCylindre(ptOriginC, centreC, axisVectorC, diametreC, vraiDiametreC)){
			displayVoxel(centreS,diametreS);
			displayVoxel(centreC,diametreC);
		}
	}
	else{
		centreS.setX(centreS.getX()-(diametreS/4));
		centreC.setX(centreC.getX()-(diametreC/4));
		centreS.setY(centreS.getY()+(diametreS/4));
		centreC.setY(centreC.getY()+(diametreC/4));
		centreS.setZ(centreS.getZ()-(diametreS/4));
		centreC.setZ(centreC.getZ()-(diametreC/4));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setX(centreS.getX()+(diametreS/2));
		centreC.setX(centreC.getX()+(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setY(centreS.getY()-(diametreS/2));
		centreC.setY(centreC.getY()-(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setX(centreS.getX()-(diametreS/2));
		centreC.setX(centreC.getX()-(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setZ(centreS.getZ()+(diametreS/2));
		centreC.setZ(centreC.getZ()+(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setX(centreS.getX()+(diametreS/2));
		centreC.setX(centreC.getX()+(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setY(centreS.getY()+(diametreS/2));
		centreC.setY(centreC.getY()+(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
		centreS.setX(centreS.getX()-(diametreS/2));
		centreC.setX(centreC.getX()-(diametreC/2));
		displayIntersectionSphereCylinder(centreS, vraiCentreS, diametreS/2, vraiDiametreS, ptOriginC, centreC, axisVectorC, diametreC/2, vraiDiametreC, resolution-1);
	}
}