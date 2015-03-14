#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string> 
using namespace std;

int tailleX = 256;
int tailleY = 256;
int tailleZ = 128;
unsigned short * buffer;

int getValue(unsigned short * buffer,int x, int y, int z){
	int num = z*(tailleX*tailleY)+(y*tailleX)+x;
	int oct1 = buffer[num]%256;
	int oct2 = buffer[num]/256;
	int valPixel = oct1*256+oct2;
	return valPixel;
}

int main(int argc, char const *argv[]){
	long taille;
	size_t result;
	FILE * imgFile;
	FILE * stockFile;
	short valeurPixel = 0;
	short octet1;
	short octet2;
	int seuil = 200;
	//imgFile = fopen ("./BEAUFIX/beaufix.448x576x72.0.6250x0.6250x1.4.img","rb");
	//imgFile = fopen ("./BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img","rb");
	imgFile = fopen ("./engine/engine.256x256x128.1x1x1.img","rb");
	//imgFile = fopen ("./FOOT/foot.256x256x256.1.1.1.img","rb");
	//imgFile = fopen ("./MANIX/manixSansIV.512x512x48.0.4570x0.4570x3.0.img","rb");
	//imgFile = fopen ("./WHATISIT/whatisit.301x324x56.1.1.1.4.img","rb");
	if (imgFile!=NULL){
		fseek (imgFile , 0 , SEEK_END);
		taille = ftell (imgFile);
		rewind (imgFile);
		unsigned short *buffer = new unsigned short[taille];
		result = fread (buffer,2,taille,imgFile);
		cout << result << endl;
		// if (result == taille/2) {
		// 	for (int i = 0; i < result; i++){
		// 		octet1 = buffer[i]%256;
		// 		octet2 = buffer[i]/256;
		// 		int valeurPixel = octet1*256+octet2;
		// 	}
		// }
		int retour = getValue(buffer,200,200,20);
		cout << retour << endl;

		stockFile = fopen ("engineSeuil.0.raw","wb");

		unsigned short *render = new unsigned short[(tailleX-2)*(tailleY-2)*(tailleZ-2)];
		int cpt = 0;
		for (int k = 1; k < tailleZ-1; k++){
			for (int j = 1; j < tailleY-1; j++){
				for (int i = 1; i < tailleX-1; i++){
					int val = getValue(buffer,i,j,k);
					if(val > seuil){
						render[cpt] = (256*256)-1;
					}
					else{
						render[cpt] = 00;
					}
					cpt++;
				}
			}
		}

		fwrite(render,2,tailleX*tailleY*tailleZ,stockFile);

		fclose(stockFile);
		fclose(imgFile);
		free (buffer);
	}
	return 0;
}
