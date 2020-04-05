#include "common.h"

void nimic(char** matrice, int i, int j) {}

int VerificaCelula(char** matrice, int i, int j)
{
    return matrice[i][j] > CelulaMoarta;
}

void VerificaViata(char** matrice, int i, int j, int vieti)
{
    char* celula = &(matrice[i][j]);
    if (vieti < 2 || vieti > 3)
    {
        *celula = CelulaTrebuieSaMoara;
        return;
    }
    if (vieti == 3 ||
        (vieti == 2 && (*celula) == CelulaVie))
    {
        *celula = CelulaTrebuieSaTraiasca;
        return;
    }

    *celula = CelulaTrebuieSaMoara;
}

void VerificaCentru(char** matrice, int linii, int coloane)
{
    int life;
    for (int i = 1; i < linii - 1; i++)
        for (int j = 1; j < coloane - 1; j++)
        {
            life = 0;
            life += VerificaCelula(matrice, i + 1, j + 1);
            life += VerificaCelula(matrice, i + 1, j - 1);
            life += VerificaCelula(matrice, i + 1, j);
            life += VerificaCelula(matrice, i - 1, j + 1);
            life += VerificaCelula(matrice, i - 1, j - 1);
            life += VerificaCelula(matrice, i - 1, j);
            life += VerificaCelula(matrice, i, j + 1);
            life += VerificaCelula(matrice, i, j - 1);
            VerificaViata(matrice, i, j, life);
        }
}

void PregatesteUrmatoareaSimulare(char** matrice, int linii, int coloane)
{
    for (int pozitie_linie = 0; pozitie_linie < linii; pozitie_linie++)
        for (int pozitie_coloana = 0; pozitie_coloana < coloane; pozitie_coloana++)
        {
            char* celula = &(matrice[pozitie_linie][pozitie_coloana]);
            switch (*celula)
            {
            case CelulaTrebuieSaTraiasca:
                (*celula) = CelulaVie;
                break;
            case CelulaTrebuieSaMoara:
                (*celula) = CelulaMoarta;
            default:
                break;
            }
        }
}