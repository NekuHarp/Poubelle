#include <iostream>
#include <stdlib.h>
#include <stdio.h>
//#include "tri.h"

using namespace std;

void Remplir(int * T, int n){
	for(int i=0; i<n; i++){
		T[i]=n-1-i;
	}
}

void Affiche(int * T, int n){
	for(int i=0; i<n; i++){
		cout<<T[i];
	}
	cout<<""<<endl;
}

void TriBulle(int * T, int n){
	bool tri = false;
	int x;
	while(tri!=true){
		Affiche(T,n);
		x=T[0];
		tri=true;
		for(int i=1; i<n; i++){
			if(x<=T[i]){
				x=T[i];
			} else {
				T[i-1]=T[i];
				T[i]=x;
				tri=false;
			}
		}
	}
}

void TriInsertion(int * T, int n){
	int x=T[0];
	for(int i=1; i<=n; i++){
		Affiche(T,n);
		x=T[i];
		for(int j=i-1; j>=0; j--){
			if(x<T[j]){
				T[j+1]=T[j];
				T[j]=x;
			} else {
				T[j]=x;
				j=0;
			}
		}
	}
}

int * Fusion(int * A, int * B, int a, int b){
	if(A==[]) return B;
	if(B==[]) return A;
	if(A[0]<=B[0]){
		
	}
	si A est le tableau vide
              retourner B
      si B est le tableau vide
              retourner A
      si A[1] ≤ B[1]
              retourner A[1] :: fusion(A[2, …, a], B)
      sinon
              retourner B[1] :: fusion(A, B[2, …, b])
}

int * TriFusion(int * T, int debut, int n){
	if(n>2){
		return Fusion(TriFusion(T,debut,n-debut/2),Fusion(T,(n-debut/2)+1,n),n/2,n/2);
	} else {
		return T;
	}
}


int main(){
	int n=10;
	int T[n];
	Remplir(T,n);
	cout<<"Tri à bulle"<<endl;
	TriBulle(T,n);
	cout<<""<<endl;
	Remplir(T,n);
	cout<<"Tri par insertion"<<endl;
	TriInsertion(T,n);
	cout<<""<<endl;
	Remplir(T,n);
	cout<<"Tri fusion"<<endl;
	
	cout<<""<<endl;
}
