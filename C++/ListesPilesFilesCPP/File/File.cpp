#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class File
{
    int tete ;
    int queue ;
    int * tab ;
    int max ;
    public :
    File(){
        tete=0;
        queue=0;
        max=1000;
        tab=new int[max];
        tab[queue]=0;
    };
    File(int n, int x){
        tete=0;
        queue=0;
        max=n;
        tab=new int[max];
        tab[queue]=x;
    };
    ~File(){
        if(tete>-1){
            tete=-1;
            queue=-1;
            delete tab;
        }
    };
    bool Vide();
    bool Pleine();
    void Enfiler(int x);
    int Defiler();
    void Afficher();
};

bool File::Vide(){
    if(queue>-1){
        return false;
    } else {
        return true;
    }
}

bool File::Pleine(){
    if(queue=max){
        return true;
    } else {
        return false;
    }
}

void File::Enfiler(int x){
    if(!Pleine()){
        queue = queue + 1;
        tab[queue]=x;
    }
}

int File::Defiler(){
    int x=-1;
    if(!Vide()){
        x = tab[tete];
        tete = tete + 1;
    }
    return x;
}

void File::Afficher(){
    int i=tete;
    if(Vide()){
        cout << "Vide." << endl;
    } else {
        cout << "La tete est ici." << endl;
        while(i<=queue){
            cout << tab[i] << endl;
            i++;
        }
        cout << "La queue est ici." << endl;
    }
}

int main()
{
    return 0;
}
