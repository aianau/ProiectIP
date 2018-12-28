#define _WIN32_WINNT 0x501
#define PORT "1338"
#define HOST "192.168.0.1"

#include "functii_socket.cpp"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include <winbgim.h>
#include <cmath>
#include <conio.h>

using namespace std;

struct CORD{
    int x, y;
}desenCord;

struct BUTON{
    CORD stSus, drJos;
};
BUTON upArrow, downArrow;
BUTON zero, unu, doi, trei, patru, cinci, sase, sapte, opt, noua;
BUTON exitMenuButon, singlePlayerButon, playerVsPlayerButon, exitSinglePlayerButon, exitPlayervsPlayerButon, deleteNumber, instructiuniMeniu, exitinstructiuni,setariJocButon,exitSetariButon,scorButon;
BUTON clasicButon, popButon, folkButon, jazButon, rockButon,popularButon, opresteMuzicButon,pornesteMuzicaButon;
unsigned latura,  latime, linie;
unsigned gataPlayerVsPC, gataPlayerVsPlayer, gataGame, gatainstructiuni,gataSetari;
unsigned scor;

int scroll;

void drawButon(BUTON buton){
    rectangle(buton.stSus.x, buton.stSus.y, buton.drJos.x, buton.drJos.y);
}

void initCordButon(BUTON &buton, int stSusX, int stSusY, int drJosX, int drJosY){
    buton.stSus.x=stSusX;
    buton.stSus.y=stSusY;
    buton.drJos.x=drJosX;
    buton.drJos.y=drJosY;
}

void drawScrollArrows(){

    initCordButon(upArrow, 10, 10, 30, 30);
    initCordButon(downArrow, 10, 35, 30, 55);

    drawButon(upArrow);
    line(upArrow.stSus.x+10, upArrow.stSus.y+5, upArrow.stSus.x+10, upArrow.stSus.y+15);
    line(upArrow.stSus.x+5, upArrow.stSus.y+10, upArrow.stSus.x+10, upArrow.stSus.y+5);
    line(upArrow.stSus.x+15, upArrow.stSus.y+10, upArrow.stSus.x+10, upArrow.stSus.y+5);

    drawButon(downArrow);
    line(downArrow.stSus.x+10, downArrow.stSus.y+5, downArrow.stSus.x+10, downArrow.stSus.y+15);
    line(downArrow.stSus.x+5, downArrow.stSus.y+10, downArrow.stSus.x+10, downArrow.stSus.y+15);
    line(downArrow.stSus.x+15, downArrow.stSus.y+10, downArrow.stSus.x+10, downArrow.stSus.y+15);
}

void drawGUIInputNumber(){
    initCordButon(zero, 100, 100, 142, 142);
    drawButon(zero);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(107,101, "0");

    initCordButon(unu, 142, 100, 184, 142);
    drawButon(unu);
    outtextxy(150,102, "1");

    initCordButon(doi, 184, 100, 226, 142);
    drawButon(doi);
    outtextxy(193,102, "2");

    initCordButon(trei, 100, 142, 142, 184);
    drawButon(trei);
    outtextxy(108,143, "3");

    initCordButon(patru, 142, 142, 184, 184);
    drawButon(patru);
    outtextxy(150,143, "4");

    initCordButon(cinci, 184, 142, 226, 184);
    drawButon(cinci);
    outtextxy(193,143, "5");

    initCordButon(sase, 100, 184, 142, 226);
    drawButon(sase);
    outtextxy(108,185, "6");

    initCordButon(sapte, 142, 184, 184, 226);
    drawButon(sapte);
    outtextxy(150,185, "7");

    initCordButon(opt, 184, 184, 226, 226);
    drawButon(opt);
    outtextxy(193,185, "8");

    initCordButon(noua, 142, 226, 184, 268);
    drawButon(noua);
    outtextxy(150,228, "9");
}

void initDesenAuxiliaryButons(){

    drawScrollArrows();

    initCordButon(deleteNumber ,60, getmaxy()/2-150, 350, getmaxy()/2-90);
    drawButon(deleteNumber);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(deleteNumber.stSus.x+13, deleteNumber.stSus.y+10, "Sterge Cifra");

    //coordonate butoane cu numere si desenarea lor.
    drawGUIInputNumber();

    initCordButon(opresteMuzicButon,30, getmaxy()/2-30, 380, getmaxy()/2+30);
    drawButon(opresteMuzicButon);
    outtextxy(opresteMuzicButon.stSus.x+10,opresteMuzicButon.stSus.y+12, "Opreste Muzica");

    //coordonata btn exitSinglePlayerButon
    initCordButon(exitSinglePlayerButon, 30, getmaxy()/2+100, 350, getmaxy()/2+160);
    initCordButon(exitPlayervsPlayerButon, 30, getmaxy()/2+100, 350, getmaxy()/2+160);
    drawButon(exitSinglePlayerButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(exitSinglePlayerButon.stSus.x+10, exitSinglePlayerButon.stSus.y+10, "To Main Menu");

    setcolor(BLACK);
    initCordButon(scorButon, getmaxx()/2+390,  getmaxy()/2-400, getmaxx()/2+550,getmaxy()/2-445 );
    drawButon(scorButon);
    setcolor(GREEN);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
    outtextxy(scorButon.stSus.x+15, scorButon.stSus.y-38, "Scor: 0 ");
    setcolor(WHITE);
}

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
//functie care imi returneaza un cifru random
unsigned *creareCifru(){
    //declarare variabile
    unsigned *cifru, *estePus;
    cifru=new unsigned[5];
    estePus=new unsigned[9];


    for(int i=0; i<10; ++i)
        estePus[i]=0;

    //magie care ne face sa avem un random cu adevarat random.
    /* initialize random seed: */
    srand (time(NULL));

    //generez un nr intre 1 si 9 pt pozitia 1
    unsigned *nrSecret;
    nrSecret=new unsigned;
    *nrSecret=(unsigned)(rand()%9)+1;
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

//functie ce la coordonata x,y imi afiseaza text clipind.
void blinkMessage(int x, int y, char *text){
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(x, y, text);
    Sleep(300);
    setcolor(BLACK);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(x, y, text);
    Sleep(150);
    setcolor(WHITE);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(x, y, text);
    Sleep(300);
    setcolor(BLACK);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 2);
    outtextxy(x, y, text);
    Sleep(150);
    setcolor(WHITE);
}

//returneaza 1 daca cifra a mai fost pus in vectorul linieMat[] (o vom apela ca fix pt ultima linie), avand "nrElem" elemente
bool checkPunere(unsigned cifra, unsigned linieMat[], unsigned nrElem){
    for(int i=2; i<=nrElem; ++i)
        if(linieMat[i]==cifra) return 1;
    return 0;
}

void initDesenMenu(){
    cleardevice();

    initCordButon(exitMenuButon, getmaxx()/2-95, getmaxy()/2+70, getmaxx()/2+30,  getmaxy()/2+138);
    drawButon(exitMenuButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(exitMenuButon.stSus.x+20, exitMenuButon.stSus.y+10, "Exit");

    initCordButon(singlePlayerButon, getmaxx()/2-190, getmaxy()/2-240, getmaxx()/2+140,  getmaxy()/2-167);
    drawButon(singlePlayerButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(singlePlayerButon.stSus.x+5, singlePlayerButon.stSus.y+10, "Single Player");

    initCordButon(playerVsPlayerButon, getmaxx()/2-230, getmaxy()/2-350, getmaxx()/2+185,  getmaxy()/2-280);
    drawButon(playerVsPlayerButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(playerVsPlayerButon.stSus.x+20, playerVsPlayerButon.stSus.y+7,"Player vs Player");

    initCordButon(setariJocButon, getmaxx()/2-160, getmaxy()/2-130, getmaxx()/2+118, getmaxy()/2-60);
    drawButon(setariJocButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(setariJocButon.stSus.x+18,setariJocButon.stSus.y+8, "Setari Joc");

    initCordButon(instructiuniMeniu, getmaxx()/2-160, getmaxy()/2-30, getmaxx()/2+118, getmaxy()/2+30);
    drawButon(instructiuniMeniu);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(instructiuniMeniu.stSus.x+13,instructiuniMeniu.stSus.y+5, "Instructiuni");
}

//acest update va fi constant. gandeste ca va rula la infinit
//pana cand jocul sa termina. acesta va verifica daca un buton este apasat si atunci imi va
//updata jocul, la fiecare secunda.
//de fiecare data cand vom desena ceva, vom desena in functie de desenCord.y (care se va schimba daca
//vreau sa implementez butoanele de scroll).
void updatePlayerVsPC(unsigned *cifru, unsigned &pozCifra, unsigned matCifru[1000][7]){

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

        //le fac sir si le afisez
        char* nrElemCentrateChar, *nrElemMutateChar;
        nrElemCentrateChar=new char[2];
        nrElemMutateChar=new char[2];

        itoa(nrElemCentrate, nrElemCentrateChar, 10);
        itoa(nrElemMutate, nrElemMutateChar, 10);

        //le desenez
        outtextxy(desenCord.x+latura/2-16, desenCord.y+latura*linie+latura/2-18, nrElemCentrateChar);
        outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura*linie+latura/2-18, nrElemMutateChar);

        //daca s-a terminat jocul, stop.
        if(suntEgale(cifru, (matCifru[linie]+2))){
            cleardevice();
            outtextxy(getmaxx()-100, 100, "FELICITARI");
            Sleep(3000);
            gataPlayerVsPC=1;

        }
        else{
            //updatez pozitia si trec la urmatoarea linie
            pozCifra=2;

            linie++;
            //pregatesc noul teren pt urmatoarea linie.
            for(int j=0; j<7; ++j)
            {
                rectangle(desenCord.x+latura*j, desenCord.y+latura*linie,
                           desenCord.x+latura*(j+1), desenCord.y+latura*(linie+1));
            }
                  if(linie>=0)
                {
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                    setcolor(GREEN);
                    for( int cifraScor=0; cifraScor<10000; ++cifraScor)
                        {
                            char *cifraScorChar;
                            cifraScorChar = new char[5];
                            cifraScorChar = itoa(cifraScor, cifraScorChar, 10);
                            if(linie-2 == cifraScor-1)
                                outtextxy(scorButon.stSus.x+115, scorButon.stSus.y-35, cifraScorChar);
                        }

                }

                setcolor(WHITE);

        }
    }

    //daca butonul este apasat
    if(ismouseclick(WM_LBUTTONDOWN)){
        //eliberam "mouse"-ul. asa facea proful, am vazut si am scris la fel si a mers.
        clearmouseclick(WM_LBUTTONDOWN);

        //retinem coordonatele mouse-ului unde a dat click.
        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();

        //daca este apasata vreo sageata.

        if(isButonClicked(mouse, upArrow)){
            //scrollul trece pe minus pentru a updata desenCord.
            scroll=-abs(scroll);

            //stergere
            setcolor(BLACK);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            for(int linieTemp=-80; linieTemp<=5; ++linieTemp){
                rectangle(desenCord.x, desenCord.y+linieTemp*latura,
                      desenCord.x+latura, desenCord.y+(linieTemp+1)*latura);
                rectangle(desenCord.x+latura, desenCord.y+linieTemp*latura,
                      desenCord.x+latura*2, desenCord.y+(linieTemp+1)*latura);
            }

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            rectangle(desenCord.x, desenCord.y,
                      desenCord.x+latura, desenCord.y+latura);
            rectangle(desenCord.x+latura, desenCord.y,
                      desenCord.x+latura*2, desenCord.y+latura);

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    //daca sunt pe ultima linie si am numarul 0 in matrice si trebuie sa umplu patratul
                    //in care jucatorul nu a pus un numar sau patratul cu C si M de pe ultima linie,
                    //inseamna ca acolo trebuie sa fie gol. deci acolo nu rescriu nimic.
                    if(i==linie && matCifru[i][j]==0 && (j>=pozCifra||j==0||j==1)){
                    }else{
                        char *cifra;
                        cifra=new char[5];
                        itoa(matCifru[i][j], cifra, 10);
                        outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, downArrow)){
            scroll=abs(scroll);

            //stergere
            setcolor(BLACK);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            for(int linieTemp=-80; linieTemp<=10; ++linieTemp){
                rectangle(desenCord.x, desenCord.y+linieTemp*latura,
                      desenCord.x+latura, desenCord.y+(linieTemp+1)*latura);
                rectangle(desenCord.x+latura, desenCord.y+linieTemp*latura,
                      desenCord.x+latura*2, desenCord.y+(linieTemp+1)*latura);
            }

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            rectangle(desenCord.x, desenCord.y,
                      desenCord.x+latura, desenCord.y+latura);
            rectangle(desenCord.x+latura, desenCord.y,
                      desenCord.x+latura*2, desenCord.y+latura);

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    //daca sunt pe ultima linie si am numarul 0 in matrice si trebuie sa umplu patratul
                    //in care jucatorul nu a pus un numar sau patratul cu C si M de pe ultima linie,
                    //inseamna ca acolo trebuie sa fie gol. deci acolo nu rescriu nimic.
                    if(i==linie && matCifru[i][j]==0 && (j>=pozCifra||j==0||j==1)){
                    }else{
                        char *cifra;
                        cifra=new char[5];
                        itoa(matCifru[i][j], cifra, 10);
                        outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, exitSinglePlayerButon)){
            gataPlayerVsPC=1;
            initDesenMenu();
        }

        if(isButonClicked(mouse, deleteNumber)){
            if(pozCifra>2){
                pozCifra--;

                setcolor(BLACK);
                for(int i=0; i<9; ++i){
                    char *cifra;
                    cifra = new char[5];

                    itoa(i, cifra, 10);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, cifra);
                }
                setcolor(WHITE);
            }
        }


        //daca utilizatorul apasa pe unul dintre acele butoane.
        if(isButonClicked(mouse, zero)){
            //daca e pe prima pozitie, arata eroare
            if(pozCifra==2){
                blinkMessage(getmaxx()-920, 50, "APASATI ALTA CIFRA");
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
            }else{
                //daca cifra a mai fost pusa
                if(checkPunere(0, matCifru[linie], pozCifra-1))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    //bag in matrice
                    matCifru[linie][pozCifra]=0;
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "0");
                    //increment pozitie cifra
                    pozCifra++;
                }
            }
        }
        if(isButonClicked(mouse, unu)){
            if(checkPunere(1, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=1;
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "1");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, doi)){
            if(checkPunere(2, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=2;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "2");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, trei)){
            if(checkPunere(3, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=3;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "3");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, patru)){
            if(checkPunere(4, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=4;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "4");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, cinci)){
            if(checkPunere(5, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=5;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "5");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sase)){
            if(checkPunere(6, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=6;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "6");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sapte)){
            if(checkPunere(7, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);

                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=7;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "7");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, opt)){
            if(checkPunere(8, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=8;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "8");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, noua)){
            if(checkPunere(9, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=9;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "9");
                    //increment pozitie cifra
                    pozCifra++;
                }
            }
         if(isButonClicked(mouse,opresteMuzicButon))
            {
                PlaySound(NULL, 0, 0);
            }
        }
}

void drawLineZeroAndPrepareTable(){
    //desenare linie 0
    for(int linieTemp=0; linieTemp<2; ++linieTemp)
        rectangle(desenCord.x+linieTemp*latura, desenCord.y,
                  desenCord.x+(linieTemp+1)*latura, desenCord.y+latura);

    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(desenCord.x+latura/2-17, desenCord.y+latura/2-18, "C");
    outtextxy(desenCord.x+latura+latura/2-17, desenCord.y+latura/2-17, "M");

    //pregatesc noul teren pt prima linie in care utilizatorul pune cifre.
    linie++;
    for(int j=0; j<7; ++j){
        rectangle(desenCord.x+latura*j, desenCord.y+latura*linie,
                  desenCord.x+latura*(j+1), desenCord.y+latura*(linie+1));
    }
}

void initDesenPlayerVsPc(){

    //init variabile pt PlayerVsPc
    latime=320;
    latura=320/7;
    desenCord.x=(getmaxx()-latime)/2+130;
    desenCord.y=100;
    linie=0;
    scroll=90;

    drawLineZeroAndPrepareTable();
}

void playerVsPC(){

    //desenare auxiliary butons
    initDesenAuxiliaryButons();

    //desenare playerVsPC graphic.
    initDesenPlayerVsPc();

    //variabile
    unsigned *cifru, *cifruMeu, nrElemCentrate, nrElemMutate, scor=0, pozCifra=2, matCifru[1000][7]={};

    //fac cifrul secret
    cifru=new unsigned[5];
    cifru=creareCifru();
    cifruMeu=new unsigned[5];

    //pun pe linia 0 din matrice cifrul secret.
    for(int i=2; i<7; ++i)
        matCifru[0][i]=cifru[i-2];


    //do pana cand nu e gata jocul.
    do{
        updatePlayerVsPC(cifru, pozCifra, matCifru);
    }while (!gataPlayerVsPC && !suntEgale(cifru, (matCifru[linie]+2)));

    cleardevice();
    initDesenMenu();

}

void initVarPlayerVsPlayer(){
    latime=320;
    latura=320/7;
    desenCord.x=(getmaxx()-latime)/2+130;
    desenCord.y=100;
    linie=0;
    scroll=90;
}

//verific daca cifra a mai fost pusa in cifruAles pana la pozitia pozCifra
bool checkPunerePlayerVsPlayer(int cifra, char *cifruAles, unsigned pozCifra){
    for(int i=0; i<pozCifra; ++i)
        if((unsigned) (cifruAles[i]-'0') == cifra)
            return true;
    return false;
}
void updateSetari()
{
    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();

        if(isButonClicked(mouse, exitSetariButon))
            {
                gataSetari=1;
                initDesenMenu();
            }
        if(isButonClicked(mouse,clasicButon))
            {
               PlaySound(TEXT("clasicmusic.wav"),NULL, SND_FILENAME | SND_ASYNC);

            }
        if(isButonClicked(mouse,rockButon))
            {
               PlaySound(TEXT("rockmusic1.wav"),NULL, SND_FILENAME | SND_ASYNC);

            }
        if(isButonClicked(mouse,jazButon))
            {
               PlaySound(TEXT("jazzmusic.wav"),NULL, SND_FILENAME | SND_ASYNC);

            }
        if(isButonClicked(mouse,popButon))
            {
               PlaySound(TEXT("popmusic.wav"),NULL, SND_FILENAME | SND_ASYNC);

            }
        if(isButonClicked(mouse,folkButon))
            {
               PlaySound(TEXT("folkmusic.wav"),NULL, SND_FILENAME | SND_ASYNC);

            }
        if(isButonClicked(mouse,popularButon))
            {
               PlaySound(TEXT("popularamusic.wav"),NULL, SND_FILENAME | SND_ASYNC);

            }
        if(isButonClicked(mouse,opresteMuzicButon))
            {
                PlaySound(NULL, 0, 0);
            }
         if(isButonClicked(mouse,pornesteMuzicaButon))
         {
             PlaySound(TEXT("clasicmusic.wav"),NULL, SND_FILENAME | SND_ASYNC);
         }

      }


    else if(ismouseclick(WM_MOUSEMOVE))
    {
        clearmouseclick(WM_MOUSEMOVE);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();


        if(isButonClicked(mouse,clasicButon ))
        {
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(60,175, "Muzica Clasica");

                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(30,175, "Muzica Clasica");
                Sleep(500);
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(30,175, "Muzica Clasica");
                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(60,175, "Muzica Clasica");

        }

        if(isButonClicked(mouse,rockButon ))
        {
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(515,175, "Muzica Rock");

                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(495,175, "Muzica Rock");
                Sleep(500);
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(495,175, "Muzica Rock");
                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(530,175, "Muzica Rock");
        }

          if(isButonClicked(mouse,jazButon ))
          {

                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(900,175, "Muzica Jazz");

                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(900,175, "Muzica Jazz");
                Sleep(500);
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(900,175, "Muzica Jazz");
                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(930,175, "Muzica Jazz");

          }

          if(isButonClicked(mouse,popButon ))
          {
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(50,425, "Muzica Pop");

                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(50,425, "Muzica Pop");
                Sleep(500);
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(50,425, "Muzica Pop");
                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(80,425, "Muzica Pop");
          }

          if(isButonClicked(mouse,folkButon ))
          {
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(500,425, "Muzica Folk");

                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(500,425, "Muzica Folk");
                Sleep(500);
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(500,425, "Muzica Folk");
                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(540,425, "Muzica Folk");
              }

           if(isButonClicked(mouse,popularButon))
           {
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(850,425, "Muzica Populara");

                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(850,425, "Muzica Populara");
                Sleep(500);
                setcolor(BLACK);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
                outtextxy(850,425, "Muzica Populara");
                setcolor(GREEN);
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
                outtextxy(900,425, "Muzica Populara");
           }

           if(isButonClicked(mouse,opresteMuzicButon))
           {
               setcolor(BLACK);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
               outtextxy(68,607, "Opreste Muzica");

               setcolor(GREEN);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
               outtextxy(40,590, "Opreste Muzica");
               Sleep(500);
               setcolor(BLACK);
               outtextxy(40,590, "Opreste Muzica");
               setcolor(GREEN);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
               outtextxy(68,607, "Opreste Muzica");


           }

           if(isButonClicked(mouse,pornesteMuzicaButon))
           {
               setcolor(BLACK);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
               outtextxy(470,607, "Porneste Muzica");

               setcolor(GREEN);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
               outtextxy(430,590, "Porneste Muzica");
               Sleep(500);
               setcolor(BLACK);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
               outtextxy(430,590, "Porneste Muzica");
               setcolor(GREEN);
               settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
               outtextxy(470,607, "Porneste Muzica");

           }
           if(isButonClicked(mouse,exitSetariButon))
           {

              setcolor(BLACK);
              settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
              outtextxy(887,610, "To main meniu");

              setcolor(GREEN);
              settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
              outtextxy(847,590, "To main meniu");
              Sleep(500);
              setcolor(BLACK);
              settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
              outtextxy(847,590, "To main meniu");
              setcolor(GREEN);
              settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
              outtextxy(887,610, "To main meniu");

           }

    }
}

void desenSetari()
{
    setcolor(BLACK);
    initCordButon(clasicButon,50,20,350,220);
    drawButon(clasicButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
    setcolor(GREEN);
    outtextxy(60,175, "Muzica Clasica");
    readimagefile("clasic.jpg",50,20,350,150);

    setcolor(BLACK);
    initCordButon(rockButon,500,20,800,220);
    drawButon(rockButon);
    setcolor(GREEN);
    outtextxy(530,175, "Muzica Rock");
    readimagefile("rock.jpg",500,20,800,150);

    setcolor(BLACK);
    initCordButon(jazButon,900,20,1200,220);
    drawButon(jazButon);
    setcolor(GREEN);
    outtextxy(930,175, "Muzica Jazz");
    readimagefile("jazz.jpg",900,20,1200,150);

    setcolor(BLACK);
    initCordButon(popButon,50,250,350,470);
    drawButon(popButon);
    setcolor(GREEN);
    outtextxy(80,425, "Muzica Pop");
    readimagefile("pop.jpg",50,250,350,400);

    setcolor(BLACK);
    initCordButon(folkButon,500,250,800,470);
    drawButon(folkButon);
    setcolor(GREEN);
    outtextxy(540,425, "Muzica Folk");
    readimagefile("folk.jpg",500,250,800,400);

    setcolor(BLACK);
    initCordButon(popularButon,900,250,1200,470);
    drawButon(popularButon);
    setcolor(GREEN);
    outtextxy(900,425, "Muzica Populara");
    readimagefile("popular.jpg",900,250,1200,400);

    setcolor(BLACK);
    initCordButon(opresteMuzicButon,50, 600, 360,650);
    drawButon(opresteMuzicButon);
    setcolor(GREEN);
    outtextxy(68,607, "Opreste Muzica");

    setcolor(BLACK);
    initCordButon(pornesteMuzicaButon,450, 600, 790,650);
    drawButon(pornesteMuzicaButon);
    setcolor(GREEN);
    outtextxy(470,607, "Porneste Muzica");

    setcolor(BLACK);
    initCordButon(exitSetariButon,870, 600, 1160,650);
    drawButon(exitSetariButon);
    setcolor(GREEN);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
    outtextxy(887,610, "To main meniu");

    do
    {
        updateSetari();
    }
    while (!gataSetari);
    setcolor(WHITE);

    cleardevice();
    initDesenMenu();
}
void updateCerereCifru(SOCKET &client, char *cifruAles, unsigned &pozCifra){

    //daca butonul este apasat
    if(ismouseclick(WM_LBUTTONDOWN)){
        //eliberam "mouse"-ul. asa facea proful, am vazut si am scris la fel si a mers.
        clearmouseclick(WM_LBUTTONDOWN);

        //retinem coordonatele mouse-ului unde a dat click.
        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();

        if(isButonClicked(mouse, exitPlayervsPlayerButon)){
            send(client, "-1", 2, 0);
            send(client, "0", 1, 0);

            cleardevice();
            initDesenMenu();
            gataPlayerVsPlayer=1;
        }

        if(isButonClicked(mouse, deleteNumber)){
            if(pozCifra>0){
                pozCifra--;

                setcolor(BLACK);
                for(int i=0; i<9; ++i){
                    char *cifra;
                    cifra = new char[5];

                    itoa(i, cifra, 10);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, cifra);
                }
                setcolor(WHITE);
            }
        }

        //daca utilizatorul apasa pe unul dintre acele butoane.
        if(isButonClicked(mouse, zero)){
            //daca e pe prima pozitie, arata eroare
            if(pozCifra==0){
                blinkMessage(getmaxx()-920, 50, "APASATI ALTA CIFRA");
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
            }else{
                //daca cifra a mai fost pusa
                if(checkPunerePlayerVsPlayer(0, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='0';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "0");
                    //increment pozitie cifra
                    pozCifra++;
                }
            }
        }
        if(isButonClicked(mouse, unu)){
            if(checkPunerePlayerVsPlayer(1, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='1';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "1");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, doi)){
            if(checkPunerePlayerVsPlayer(2, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='2';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "2");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, trei)){
            if(checkPunerePlayerVsPlayer(3, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='3';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "3");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, patru)){
            if(checkPunerePlayerVsPlayer(4, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='4';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "4");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, cinci)){
            if(checkPunerePlayerVsPlayer(5, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='5';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "5");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sase)){
           if(checkPunerePlayerVsPlayer(6, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='6';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "6");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sapte)){
            if(checkPunerePlayerVsPlayer(7, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='7';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "7");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, opt)){
            if(checkPunerePlayerVsPlayer(8, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='8';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "8");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, noua)){
            if(checkPunerePlayerVsPlayer(9, cifruAles, pozCifra))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    cifruAles[pozCifra]='9';
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "9");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
    }
}

void updatePlayerVsPlayer(SOCKET &client, unsigned *cifru, unsigned &pozCifra, unsigned matCifru[1000][7]){

    //var pt transmitere
    char mesajDeTrimis[512];
    char mesajPrimit[512];

    mesajDeTrimis[511] = '\0';
    strcpy(mesajDeTrimis, "0");
    mesajDeTrimis[1]='\0';
    mesajPrimit[511] = '\0';

    int result_send,  result_recv;

    //trimite semnal ca nu ai castigat.
    result_send = send(client, mesajDeTrimis, (int)strlen(mesajDeTrimis), 0);

    //primeste semnal de la celalalt client daca jocu e gata.
    result_recv = recv(client, mesajPrimit, 512, 0);
    mesajPrimit[result_recv] = '\0';

    //daca oponentul a terminat.
    if(strcmp(mesajPrimit, "1") == 0){
        cleardevice();
        outtextxy(getmaxx()/2-30, getmaxy()/2, "Oponentul a castigat!");
        Sleep(2000);
        cleardevice();
        initDesenMenu();
        gataPlayerVsPlayer=1;
    }

    //daca oponentul a iesit din joc
    if(strcmp(mesajPrimit, "-1") == 0){
        cleardevice();
        outtextxy(getmaxx()/2-30, getmaxy()/2, "Oponentul a iesit din joc!");
        Sleep(2000);
        cleardevice();
        initDesenMenu();
        gataPlayerVsPlayer=1;
    }

    if(strcmp(mesajPrimit, "1") != 0 &&
        strcmp(mesajPrimit, "0") !=0 &&
        strcmp(mesajPrimit, "-1") != 0){
            cleardevice();
            outtextxy(getmaxx()/2-30, getmaxy()/2, "Eroare");
            Sleep(2000);
            cleardevice();
            initDesenMenu();
            gataPlayerVsPlayer=1;
    }

    //reinit mesaje
    mesajDeTrimis[511] = '\0';
    mesajPrimit[511] = '\0';


    //daca utilizatorul a ales 5 cifre, i se va updata C si M in tabel.
    if(pozCifra==7){
        //creste scorul
        scor++;

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

        //le fac sir si le afisez
        char* nrElemCentrateChar, *nrElemMutateChar;
        nrElemCentrateChar=new char[2];
        nrElemMutateChar=new char[2];

        itoa(nrElemCentrate, nrElemCentrateChar, 10);
        itoa(nrElemMutate, nrElemMutateChar, 10);

        //le desenez
        outtextxy(desenCord.x+latura/2-16, desenCord.y+latura*linie+latura/2-18, nrElemCentrateChar);
        outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura*linie+latura/2-18, nrElemMutateChar);


        //daca s-a terminat jocul, stop.
        if(suntEgale(cifru, (matCifru[linie]+2))){

            //trimite semnal catre celalalt client ca jocu e gata.
            strcpy(mesajDeTrimis, "1");
            result_send = send(client, mesajDeTrimis, (int)strlen(mesajDeTrimis), 0);
            strcpy(mesajDeTrimis, "0");

            //felicitari.
            cleardevice();
            outtextxy(getmaxx()/2, getmaxy()/2, "FELICITARI");
            Sleep(3000);
            gataPlayerVsPlayer=1;

            cleardevice();
            initDesenMenu();

            //compara scorurile sa vezi cine a castigat.
            ///ASTA E VARIANTA CARE CASTIGA
            ///MAI REPEDE, NU CEL CARE CASTIGA DIN CELE MAI PUTINE MISCARI.
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

    //daca butonul este apasat
    if(ismouseclick(WM_LBUTTONDOWN)){
        //eliberam "mouse"-ul. asa facea proful, am vazut si am scris la fel si a mers.
        clearmouseclick(WM_LBUTTONDOWN);

        //retinem coordonatele mouse-ului unde a dat click.
        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();

        //daca este apasata vreo sageata.

        if(isButonClicked(mouse, upArrow)){
            //scrollul trece pe minus pentru a updata desenCord.
            scroll=-abs(scroll);

            //stergere
            setcolor(BLACK);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            for(int linieTemp=-80; linieTemp<=5; ++linieTemp){
                rectangle(desenCord.x, desenCord.y+linieTemp*latura,
                      desenCord.x+latura, desenCord.y+(linieTemp+1)*latura);
                rectangle(desenCord.x+latura, desenCord.y+linieTemp*latura,
                      desenCord.x+latura*2, desenCord.y+(linieTemp+1)*latura);
            }

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            rectangle(desenCord.x, desenCord.y,
                      desenCord.x+latura, desenCord.y+latura);
            rectangle(desenCord.x+latura, desenCord.y,
                      desenCord.x+latura*2, desenCord.y+latura);

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    //daca sunt pe ultima linie si am numarul 0 in matrice si trebuie sa umplu patratul
                    //in care jucatorul nu a pus un numar sau patratul cu C si M de pe ultima linie,
                    //inseamna ca acolo trebuie sa fie gol. deci acolo nu rescriu nimic.
                    if(i==linie && matCifru[i][j]==0 && (j>=pozCifra||j==0||j==1)){
                    }else{
                        char *cifra;
                        cifra=new char[5];
                        itoa(matCifru[i][j], cifra, 10);
                        outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, downArrow)){
            scroll=abs(scroll);

            //stergere
            setcolor(BLACK);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            for(int linieTemp=-80; linieTemp<=10; ++linieTemp){
                rectangle(desenCord.x, desenCord.y+linieTemp*latura,
                      desenCord.x+latura, desenCord.y+(linieTemp+1)*latura);
                rectangle(desenCord.x+latura, desenCord.y+linieTemp*latura,
                      desenCord.x+latura*2, desenCord.y+(linieTemp+1)*latura);
            }

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    char *cifra;
                    cifra=new char[5];
                    itoa(matCifru[i][j], cifra, 10);
                    outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-16, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-16, desenCord.y+latura/2-18, "M");

            rectangle(desenCord.x, desenCord.y,
                      desenCord.x+latura, desenCord.y+latura);
            rectangle(desenCord.x+latura, desenCord.y,
                      desenCord.x+latura*2, desenCord.y+latura);

            //restul liniilor
            for(int i=1; i<=linie; ++i)
                for(int j=0; j<7; ++j){
                    rectangle(desenCord.x+latura*j, desenCord.y+latura*i,
                              desenCord.x+latura*(j+1), desenCord.y+latura*(i+1));
                    //daca sunt pe ultima linie si am numarul 0 in matrice si trebuie sa umplu patratul
                    //in care jucatorul nu a pus un numar sau patratul cu C si M de pe ultima linie,
                    //inseamna ca acolo trebuie sa fie gol. deci acolo nu rescriu nimic.
                    if(i==linie && matCifru[i][j]==0 && (j>=pozCifra||j==0||j==1)){
                    }else{
                        char *cifra;
                        cifra=new char[5];
                        itoa(matCifru[i][j], cifra, 10);
                        outtextxy(desenCord.x+latura*j+latura/2-16, desenCord.y+latura*i+latura/2-18, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, exitPlayervsPlayerButon)){
            strcpy(mesajDeTrimis, "-1");
            send(client, mesajDeTrimis, (int)strlen(mesajDeTrimis), 0);
            strcpy(mesajDeTrimis, "0");
            gataPlayerVsPlayer=1;
            cleardevice();
            initDesenMenu();
        }

        if(isButonClicked(mouse, deleteNumber)){
            if(pozCifra>2){
                pozCifra--;

                setcolor(BLACK);
                for(int i=0; i<9; ++i){
                    char *cifra;
                    cifra = new char[5];

                    itoa(i, cifra, 10);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, cifra);
                }
                setcolor(WHITE);
            }
        }


        //daca utilizatorul apasa pe unul dintre acele butoane.
        if(isButonClicked(mouse, zero)){
            //daca e pe prima pozitie, arata eroare
            if(pozCifra==2){
                blinkMessage(getmaxx()-920, 50, "APASATI ALTA CIFRA");
                settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
            }else{
                //daca cifra a mai fost pusa
                if(checkPunere(0, matCifru[linie], pozCifra-1))
                {
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }
                else
                {
                    //bag in matrice
                    matCifru[linie][pozCifra]=0;
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "0");
                    //increment pozitie cifra
                    pozCifra++;
                }
            }
        }
        if(isButonClicked(mouse, unu)){
            if(checkPunere(1, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=1;
                    //desenez
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "1");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, doi)){
            if(checkPunere(2, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=2;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "2");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, trei)){
            if(checkPunere(3, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=3;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "3");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, patru)){
            if(checkPunere(4, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=4;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "4");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, cinci)){
            if(checkPunere(5, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=5;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "5");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sase)){
            if(checkPunere(6, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=6;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "6");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sapte)){
            if(checkPunere(7, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);

                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=7;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "7");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, opt)){
            if(checkPunere(8, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=8;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "8");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, noua)){
            if(checkPunere(9, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-920, 50, "CIFRA A MAI FOST PUSA");
                    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=9;
                    //desenez
                     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-16, desenCord.y+linie*latura+latura/2-18, "9");
                    //increment pozitie cifra
                    pozCifra++;
                }
            }
        }
}

void playerVsPlayer(){
    //desenare auxiliary buttons
    initDesenAuxiliaryButons();

    initVarPlayerVsPlayer();

    initSockLibrary();
	SOCKET client;

    //conectare client la host
	int result_connect = clientSocketConnect(client, HOST, PORT);

	//daca s-a conectat cu succes
	if(result_connect){
        //isi dau cifrul unul altuia
        outtextxy(120, 5, "Introduceti cifrul pentru oponent!");

        //desenare linie pentru cifru.
        for(int j=0; j<5; ++j){
            rectangle(desenCord.x+latura*j, desenCord.y+latura*linie,
                      desenCord.x+latura*(j+1), desenCord.y+latura*(linie+1));
        }

        //alegere cifru.
        char *cifruAles;
        cifruAles = new char[5];

        unsigned pozCifra=0;

        do{
            updateCerereCifru(client, cifruAles, pozCifra);
        }while(pozCifra<5 && !gataPlayerVsPlayer);


        //daca totul e bine si oponentul nu a parasit jocu
        if (!gataPlayerVsPlayer){
            cifruAles[5]='\0';

            //asteptare
            Sleep(1000);

            //clear device si apoi rescriere butoane aux
            cleardevice();
            initDesenAuxiliaryButons();

            //transmitere cifru.
            int result_send, result_recv;

            result_send = send(client, cifruAles, 5, 0);

            //primire cifru
            char *cifruPrimit;
            cifruPrimit = new char[5];
            result_recv = recv(client, cifruPrimit, 5, 0);
            cifruPrimit[5]='\0';

            //oponentul iese din joc cand alege cifrul pt jucator
            if(strcmp(cifruPrimit, "-1") == 0){
                send(client, "-1", 2, 0);
                send(client, "0", 1, 0);

                cleardevice();
                outtextxy(getmaxx()/2-30, getmaxy()/2, "Oponentul a iesit din joc!");
                Sleep(2000);
                cleardevice();
                initDesenMenu();
                gataPlayerVsPlayer=1;
            }else {
                //variabile
                unsigned *cifru, *cifruMeu, nrElemCentrate, nrElemMutate, scor=0, pozCifra=2, matCifru[1000][7]={};

                //fac cifrul secret primit de la oponent
                cifru=new unsigned[5];
                for(int i=0; i<5; ++i){
                    cifru[i]=(unsigned) (cifruPrimit[i]-'0');
                }
                cifruMeu=new unsigned[5];

                //pun pe linia 0 din matrice cifrul secret.
                for(int i=2; i<7; ++i)
                    matCifru[0][i]=cifru[i-2];

                drawLineZeroAndPrepareTable();

                //do pana cand nu e gata jocul.
                do{
                    updatePlayerVsPlayer(client, cifru, pozCifra, matCifru);
                }while (!gataPlayerVsPlayer);
            }
        }
	} //daca oponentul nu exista.
	else {
        send(client, "-1", 2, 0);
        send(client, "0", 1, 0);
        cleardevice();
        outtextxy(getmaxx()/2-100, getmaxy()/2, "Conectare esuata!");
        Sleep(2000);
        cleardevice();
        initDesenMenu();
	}
}

 void updateInstructiuni(){
      if(ismouseclick(WM_LBUTTONDOWN)){
            clearmouseclick(WM_LBUTTONDOWN);

            CORD mouse;
            mouse.x=mousex();
            mouse.y=mousey();

       if(isButonClicked(mouse, exitinstructiuni)){
            gatainstructiuni=1;
            initDesenMenu();
        }
    }
 }

void desenInstructiuni(){
   // initwindow(1280, 1024, "Instuctiuni");
       setcolor(WHITE);
       initCordButon(exitinstructiuni,870, 600, 1160,650);
       drawButon(exitinstructiuni);
       settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 4);
       outtextxy(887 ,610, "To main meniu");

       readimagefile("CifruG.jpg",50,20,350,150);
       readimagefile("DubluraCif.jpg",500,20,800,150);
       readimagefile("IntrebareG.jpg",900,20,1200,150);
       readimagefile("Dublura.jpg",50,250,350,400);
       readimagefile("0M0C.jpg",500,250,800,400);
       readimagefile("3M0C.jpg",900,250,1200,400);
       readimagefile("2M3C.jpg",50,480,350,630);
       readimagefile("0M5C.jpg",500,480,800,630);

    do{
        updateInstructiuni();
    }while (!gatainstructiuni);

     cleardevice();
     initDesenMenu();
}

void updateGame(){


    if(ismouseclick(WM_LBUTTONDOWN))
    {
        clearmouseclick(WM_LBUTTONDOWN);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();


        if(isButonClicked(mouse, exitMenuButon)){
            gataGame=1;
        }

        if(isButonClicked(mouse, singlePlayerButon)){

            gataPlayerVsPC=0;
            //sterg main menu
            setcolor(BLACK);
            initDesenMenu();

            setcolor(WHITE);
            playerVsPC();
        }

        if(isButonClicked(mouse, playerVsPlayerButon)){
            gataPlayerVsPlayer=0;
            setcolor(BLACK);
            initDesenMenu();

            setcolor(WHITE);
            playerVsPlayer();
        }

        if(isButonClicked(mouse, instructiuniMeniu)){
            gatainstructiuni=0;
            setcolor(BLACK);
            initDesenMenu();
            desenInstructiuni();
        }
        if(isButonClicked(mouse,setariJocButon ))
        {
            gataSetari=0;
            setcolor(BLACK);
            initDesenMenu();
            desenSetari();


        }
    }
}


int main() {

    initwindow(1280,1024, "Cinci Cifre", 0, 0, 0);

    initDesenMenu();

    do{
        updateGame();
    }while(!gataGame);

    closegraph();

    return 0;
}
