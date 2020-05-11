#pragma once

#include <stdio.h>

enum TipCelula
{
    CelulaMoarta = 0,
    CelulaVie = 1,
    CelulaTrebuieSaMoara = 2,
    CelulaTrebuieSaTraiasca = 3,
};

typedef enum TipSimulare
{
    Nimic = 0,
    Planar,
    Tiroidala,
} Simulare;


void nimic(int** matrice, int i, int j);
int VerificaCelula(int** matrice, int i, int j);
void VerificaViata(int** matrice, int i, int j, int vieti);
void VerificaCentru(int** matrice, int linii, int coloane);
void PregatesteUrmatoareaSimulare(int** matrice, int linii, int coloane);

void AfisareMatrice(int** matrice, int linii, int coloane,FILE*out);