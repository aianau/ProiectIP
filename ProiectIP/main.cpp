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
BUTON exitMenuButon, playerVsPcButon, playerVsPlayerButon, exitPlayerVsPcButon, exitPlayervsPlayerButon, DeleteNumber, Instructiuni, exitinstructiuni;

unsigned latura,  latime, linie;
unsigned gataPlayerVsPC, gataPlayerVsPlayer, gataGame, gatainstructiuni;

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
    initCordButon(DeleteNumber ,30, getmaxy()/2-50, 340, getmaxy()/2+5);
    drawButon(DeleteNumber);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(DeleteNumber.stSus.x+13, DeleteNumber.stSus.y+10, "Sterge Cifra");

    //coordonate butoane cu numere si desenarea lor.
    drawGUIInputNumber();

    //coordonata btn exitPlayerVsPcButon
    initCordButon(exitPlayerVsPcButon, 30, getmaxy()/2+100, 350, getmaxy()/2+160);
    drawButon(exitPlayerVsPcButon);
     settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 5);
    outtextxy(exitPlayerVsPcButon.stSus.x+10, exitPlayerVsPcButon.stSus.y+10, "To Main Menu");
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
    initCordButon(exitMenuButon, getmaxx()/2-95, getmaxy()/2+70, getmaxx()/2+30,  getmaxy()/2+138);
    drawButon(exitMenuButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(exitMenuButon.stSus.x+20, exitMenuButon.stSus.y+10, "Exit");

    initCordButon(playerVsPcButon, getmaxx()/2-190, getmaxy()/2-140, getmaxx()/2+140,  getmaxy()/2-70);
    drawButon(playerVsPcButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(playerVsPcButon.stSus.x+15, playerVsPcButon.stSus.y+10, "Player vs PC");

    initCordButon(playerVsPlayerButon, getmaxx()/2-230, getmaxy()/2-250, getmaxx()/2+185,  getmaxy()/2-185);
    drawButon(playerVsPlayerButon);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(playerVsPlayerButon.stSus.x+20, playerVsPlayerButon.stSus.y+7,"Player vs Player");

    initCordButon(Instructiuni, getmaxx()/2-160, getmaxy()/2-30, getmaxx()/2+118, getmaxy()/2+30);
    drawButon(Instructiuni);
    settextstyle( SANS_SERIF_FONT, HORIZ_DIR, 6);
    outtextxy(Instructiuni.stSus.x+13,Instructiuni.stSus.y+5, "Instructiuni");
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
        outtextxy(desenCord.x+latura/2-13, desenCord.y+latura*linie+latura/2-18, nrElemCentrateChar);
        outtextxy(desenCord.x+latura+latura/2-13, desenCord.y+latura*linie+latura/2-18, nrElemMutateChar);

        //daca s-a terminat jocul, stop.
        if(suntEgale(cifru, (matCifru[linie]+2))){
            outtextxy(getmaxx()-100, 100, "FELICITARI");
            Sleep(500);
            gataPlayerVsPC=1;
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
            outtextxy(desenCord.x+latura/2-13, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-13, desenCord.y+latura/2-18, "M");

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
                    outtextxy(desenCord.x+latura*j+latura/2-13, desenCord.y+latura*i+latura/2-18, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-13, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-13, desenCord.y+latura/2-18, "M");

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
                        outtextxy(desenCord.x+latura*j+latura/2-13, desenCord.y+latura*i+latura/2-18, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, downArrow)){
            scroll=abs(scroll);

            //stergere
            setcolor(BLACK);

            //linia 0
            outtextxy(desenCord.x+latura/2-15, desenCord.y+latura/2-18, "C");
            outtextxy(desenCord.x+latura+latura/2-15, desenCord.y+latura/2-18, "M");

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
                    outtextxy(desenCord.x+latura*j+latura/2-13, desenCord.y+latura*i+latura/2-18, cifra);
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

        if(isButonClicked(mouse, exitPlayerVsPcButon)){
            gataPlayerVsPC=1;
            initDesenMenu();
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "0");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "1");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "2");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "3");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "4");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "5");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "6");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "7");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "8");
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
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-13, desenCord.y+linie*latura+latura/2-18, "9");
                    //increment pozitie cifra
                    pozCifra++;
                }
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
    scroll=100;

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


void playerVsPlayer(){
    //desenare auxiliary buttons
    initDesenAuxiliaryButons();
}


void DesenInstructiuni(){
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




}
void updateGame(){


   if(ismouseclick(WM_LBUTTONDBLCLK)){
        clearmouseclick(WM_LBUTTONDBLCLK);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();


        if(isButonClicked(mouse, exitMenuButon)){
            gataGame=1;
        }

        if(isButonClicked(mouse, playerVsPcButon)){

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

         if(ismouseclick(WM_LBUTTONDOWN)){
        clearmouseclick(WM_LBUTTONDOWN);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();
         if(isButonClicked(mouse, Instructiuni))
        {
            setcolor(BLACK);
            initDesenMenu();
            DesenInstructiuni();

    }
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
