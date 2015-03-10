#include <iostream>
#include <stdio.h>
#include <cmath>

#include "Point.h"

using namespace std;

Point::Point(){
	this->x=0;
	this->y=0;
	this->z=0;
}

Point::Point(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Point::Point(Point &p){
	this->x = p.getX();
	this->y = p.getY();
	this->z = p.getZ();
}

double Point::getX(){
	return this->x;
}
double Point::getY(){
	return this->y;
}
double Point::getZ(){
	return this->z;
}
void Point::setX(double d){
	this->x = d;
}
void Point::setY(double d){
	this->y = d;
}
void Point::setZ(double d){
	this->z = d;
}

Point Point::projectOnLine(Point Point1Line, Point Point2Line){
	Vector BC(Point2Line.getX()-Point1Line.getX(),Point2Line.getY()-Point1Line.getY(),Point2Line.getZ()-Point1Line.getZ());
	Vector BA(Point1Line.getX()-this->getX(),Point1Line.getY()-this->getY(),Point1Line.getZ()-this->getZ());
	BC.normalize();
	double dist = abs(BA.scalar(BC));
	double xA = Point1Line.getX() + BC.getX()*dist;
	double yA = Point1Line.getY() + BC.getY()*dist;
	double zA = Point1Line.getZ() + BC.getZ()*dist;
	Point p(xA, yA, zA);
	return p;
}

Point Point::projectOnLine(Vector vecteur, Point PLine){
	Vector BA(PLine.getX()-this->getX(),PLine.getY()-this->getY(),PLine.getZ()-this->getZ());
	vecteur.normalize();
	double dist = abs(BA.scalar(vecteur));
	double xA = PLine.getX() + (vecteur.getX()*dist);
	double yA = PLine.getY() + (vecteur.getY()*dist);
	double zA = PLine.getZ() + (vecteur.getZ()*dist);
	Point p(xA, yA, zA);
	return p;
}

Point Point::projectOnPlan(Point pointOnPlane, Vector normalOfPlane){
	Vector MA(pointOnPlane.getX()-this->getX(),pointOnPlane.getY()-this->getY(),pointOnPlane.getZ()-this->getZ());
	normalOfPlane.normalize();
	double dist = abs(MA.scalar(normalOfPlane));
	double xA = this->getX() - (normalOfPlane.getX() * dist);
	double yA = this->getY() - (normalOfPlane.getY() * dist);
	double zA = this->getZ() - (normalOfPlane.getZ() * dist);
	Point p(xA, yA, zA);
	return p;
}
