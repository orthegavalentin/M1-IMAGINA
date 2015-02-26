#include <iostream>
#include <vector>
#include <string>
#include "huffman.h"

using namespace std;

//retourn VRAI si carac est contenu dans le vector tab
bool isInside(string carac, vector<string> tab){
	bool retour = false;
	for(int i = 0; i<tab.size(); i++){
		if (tab[i] == (carac)){
			retour = true;
		}
	}
	return retour;
}

int main (int argc, char *argv[]){
	string argument = argv[1];
	cout << "la source contient " << argument.size() << " caracteres." << endl;
	vector<string> tabCaracteresContenus;
	string nextCar;
	//on lit les arguments caractere par caractere
	for(int i = 0; i<argument.size(); i++){
		nextCar = argv[1][i];
		//si le caractere n est pas dans le tableau, on l ajoute, sinon rien
		if(!isInside(nextCar, tabCaracteresContenus)){
			tabCaracteresContenus.push_back(nextCar);
		}
	}
	//affichage tu tableau de caracteres
	cout << "le parametre contient les caracteres suivants : " << endl;
	for(auto& i : tabCaracteresContenus){
		cout << i;
	}
		
	cout << endl;
	return 0;
	/* g++ -std=c++11 huffman.cpp -o huffman */
	
}