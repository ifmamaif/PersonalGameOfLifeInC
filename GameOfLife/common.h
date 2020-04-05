#pragma once

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


void nimic(char** matrice, int i, int j);
int VerificaCelula(char** matrice, int i, int j);
void VerificaViata(char** matrice, int i, int j, int vieti);
void VerificaCentru(char** matrice, int linii, int coloane);
void PregatesteUrmatoareaSimulare(char** matrice, int linii, int coloane);