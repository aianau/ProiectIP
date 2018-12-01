#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include <winbgim.h>
#include <cmath>
using namespace std;

/*
 * IDEE:
 * 1. buton de hint. scor+=20.
 */

 //variabile globale
unsigned latura, gata, latime, linie;
int scroll;

struct CORD{
    int x, y;
}desenCord;

struct BUTON{
    CORD stSus, drJos;
}upArrow, downArrow, zero, unu, doi, trei, patru, cinci, sase, sapte, opt, noua;


void drawButton(BUTON buton){
    rectangle(buton.stSus.x, buton.stSus.y, buton.drJos.x, buton.drJos.y);
}

void initCordButton(BUTON &buton, int x1, int y1, int x2, int y2){
    buton.stSus.x=x1;
    buton.stSus.y=y1;
    buton.drJos.x=x2;
    buton.drJos.y=y2;
}

//init desen
void initDesen(){
    latime=300;
    latura=300/7;
    desenCord.x=(getmaxx()-latime)/2;
    desenCord.y=100;
    linie=0;
    scroll=100;

    //coordonate sageti
    initCordButton(upArrow, 10, 10, 30, 30);
    initCordButton(downArrow, 10, 35, 30, 55);

    //desenare sageti
    drawButton(upArrow);
    line(upArrow.stSus.x+10, upArrow.stSus.y+5, upArrow.stSus.x+10, upArrow.stSus.y+15);
    line(upArrow.stSus.x+5, upArrow.stSus.y+10, upArrow.stSus.x+10, upArrow.stSus.y+5);
    line(upArrow.stSus.x+15, upArrow.stSus.y+10, upArrow.stSus.x+10, upArrow.stSus.y+5);

    drawButton(downArrow);
    line(downArrow.stSus.x+10, downArrow.stSus.y+5, downArrow.stSus.x+10, downArrow.stSus.y+15);
    line(downArrow.stSus.x+5, downArrow.stSus.y+10, downArrow.stSus.x+10, downArrow.stSus.y+15);
    line(downArrow.stSus.x+15, downArrow.stSus.y+10, downArrow.stSus.x+10, downArrow.stSus.y+15);

    //coordonate butoane cu numere si desenarea lor.
    initCordButton(zero, 100, 100, 130, 130);
    drawButton(zero);
    outtextxy(110,110, "0");

    initCordButton(unu, 130, 100, 160, 130);
    drawButton(unu);
    outtextxy(140,110, "1");

    initCordButton(doi, 160, 100, 190, 130);
    drawButton(doi);
    outtextxy(170,110, "2");

    initCordButton(trei, 100, 130, 130, 160);
    drawButton(trei);
    outtextxy(110,140, "3");

    initCordButton(patru, 130, 130, 160, 160);
    drawButton(patru);
    outtextxy(140,140, "4");

    initCordButton(cinci, 160, 130, 190, 160);
    drawButton(cinci);
    outtextxy(170,140, "5");

    initCordButton(sase, 100, 160, 130, 190);
    drawButton(sase);
    outtextxy(110,170, "6");

    initCordButton(sapte, 130, 160, 160, 190);
    drawButton(sapte);
    outtextxy(140,170, "7");

    initCordButton(opt, 160, 160, 190, 190);
    drawButton(opt);
    outtextxy(170,170, "8");

    initCordButton(noua, 130, 190, 160, 220);
    drawButton(noua);
    outtextxy(140,200, "9");


    for(int i=0; i<2; ++i)
        rectangle(desenCord.x+i*latura, desenCord.y,
                   desenCord.x+(i+1)*latura, desenCord.y+latura);

    outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
    outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

    //pregatesc noul teren pt prima linie in care utilizatorul pune cifre.
    linie++;
    for(int j=0; j<7; ++j){
        rectangle(desenCord.x+latura*j, desenCord.y+latura*linie,
                   desenCord.x+latura*(j+1), desenCord.y+latura*(linie+1));
    }

}

//functii folositoare
bool suntEgale(unsigned *cifru, unsigned *cifru1){
    for(int i=0; i<5; ++i){
        if(cifru[i]!=cifru1[i])
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
    return(buton.stSus.x<mouse.x && mouse.x<buton.drJos.x &&
           buton.stSus.y<mouse.y && mouse.y<buton.drJos.y);
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

void update(unsigned *cifru, unsigned &pozCifra, unsigned matCifru[1000][7]){

    //daca utilizatorul a ales 5 cifre, i se va updata C si M in tabel.
    if(pozCifra==7){
        //le calculez
        unsigned nrElemCentrate=0, nrElemMutate=0;

        for(int j=0; j<5; ++j){
            //numar elementele centrate
            if (cifru[j]==matCifru[linie][j+2])
                nrElemCentrate++;
            //numar elementele mutate.
            for(int jtemp=0; jtemp<5; ++jtemp)
                if(j!=jtemp && cifru[j]==matCifru[linie][jtemp+2])
                    nrElemMutate++;
        }

        //le pun in matrice
        matCifru[linie][0]=nrElemCentrate;
        matCifru[linie][1]=nrElemMutate;

        //le fac sir
        char* nrElemCentrateChar, *nrElemMutateChar;
        nrElemCentrateChar=new char[5];
        nrElemMutateChar=new char[5];

        itoa(nrElemCentrate, nrElemCentrateChar, 10);
        itoa(nrElemMutate, nrElemMutateChar, 10);

        //le desenez
        outtextxy(desenCord.x+latura/2-5, desenCord.y+latura*linie+latura/2-5, nrElemCentrateChar);
        outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura*linie+latura/2-5, nrElemMutateChar);

        //daca s-a terminat jocul, stop.
        if(suntEgale(cifru, (matCifru[linie]+2))){
            outtextxy(getmaxx()-100, 100, "FELICITARI");
            Sleep(5);
            ///TODO: Enter Main Menu.
        }
        else{
            //updatez pozitia si trec la urmatoarea linie
            pozCifra=2;

            linie++;
            //pregatesc noul teren pt urmatoarea linie.
            for(int j=0; j<7; ++j){
                rectangle(desenCord.x+latura*j, desenCord.y+latura*linie,
                           desenCord.x+latura*(j+1), desenCord.y+latura*(linie+1));
            }

        }
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


            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");



            //restul liniilor
            for(int i=1; i<=linie; ++i)
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

            ///TODO: aici nu imi sterge box-urile de la C,M dupa ce trec de prima linie. deci trec de prima linie
            ///si "linie" imi ramane in urma si de aia nu pot sterge boxurile. cred..
            //linia 0
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");
            outtextxy(desenCord.x+latura/2-5, desenCord.y-latura*2+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y-latura*2+latura/2-5, "M");
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura+latura/2-5, "M");

            rectangle(desenCord.x, desenCord.y+(linie-1)*latura,
                      desenCord.x+latura, desenCord.y+linie*latura);
            rectangle(desenCord.x+latura, desenCord.y+(linie-1)*latura,
                      desenCord.x+latura*2, desenCord.y+linie*latura);

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura*i+latura/2-5, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

            rectangle(desenCord.x, desenCord.y+(linie-1)*latura,
                      desenCord.x+latura, desenCord.y+linie*latura);
            rectangle(desenCord.x+latura, desenCord.y+(linie-1)*latura,
                      desenCord.x+latura*2, desenCord.y+linie*latura);

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura*i+latura/2-5, cifra);
                }



        }

        //daca utilizatorul apasa pe unul dintre acele butoane.
        if(isButonClicked(mouse, zero)){
            //bag in matrice
            matCifru[linie][pozCifra]=0;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "0");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, unu)){
            //bag in matrice
            matCifru[linie][pozCifra]=1;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "1");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, doi)){
            //bag in matrice
            matCifru[linie][pozCifra]=2;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "2");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, trei)){
            //bag in matrice
            matCifru[linie][pozCifra]=3;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "3");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, patru)){
            //bag in matrice
            matCifru[linie][pozCifra]=4;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "4");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, cinci)){
            //bag in matrice
            matCifru[linie][pozCifra]=5;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "5");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, sase)){
            //bag in matrice
            matCifru[linie][pozCifra]=6;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "6");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, sapte)){
            //bag in matrice
            matCifru[linie][pozCifra]=7;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "7");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, opt)){
            //bag in matrice
            matCifru[linie][pozCifra]=8;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "8");
            //increment pozitie cifra
            pozCifra++;
        }
        if(isButonClicked(mouse, noua)){
            //bag in matrice
            matCifru[linie][pozCifra]=9;
            //desenez
            outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "9");
            //increment pozitie cifra
            pozCifra++;
        }

    }
}


void calcAjutator(){
    //variabile
    unsigned *cifru, *cifruMeu, nrElemCentrate, nrElemMutate, scor=0, pozCifra=2, matCifru[1000][7]={};

    //fac cifrul secret
    cifru=new unsigned[5];
    cifru=creareCifru();
    cifruMeu=new unsigned[5];

    //pun pe linia 0 din matrice cifrul.
    for(int i=2; i<7; ++i)
        matCifru[0][i]=cifru[i-2];


    //do pana cand nu e gata jocul.
    do{
        update(cifru, pozCifra, matCifru);
    }while (!suntEgale(cifru, (matCifru[linie]+2)));

}



int main() {

    initwindow(1500,1270);

    unsigned* cifru=new unsigned[5];
    cifru=creareCifru();
    initDesen();

    calcAjutator();

    getch();
    closegraph();

    return 0;
}
