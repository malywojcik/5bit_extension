// funkcje do redukcji kolorów i tworzenia palet
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"

void narzuconaV1()
{
    SDL_Color kolor;
    int R,G,B;
    int kolor5bit;
    int nowyR,nowyG,nowyB;

    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>6;//2bit
            nowyG = G>>6;//2bit
            nowyB = B>>7;//1bit

            R = nowyR<<6;
            G = nowyG<<6;
            B = nowyB<<7;

            setPixel(x+szerokosc/2,y,R,G,B);
        }
    }
}

void narzuconaV2()
{
    SDL_Color kolor;
    int R,G,B;
    int kolor5bit;
    int nowyR,nowyG,nowyB;

    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>6;//2bit     daje 3 w dziesietnym stad nizej mnozene przez 3
            nowyG = G>>6;//2bit
            nowyB = B>>7;//1bit     daje 1 wiec analogicznie

            R = nowyR*255.0/3.0;
            G = nowyG*255.0/3.0;
            B = nowyB*255.0/1.0;

            setPixel(x, (y+wysokosc/2),R,G,B);
        }
    }
}

void narzuconaV3()
{
    SDL_Color kolor;
    int R,G,B;
    int kolor5bit;
    int nowyR,nowyG,nowyB;

    for(int y = 0 ; y < wysokosc/2; y++)
    {
        for(int x = 0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x,y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R*3.0/255.0);
            nowyG = round(G*3.0/255.0);
            nowyB = round(B*1.0/255.0);

            R = nowyR*255.0/3.0;
            G = nowyG*255.0/3.0;
            B = nowyB*255.0/1.0;

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
            int tablicaBayera[y % 4][x % 4];
            konwersjaOdcieni = round( (szary*(levels - 1)) / 255.0f);

            nowySzary = (szary * 255.0f) / (levels - 1);

            setPixel(x + szerokosc/2,y+wysokosc/2,nowySzary,nowySzary,nowySzary);

        }
    }
}

Uint8 z24Kdo5K(SDL_Color kolor)
{
    int R,G,B;
    int nowyR,nowyG,nowyB;
    Uint8 kolor5bit;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R*3.0/255.0);
    nowyG = round(G*3.0/255.0);
    nowyB = round(B*1.0/255.0);

    kolor5bit = (nowyR<<3) | (nowyG<<1) | nowyB; //000RRGGB

    return kolor5bit; //liczba 0-31
}

SDL_Color z5Kdo24K(Uint8 kolor5bit)
{
    SDL_Color kolor;
    int R,G,B;
    int nowyR,nowyG,nowyB;

    //...
    nowyR = (kolor5bit&(0b00011000))>>3;    // 000RRGGB -> 000RR000 -> RR
    nowyG = (kolor5bit&(0b00000110))>>1;    // 000RRGGB -> 00000GG0 -> GG
    nowyB = (kolor5bit&(0b00000001));       // 000RRGGB -> 0000000B -> B

    R = nowyR*255.0/3.0;
    G = nowyG*255.0/3.0;
    B = nowyB*255.0/1.0;

    kolor.r = R;
    kolor.g = G;
    kolor.b = B;

    return kolor;
}

void paletaNarzucona()
{
    Uint8 kolor5bit, szary5bit;
    SDL_Color kolor, nowyKolor, nowySzary;

    for(int y=0;y<wysokosc/2; y++)
        for(int x=0; x<szerokosc/2;x++)
        {
            kolor = getPixel(x, y);
            kolor5bit = z24Kdo5K(kolor);
            nowyKolor = z5Kdo24K(kolor5bit);
            setPixel(x + szerokosc/2, y, nowyKolor.r, nowyKolor.g, nowyKolor.b);
        }

    for(int k=0;k<32; k++)
        paleta5k[k] = z5Kdo24K(k);
    narysujPalete(0, 210, paleta5k);

    SDL_UpdateWindowSurface(window);
}

void narysujPalete(int px, int py, SDL_Color pal5[])
{
    int x, y;
    for(int k=0; k<32; k++)
    {
        y = k / 6;
        x = k % 6;

        for(int xx=0; xx<10; xx++)
            for(int yy=0; yy<10; yy++)
                setPixel(x*10+xx+px, y*10+yy+py, pal5[k].r, pal5[k].g, pal5[k].b);
    }
}

int sprawdzKolor(SDL_Color kolor)
{
    if(ileKolorow > 0)
        for(int k=0; k<ileKolorow; k++)
            if(porownajKolory(kolor, paleta8[k]))
                return k;
    return dodajKolor(kolor);
}

bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2)
{
    if(kolor1.r != kolor2.r)
        return false;
    if(kolor1.g != kolor2.g)
        return false;
    if(kolor1.b != kolor2.b)
        return false;

    return true;
}

int dodajKolor(SDL_Color kolor)
{
    int aktualnyKolor = ileKolorow;
    paleta8[aktualnyKolor] = kolor;
    if(ileKolorow<32)
    {
        cout<<aktualnyKolor<<": [";
        cout<<(int)kolor.r<<","<<(int)kolor.g<<","<<(int)kolor.b;
        cout<<"]"<<endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}

void czyscPalete()
{
    for(int k=0; k<ileKolorow; k++)
        paleta8[k] = {0, 0, 0};
    ileKolorow = 0;
}

void paletaWykryta() // paletaDedykowana
{
    czyscPalete();
    int indexKolor;
    SDL_Color kolor;
    for(int y=0; y<wysokosc/2; y++)
        for(int x=0; x<szerokosc/2; x++)
        {
            kolor = getPixel(x, y);
            indexKolor = sprawdzKolor(kolor);
        }
    cout<<endl<<"ile kolorow: "<<ileKolorow<<endl;
    if(ileKolorow <=32)
    {
        cout<<"paleta spelnia ograniczenia 5-bit"<<endl;
        narysujPalete(0, 210, paleta8);
    }
    else
        cout<<"paleta przekracza ograniczenia 5-bit"<<endl;
}
