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
#include <stdio.h> // includerea biblioteci tip header "stdio.h"
#include <stdlib.h>

#include "oldImplementation.h"
#include "newImplementation.h"

int main(int argc,char** argv)
{
    int whichImplementation = 1;
    if (argc < 2)
    {
        printf("Which implementation to run?\n1: Old implementantion\n2: New implementation\n");
        scanf_s("\n%d", &whichImplementation);
    }
    else 
    {
        return 0;
    }

    switch (whichImplementation)
    {
    case 1:
        RunOldImplementation(argc, argv);
        break;
    case 2:
        RunNewImplementation(argc, argv);
        break;
    default:
        printf("No implementation chosen\nExit program\n");
        break;
    }

    return 0;
}   // END main()
