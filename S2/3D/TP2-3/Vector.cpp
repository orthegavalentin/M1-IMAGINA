#include <iostream>
#include <math.h>
#include <stdio.h>

#include"Vector.h"

using namespace std;

Vector::Vector(){
	this->x=0;
	this->y=0;
	this->z=0;
}

Vector::Vector(double x,double y,double z){
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector::Vector(Vector &v){
	this->x = v.getX();
	this->y = v.getY();
	this->z = v.getZ();
}

double Vector::getX(){
	return this->x;
}
double Vector::getY(){
	return this->y;
}
double Vector::getZ(){
	return this->z;
}
void Vector::setX(double d){
	this->x = d;
}
void Vector::setY(double d){
	this->y = d;
}
void Vector::setZ(double d){
	this->z = d;
}

double Vector::norme(){
	double x = this->getX();
	double y = this->getY();
	double z = this->getZ();
	return sqrt((x*x) + (y*y) + (z*z));
}

void Vector::normalize(){
	double norme = this->norme();
	this->setX(this->getX() / norme);
	this->setY(this->getY() / norme);
	this->setZ(this->getZ() / norme);
}

double Vector::scalar(Vector Vector2){
	double part1 = this->getX() * Vector2.getX();
	double part2 = this->getY() * Vector2.getY();
	double part3 = this->getZ() * Vector2.getZ();
	return (part1 + part2 + part3);
}

Vector Vector::vectoriel(Vector Vector2){
	double retourX = (this->getY() * Vector2.getZ()) - (this->getZ() * Vector2.getY());
	double retourY = (this->getZ() * Vector2.getX()) - (this->getX() * Vector2.getZ());
	double retourZ = (this->getX() * Vector2.getY()) - (this->getY() * Vector2.getX());
	Vector retour(retourX, retourY, retourZ);
	return retour;
}

double Vector::angle(Vector Vector2){
	double cosA = (this->scalar(Vector2))/(this->norme()*Vector2.norme());
	return acos(cosA) * 180.0 / M_PI;
}

