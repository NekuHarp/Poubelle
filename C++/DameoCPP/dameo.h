class Grille
{
	int size;
	int **grid;
	public:
	Grille();
	void Initialise(int gridsize);
	void Affiche();
	void Jouer(bool joueur);
	bool Selection(bool joueur, int x, int y);
	bool Possible(int x, int y, int a, int b);
	bool PossibleChain(int x, int y, int a, int b);
	void Deplacement(int x, int y, int a, int b);
	void SerieDeplacement(int x, int y);
	int VerifRoi(int x, int y, int a, int b);
	void DeplaRoi(int compteur, int x, int y, int a, int b);
	void Delete(int x, int y);
	bool Fin();
};
