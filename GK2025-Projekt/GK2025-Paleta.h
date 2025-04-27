// funkcje do redukcji kolor�w i tworzenia palet
#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;
void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
void narzuconaSzary(int n);

Uint8 z24Kdo5K(SDL_Color kolor);
SDL_Color z5Kdo24K(Uint8 kolor5bit);
void paletaNarzucona();
void narysujPalete(int px, int py, SDL_Color pal5[]);
void paletaWykryta();
int sprawdzKolor(SDL_Color kolor);
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
void czyscPalete();
void paletaWykryta();

#endif // GK2025_PALETA_H_INCLUDED
