#include "planar.h"
#include "common.h"

void VerificaRamaSusPlanar2x2(int** matrice, int linii, int coloane)
{
    int life = VerificaCelula(matrice, 0, 1);
    life += VerificaCelula(matrice, 1, 0);
    life += VerificaCelula(matrice, 1, 1);
    VerificaViata(matrice, 0, 0, life);

    life = VerificaCelula(matrice, 0, 0);
    life += VerificaCelula(matrice, 1, 0);
    life += VerificaCelula(matrice, 1, 1);
    VerificaViata(matrice, 0, 1, life);
}

void VerificaRamaSusPlanarOLinie(int** matrice, int linii, int coloane)
{
    // garantat este mai mult de o coloana , altfel s-ar fi apelat VerificaRamaSusPlanarOColoana

    VerificaViata(matrice, 0, 0, 0);

    int life;
    for (int i = 1; i < coloane - 1; i++)
    {
        life = VerificaCelula(matrice, 0, i - 1);
        life += VerificaCelula(matrice, 0, i + 1);
        VerificaViata(matrice, 0, 0, life);
    }

    // i == coloane -1;
    VerificaViata(matrice, 0, coloane - 1, 0);
}

void VerificaRamaSusPlanarOColoana(int** matrice, int linii, int coloane)
{
    VerificaViata(matrice, 0, 0, 0);
}

void VerificaRamaSusPlanar(int** matrice, int linii, int coloane)
{
    // garantat este mai mult de o linie , altfel s-ar fi apelat VerficaRamaSusPlanarOLinie
    // garantat este mai mult de o coloana , altfel s-ar fi apelat VerificaRamaSusPlanarOColoana

    // i == 0
    int life = VerificaCelula(matrice, 0, 1);
    life += VerificaCelula(matrice, 1, 0);
    life += VerificaCelula(matrice, 1, 1);
    VerificaViata(matrice, 0, 0, life);

    for (int i = 1; i < coloane - 1; i++)
    {
        life = VerificaCelula(matrice, 0, i - 1);
        life += VerificaCelula(matrice, 0, i + 1);
        life += VerificaCelula(matrice, 1, i - 1);
        life += VerificaCelula(matrice, 1, i + 1);
        life += VerificaCelula(matrice, 1, i);
        VerificaViata(matrice, 0, 0, life);
    }

    // i == coloane -1;
    life = VerificaCelula(matrice, 0, coloane - 1);
    life += VerificaCelula(matrice, 1, coloane - 1);
    life += VerificaCelula(matrice, 1, coloane - 1);
    VerificaViata(matrice, 0, coloane - 1, life);
}

void VerificaRamaDreaptaPlanar2x2(int** matrice, int linii, int coloane)
{
    int life = VerificaCelula(matrice, 0, 0);
    life += VerificaCelula(matrice, 0, 1);
    life += VerificaCelula(matrice, 1, 0);
    VerificaViata(matrice, 1, 1, life);
}

void VerificaRamaDreaptaPlanarOColoana(int** matrice, int linii, int coloane)
{
    // garantat avem mai multe linii , atlfel s-ar fi apelat nimic
    int life;
    for (int i = 1; i < linii - 1; i++)
    {
        life = VerificaCelula(matrice, i - 1, 0);
        life += VerificaCelula(matrice, i + 1, 0);
        VerificaViata(matrice, i, 0, life);
    }

    // i == linii -1;
    VerificaViata(matrice, linii - 1, 0, 0);
}

void VerificaRamaDreaptaPlanar(int** matrice, int linii, int coloane)
{
    int life;
    for (int i = 1; i < linii - 1; i++)
    {
        life = VerificaCelula(matrice, i - 1, coloane - 1);
        life += VerificaCelula(matrice, i - 1, coloane - 2);
        life += VerificaCelula(matrice, i, coloane - 2);
        life += VerificaCelula(matrice, i + 1, coloane - 2);
        life += VerificaCelula(matrice, i + 1, coloane - 1);
        VerificaViata(matrice, i, coloane - 1, life);
    }

    life = VerificaCelula(matrice, linii - 2, coloane - 1);
    life += VerificaCelula(matrice, linii - 2, coloane - 2);
    life += VerificaCelula(matrice, linii - 1, coloane - 2);
    VerificaViata(matrice, linii - 1, coloane - 1, life);
}

void VerificaRamaJosPlanar2x2(int** matrice, int linii, int coloane)
{
    int life = VerificaCelula(matrice, 0, 0);
    life += VerificaCelula(matrice, 0, 1);
    life += VerificaCelula(matrice, 1, 1);
    VerificaViata(matrice, 1, 0, life);
}

void VerificaRamaJosPlanar(int** matrice, int linii, int coloane)
{
    int life = VerificaCelula(matrice, linii - 2, 0);
    life += VerificaCelula(matrice, linii - 2, 1);
    life += VerificaCelula(matrice, linii - 1, 1);
    VerificaViata(matrice, linii - 1, 0, life);

    for (int i = 1; i < coloane - 2; i++)
    {
        life = VerificaCelula(matrice, linii - 1, i - 1);
        life += VerificaCelula(matrice, linii - 1, i + 1);
        life += VerificaCelula(matrice, linii - 2, i - 1);
        life += VerificaCelula(matrice, linii - 2, i + 1);
        life += VerificaCelula(matrice, linii - 2, i);
        VerificaViata(matrice, linii - 1, i, life);
    }
}

void VerificaRamaStangaPlanar(int** matrice, int linii, int coloane)
{
    int life;
    for (int i = 1; i < linii - 1; i++)
    {
        life = VerificaCelula(matrice, i - 1, 0);
        life += VerificaCelula(matrice, i - 1, 1);
        life += VerificaCelula(matrice, i, 1);
        life += VerificaCelula(matrice, i + 1, 0);
        life += VerificaCelula(matrice, i + 1, 1);
        VerificaViata(matrice, i, 0, life);
    }
}