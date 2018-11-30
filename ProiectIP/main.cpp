#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>


using namespace std;


/*
 * IDEE:
 * 1. buton de hint. scor+=20.
 */

//functii folositoare
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


//VARIANTA PC AJUTATOR

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

void calcAjutator(){
    unsigned *cifru, *cifruMeu, nrElemCentrate, nrElemMutate, scor=0;

    cifru=new unsigned[5];
    cifru=creareCifru();
    cifruMeu=new unsigned[5];

    do{
        nrElemCentrate=nrElemMutate=0;

        printf("Introduceti cifrul dvs:");
        char *cifruMeuChar;
        cifruMeuChar=new char;

        cin>>cifruMeuChar;

        for(int i=0; i<5; ++i){
            cifruMeu[i]=cifruMeuChar[i]-'0';
            if(cifruMeu[i]==cifru[i])
                nrElemCentrate++;        }


        for(int i=0; i<5; ++i)
            for(int j=0; j<5; ++j){
                if(i!=j)
                    if (cifru[i]==cifruMeu[j]){
                        nrElemMutate++;
                        break;
                    }
            }
        cout<<"elemCentrate: "<<nrElemCentrate<<'\t'<<"elemMutate: "<<nrElemMutate<<"\n";
        scor++;
    }while (!suntEgale(cifru, cifruMeu));

    cout<<"\n\nfelicita!";
    cout<<"\nscor: "<<scor;

}

int main() {

    calcAjutator();

    return 0;
}
