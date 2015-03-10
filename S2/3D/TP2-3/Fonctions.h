#ifndef Fonctions_h
#define Fonctions_h

#include "Point.h"
#include "Vector.h"

void drawGrid();
double facto(double d);
void drawCurve(Point** tabPointOfCurve, long nbPoints);
Point** hermiteCubicCurve(Point P0, Point P1, Vector V0, Vector V1, long nbU);
Point** bezierCurveByBernstein(Point** TabControlPoint, long nbControlPoint, long nbU);
Point* casteljau(Point **t, long nbControlPoint, double u);
Point** bezierCurveByCasteljau(Point** TabControlPoint, long nbControlPoint, long nbU);

#endif