#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include <winbgim.h>
#include <cmath>


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
    scroll=100;

    //coordonate sageti
    upArrow.stSus.x=10;
    upArrow.stSus.y=10;
    upArrow.drJos.x=30;
    upArrow.drJos.y=30;

    downArrow.stSus.x=10;
    downArrow.stSus.y=35;
    downArrow.drJos.x=30;
    downArrow.drJos.y=55;

    rectangle(upArrow.stSus.x, upArrow.stSus.y, upArrow.drJos.x, upArrow.drJos.y);
    rectangle(downArrow.stSus.x, downArrow.stSus.y, downArrow.drJos.x, downArrow.drJos.y);

    for(int i=0; i<7; ++i)
        rectangle(desenCord.x+i*latura, desenCord.y,
                   desenCord.x+(i+1)*latura, desenCord.y+latura);

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

bool isButonClicked(CORD mouse, BUTON buton){
    return(buton.stSus.x<=mouse.x && mouse.x<=buton.drJos.x &&
           buton.stSus.y<=mouse.y && mouse.y<=buton.drJos.y);
}

void update(unsigned *cifruMeu, unsigned *cifru, unsigned nrElemMutate, unsigned nrElemCentrate, unsigned matCifru[1000][5]){

        char *elemM, *elemC;
        elemM=new char[5];
        elemC=new char[5];
        itoa(nrElemMutate, elemM, 10);
        itoa(nrElemCentrate, elemC, 10);


        for(int i=0; i<5; ++i){
            char *cifra;
            cifra=new char[5];
            itoa(cifruMeu[i], cifra, 10);
            outtextxy(desenCord.x+latura*(i+2)+latura/2-5, desenCord.y+latura*linie+latura/2-5, cifra);
        }

        for(int i=0; i<5; ++i){
            char *cifra;
            cifra=new char[5];
            itoa(cifru[i], cifra, 10);
            outtextxy(desenCord.x+latura*(i+2)+latura/2-5, desenCord.y+latura/2-5, cifra);
        }


    if(ismouseclick(WM_LBUTTONDOWN)){
        clearmouseclick(WM_LBUTTONDOWN);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();

        if(isButonClicked(mouse, upArrow)){
            scroll=-abs(scroll);

            //stergere
            setcolor(BLACK);

            //prima linie.
            for(int j=0; j<7; ++j){
                rectangle(desenCord.x+j*latura, desenCord.y+linie*latura,
                        desenCord.x+(j+1)*latura, desenCord.y+latura*(linie+1));
            }
            for(int j=0; j<5; ++j){
                char *cifra;
                cifra=new char[5];
                itoa(cifru[j], cifra, 10);
                outtextxy(desenCord.x+latura*(j+2)+latura/2-5, desenCord.y+latura/2-5, cifra);
            }
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

            //restul liniilor
            for(int i=1; i<linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura/2-5, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //prima linie.
            for(int j=0; j<7; ++j)
                rectangle(desenCord.x+j*latura, desenCord.y+linie*latura,
                        desenCord.x+(j+1)*latura, desenCord.y+latura*(linie+1));

            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

            //restul liniilor....
            ///TODO: nu prea merge de aici.. deci nu isi are rostul sa faci din cod aici. tb sa refaci cateva chesstiii.
        }


        if(isButonClicked(mouse, downArrow)){
            scroll=abs(scroll);

            //stergere
            setcolor(BLACK);

            //prima linie.
            for(int j=0; j<7; ++j){
                rectangle(desenCord.x+j*latura, desenCord.y+linie*latura,
                        desenCord.x+(j+1)*latura, desenCord.y+latura*(linie+1));
            }
            for(int j=0; j<5; ++j){
                char *cifra;
                cifra=new char[5];
                itoa(cifru[j], cifra, 10);
                outtextxy(desenCord.x+latura*(j+2)+latura/2-5, desenCord.y+latura/2-5, cifra);
            }
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

            //restul liniilor
            for(int i=1; i<linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura/2-5, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //prima linie.
            for(int j=0; j<7; ++j)
                rectangle(desenCord.x+j*latura, desenCord.y+linie*latura,
                        desenCord.x+(j+1)*latura, desenCord.y+latura*(linie+1));

            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");
        }

    }
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
    //variabile
    unsigned *cifru, *cifruMeu, nrElemCentrate, nrElemMutate, scor=0, matCifru[1000][5]={};

    cifru=new unsigned[5];
    cifru=creareCifru();
    cifruMeu=new unsigned[5];

    for(int i=2; i<7; ++i)
        matCifru[0][i]=cifru[i-2];

    do{
        nrElemCentrate=nrElemMutate=0;

        //input utilizator
        printf("Introduceti cifrul dvs:");
        char *cifruMeuChar;
        cifruMeuChar=new char;

        cin>>cifruMeuChar;

        //prelucrare input
        for(int i=0; i<5; ++i){
            cifruMeu[i]=cifruMeuChar[i]-'0';
            if(cifruMeu[i]==cifru[i])
                nrElemCentrate++;

            //pun inputul in matrice
            matCifru[linie+1][i+2]=cifruMeu[i];
        }
        for(int i=0; i<5; ++i)
            for(int j=0; j<5; ++j){
                if(i!=j)
                    if (cifru[i]==cifruMeu[j]){
                        nrElemMutate++;
                        break;
                    }
            }
        matCifru[linie+1][0]=nrElemCentrate;
        matCifru[linie+1][1]=nrElemMutate;

        scor++;

        //afisare prelucrare.
        //crestem linia pe care ne-am afla.
        linie++;
        //desenam
        for(int i=0; i<7; ++i)
            rectangle(desenCord.x+i*latura, desenCord.y+linie*latura,
                      desenCord.x+(i+1)*latura, desenCord.y+latura*(linie+1));

        char *elemM, *elemC;
        elemM=new char[5];
        elemC=new char[5];
        itoa(nrElemMutate, elemM, 10);
        itoa(nrElemCentrate, elemC, 10);

        outtextxy(desenCord.x+latura/2-5, desenCord.y+latura*linie+latura/2-5, elemC);
        outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura*linie+latura/2-5, elemM);

        //punem cifrele alese de utilizator
        for(int i=0; i<5; ++i){
            char *cifra;
            cifra=new char[5];
            itoa(cifruMeu[i], cifra, 10);
            outtextxy(desenCord.x+latura*(i+2)+latura/2-5, desenCord.y+latura*linie+latura/2-5, cifra);
        }

        //update pentru cazul in care apasa pe scroll buttons.
        update(cifruMeu, cifru, nrElemMutate, nrElemCentrate, matCifru);

    }while (!suntEgale(cifru, cifruMeu));

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
