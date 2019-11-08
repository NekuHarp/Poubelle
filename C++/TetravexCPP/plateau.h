#include "tetra.h"


class Plateau {
	// Cette classe gère le plateau de jeu, ainsi que la réserve de pièces de tetravex
	// Elle est inspirée de ma classe de plateau utilisée pour mon Dameo, lors de ma licence informatique
	
	public:
	int x;
	int y;
	int taillereserve;
	int taillereservemax;
	Tetra **grid;
	Tetra *reserve;
	bool *reserveused;
	
	Plateau();
	void Initialise();
	void AffichePlateau();
	void AfficheReserve();
	void AjoutReserve(Tetra tetra);
	void RemplirReserve();
	bool VerifCoup(int a, int i, int j);
	void JouerSeq(int i, int j);
	void JouerThread(int i, int j);
	//void JouerThreadpool(int i, int j);
	void AjoutPlateau(int a, int i, int j);
	void RetraitPlateau(int a, int i, int j);
	
};
