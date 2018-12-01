#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include <winbgim.h>


using namespace std;
///TODO:

/*
 * IDEE:
 * 1. buton de hint. scor+=20.
 */

 //variabile globale


unsigned latura, gata=0, latime, linie;
int scroll;

struct CORD{
    int x, y;
}desenCord;

struct BUTON{
    CORD stSus, drJos;
}upArrow, downArrow;


//init desen
void initDesen(unsigned *cifru){
    latime=300;
    latura=300/7;
    desenCord.x=(getmaxx()-latime)/2;
    desenCord.y=100;
    linie=0;

    for(int i=0; i<7; ++i)
        rectangle(desenCord.x+i*latura, desenCord.y, desenCord.x+(i+1)*latura, desenCord.y+latura);

    outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
    outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

    for(int i=0; i<5; ++i){
        char *cifra;
        cifra=new char[5];
        itoa(cifru[i], cifra, 10);
        outtextxy(desenCord.x+latura*(i+2)+latura/2-5, desenCord.y+latura/2-5, cifra);
    }
}

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

        scor++;


        linie++;
        for(int i=0; i<7; ++i)
            rectangle(desenCord.x+i*latura, desenCord.y+linie*latura, desenCord.x+(i+1)*latura, desenCord.y+latura*(linie+1));


        char *elemM, *elemC;
        elemM=new char[5];
        elemC=new char[5];
        itoa(nrElemMutate, elemM, 10);
        itoa(nrElemCentrate, elemC, 10);

        outtextxy(desenCord.x+latura/2-5, desenCord.y+latura*linie+latura/2-5, elemC);
        outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura*linie+latura/2-5, elemM);

        for(int i=0; i<5; ++i){
            char *cifra;
            cifra=new char[5];
            itoa(cifru[i], cifra, 10);
            outtextxy(desenCord.x+latura*(i+2)+latura/2-5, desenCord.y+latura*linie+latura/2-5, cifra);
        }

    }while (!suntEgale(cifru, cifruMeu));

    cout<<"\n\nfelicita!";
    cout<<"\nscor: "<<scor;
}



int main() {

    initwindow(800,800);

    unsigned* cifru=new unsigned[5];
    cifru=creareCifru();
    initDesen(cifru);

    calcAjutator();


    getch();
    closegraph();

    return 0;
}
