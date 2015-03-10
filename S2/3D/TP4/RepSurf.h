#ifndef RepSurf_h
#define RepSurf_h

#include "Point.h"
#include "Vector.h"

Point*** calcSommetsCylindre(float rayon, float hauteur, float nbMeri);
Point*** calcSommetsCone(float rayon, float hauteur, float tailleCouvHaut, int nbMeri);
void calcSommetsCercle(float rayon, int nbMeri, int nbPara);

#endif