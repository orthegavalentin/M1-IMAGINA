#include <iostream>
#include <cstdlib>
#include "Wave.hpp"

using namespace std;

int main()
{

    Wave *w = new Wave();
    char* fichier = "/auto_home/tcastanie/Dropbox/M1 IMAGINA/Signal/TP1_son/GammePiano.wav";

    w->read(fichier);

    unsigned char** data = new unsigned char*[1];
    int* size = (int*) malloc(sizeof(int));
    w->getData8(data,size);

    Wave *w2 = new Wave((*data), (*size),1,11025);

    w2->write("fichierCopie.wav");




    return 0;
}

