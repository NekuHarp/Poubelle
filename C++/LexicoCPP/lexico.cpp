#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "lexico.h"

using namespace std;

Noeud::Noeud(char newinfo)
{
	info=newinfo;
	fils=NULL;
	frere=NULL;
	compteur=0;
}

ArbreLex::ArbreLex()
{
	racine=NULL;
}

void Noeud::Recherche(string word, int n)
{
	/*if(!info)
	{
		info=word[n];
	}*/
	if((info==word[n])&&(n==word.size()))
	{
		compteur=compteur+1;
	}

	if((info==word[n])&&(n!=word.size()))
	{
		if(!fils)
		{
			fils=new Noeud(word[n+1]);
		}
		fils->Recherche(word, n+1);
	}

	if(info!=word[n])
	{
		if(!frere)
		{
			frere=new Noeud(word[n]);
		}
		frere->Recherche(word, n);
	}
}

void ArbreLex::Recherche(string word)
{
	if(!racine) racine=new Noeud(word[0]);
	racine->Recherche(word, 0);
}

void ArbreLex::InsertFichier()
{
	ifstream fichier("texte_petit.txt"); // On pourra remplacer "texte_petit.txt" par "texte_moyen.txt" ou "texte_gros.txt"
        if(fichier)
        {
		fichier.seekg(0, ios::end);
    		int taille;
    		taille = fichier.tellg();
		fichier.seekg(0, ios::beg);
                string contenu;
		while(fichier >> contenu){
			Recherche(contenu);
		}
                fichier.close();
        }
        else
	{
                cout << "Impossible d'ouvrir le fichier !" << endl;
	}
}

void Noeud::Affiche(string debut)
{
	if(compteur!=0) cout<<debut<<" "<<compteur<<endl;
	else {
		fils->Affiche(debut+info);
	}
	if(frere) frere->Affiche(debut);	
}

void ArbreLex::Affiche()
{
	string debut;
	if(racine) racine->Affiche(debut);
	else cout<<"Arbre vide"<<endl;
}

int main()
{
	ArbreLex A;
	A.InsertFichier();
	A.Affiche();
	return 0;
}
