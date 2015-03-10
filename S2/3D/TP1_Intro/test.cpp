#include <iostream>
#include <stdio.h>

#include "Point.cpp"
#include "Vector.cpp"

using namespace std;

int main(){
	cout << "Début\n";
	Point pt1(1,2,0);
	Point pt2(3,2,0);
	Point ptA(2,4,0);
	Point ptAproj;
	ptAproj = ptA.projectOnLine(pt1, pt2);
	cout << "Point projeté... x: " << ptAproj.getX() << " y: " << ptAproj.getY() << " z: " << ptAproj.getZ();
	cout << "\n";

	Point d(0,0,0);
	Point p(1,1,1);
	Vector v(0,0,1);

	Point p2;
	p2 = p.projectOnPlan(d,v);
	cout << "Pt sur plan... x: " << p2.getX() << " y: " << p2.getY() << " z: " << p2.getZ();
	cout << "\n";
	cout << "Fin\n";

	return 0;
}
