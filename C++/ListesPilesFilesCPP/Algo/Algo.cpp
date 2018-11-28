#include <iostream>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class maillon
{
    public :
    int val ;
    maillon * succ ;
    maillon * pred ;
    ~maillon(){
        if(succ){
            delete succ;
        }
    } ;
} ;

class Liste
{
    maillon * tete ;
    maillon * queue ;
    public :
    Liste(){
        tete=NULL;
        queue=NULL;
    };
    ~Liste(){
        if(tete){
            delete tete;
        }
    };
    bool Vide();
    void insertion_queue(maillon *x);
    void insertion_tete(maillon *x);
    int recherche(maillon *x);
    void suppression(int x);
} ;

void Liste::insertion_queue(maillon *x){
    x->pred=queue;
    x->succ=NULL;
    if(!Vide()){
        queue->succ=x;
    } else {
        tete=x;
    }
    queue=x;
    return;
}

void Liste::insertion_tete(maillon *x){
    x->pred=NULL;
    x->succ=tete;
    if(!Vide()){
        tete->pred=x;
    } else {
        queue=x;
    }
    tete=x;
    return;
}

bool Liste::Vide(){
    if(tete==NULL){
        return true;
    } else {
        return false;
    }
}

int Liste::recherche(maillon *x){
    if(Vide()) {
        return -1;
    }
    int count = 0;
    maillon* temp;
    temp = tete;
    while((temp!=NULL)&&(x->val!=temp->val)){
        temp=temp->succ;
        count++;
    }
    cout << count << endl;
    return count;
}

void Liste::suppression(int x){
    if((Vide())||(x<0)) {
        return;
    }
    maillon* temp;
    maillon* tempmoinsun;
    temp=tete;
    int count = 0;
    while((count!=x)&&(temp!=NULL)){
        tempmoinsun=temp;
        temp=temp->succ;
        count++;
    }
    tempmoinsun->succ=temp->succ;
    return;
}

int main()
{
    Liste test;
    maillon x;
    maillon y;
    x.val=1;
    y.val=5;
    test.insertion_tete(&x);
    test.insertion_queue(&y);
    if(test.Vide()){
        cout << "Vide." << endl;
    } else {
        cout << "Non-vide." << endl;
    }
    test.recherche(&x);
    test.suppression(0);
    return 0;
}
