#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>

using namespace std;

int tailleX = 448;
int tailleY = 576;
int tailleZ = 72;

char * buffer;

int getValue(int x, int y, int z){
	return (int) buffer[z*(tailleX*tailleY)+(y*tailleY)+x];
}

int main(int argc, char const *argv[]){

	long taille;
	size_t result;
	FILE * imgFile;
	FILE * stockFile;
	short valeurPixel = 0;
	short max = 0;
	short octet1;
	short octet2;
	imgFile = fopen ("./BEAUFIX/beaufix.448x576x72.0.6250x0.6250x1.4.img","rb");
	stockFile = fopen ("stockage.txt","wb");
	if (imgFile!=NULL && stockFile!=NULL){
		fseek (imgFile , 0 , SEEK_END);
		taille = ftell (imgFile);
		rewind (imgFile);

		unsigned short *buffer = new unsigned short[taille];
		result = fread (buffer,2,taille,imgFile);
		cout << result << endl;
		if (result == taille/2) {
			for (int i = 0; i < result; i++){
				octet1 = buffer[i]%256;
				octet2 = buffer[i]/256;
				int valeurPixel = octet1*256+octet2;
				if (valeurPixel > max){
					max = valeurPixel;
				}
			}
			cout << "Max :\t" << max << endl;;
		}
		int retour = getValue(200,200,20);
		cout << retour;

		fclose (imgFile);
		free (buffer);
	}
	return 0;
}