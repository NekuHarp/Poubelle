#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "hash.h"

using namespace std;

int hashage(string mot, int B){
	int x=0;
	int N=mot.size();
	for(int i=0;i<N;i++){
		x=(x%B)+(((mot[i]-'A')*B)%B);
		x=x%B;
	}
	return x;
}

int hashage(int mot, int B){
	return mot%B;
}

template <typename T>
Maillon<T>::Maillon(T x){
	valeur=x;
	suivant=NULL;
}

template <typename T>
void Maillon<T>::inserermaillon(T x){
	if(suivant){
		suivant->inserermaillon(x);
	} else {
		suivant=new Maillon(x);
	}
}

template <typename T>
void Listechain<T>::insertion(T mot){
	if(!debut){
		debut=new Maillon<T>(mot);
	} else {
		debut->inserermaillon(mot);
	}
}

template <typename T>
void hash<T>::inserthash(T mot, int B){
	int x=hashage(mot,B);
	if(!tableau[x]) tableau[x]=new Listechain<T>;
	tableau[x]->insertion(mot);
}

template <typename T>
void hash<T>::fileinserthash(int B){
	ifstream fichier("mots.txt");
	if(fichier)
	{
		fichier.seekg(0, ios::end);
    		int taille;
    		taille = fichier.tellg();
		fichier.seekg(0, ios::beg);
	        string contenu;
		while(fichier >> contenu){
			inserthash(contenu,B);
		}
	        fichier.close();
	}
	else
	{
	        cout << "Impossible d'ouvrir le fichier !" << endl;
	}
}

template <typename T>
hash<T>::hash(T mot, int B){
	inserthash(mot,B);
}

int main(){
	string teststring = "azertyuiop";
	int testint = 12345;
	hash<string> * x = new hash<string>(teststring,26);
	delete x;
	hash<int> * y = new hash<int>(testint,26);
	delete y;
	return 0;
}
