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


int verificareCelulaT0(int** matrice, int linie, int coloana)
{
    if (matrice[linie][coloana] == 1 ||
        matrice[linie][coloana] == 3)
    {
        return 1;
    }
    return 0;
}

int verificacaz1T(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, short** matrice)
{
    if (pozitie_coloana < 0 &&
        verificareCelulaT0(matrice,0,numar_coloane-1) == 1)
    {
        return 1;
    }

    if (pozitie_coloana > (numar_coloane - 1) &&
       verificareCelulaT0(matrice,0,0) == 1)
    {
        return 1;
    }

    return verificacelulaP(pozitie_linie, pozitie_coloana, numar_linii, numar_coloane, matrice);
}

int verificacelulaP(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, short** matrice)
{
    if (pozitie_linie < 0 ||
        pozitie_coloana < 0 ||
        pozitie_linie >= numar_linii ||
        pozitie_coloana >= numar_coloane)
    {
        return 0;
    }

    return verificareCelulaT0(matrice, pozitie_linie, pozitie_coloana);
}   //END verificacelulaP()


int verificacelulaT(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, short** matrice)
{
    if (pozitie_linie < 0 && pozitie_coloana < 0)
    {
        return verificareCelulaT0(matrice, numar_linii - 1, numar_coloane - 1);
    }

    if (pozitie_linie >= numar_linii && pozitie_coloana >= numar_coloane)
    {
        return verificareCelulaT0(matrice, 0, 0);
    }

    if (pozitie_linie < 0 && pozitie_coloana >= numar_coloane)
    {
        return verificareCelulaT0(matrice, numar_linii - 1, 0);
    }

    if (pozitie_linie >= numar_linii && pozitie_coloana < 0)
    {
        return verificareCelulaT0(matrice, 0, numar_coloane - 1);
    }

    if (pozitie_linie < 0)
    {
        return verificareCelulaT0(matrice, numar_linii - 1, pozitie_coloana);
    }


    if (pozitie_linie >= numar_linii)
    {
        return verificareCelulaT0(matrice, 0, pozitie_coloana);
    }

    if (pozitie_coloana < 0)
    {
        return verificareCelulaT0(matrice, pozitie_linie, numar_coloane - 1);
    }


    if (pozitie_coloana >= numar_coloane)
    {
        return verificareCelulaT0(matrice, pozitie_linie, 0);
    }

    return verificareCelulaT0(matrice, pozitie_linie, pozitie_coloana);
}   //END verificacelulaT()


int NumberOfLifes(int pozitie_linie, int pozitie_coloana, int numar_linii, int numar_coloane, short matrice[1000][1000])
{

    int life = 0;
    life += verificacelulaP(pozitie_linie - 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie - 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie - 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie + 1, pozitie_coloana - 1, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie + 1, pozitie_coloana, numar_linii, numar_coloane, matrice);
    life += verificacelulaP(pozitie_linie + 1, pozitie_coloana + 1, numar_linii, numar_coloane, matrice);
    return life;
}

void EvolutiaCelulelor(short** matrice, int numar_linii, int numar_coloane, int* populatie , int* maximpopulatie)
{
    if (populatie == NULL || maximpopulatie == NULL)
    {
        return;
    }

    int varPopulatie = *populatie;
    int maxVarPopulatie = *maximpopulatie;

    for (int pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
        for (int pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
        {
            // "Evolutia celulor"
            switch (matrice[pozitie_linie][pozitie_coloana])
            {
            case 2:
                matrice[pozitie_linie][pozitie_coloana] = 1;
            case 1:
                varPopulatie++;
                break;
            case 3:
                matrice[pozitie_linie][pozitie_coloana] = 0;
                break;
            default:
                break;
            }
            // END  "Evolutia celulor"
        }


    if (varPopulatie > maxVarPopulatie)
    {
        maxVarPopulatie = populatie;
    }

    *populatie = varPopulatie;
    *maximpopulatie = maxVarPopulatie;
}

void KillOverPopulatedCells(short** matrice, int numar_linii, int numar_coloane)
{
    for (int pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
        for (int pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
        {
            if (matrice[pozitie_linie][pozitie_coloana] == 3)
            {
                matrice[pozitie_linie][pozitie_coloana] = 0;
            }
        }
}

int main()
{
    char Tip_plan[1]; // tipul de problema/afisare ; Adica daca se face reprezentarea tip plan sau toroidala
    int numar_linii, numar_coloane, Etape, maximpopulatie = 0;// declararea variabilelor cerintei numar linii,generatiile de simulari , numar biti, matricea , maxim populatie
    int pozitie_linie, pozitie_coloana, populatie = 0;
    short int life = 0; // variabile auxiliare pentru parcurgerea in matrice , numar populatie , numar vecini
    short int matrice[1000][1000];
    // short int numar_linii:6, numar_coloane:6;
    // struct _BOOL : 1 , _BOOL:1 pentru matrice;


    //  BEGIN citeste_variabile
    scanf("%c", &Tip_plan);
    scanf("%d %d %d", &numar_linii, &numar_coloane, &Etape);
    for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
        for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
        {
            scanf("%d", &matrice[pozitie_linie][pozitie_coloana]);
        }
    // END citeste_variabile

    // Calculare Populatia initiala
    for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
        for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
            if (matrice[pozitie_linie][pozitie_coloana] == 1)
            {
                maximpopulatie++;
            }
    // End Calculare Populatia initiala
    if (Tip_plan[0] == 'P' || Tip_plan[0] == 'p')
    {
        printf("\n Reprezentare planara! \n");
        while (Etape > 0)
        {
            //Begin verificare_celula
            for (pozitie_linie = 0; pozitie_linie < numar_linii; pozitie_linie++)
                for (pozitie_coloana = 0; pozitie_coloana < numar_coloane; pozitie_coloana++)
                {
                    //Aflarea vecinilor
                    life = NumberOfLifes(pozitie_linie, pozitie_coloana, numar_linii, numar_coloane, matrice);
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
            EvolutiaCelulelor(matrice, numar_linii, numar_coloane, &populatie, &maximpopulatie);
            //Modificarea gradului maxim de populatie

            Etape--; //Scaderea numarului de evolutii / K / Etape (cerute)
        }
    }
    else if (Tip_plan[0] == 'T' || Tip_plan[0] == 't')
    {
        printf("\n Reprezentare Toroidala! \n");
        if (numar_coloane == 1 && numar_linii == 1 && Etape > 0)
        {
            matrice[0][0];
        }
        else if (numar_coloane == 1 && numar_linii == 2 && Etape > 0)
        {
            matrice[0][0] = matrice[1][0] = 0;
        }
        else if (numar_coloane == 2 && numar_linii == 1 && Etape > 0)
        {
            matrice[0][0] = matrice[0][1] = 0;
        }
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
                    {
                        matrice[pozitie_linie][0] = 3;
                    }
                }
                KillOverPopulatedCells(matrice, numar_linii, numar_coloane);
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
                    {
                        matrice[0][pozitie_coloana] = 3;
                    }
                }
                KillOverPopulatedCells(matrice, numar_linii, numar_coloane);
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
                        life = NumberOfLifes(pozitie_linie, pozitie_coloana, numar_linii, numar_coloane, matrice);
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
                EvolutiaCelulelor(matrice, numar_linii, numar_coloane, &populatie, &maximpopulatie);
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
                EvolutiaCelulelor(matrice, numar_linii, numar_coloane, &populatie, &maximpopulatie);
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
                EvolutiaCelulelor(matrice, numar_linii, numar_coloane, &populatie, &maximpopulatie);
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

    return 0;
}   // END main()
