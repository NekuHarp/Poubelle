#include <string>

class Noeud
{
	char info;
	Noeud * fils, * frere;
	int compteur;
	public :
	Noeud(char newinfo);
	void Recherche(std::string word, int n);
	void Affiche(std::string debut);
};

class ArbreLex
{
	Noeud *racine;
	public :
	ArbreLex();
	void Recherche(std::string word);
	void InsertFichier();
	void Affiche();
};
