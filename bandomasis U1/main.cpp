#include <set>
#include <iostream>
#include <fstream>
using namespace std;

struct Vaikas
{
    int turimuZaisluSk = 0;
    int zaislai[500];
    int pasikartojanciuSk = 0;
    int pasikartojantys[250];
    int mainomuKiekis = 0;
    int mainomi[250];
};

void skaitymas(Vaikas &tomas, Vaikas &aiste)
{
    ifstream data("U1duom.txt");
    data >> tomas.turimuZaisluSk >> aiste.turimuZaisluSk;
    for (int i = 0; i < tomas.turimuZaisluSk; i++)
    {
        data >> tomas.zaislai[i];
    }
    for (int i = 0; i < aiste.turimuZaisluSk; i++)
    {
        data >> aiste.zaislai[i];
    }
    data.close();
}

void atrinktiPasikartojancius(Vaikas &vaikas)
{
    set<int> unikalusZaislai;
    for (int i = 0; i < vaikas.turimuZaisluSk; i++)
    {
        if (unikalusZaislai.find(vaikas.zaislai[i]) != unikalusZaislai.end())
        {
            vaikas.pasikartojantys[vaikas.pasikartojanciuSk] = vaikas.zaislai[i];
            vaikas.pasikartojanciuSk++;
        }
        unikalusZaislai.insert(vaikas.zaislai[i]);
    }
}

void atrinktiMainomus(Vaikas &vaikas1, Vaikas vaikas2)
{
    for (int i = 0; i < vaikas1.pasikartojanciuSk; i++)
    {
        bool kitasNeturi = true;
        for (int j = 0; j < vaikas2.turimuZaisluSk; j++)
        {
            if (vaikas1.pasikartojantys[i] == vaikas2.zaislai[j])
            {
                kitasNeturi = false;
                break;
            }
        }
        if (kitasNeturi)
        {
            vaikas1.mainomi[vaikas1.mainomuKiekis] = vaikas1.pasikartojantys[i];
            vaikas1.mainomuKiekis++;
        }
    }
}

void atrinktiKolekcija(Vaikas tomas, Vaikas aiste, set<int> &bendraKolekcija)
{
    for (int i = 0; i < tomas.turimuZaisluSk; i++)
    {
        bendraKolekcija.insert(tomas.zaislai[i]);
    }
    for (int i = 0; i < aiste.turimuZaisluSk; i++)
    {
        bendraKolekcija.insert(aiste.zaislai[i]);
    }
}

void rez(Vaikas tomas, Vaikas aiste, set<int> bendraKolekcija)
{
    ofstream rez("U1rez.txt");
    if (tomas.mainomuKiekis == 0)
    {
        rez << 0 << endl;
    }
    else
    {
        for (int i = 0; i < tomas.mainomuKiekis; i++)
        {
            rez << tomas.mainomi[i] << " ";
        }
        rez << endl;
    }

    if (aiste.mainomuKiekis == 0)
    {
        rez << 0 << endl;
    }
    else
    {
        for (int i = 0; i < aiste.mainomuKiekis; i++)
        {
            rez << aiste.mainomi[i] << " ";
        }
        rez << endl;
    }

    for (int i : bendraKolekcija)
    {
        rez << i << " ";
    }
    rez << endl;
    rez.close();
}

int main()
{
    Vaikas tomas;
    Vaikas aiste;
    set<int> bendraKolekcija;

    skaitymas(tomas, aiste);

    atrinktiPasikartojancius(tomas);
    atrinktiPasikartojancius(aiste);

    atrinktiMainomus(tomas, aiste);
    atrinktiMainomus(aiste, tomas);

    atrinktiKolekcija(tomas, aiste, bendraKolekcija);

    rez(tomas, aiste, bendraKolekcija);

    return 0;
}