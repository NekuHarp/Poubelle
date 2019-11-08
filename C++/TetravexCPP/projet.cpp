#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <mutex>
#include "plateau.h"

using namespace std;

// Pour compiler : g++ -std=c++11 -pthread projet.cpp tetra.h plateau.h -O3 -o projet
// On pensera à mettre le fichier input.txt au même endroit que l'exécutable

Tetra::Tetra(){
	// Constructeur par défaut d'une pièce de tetravex, qui contient les 4 valeurs de la pièce
	
	nord = 0;
	sud = 0;
	est = 0;
	ouest = 0;
	
}

Plateau::Plateau(){
	// Constructeur du plateau de jeu
	// grid est une matrice de pièces de tetravex qui correspond au plateau de jeu, x et y correspondent au nombre de ligne et de colonne
	// reserve est un tableautaillereserve est un compteur qui servira pour le remplissage et l'affichage de la réserve, taillereservemax est x*y pour le nombre de pièces max
	// On lance, lors de la construction du plateau, la fonction RemplirReserve, qui s'occupera alors de lire le fichier d'input afin de définir les valeurs des variables du plateau, ainsi que de remplir la réserve
	
	x = 0;
	y = 0;
	taillereserve = 0;
	taillereservemax = 0;
	grid = NULL;
	reserve = NULL;
	reserveused = NULL;
	RemplirReserve();
	
}

bool Plateau::VerifCoup(int a, int i, int j){
	// Cette fonction vérifie si un coup peut être joué, en fonction de sa position dans la réserve (int a), et de la position sur laquelle on veut la jouer sur le plateau (int i, int j)
	// Puisqu'on rempli le plateau dans le sens de lecture (de gauche à droite, de haut en bas), on ne vérifie que les pièces à gauche et en haut de la position i j
	
	
	Tetra tetra = reserve[a];
	
	if(i==0){
		if(j==0){
			return true;
		} else {
			if(tetra.nord==grid[i][j-1].sud){
				return true;
			} else {
				return false;
			}
		}
		if(j==0){
			return true;
		} else {
			if(tetra.nord==grid[i][j-1].sud){
				return true;
			} else {
				return false;
			}
		}
	} else {
		if(j==0){
			if(tetra.ouest==grid[i-1][j].est){
				return true;
			} else {
				return false;
			}
		} else {
			if((tetra.ouest==grid[i-1][j].est)&&(tetra.nord==grid[i][j-1].sud)){
				return true;
			} else {
				return false;
			}
		}
	}
	
}

void Plateau::AjoutReserve(Tetra tetra){
	// Cette fonction permet d'ajouter une pièce de tetravex dans la réserve, ainsi que de changer par défaut leur utilisation à "false"
	
	reserve[taillereserve] = tetra;
	reserveused[taillereserve] = false;
	taillereserve++;
	
}

void Plateau::RemplirReserve(){
	// Cette fonction est une réadaptation d'une fonction que j'avais moi-même réalisée en L2 dans un TP d'arbre lexicographique
	// La fonction originale, que j'avais réalisée en L2, est disponible en ligne à https://github.com/NekuHarp/Poubelle/tree/master/C%2B%2B/LexicoCPP
	// Elle permet de lire le fichier d'input et d'en extraire le nombre de lignes, colonnes, et les pièces, pour ensuite appeler AjoutReserve pour les ajouter à la réserve
	
	ifstream fichier("input.txt");
	
	int cpt = 0;
	int tempa;
	int tempb;
	int tempc;
	int tempd;
	
	if(fichier){
		
		fichier.seekg(0, ios::end);
		int taille;
		taille = fichier.tellg();
		fichier.seekg(0, ios::beg);
		string contenu;
		while(fichier >> contenu){
			if(cpt==0){
				y = stoi(contenu);
			} else if(cpt==1){
				x = stoi(contenu);
				Initialise();
			} else {
				if((cpt-2)%4==0){
					tempa = stoi(contenu);
				} else if((cpt-2)%4==1){
					tempb = stoi(contenu);
				} else if((cpt-2)%4==2) {
					tempc = stoi(contenu);
				} else {
					tempd = stoi(contenu);
					Tetra tetratemp;
					tetratemp.ouest = tempa;
					tetratemp.nord = tempb;
					tetratemp.est = tempc;
					tetratemp.sud = tempd;
					AjoutReserve(tetratemp);
				}
			}
			cpt++;
		}
	fichier.close();
	} else {
		cout << "Impossible d'ouvrir le fichier !" << endl;
	}
	
}

void Plateau::Initialise(){
	// Cette fonction va définir taillereservemax avec x et y, puis créer la réserve, un tableau reserveused, et la matrice du plateau de jeu
	
	taillereservemax = x*y;
	reserve = new Tetra [taillereservemax];
	reserveused = new bool [taillereservemax];
	grid = new Tetra *[x];
	for(int f=0;f<x;f++){
		grid[f] = new Tetra [y];
	}
	
}

void Plateau::AjoutPlateau(int a, int i, int j){
	// Cette fonction permet d'ajouter la pièce de tetravex stockée dans la réserve en position a sur le plateau en position i j, ainsi que de changer son état dans reserveused
	
	reserveused[a] = true;
	grid[i][j] = reserve[a];
	
}

void Plateau::RetraitPlateau(int a, int i, int j){
	// Cette fonction permet de retirer la pièce de tetravex stockée dans la réserve en position a sur le plateau en position i j, ainsi que de changer son état dans reserveused
	
	reserveused[a] = false;
	
}

void Plateau::AffichePlateau(){
	// Cette fonction simple affiche le plateau de jeu
	// Il faut cependant remplir le plateau avant de l'afficher, sous peine d'avoir une segmentation fault
	
	cout<<"S O L U T I O N"<<endl;
	for(int i=0; i<x; i++){
		cout<<"=====";
	}
	cout<<endl;
	for(int j=0; j<y; j++){
		for(int i=0; i<x; i++){
			cout<<"| "<<grid[i][j].nord<<" |";
		}
		cout<<endl;
		for(int i=0; i<x; i++){
			cout<<"|"<<grid[i][j].ouest<<" "<<grid[i][j].est<<"|";
		}
		cout<<endl;
		for(int i=0; i<x; i++){
			cout<<"| "<<grid[i][j].sud<<" |";
		}
		cout<<endl;
		for(int i=0; i<x; i++){
			cout<<"=====";
		}
		cout<<endl;
	}
	cout<<endl;
	
}

void Plateau::AfficheReserve(){
	// Cette fonction simple affiche la réserve, en affichant un maximum de 24 pièces par ligne
	
	cout<<endl<<"R E S E R V E"<<endl;
	int temp = 0;
	int lines = 0;
	if(taillereserve>=24){
		temp = taillereserve-24;
		taillereserve = 24;
	}
	for(int i=0; i<taillereserve; i++){
		cout<<"=====";
	}
	cout<<endl;
	for(int i=0; i<taillereserve; i++){
		cout<<"| "<<reserve[i+(lines*24)].nord<<" |";
	}
	cout<<endl;
	for(int i=0; i<taillereserve; i++){
		cout<<"|"<<reserve[i+(lines*24)].ouest<<" "<<reserve[i+(lines*24)].est<<"|";
	}
	cout<<endl;
	for(int i=0; i<taillereserve; i++){
		cout<<"| "<<reserve[i+(lines*24)].sud<<" |";
	}
	cout<<endl;
	for(int i=0; i<taillereserve; i++){
		cout<<"=====";
	}
	cout<<endl;
	taillereserve=temp;
	
	while(taillereserve>0){
		if(taillereserve>=24){
			temp = taillereserve-24;
			taillereserve = 24;
		} else {
			temp = 0;
		}
		
		lines++;
		for(int i=0; i<taillereserve; i++){
			cout<<"=====";
		}
		cout<<endl;
		for(int i=0; i<taillereserve; i++){
			cout<<"| "<<reserve[i+(lines*24)].nord<<" |";
		}
		cout<<endl;
		for(int i=0; i<taillereserve; i++){
			cout<<"|"<<reserve[i+(lines*24)].ouest<<" "<<reserve[i+(lines*24)].est<<"|";
		}
		cout<<endl;
		for(int i=0; i<taillereserve; i++){
			cout<<"| "<<reserve[i+(lines*24)].sud<<" |";
		}
		cout<<endl;
		for(int i=0; i<taillereserve; i++){
			cout<<"=====";
		}
		cout<<endl;
		taillereserve=temp;
		
	}
	
	cout<<endl;

}

void Plateau::JouerSeq(int i, int j){
	// Cette fonction est la fonction récursive qui permet de résoudre le tetravex, de façon séquencielle
	
	int ii = i;
	int jj = j;
	for(int temp = 0; temp<taillereservemax; temp++){
		if(!reserveused[temp]){
			if(VerifCoup(temp, i, j)){
				AjoutPlateau(temp, i, j);
				if(i+1==x){
					if(j+1==y){
						AffichePlateau();
						return;
					} else {
						ii = 0;
						jj=j+1;
					}
				} else {
					ii=i+1;
				}
				JouerSeq(ii, jj);
				RetraitPlateau(temp, i, j);
			}
		}
	}
	return;
	
}

void Plateau::JouerThread(int i, int j){
	// Cette fonction est la fonction récursive qui permet de résoudre le tetravex, avec des threads
	
	int ii = i;
	int jj = j;
	for(int temp = 0; temp<taillereservemax; temp++){
		if(!reserveused[temp]){
			if(VerifCoup(temp, i, j)){
				AjoutPlateau(temp, i, j);
				if(i+1==x){
					if(j+1==y){
						AffichePlateau();
						return;
					} else {
						ii = 0;
						jj=j+1;
					}
				} else {
					ii=i+1;
				}
				thread t(&Plateau::JouerThread, this, ii, jj);
				t.join();
				RetraitPlateau(temp, i, j);
			}
		}
	}
	return;
	
}

int main(int ac, char** av) {
	
	Plateau plat;
	//plat.AfficheReserve();
	plat.JouerSeq(0, 0);
	//plat.JouerThread(0, 0);
	return 0;
	
}