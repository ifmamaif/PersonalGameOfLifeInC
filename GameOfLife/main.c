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
#include <string.h>

#include "oldImplementation.h"
#include "newImplementation.h"
#include "ExpectedOut.h"

//void CreateArgs(int* outArgc, char*** outArgv,const char*file1,const char* file2)
//{
//    char** argvMade = malloc(sizeof(char*) * 3);
//    int str1 = strlen(file1);
//    int str2 = strlen(file2);
//
//    argvMade[1] = malloc(sizeof(char) * (str1 + 1));
//    strcpy_s(argvMade[1], file1,str1);
//
//    argvMade[2] = malloc(sizeof(char) * (str2 + 1));
//    strcpy_s(argvMade[2], file2,str2);
//}
//
//void DeleteArgs(char** argvs)
//{
//    free(argvs[1]);
//    free(argvs[2]);
//    free(argvs);
//}
//
//void RunTest(const char* filePath)
//{
//    int argc;
//    char** argv;
//
//   // CreateArgs(&argv,&argv,filePath)
//}


void RunTests()
{
    int argcMade = 4;
    char** argvMade = malloc(sizeof(char*) * 4);
    argvMade[0] = "main.exe";
    argvMade[1] = malloc(sizeof(char) * (14));
    argvMade[2] = malloc(sizeof(char) * (14));
    argvMade[3] = malloc(sizeof(char) * (14));
    strcpy_s(argvMade[1], 13, "tests/t0.in");
    strcpy_s(argvMade[2], 13, "tests/t0.out");
    strcpy_s(argvMade[3], 13, "tests/t0.exp");
    for (int i = 0; i < 10; i++)
    {
        argvMade[1][7] = argvMade[2][7] = argvMade[3][7] = '0' + i;
        if (RunNewImplementation(argcMade, argvMade) < 1)
        {
            printf("Failed test %s\n", argvMade[1]);
        }
        if (VerifyOutput(argvMade[2], argvMade[3]) < 1)
        {
            printf("Expected test failed: %s\n", argvMade[1]);
        }
    }

    strcpy_s(argvMade[1], 14, "tests/t00.in");
    strcpy_s(argvMade[2], 14, "tests/t00.out");
    strcpy_s(argvMade[3], 14, "tests/t00.exp");

    for (int i = 0; i < 7; i++)
    {
        argvMade[1][7] = argvMade[2][7] = argvMade[3][7] = '0' + i;
        for (int j = 0; j < 10; j++)
        {
            argvMade[1][8] = argvMade[2][8] = argvMade[3][8] = '0' + j;
            if (RunNewImplementation(argcMade, argvMade) < 1)
            {
                printf("Failed test %s\n", argvMade[1]);
            }
            //if (VerifyOutput(argvMade[2], argvMade[3]) < 1)
            //{
            //    printf("Expected test failed: %s\n", argvMade[1]);
            //}
        }
    }

    free(argvMade[1]);
    free(argvMade[2]);
    free(argvMade[3]);
    free(argvMade);
}

int main(int argc,char** argv)
{
    /*int whichImplementation = 2;
    if (argc < 2)
    {
        printf("Which implementation to run?\n1: Old implementantion\n2: New implementation\n");
        scanf_s("\n%d", &whichImplementation);
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
    }*/


    RunTests();
   


    return 0;
}   // END main()
