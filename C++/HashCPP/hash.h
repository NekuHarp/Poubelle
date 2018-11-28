#include <string>
using namespace std;

template <typename T>
class Maillon
{
	T valeur;
	Maillon<T> * suivant;
	public :
	/*Maillon(){
		valeur=NULL;
		suivant=NULL;
	};*/
	Maillon(T x);
	void inserermaillon(T x);
};

template <typename T>
class Listechain
{
	Maillon<T> * debut;
	public :
	Listechain<T>(){
		debut = NULL;
	};
	void insertion(T x);
};

template <typename T>
class hash
{
	int N;
	Listechain<T> * tableau[];
	public :
	hash<T>(T mot, int B);
	void fileinserthash(int B);
	void inserthash(T mot, int B);
};
