#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Noeud{
	public :
	string name;
	Noeud* pere;
	Noeud* fg;
	Noeud* frd;
	Noeud(string &s){
		name = s;
		pere = NULL;
		fg = NULL;
		frd = NULL;
	};
};

class Arbre{
	Noeud * r ;
	Noeud * c ;
	public :
	Arbre() ;
	∼Arbre() ;
	Noeud* construitNoeud(string &s) ;

};

Arbre::Arbre(){
	string h = "/";
	r=construitNoeud(h);
	c=r;
}

Noeud* Arbre::construitNoeud(string &s){
	Noeud* n = new Noeud(s);
	string h = ".";
	n->fg = new Noeud(h);
	h = "..";
	n->fg->frd = new Noeud(h);
	return(n);
}

void analyserchemin(string &s, int &n, string *T){
	n=0;
	int i=1;
	while(1<s.size()){
		while(s[i]!="/" && i<s.size()){
			T[n]+=s[i];
			i++;
		}
		i++;
		n++;
	}
}



