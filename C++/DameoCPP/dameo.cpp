#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "dameo.h"

using namespace std;

Grille::Grille(){
	size = 8;
	grid = NULL;
}

void Grille::Initialise(int gridsize){
	size = gridsize;
	grid = new int *[size];
	for(int f=0;f<size;f++){
        	grid[f] = new int[size];
	}
	// Génération normale
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(i==0){
				grid[i][j]=-1;
			} else if(i==size-1){
				grid[i][j]=1;
			} else if((i==1)&&(j>0)&&(j<size-1)){
				grid[i][j]=-1;
			} else if((i==2)&&(j>1)&&(j<size-2)){
				grid[i][j]=-1;
			} else if((i==size-2)&&(j>0)&&(j<size-1)){
				grid[i][j]=1;
			} else if((i==size-3)&&(j>1)&&(j<size-2)){
				grid[i][j]=1;
			} else {
				grid[i][j]=0;
			}
		}
	}
	// Génération test
	/*for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			grid[i][j]=0;
		}
	}
	grid[2][3]=1;
	grid[2][2]=-1;
	grid[3][1]=-1;
	grid[0][7]=2;*/
}



bool Grille::Selection(bool joueur, int x, int y){
	if((x<0)||(x>=size)||(y<0)||(y>=size)||(grid[x][y]==0)){
		return false;
	} else if(((grid[x][y]<0)&&(joueur==true))||((grid[x][y]>0)&&(joueur==false))){
		return false;
	} else {
		return true;
	}
}

bool Grille::Possible(int x, int y, int a, int b){
	int pion = grid[x][y];
	int destination = grid[a][b];
	if(destination != 0){
		return false;
	}
	if((a<0)||(a>=size)||(b<0)||(b>=size)){
		return false;
	}
	if(pion<0){ // conditions pour joueur 2 / * / #
		if(pion==-1){ // Gérer les pions *
			if((a==x+1)&&((b>=y-1)&&(b<=y+1))){
				Deplacement(x, y, a, b);
				return true;
			}
			if((a==x)&&(((b==y+2)&&(grid[x][y+1]>0))||((b==y-2)&&(grid[x][y-1]>0)))){
				if(b==y+2){
					Delete(x,y+1);
				} else {
					Delete(x,y-1);
				}
				Deplacement(x, y, a, b);
				SerieDeplacement(a, b);
				return true;
			}
			if((b==y)&&(((a==x+2)&&(grid[x+1][y]>0))||((a==x-2)&&(grid[x-1][y]>0)))){
				if(a==x+2){
					Delete(x+1,y);
				} else {
					Delete(x-1,y);
				}
				Deplacement(x, y, a, b);
				SerieDeplacement(a, b);
				return true;
			}
			return false;
		} else { // Gérer les rois #
			if(((x==a)&&(b!=y))||((y==b)&&(a!=x))||(x-a==y-b)){
				int compteur = VerifRoi(x, y, a, b);
				if(compteur<=1){
					DeplaRoi(compteur, x, y, a, b);
					return true;
				}
			}
			return false;
		}
	} else { // conditions pour joueur 1 / + / x
		if(pion==1){ // Gérer les pions +
			if((a==x-1)&&((b>=y-1)&&(b<=y+1))){
				Deplacement(x, y, a, b);
				return true;
			}
			if((a==x)&&(((b==y+2)&&(grid[x][y+1]<0))||((b==y-2)&&(grid[x][y-1]<0)))){
				if(b==y+2){
					Delete(x,y+1);
				} else {
					Delete(x,y-1);
				}
				Deplacement(x, y, a, b);
				SerieDeplacement(a, b);
				return true;
			}
			if((b==y)&&(((a==x+2)&&(grid[x+1][y]<0))||((a==x-2)&&(grid[x-1][y]<0)))){
				if(a==x+2){
					Delete(x+1,y);
				} else {
					Delete(x-1,y);
				}
				Deplacement(x, y, a, b);
				SerieDeplacement(a, b);
				return true;
			}
			return false;
		} else { // Gérer les rois x
			if(((x==a)&&(b!=y))||((y==b)&&(a!=x))||(x-a==y-b)){
				int compteur = VerifRoi(x, y, a, b);
				if(compteur<=1){
					DeplaRoi(compteur, x, y, a, b);
					return true;
				}
			}
			return false;
		}			
	}
}

bool Grille::PossibleChain(int x, int y, int a, int b){
	if(((x==a)&&((y+2==b)||(y-2==b)))||((y==b)&&((x+2==a)||(x-2==a)))){
		if((grid[x][y]>0)&&(grid[a][b]==0)&&(grid[(x+a)/2][(y+b)/2]<0)){
			Delete((x+a)/2,(y+b)/2);
			Deplacement(x, y, a, b);
			SerieDeplacement(a, b);
			return true;
		}
		if((grid[x][y]<0)&&(grid[a][b]==0)&&(grid[(x+a)/2][(y+b)/2]>0)){
			Delete((x+a)/2,(y+b)/2);
			Deplacement(x, y, a, b);
			SerieDeplacement(a, b);
			return true;
		}
	}
	return false;
}

void Grille::Deplacement(int x, int y, int a, int b){
	if((a==0)&&(grid[x][y]==1)){
		grid[x][y]=2;
	}
	if((a==size-1)&&(grid[x][y]==-1)){
		grid[x][y]=-2;
	}
	int temp = grid[x][y];
	grid[x][y]=0;
	grid[a][b]=temp;
}

void Grille::SerieDeplacement(int x, int y){
	int test=0;
	int a;
	int b;
	Affiche();
	if((x>0)&&(x<size-1)&&(y>0)&&(y<size-1)){
		if(((grid[x][y]>0)&&(((grid[x][y+1]<0)&&(grid[x][y+2]==0))||((grid[x][y-1]<0)&&(grid[x][y-2]==0))||((grid[x+1][y]<0)&&(grid[x+2][y]==0))||((grid[x-1][y]<0)&&(grid[x-2][y]==0))))||((grid[x][y]<0)&&(((grid[x][y+1]>0)&&(grid[x][y+2]==0))||((grid[x][y-1]>0)&&(grid[x][y-2]==0))||((grid[x+1][y]>0)&&(grid[x+2][y]==0))||((grid[x-1][y]>0)&&(grid[x-2][y]==0))))){
			cout << "Vous pouvez prendre un autre pion. Voulez-vous le faire ?" << endl << "(Un nombre positif ou nul pour oui, un nombre négatif pour non)" << endl;
			cin >> test;
			if(test>=0){
				cout << "Saisir les coordonnées de déplacement" << endl;
				cin >> b;
				cin >> a;
				while(!PossibleChain(x, y, a, b)){
					cout << "Coordonnées incorrectes, saisissez les coordonnées de déplacement" << endl;
					cin >> b;
					cin >> a;
				}
			}
		}
	}
}

int Grille::VerifRoi(int x, int y, int a, int b){
	int compteur = 0;
	if(grid[x][y]==2){
		if(x>=a){
			for(int i=a;i<x;i++){
				if(y>=b){
					for(int j=b;j<=y;j++){
						if(grid[i][j]<0) compteur++;
						if(grid[i][j]>0) compteur = compteur + 2;
					}
				} else {
					for(int j=y;j<=b;j++){
						if(grid[i][j]<0) compteur++;
						if(grid[i][j]>0) compteur = compteur + 2;
					}
				}
			}
		} else {
			for(int i=x+1;i<=a;i++){
				if(y>=b){
					for(int j=b;j<=y;j++){
						if(grid[i][j]<0) compteur++;
						if(grid[i][j]>0) compteur = compteur + 2;
					}
				} else {
					for(int j=y;j<=b;j++){
						if(grid[i][j]<0) compteur++;
						if(grid[i][j]>0) compteur = compteur + 2;
					}
				}
			}
		}
	} else {
		if(x>=a){
			for(int i=a;i<x;i++){
				if(y>=b){
					for(int j=b;j<=y;j++){
						if(grid[i][j]>0) compteur++;
						if(grid[i][j]<0) compteur = compteur + 2;
					}
				} else {
					for(int j=y;j<=b;j++){
						if(grid[i][j]>0) compteur++;
						if(grid[i][j]<0) compteur = compteur + 2;
					}
				}
			}
		} else {
			for(int i=x+1;i<=a;i++){
				if(y>=b){
					for(int j=b;j<=y;j++){
						if(grid[i][j]>0) compteur++;
						if(grid[i][j]<0) compteur = compteur + 2;
					}
				} else {
					for(int j=y;j<=b;j++){
						if(grid[i][j]>0) compteur++;
						if(grid[i][j]<0) compteur = compteur + 2;
					}
				}
			}
		}
	}
	return compteur;
}

void Grille::DeplaRoi(int compteur, int x, int y, int a, int b){
	int temp = grid[x][y];
	grid[x][y] = 0;
	if(compteur==1){	
		if(x>=a){
			for(int i=a;i<=x;i++){
					if(y>=b){
						for(int j=b;j<=y;j++){
							grid[i][j]=0;
						}
					} else {
						for(int j=y;j<=b;j++){
							grid[i][j]=0;
						}
					}
			}
		} else {
			for(int i=x;i<=a;i++){
				if(y>=b){
					for(int j=b;j<=y;j++){
						grid[i][j]=0;
					}
				} else {
					for(int j=y;j<=b;j++){
						grid[i][j]=0;
					}
				}
			}
		}
	}
	grid[a][b] = temp;
	if(compteur==1){
		SerieDeplacement(a, b);
	}
}
	

void Grille::Delete(int x, int y){
	grid[x][y]=0;
}

bool Grille::Fin(){
	bool a=true;
	bool b=true;
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(grid[i][j]>0){
				a=false;
			}
			if(grid[i][j]<0){
				b=false;
			}
		}
	}
	if((a==true)||(b==true)){
		return true;
	} else {
		return false;
	}
}

void Grille::Affiche(){
	system("clear");
	for(int i=0;i<size;i++){
		if(i<10){
			cout << i << " |";
		} else {
			cout << i << "|";
		}
		for(int j=0;j<size;j++){
			if(grid[i][j]==1){
				cout << " + ";
			}
			if(grid[i][j]==-1) {
				cout << " * ";
			}
			if(grid[i][j]==2) {
				cout << " x ";
			}
			if(grid[i][j]==-2) {
				cout << " # ";
			}
			if(grid[i][j]==0) {
				cout << "   ";
			}
		}
		cout << endl;
	}
	cout << "   ";
	for(int k=0;k<size;k++){
		cout << "---";
	}
	cout << endl;
	cout << "   ";
	for(int k=0;k<size;k++){
		if(k<10){
			cout << " " << k << " ";
		} else {
			cout << k << " ";
		}
	}
	cout << endl;
}

void Grille::Jouer(bool joueur){ // true = joueur -(2) = */#; false = joueur +(1) = +/x
	Affiche();
	int x;
	int y;
	int a;
	int b;
	if(joueur==true){
		cout << "Joueur 1, + x" << endl;
	} else {
		cout << "Joueur 2, * #" << endl;
	}
	cout << "Saisissez les coordonnées du pion à bouger" << endl;
	cin >> y;
	cin >> x;
	while(!Selection(joueur, x, y)){
		cout << "Coordonnées incorrectes, saisissez les coordonnées du pion à bouger" << endl;
		cin >> y;
		cin >> x;
	}
	cout << "Saisissez les coordonnées de la case destination (une valeur négative pour annuler la sélection du pion)" << endl;
	cin >> b;
	cin >> a;
	if((a<0)||(b<0)){
		Jouer(joueur);
	} else {
		while((!Possible(x, y, a, b))||(a<0)||(b<0)){
			cout << "Coordonnées incorrectes, saisissez les coordonnées de la case destination" << endl;
			cin >> b;
			cin >> a;
		}
		if((a<0)||(b<0)){
			Jouer(joueur);
		} else {
			if(!Fin()){
				if(joueur==true){
					Jouer(false);
				} else {
					Jouer(true);
				}
			} else {
				Affiche();
				cout << "Victoire !" << endl;
			}		
		}
	}
}

int main(){
	system("clear");
	int gridsize;
	cout << "Entrez une taille de grille carrée (minimum 8, maximum 60)" << endl << "(La taille maximale est là pour éviter des problèmes visuels)" << endl;
	cin >> gridsize;
	if(gridsize <= 8){
		gridsize = 8;
	}
	if(gridsize >= 60){
		gridsize = 60;
	}
	Grille plateau;
	plateau.Initialise(gridsize);
	plateau.Jouer(true);
}
