#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
#include "Wave.hpp"

char fileName[200]; // Fichier wave

//==============================================================================
void printUsage(char* name) {

  cout << "\nUsage : "
       <<name
       <<" fichier.wav\n";
  exit(-1);
}

//==============================================================================
void processOptionsInLine(int argc, char** argv){  
  if (argc != 2) {
    printUsage(argv[0]);
  }
  //RECOPIE DU NOM DE L'IMAGE DANS LA VARIABLE seqName
  strcpy(fileName, argv[1]);  
}

int main(int argc, char *argv[]) {

  processOptionsInLine(argc, argv);

  cout<<"a compléter ...\n";
}

