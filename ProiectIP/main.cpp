#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cstdio>
#include <cstring>
#include <winbgim.h>
#include <cmath>
#include <conio.h>

using namespace std;

/*
 * IDEE:
 * 1. buton de hint. scor+=20.
 */

 //structuri
 //fiindca vom lucra in coordonate x, y, am ales sa fac o structura care are x si y.
struct CORD{
    int x, y;
}desenCord; //desenCord este de fapt coordonata stanga sus de la care exista desenul nostru.

//o structura prin care definesc un buton. acest buton va avea doua coordonate esentiale. Stanga sus si dreaptaJos.
struct BUTON{
    CORD stSus, drJos;
}upArrow, downArrow, zero, unu, doi, trei, patru, cinci, sase, sapte, opt, noua;
BUTON exitMenu, playerVsPcButton, playerVsPlayerButton, exitPlayerVsPc;
//acestea sunt toate butoanele pe care le vom folosi. daca deschizi consola, vei vedea la ce ma refer.

 //variabile globale
unsigned latura, gataPlayerVsPC, gataGame, latime, linie;
//gataPlayerVsPC-flag pt cand jocul s-a terminat.
//linie - sa stim pe ce linie ne aflam in jocul nostru.
int scroll;
//scroll-ul il folosim pentru a implementa "scroll buttons". cele de sus stanga din consola.

//functie ce imi deseneaza un buton. gandeste ca fiecare functie cu parametru GENERAL pe care o facem este pentru ca
//o vom folosi de mai multe ori.
void drawButton(BUTON buton){
    rectangle(buton.stSus.x, buton.stSus.y, buton.drJos.x, buton.drJos.y);
}

//initializam coordonatele unui buton.
void initCordButton(BUTON &buton, int x1, int y1, int x2, int y2){
    buton.stSus.x=x1;
    buton.stSus.y=y1;
    buton.drJos.x=x2;
    buton.drJos.y=y2;
}

//self explanatory
void drawScrollArrows(){
    drawButton(upArrow);
    line(upArrow.stSus.x+10, upArrow.stSus.y+5, upArrow.stSus.x+10, upArrow.stSus.y+15);
    line(upArrow.stSus.x+5, upArrow.stSus.y+10, upArrow.stSus.x+10, upArrow.stSus.y+5);
    line(upArrow.stSus.x+15, upArrow.stSus.y+10, upArrow.stSus.x+10, upArrow.stSus.y+5);

    drawButton(downArrow);
    line(downArrow.stSus.x+10, downArrow.stSus.y+5, downArrow.stSus.x+10, downArrow.stSus.y+15);
    line(downArrow.stSus.x+5, downArrow.stSus.y+10, downArrow.stSus.x+10, downArrow.stSus.y+15);
    line(downArrow.stSus.x+15, downArrow.stSus.y+10, downArrow.stSus.x+10, downArrow.stSus.y+15);
}

//desenam graphic user interface input (adica tastatura cu cifre)
void drawGUIInputNumber(){
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
}

//desenare piese auxiliare.
void initDesenAuxiliaryButtons(){
    //coordonate sageti
    initCordButton(upArrow, 10, 10, 30, 30);
    initCordButton(downArrow, 10, 35, 30, 55);

    //desenare sageti
    drawScrollArrows();

    //coordonate butoane cu numere si desenarea lor.
    drawGUIInputNumber();

    //coordonata btn exitPlayerVsPc
    initCordButton(exitPlayerVsPc, 30, getmaxy()/2+100, 150, getmaxy()/2+130);
    drawButton(exitPlayerVsPc);
    outtextxy(exitPlayerVsPc.stSus.x+10, exitPlayerVsPc.stSus.y+10, "To Main Menu");
}

//functii folositoare
//daca doi vectori sunt egali.
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

//daca un buton este apasat.
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

    //vector care estePus[i]=1 daca cifra i e pusa, si =0 daca nu e pusa.
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
    outtextxy(x, y, text);
    Sleep(300);
    setcolor(BLACK);
    outtextxy(x, y, text);
    Sleep(150);
    setcolor(WHITE);
    outtextxy(x, y, text);
    Sleep(300);
    setcolor(BLACK);
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
    initCordButton(exitMenu, getmaxx()/2-50, getmaxy()/2+50, getmaxx()/2+50,  getmaxy()/2+100);
    drawButton(exitMenu);
    outtextxy(exitMenu.stSus.x+35, exitMenu.stSus.y+20, "Exit");

    initCordButton(playerVsPcButton, getmaxx()/2-100, getmaxy()/2-50, getmaxx()/2+100,  getmaxy()/2);
    drawButton(playerVsPcButton);
    outtextxy(playerVsPcButton.stSus.x+35, playerVsPcButton.stSus.y+20, "Player vs PC");
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
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

            for(int linieTemp=-5; linieTemp<=5; ++linieTemp){
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
                    outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura*i+latura/2-5, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

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
                        outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura*i+latura/2-5, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, downArrow)){
            scroll=abs(scroll);

            //stergere
            setcolor(BLACK);

            //linia 0
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

            for(int linieTemp=-10; linieTemp<=10; ++linieTemp){
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
                    outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura*i+latura/2-5, cifra);
                }

            //update la coordonata desenului pe y.
            desenCord.y+=scroll;

            //desenare la loc.
            setcolor(WHITE);

            //linia 0
            outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
            outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

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
                        outtextxy(desenCord.x+latura*j+latura/2-5, desenCord.y+latura*i+latura/2-5, cifra);
                    }
                }
        }

        if(isButonClicked(mouse, exitPlayerVsPc)){
            gataPlayerVsPC=1;
// TODO (andre#1#): ERASE ALL.
            initDesenMenu();
        }

        //daca utilizatorul apasa pe unul dintre acele butoane.
        if(isButonClicked(mouse, zero)){
            //daca e pe prima pozitie, arata eroare
            if(pozCifra==2){
                blinkMessage(getmaxx()-300, 200, "APASATI ALTA CIFRA");
            }else{
                //daca cifra a mai fost pusa
                if(checkPunere(0, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=0;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "0");
                    //increment pozitie cifra
                    pozCifra++;
                }
            }
        }
        if(isButonClicked(mouse, unu)){
            if(checkPunere(1, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=1;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "1");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, doi)){
            if(checkPunere(2, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=2;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "2");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, trei)){
            if(checkPunere(3, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=3;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "3");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, patru)){
            if(checkPunere(4, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=4;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "4");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, cinci)){
            if(checkPunere(5, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=5;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "5");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sase)){
            if(checkPunere(6, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=6;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "6");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, sapte)){
            if(checkPunere(7, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=7;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "7");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, opt)){
            if(checkPunere(8, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=8;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "8");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }
        if(isButonClicked(mouse, noua)){
            if(checkPunere(9, matCifru[linie], pozCifra-1)){
                    blinkMessage(getmaxx()-300, 200, "CIFRA A MAI FOST PUSA");
                }else {
                    //bag in matrice
                    matCifru[linie][pozCifra]=9;
                    //desenez
                    outtextxy(desenCord.x+pozCifra*latura+latura/2-5, desenCord.y+linie*latura+latura/2-5, "9");
                    //increment pozitie cifra
                    pozCifra++;
                }
        }

    }
}

void initDesenPlayerVsPc(){

    //init variabile pt PlayerVsPc
    latime=300;
    latura=300/7;
    desenCord.x=(getmaxx()-latime)/2;
    desenCord.y=100;
    linie=0;
    scroll=100;

    //desenare linie 0
    for(int linieTemp=0; linieTemp<2; ++linieTemp)
        rectangle(desenCord.x+linieTemp*latura, desenCord.y,
                   desenCord.x+(linieTemp+1)*latura, desenCord.y+latura);

    outtextxy(desenCord.x+latura/2-5, desenCord.y+latura/2-5, "C");
    outtextxy(desenCord.x+latura+latura/2-5, desenCord.y+latura/2-5, "M");

    //pregatesc noul teren pt prima linie in care utilizatorul pune cifre.
    linie++;
    for(int j=0; j<7; ++j){
        rectangle(desenCord.x+latura*j, desenCord.y+latura*linie,
                   desenCord.x+latura*(j+1), desenCord.y+latura*(linie+1));
    }

}


void playerVsPC(){

    //desenare auxiliary buttons
    initDesenAuxiliaryButtons();

    //desenare playerVsPC graphic.
    initDesenPlayerVsPc();

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
        updatePlayerVsPC(cifru, pozCifra, matCifru);
    }while (!gataPlayerVsPC && !suntEgale(cifru, (matCifru[linie]+2)));

    initDesenMenu();

}


void updateGame(){
    if(ismouseclick(WM_LBUTTONDOWN)){
        clearmouseclick(WM_LBUTTONDOWN);

        CORD mouse;
        mouse.x=mousex();
        mouse.y=mousey();

        if(isButonClicked(mouse, exitMenu)){
            gataGame=1;
        }

        if(isButonClicked(mouse, playerVsPcButton)){
            gataPlayerVsPC=0;
            setcolor(BLACK);
            initDesenMenu();
            setcolor(WHITE);
            playerVsPC();
        }

    }
}


int main() {

    initwindow(1500,1270);


    initDesenMenu();

    do{
        updateGame();
    }while(!gataGame);

/*
    //desenam inceputul si toate cele
    initDesen();

    //versiunea player VS PC
    playerVsPC();
*/
    getch();
    closegraph();

    return 0;
}
