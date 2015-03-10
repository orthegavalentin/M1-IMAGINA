#include "Fonctions.h"
#include <math.h>
#include <stdio.h>

using namespace std;

double facto(double d){
	if (d == 0) {
		return 1;
	}
	return d*facto(d-1);
}

void drawGrid(){
	glBegin(GL_LINES);
	for(int i=-10;i<=10;i++) {
		if (i==0) { 
			glColor3f(.5,.5,.5);
		} else { 
			glColor3f(.8,.8,.8);
		}
		glVertex3f(i,-10,0);
		glVertex3f(i,10,0);
		if (i==0) {
			glColor3f(.5,.5,.5);
		} else {
			glColor3f(.8,.8,.8);
		}
		glVertex3f(-10,i,0);
		glVertex3f(10,i,0);
	}
	for(int i=-10;i<=10;i++) {
		if (i==0) { 
			glColor3f(.5,.5,.5);
		} else { 
			glColor3f(.8,.8,.8);
		}
		glVertex3f(i,0,-10);
		glVertex3f(i,0,10);
		if (i==0) {
			glColor3f(.5,.5,.5);
		} else {
			glColor3f(.8,.8,.8);
		}
		glVertex3f(-10,0,i);
		glVertex3f(10,0,i);
	}
	for(int i=-10;i<=10;i++) {
		if (i==0) { 
			glColor3f(.5,.5,.5);
		} else { 
			glColor3f(.8,.8,.8);
		}
		glVertex3f(0,-10,i);
		glVertex3f(0,10,i);
		if (i==0) {
			glColor3f(.5,.5,.5);
		} else {
			glColor3f(.8,.8,.8);
		}
		glVertex3f(0,i,-10);
		glVertex3f(0,i,10);
	}
	glEnd();
}

void drawCurve(Point** tabPointOfCurve, long nbPoints){
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < nbPoints; ++i){
		glVertex3f(tabPointOfCurve[i]->getX(),tabPointOfCurve[i]->getY(),tabPointOfCurve[i]->getZ());
	}
	glEnd();
	glBegin(GL_POINTS);
	for (int i = 0; i < nbPoints; ++i){
		glVertex3f(tabPointOfCurve[i]->getX(),tabPointOfCurve[i]->getY(),tabPointOfCurve[i]->getZ());
	}
	glEnd();
}

Point** hermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU){
	Point** tabPts = new Point*[nbU];
	for (int i = 0; i < nbU; i++){
		double u = 1/(nbU-1) * (double) i;
		double f1 = (2*pow(u,3)) - (3*pow(u,2)) + 1;
		double f2 = (-2*pow(u,3)) + (3*pow(u,2));
		double f3 = (pow(u,3)) - (2*pow(u,2)) + u;
		double f4 = (pow(u,3)) - (pow(u,2));

		double newX = f1*P0.getX() + f2*P1.getX() + f3*V0.getX() + f4*V1.getX();
		double newY = f1*P0.getY() + f2*P1.getY() + f3*V0.getY() + f4*V1.getY();
		double newZ = f1*P0.getZ() + f2*P1.getZ() + f3*V0.getZ() + f4*V1.getZ();
		tabPts[i] = new Point(newX,newY,newZ);
	}
	return tabPts;
}

Point** bezierCurveByBernstein(Point** TabControlPoint, long nbControlPoint, long nbU){
	Point** tabPts = new Point*[nbU+1];
	double n = nbControlPoint-1;
	for (int i = 0; i < nbU; i++) {
		double u = 1/(float) nbU * (double) i;
		double x=0, y=0, z=0;
		for (int j = 0; j < n; j++){
			double B = (facto(n) / (facto(j) * facto(n-j))) * pow(u, j) * pow((1-u), n-j);
			cout << B << endl;
			x +=(B*TabControlPoint[j]->getX());
			y +=(B*TabControlPoint[j]->getY());
			z +=(B*TabControlPoint[j]->getZ());
		}

		cout << x << " " << y << " " << z << endl;
		tabPts[i] = new Point(x,y,z);
	}
	int i = nbU;
	tabPts[i] = new Point(TabControlPoint[i]->getX(),TabControlPoint[i]->getY(),TabControlPoint[i]->getZ());

	return tabPts;
}

Point* casteljau(Point **t, long nbControlPoint, double u) {
	if(nbControlPoint == 1) {
		return new Point(t[0]->getX(), t[0]->getY(), t[0]->getZ());
	} else {
		Point* pts[nbControlPoint - 1];
		for (int i = 0; i < nbControlPoint - 1; ++i) {
			Vector v(t[i+1]->getX()-t[i]->getX(), t[i+1]->getY()-t[i]->getY(),t[i+1]->getZ()-t[i]->getZ());
			v.setX(u*v.getX());
			v.setY(u*v.getY());
			v.setZ(u*v.getZ());

			if (u==0.5){
				glColor3f(0.6,0.6,0.6);
				glBegin(GL_LINE_STRIP);
				glVertex3f(t[i]->getX(),t[i]->getY(),t[i]->getZ());
				glVertex3f(t[i+1]->getX(),t[i+1]->getY(),t[i+1]->getZ());
				glEnd();
			}


			Point *p = new Point(v.getX() + t[i]->getX(),v.getY() + t[i]->getY(),v.getZ() + t[i]->getZ());
			pts[i] = p;
		}
		return casteljau(pts, nbControlPoint - 1, u);
	}
}
Point **bezierCurveByCasteljau(Point **TabControlPoint, long nbControlPoint, long nbU) {
	Point **pts = new Point*[nbU];
	for (int j = 0; j < nbU; ++j){
		double u = (1.0f / (double) (nbU - 1))* (double) j;
		pts[j] = casteljau(TabControlPoint, nbControlPoint, u);
	}
	return pts;
}

