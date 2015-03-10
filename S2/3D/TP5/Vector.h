#ifndef Vector_h
#define Vector_h

#include "Point.h"

class Vector{
	private:
		double x;
		double y;
		double z;	
	public:
		Vector();
		Vector(double x, double y, double z);
		Vector(Vector &v);
		
		double getX();
		double getY();
		double getZ();
		void setX(double d);
		void setY(double d);
		void setZ(double d);
		
		double norme();
		void normalize();
		double scalar (Vector Vector2);
		Vector vectoriel(Vector Vector2);
		double angle(Vector Vector2);
};

#endif
