// funkcje do redukcji kolorów i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
void narzuconaV1()
{
    SDL_Color kolor;
    int R,G,B;
    int kolor8bit;
    int nowyR,nowyG,nowyB;

    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>5;//3bit 8 -  3 (setPixel przyjmuje wartosci 8 bitowe)
            nowyG = G>>5;//3bit
            nowyB = B>>6;//2bit

            R = nowyR<<5;
            G = nowyG<<5;
            B = nowyB<<6;

            setPixel(x+szerokosc/2,y,R,G,B);
        }
    }
}

void narzuconaV2()
{
    SDL_Color kolor;
    int R,G,B;
    int kolor8bit;
    int nowyR,nowyG,nowyB;

    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>5;//3bit 8 -  3 (setPixel przyjmuje wartosci 8 bitowe)
            nowyG = G>>5;//3bit
            nowyB = B>>6;//2bit

            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;

            setPixel(x, (y+wysokosc/2),R,G,B);
        }
    }
}

void narzuconaV3()
{
    SDL_Color kolor;
    int R,G,B;
    int kolor8bit;
    int nowyR,nowyG,nowyB;

    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R*7.0/255.0);
            nowyG = round(G*7.0/255.0);
            nowyB = round(B*3.0/255.0);

            R = nowyR*255.0/7.0;
            G = nowyG*255.0/7.0;
            B = nowyB*255.0/3.0;

            setPixel(x + szerokosc/2,y+wysokosc/2,R,G,B);
        }
    }
}


void narzuconaSzary(int n)
{
    SDL_Color kolor;
    float szary;
    int konwersjaOdcieni;
    Uint8 nowySzary;
    int levels  = pow(2,n);
    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            szary = 0.299f*kolor.r + 0.587f*kolor.g + 0.114f*kolor.b;

            konwersjaOdcieni = round( (szary*(levels - 1)) / 255.0f);

            nowySzary = (szary * 255.0f) / (levels - 1);

            setPixel(x + szerokosc/2,y+wysokosc/2,nowySzary,nowySzary,nowySzary);

        }
    }
}

void narzuconaSzaryTablicaBayera(int n)
{
    SDL_Color kolor;
    float szary;
    int konwersjaOdcieni;
    Uint8 nowySzary;
    int tablicaBayera[2][2] = {{2,4},{3,1}};
    float zaktualizowanaTablicaBayera[2][2];

    int levels  = pow(2,n);
    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            szary = 0.299f*kolor.r + 0.587f*kolor.g + 0.114f*kolor.b;
            int tablicaBayera[y % 4][x % 4]
            konwersjaOdcieni = round( (szary*(levels - 1)) / 255.0f);

            nowySzary = (szary * 255.0f) / (levels - 1);

            setPixel(x + szerokosc/2,y+wysokosc/2,nowySzary,nowySzary,nowySzary);

        }
    }
}
