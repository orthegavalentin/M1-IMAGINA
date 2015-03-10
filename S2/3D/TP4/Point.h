#ifndef Point_h
#define Point_h

#include "Vector.h"

class Point {
	private:
		double x;
		double y;
		double z;
	public:
		Point();
		Point(double x, double y, double z);
		Point(Point &p);
		
		double getX();
		double getY();
		double getZ();
		void setX(double d);
		void setY(double d);
		void setZ(double d);
		
		Point projectOnLine(Point Point1Line, Point Point2Line);
		Point projectOnLine(Vector vecteur, Point PLine);
		Point projectOnPlan(Point PointOnPlane, Vector NormalOfPlane);
};

#endif
