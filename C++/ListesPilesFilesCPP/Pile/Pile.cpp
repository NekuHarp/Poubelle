#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Pile
{
    int tete ;
    int * tab ;
    int max ;
    public :
    Pile(){
        tete=0;
        max=1000;
        tab=new int[max];
        tab[tete]=0;
    };
    Pile(int n, int x){
        tete=0;
        max=n;
        tab=new int[max];
        tab[tete]=x;
    };
    ~Pile(){
        if(tete>-1){
            tete=-1;
            delete tab;
        }
    };
    bool Vide();
    bool Pleine();
    void Empiler(int x);
    int Depiler();
    void Afficher();
};

bool Pile::Vide(){
    if(tete>-1){
        return false;
    } else {
        return true;
    }
}

bool Pile::Pleine(){
    if(tete=max){
        return true;
    } else {
        return false;
    }
}

void Pile::Empiler(int x){
    if(!Pleine()){
        tete = tete + 1;
        tab[tete]=x;
    }
}

int Pile::Depiler(){
    int x=-1;
    if(!Vide()){
        x = tab[tete];
        tete = tete -1;
    }
    return x;
}

void Pile::Afficher(){
    int i=0;
    if(Vide()){
        cout << "Vide." << endl;
    } else {
        cout << "La tete est ici." << endl;
        while(i<=tete){
            cout << tab[tete-i] << endl;
            i++;
        }
        cout << "Le fond de la pile est ici." << endl;
    }
}

int main()
{
    return 0;
}
