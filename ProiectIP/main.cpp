#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <unistd.h>
#include <cstdio>

using namespace std;


//VARIANTA 2 JUCATORI
/*
 * A isi alege un cifru pe care B il va ghici
 * B ...........................A ...........
 *
 * Incep turele:
 * A intreaba un cifru, B ii va raspunde sub forma: x m, y c, unde x,y naturale, m = mutate, c=centrate
 * Scorul este numarul de intrebari pana la raspunsul corect.
 *
 *
 * IDEE:
 * 1. buton de hint. scor+=20.
 */

unsigned *creareCifru(){
    //declarare variabile
    unsigned *cifru, *estePus;
    cifru=new unsigned[5];
    estePus=new unsigned[9];

    for(int i=0; i<10; ++i)
        estePus[i]=0;

    /* initialize random seed: */
    srand (time(NULL));

    //generez un nr intre 1 si 9 pt pozitia 1
    unsigned *nrSecret;
    nrSecret=new unsigned;
    *nrSecret=(unsigned )(rand()%9)+1;
    cifru[0]=*nrSecret;
    estePus[*nrSecret]=1;

    //generare pentru restul pozitiilor din cifru
    for(int i=1; i<5; ++i){
        //generate secret number
        *nrSecret = rand() % 10;
        while (estePus[*nrSecret]!=0){
            //generate secret number
            *nrSecret = rand() % 10;
        }
        cifru[i]=*nrSecret;
        estePus[*nrSecret]=1;
    }
    delete(nrSecret);
    delete(estePus);
    return cifru;
}

bool suntEgale(unsigned *cifru, unsigned *cifruDat){
    for(int i=0; i<5; ++i){
        if(cifru[i]!=cifruDat[i])
            return 0;
    }
    return 1;
}

void afisCifru(unsigned *cifru){
    for(int i=0; i<5; ++i)
        cout<<cifru[i]<<" ";
    cout<<"\n";
}

void calcAjutator(){
    unsigned *cifru, *cifruMeu, nrElemCentrate, nrElemMutate;


    cifru=new unsigned[5];
    cifru=creareCifru();
    cifruMeu=new unsigned[5];

    do{
        nrElemCentrate=nrElemMutate=0;

        printf("Introduceti cifrul dvs:");
        for(int i=0; i<5; ++i){
            cin>>cifruMeu[i];
            if(cifruMeu[i]==cifru[i])
                nrElemCentrate++;
        }
        for(int i=0; i<5; ++i)
            for(int j=0; j<5; ++j){
                if(i!=j)
                    if (cifru[i]==cifruMeu[j]){
                        nrElemMutate++;
                        break;
                    }
            }
        cout<<"elemCentrate: "<<nrElemCentrate<<'\t'<<"elemMutate: "<<nrElemMutate<<"\n";
    }while (!suntEgale(cifru, cifruMeu));


}

int main() {

    calcAjutator();

    return 0;
}
