/*
Game of life​ („Jocul vieții”) presupune simularea evoluției unor celule într-un
spațiu bidimensional. Jocul se desfășoară într-un grid de dimensiuni N​ și M​, având o
configurație inițială de celule de la care pornește simularea. Evoluția are loc parcursul a
K​ etape, starea la pasul p​ depinzând exclusiv de starea la pasul p - 1​.
Multiplicarea celulelor urmează câteva reguli:
     orice celulă cu mai puțin de două celule vecine moare de singurătate
     orice celulă cu mai mult de trei celule vecine moare din cauza supraaglomerării
     orice celulă cu două sau trei celule vecine supraviețuiește
     celulă nouă este creată dacă are exact trei celule vecine

Veți primi de la tastatură date de intrare în următorul format:
    pe prima linie
         un caracter, fie 'P'​, dacă reprezentarea este de tip plan, fie 'T'​ dacă
        reprezentarea este toroidală
         doi întregi M​ și N​, reprezentând lățimea și înălțimea hărții
         un întreg K​, reprezentând numărul de generații de simulat
     pe următoarele N​ linii, câte M​ biți
         1, pentru a marca prezența unei celule
         0, altfel

Restricții:
     1 ≤ M​, N​ ≤ 1000
     0 ≤ K ≤ 10000

*/

#include "newImplementation.h"

#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "planar.h"

void RuleazaSimulare(char** matrice, int numar_linii, int numar_coloane, int etape, Simulare simulare)
{
    if (numar_linii < 1 ||
        numar_coloane < 1 ||
        matrice == NULL ||
        etape < 1)
    {
        return;
    }

    if (numar_linii == 1 && numar_coloane == 1)
    {
        matrice[0][0] = CelulaMoarta;
        return;
    }
    if (numar_coloane == 1 && numar_linii == 2)
    {
        matrice[0][0] = matrice[1][0] = 0;
        return;
    }
    if (numar_coloane == 2 && numar_linii == 1)
    {
        matrice[0][0] = matrice[0][1] = 0;
        return;
    }

    void (*verificaSus) (char**, int, int);
    void (*verificaDreapta) (char**, int, int);
    void (*verificaJos) (char**, int, int);
    void (*verificaStanga) (char**, int, int);
    void (*verificaCentru) (char**, int, int);

    if (numar_linii == 2 && numar_coloane == 2)
    {
        verificaSus = &VerificaRamaSusPlanar2x2;
        verificaDreapta = &VerificaRamaDreaptaPlanar2x2;
        verificaJos = &VerificaRamaJosPlanar2x2;
        verificaStanga = &nimic;
        verificaCentru = &nimic;
    }
    else
    {
        verificaSus = &VerificaRamaSusPlanar;
        verificaDreapta = &VerificaRamaDreaptaPlanar;
        verificaJos = &VerificaRamaJosPlanar;
        verificaStanga = &VerificaRamaStangaPlanar;
        verificaCentru = &VerificaCentru;

        switch (numar_linii)
        {
        case 1: // && coloane > 2
            verificaSus = &VerificaRamaSusPlanarOLinie;
            verificaJos = &nimic;
            verificaStanga = &nimic;
            verificaDreapta = &nimic;
            verificaCentru = &nimic;
            break;
        case 2: // && coloane > 2
            verificaStanga = &nimic;
            verificaCentru = &nimic;
            break;
        default:
            break;
        }

        switch (numar_coloane)
        {
        case 1: // && linii > 2
            verificaSus = &VerificaRamaSusPlanarOColoana;
            verificaDreapta = verificaDreapta == (&nimic) ? &nimic : &VerificaRamaDreaptaPlanarOColoana;
            verificaJos = &nimic;
            verificaStanga = &nimic;
            verificaCentru = &nimic;
            break;
        case 2: // && linii > 2
            verificaCentru = &nimic;
            break;
        default:
            break;
        }
    }
    
    while (etape > 0)
    {
        verificaSus(matrice, numar_linii, numar_coloane);
        verificaDreapta(matrice, numar_linii, numar_coloane);
        verificaJos(matrice, numar_linii, numar_coloane);
        verificaStanga(matrice, numar_linii, numar_coloane);
        verificaCentru(matrice, numar_linii, numar_coloane);

        PregatesteUrmatoareaSimulare(matrice, numar_linii, numar_coloane);

        etape--;
    }
}

int RunNewImplementation(int argc, char** argv)
{
    Simulare Tip_plan; // tipul de problema/afisare ; Adica daca se face reprezentarea tip plan sau toroidala
    int numar_linii, numar_coloane, Etape;
    int** matrice = NULL;
    char value;

    //  BEGIN citeste_variabile
    if (argc < 2)
    {
        printf("Alege Tip plan:\nPlan planar : 'P' sau 'p'\nPlan toroidal : 'T' sau 't'\n");
        scanf_s("\n%c", &value, 1);
        switch (value)
        {
        case 'p':
        case 'P':
            Tip_plan = Planar;
            break;
        case 't':
        case 'T':
            Tip_plan = Tiroidala;
            break;
        default:
            Tip_plan = Nimic;
            printf("Tip plan invalid\n");
            return 0;
        }

        printf("Numar lini?\nNumar coloane?\nEtape?\n");
        scanf_s("\n%d %d %d", &numar_linii, &numar_coloane, &Etape);

        if (numar_linii < 0 || numar_coloane < 0)
        {
            return 0;
        }
        matrice = (int**)malloc(sizeof(int*) * numar_linii);
        for (int pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
            matrice[pozitie_linie] = (int*)malloc(sizeof(int) * numar_coloane);

        for (int pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
            for (int pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
            {
                printf("[%d][%d] = ? ", pozitie_linie, pozitie_coloana);
                int value = 0;
                scanf_s(" %d", &value);
                matrice[pozitie_linie][pozitie_coloana] = value;
            }
    }
    else
    {
        return 0;
    }
    // END citeste_variabile


    for (int pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
        free(matrice[pozitie_linie]);
    free(matrice);
    return 0;
}