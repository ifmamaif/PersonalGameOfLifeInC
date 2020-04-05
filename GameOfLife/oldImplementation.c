﻿#include "oldImplementation.h"

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

int verificacaz1T(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, int** matrice)
{
    if (pozitie_coloana < 0 && matrice[0][numar_coloane - 1] == 1 || matrice[0][numar_coloane - 1] == 3) return 1;
    else if (pozitie_coloana > (numar_coloane - 1) && matrice[0][0] == 1 || matrice[0][0] == 3) return 1;
    else if (pozitie_linie < 0 || pozitie_coloana < 0 || pozitie_linie >= numar_linii || pozitie_coloana >= numar_coloane)return 0;
    else if (matrice[pozitie_linie][pozitie_coloana] == 1 || matrice[pozitie_linie][pozitie_coloana] == 3) return 1;
    return 0;
}

int verificacelulaP(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, int** matrice)
{
    if (pozitie_linie < 0 || pozitie_coloana < 0 || pozitie_linie >= numar_linii || pozitie_coloana >= numar_coloane)return 0;
    else if (matrice[pozitie_linie][pozitie_coloana] == 1 || matrice[pozitie_linie][pozitie_coloana] == 3) return 1;
    return 0;
}//END verificacelulaP()

int verificacelulaT(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, int** matrice)
{
    if (pozitie_linie < 0 && pozitie_coloana < 0)
    {
        if (matrice[numar_linii - 1][numar_coloane - 1] == 1 || matrice[numar_linii - 1][numar_coloane - 1] == 3) return 1;
        else return 0;
    }
    else

        if (pozitie_linie >= numar_linii && pozitie_coloana >= numar_coloane)
        {
            if (matrice[0][0] == 1 || matrice[0][0] == 3) return 1;
            else return 0;
        }
        else

            if (pozitie_linie < 0 && pozitie_coloana >= numar_coloane)
            {
                if (matrice[numar_linii - 1][0] == 1 || matrice[numar_linii - 1][0] == 3) return 1;
                else return 0;
            }
            else

                if (pozitie_linie >= numar_linii && pozitie_coloana < 0)
                {
                    if (matrice[0][numar_coloane - 1] == 1 || matrice[0][numar_coloane - 1] == 3) return 1;
                    else return 0;
                }
                else

                    if (pozitie_linie < 0)
                    {
                        if (matrice[numar_linii - 1][pozitie_coloana] == 1 || matrice[numar_linii - 1][pozitie_coloana] == 3) return 1;
                        else return 0;
                    }
                    else

                        if (pozitie_linie >= numar_linii)
                        {
                            if (matrice[0][pozitie_coloana] == 1 || matrice[0][pozitie_coloana] == 3) return 1;
                            else return 0;
                        }
                        else

                            if (pozitie_coloana < 0)
                            {
                                if (matrice[pozitie_linie][numar_coloane - 1] == 1 || matrice[pozitie_linie][numar_coloane - 1] == 3) return 1;
                                else return 0;
                            }
                            else

                                if (pozitie_coloana >= numar_coloane)
                                {
                                    if (matrice[pozitie_linie][0] == 1 || matrice[pozitie_linie][0] == 3) return 1;
                                    else return 0;
                                }
                                else

                                {
                                    if (matrice[pozitie_linie][pozitie_coloana] == 1 || matrice[pozitie_linie][pozitie_coloana] == 3) return 1;
                                    else return 0;
                                }
}//END verificacelulaT()


int RunOldImplementation(int argc, char** argv)
{
    char Tip_plan; // tipul de problema/afisare ; Adica daca se face reprezentarea tip plan sau toroidala
    int numar_linii, numar_coloane, Etape, maximpopulatie = 0;// declararea variabilelor cerintei numar linii,generatiile de simulari , numar biti, matricea , maxim populatie
    int pozitie_linie, pozitie_coloana, populatie = 0;
    char life = 0; // variabile auxiliare pentru parcurgerea in matrice , numar populatie , numar vecini
    int** matrice = NULL;
    // short int numar_linii:6, numar_coloane:6;
    // struct _BOOL : 1 , _BOOL:1 pentru matrice;

    //  BEGIN citeste_variabile
    if (argc < 2)
    {
        printf("Alege Tip plan:\nPlan planar : 'P' sau 'p'\nPlan toroidal : 'T' sau 't'\n");
        scanf_s("\n%c", &(Tip_plan), 1);
        switch (Tip_plan)
        {
        case 'p':
        case 'P':
        case 't':
        case 'T':
            break;
        default:
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
        for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
            matrice[pozitie_linie] = (int*)malloc(sizeof(int) * numar_coloane);

        for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
            for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
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

    // Calculare Populatia initiala
    for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
        for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
            if (matrice[pozitie_linie][pozitie_coloana] == 1)maximpopulatie++;

    // End Calculare Populatia initiala
    if (Tip_plan == 'P' || Tip_plan == 'p')
    {
        printf("\n Reprezentare planara! \n");
        while (Etape > 0)
        {
            //Begin verificare_celula
            for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                {
                    //Aflarea vecinilor
                    life = 0;
                    life += verificacelulaP(pozitie_linie - 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie - 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie - 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie + 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie + 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                    life += verificacelulaP(pozitie_linie + 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                    //END Aflarea vecinilor
                    if (life == 3 && matrice[pozitie_linie][pozitie_coloana] == 0)
                    {
                        //Verificarea posibilei celule noi
                        matrice[pozitie_linie][pozitie_coloana] = 2;
                        // Modificare in matrice pentru pentru evolutia celulor intr-o etapa
                    }

                    if (matrice[pozitie_linie][pozitie_coloana] == 1)
                        if (life < 2 || life >3)
                        {
                            //Verificarea posibilei celule moarte
                            matrice[pozitie_linie][pozitie_coloana] = 3;
                            //Modificare in matrice pentru evoluatia celulor intr-o etapa
                        }
                }
            //END verificare_celula

            populatie = 0;
            for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                {
                    // "Evolutia celulor"
                    if (matrice[pozitie_linie][pozitie_coloana] == 2)
                    {
                        matrice[pozitie_linie][pozitie_coloana] = 1;
                    }
                    else if (matrice[pozitie_linie][pozitie_coloana] == 3)
                    {
                        matrice[pozitie_linie][pozitie_coloana] = 0;
                    }
                    if (matrice[pozitie_linie][pozitie_coloana] == 1)populatie++;
                    // END  "Evolutia celulor"
                }

            if (populatie > maximpopulatie)
            {
                maximpopulatie = populatie;
            }
            //Modificarea gradului maxim de populatie


            Etape--; //Scaderea numarului de evolutii / K / Etape (cerute)
        }
    }
    else if (Tip_plan == 'T' || Tip_plan == 't')
    {
        printf("\n Reprezentare Toroidala! \n");
        if (numar_coloane == 1 && numar_linii == 1 && Etape > 0)matrice[0][0];
        else if (numar_coloane == 1 && numar_linii == 2 && Etape > 0)matrice[0][0] = matrice[1][0] = 0;
        else if (numar_coloane == 2 && numar_linii == 1 && Etape > 0)matrice[0][0] = matrice[0][1] = 0;
        else if (numar_coloane == 1)
        {
            while (Etape > 0)
            {
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                {
                    life = 0;
                    life += verificacaz1T(pozitie_linie - 1, 0, numar_linii, numar_coloane, matrice);
                    life += verificacaz1T(pozitie_linie + 1, 0, numar_linii, numar_coloane, matrice);
                    if (life < 2)
                        matrice[pozitie_linie][0] = 3;
                }
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                {
                    if (matrice[pozitie_linie][0] == 3)matrice[pozitie_linie][0] = 0;
                }
                Etape--;
            }
        }
        else if (numar_linii == 1)
        {
            while (Etape > 0)
            {
                for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                {
                    life = 0;
                    life += verificacaz1T(0, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                    life += verificacaz1T(0, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                    if (life < 2)
                        matrice[0][pozitie_coloana] = 3;
                }
                for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                {
                    if (matrice[0][pozitie_coloana] == 3)matrice[0][pozitie_coloana] = 0;
                }
                Etape--;
            }
        }
        else if (numar_linii == 2 && numar_coloane == 2)
        {
            while (Etape > 0)
            {
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        life = 0;
                        life += verificacelulaP(pozitie_linie - 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie - 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie - 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie + 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie + 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaP(pozitie_linie + 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        if (life == 3 && matrice[pozitie_linie][pozitie_coloana] == 0)
                        {
                            //Verificarea posibilei celule noi
                            matrice[pozitie_linie][pozitie_coloana] = 2;
                            // Modificare in matrice pentru pentru evolutia celulor intr-o etapa
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 1)
                            if (life < 2 || life >3)
                            {
                                //Verificarea posibilei celule moarte
                                matrice[pozitie_linie][pozitie_coloana] = 3;
                                //Modificare in matrice pentru evoluatia celulor intr-o etapa
                            }
                    }
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        if (matrice[pozitie_linie][pozitie_coloana] == 2)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 1;
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 3)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 0;
                        }
                    }
                Etape--;
            }
        }
        else if (numar_coloane == 2)
        {
            while (Etape > 0)
            {
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        life = 0;
                        life += verificacelulaT(pozitie_linie - 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie - 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        if (life == 3 && matrice[pozitie_linie][pozitie_coloana] == 0)
                        {
                            //Verificarea posibilei celule noi
                            matrice[pozitie_linie][pozitie_coloana] = 2;
                            // Modificare in matrice pentru pentru evolutia celulor intr-o etapa
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 1)
                            if (life < 2 || life >3)
                            {
                                //Verificarea posibilei celule moarte
                                matrice[pozitie_linie][pozitie_coloana] = 3;
                                //Modificare in matrice pentru evoluatia celulor intr-o etapa
                            }
                    }
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        if (matrice[pozitie_linie][pozitie_coloana] == 2)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 1;
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 3)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 0;
                        }
                        if (matrice[pozitie_linie][pozitie_coloana] == 1)populatie++;
                    }
                if (populatie > maximpopulatie)maximpopulatie = populatie;
                //Modificarea gradului maxim de populatie

                Etape--;//Scaderea numarului de evolutii / K / Etape (cerute)
            }
        }
        else if (numar_linii == 2)
        {
            while (Etape > 0)
            {
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        life = 0;
                        life += verificacelulaT(pozitie_linie, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        if (life == 3 && matrice[pozitie_linie][pozitie_coloana] == 0)
                        {
                            //Verificarea posibilei celule noi
                            matrice[pozitie_linie][pozitie_coloana] = 2;
                            // Modificare in matrice pentru pentru evolutia celulor intr-o etapa
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 1)
                            if (life < 2 || life >3)
                            {
                                //Verificarea posibilei celule moarte
                                matrice[pozitie_linie][pozitie_coloana] = 3;
                                //Modificare in matrice pentru evoluatia celulor intr-o etapa
                            }
                    }
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        if (matrice[pozitie_linie][pozitie_coloana] == 2)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 1;
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 3)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 0;
                        }
                        if (matrice[pozitie_linie][pozitie_coloana] == 1)populatie++;
                    }
                if (populatie > maximpopulatie)maximpopulatie = populatie;
                //Modificarea gradului maxim de populatie

                Etape--;//Scaderea numarului de evolutii / K / Etape (cerute)
            }
        }
        else
            while (Etape > 0)
            {
                //Begin verificare_celula
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        //Aflarea vecinilor
                        life = 0;
                        life += verificacelulaT(pozitie_linie - 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie - 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie - 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
                        life += verificacelulaT(pozitie_linie + 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
                        //END Aflarea vecinilor
                        if (life == 3 && matrice[pozitie_linie][pozitie_coloana] == 0)
                        {
                            //Verificarea posibilei celule noi
                            matrice[pozitie_linie][pozitie_coloana] = 2;
                            // Modificare in matrice pentru pentru evolutia celulor intr-o etapa
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 1)
                            if (life < 2 || life >3)
                            {
                                //Verificarea posibilei celule moarte
                                matrice[pozitie_linie][pozitie_coloana] = 3;
                                //Modificare in matrice pentru evoluatia celulor intr-o etapa
                            }
                    }
                //END verificare_celula
                populatie = 0;
                for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                    for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                    {
                        // "Evolutia celulor"
                        if (matrice[pozitie_linie][pozitie_coloana] == 2)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 1;
                        }
                        else if (matrice[pozitie_linie][pozitie_coloana] == 3)
                        {
                            matrice[pozitie_linie][pozitie_coloana] = 0;
                        }

                        if (matrice[pozitie_linie][pozitie_coloana] == 1)populatie++;
                        // END  "Evolutia celulor"
                    }


                if (populatie > maximpopulatie)
                {
                    maximpopulatie = populatie;
                }
                //Modificarea gradului maxim de populatie

                Etape--;//Scaderea numarului de evolutii / K / Etape (cerute)
            }
    }
    // Afisare matricea finala
    printf("\nAfisare!\n");
    for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
    {
        for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
            printf("%d ", matrice[pozitie_linie][pozitie_coloana]);
        printf("\n");
    }
    // END Afisare
    printf("Gradul maxim de populatie este %.3f%c !", (float)(maximpopulatie * 100) / (numar_linii * numar_coloane), '%');

    
    for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie)
        free(matrice[pozitie_linie]);
    free(matrice);

    return 0;
}// END main()