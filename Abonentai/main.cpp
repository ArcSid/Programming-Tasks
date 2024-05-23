#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

struct Abonentas{
    string vardas;
    string miestas;
    int minutes;
    float saskaitaFaktura;
};

// traukia duomenis apie abonentus is duom1.txt
void skaitytiAbonentus(vector<Abonentas>& abonentai){
    ifstream data("duom1.txt");
    int abonentuKiekis;
    int telefonoNumeris;
    char ch[21];
    Abonentas laikinasAbonentas;

    data >> abonentuKiekis;
    for(int i = 0; i<abonentuKiekis; i++){
        data.ignore();
        data.get(ch,20);
        laikinasAbonentas.vardas = ch;
        data >> telefonoNumeris;
        data >> laikinasAbonentas.miestas;
        data >> laikinasAbonentas.minutes;
        abonentai.push_back(laikinasAbonentas);
    }
    data.close();
}

// traukia duomenis apie kainorasti is duom2.txt
void skaitytiKainorasti(map<string, float>& miestuKainorasciai){
    ifstream data("duom2.txt");
    int miestuKiekis;
    string miestas;
    float kaina;

    data >> miestuKiekis;
    for(int i = 0; i<miestuKiekis; i++){
        data >> miestas;
        data >> kaina;
        miestuKainorasciai[miestas] = kaina;
    }
    data.close();
}

vector<Abonentas> atrinktiUnikaliusAbonentus(vector<Abonentas> abonentai){
    vector<Abonentas> naujiAbonentai;
    for(int i = 0; i<abonentai.size(); i++){
        bool naujasAbonentas = true;
        for(int j = 0; j<naujiAbonentai.size(); j++){
            if(naujiAbonentai[j].vardas == abonentai[i].vardas){
                naujiAbonentai[j].saskaitaFaktura += abonentai[i].saskaitaFaktura;
                naujasAbonentas = false;
                break;
            }
        }
        if(!naujasAbonentas){
            continue;
        }
        naujiAbonentai.push_back(abonentai[i]);
    }
    return naujiAbonentai;
}

void apskaiciuotiFaktura(vector<Abonentas>& abonentai, map<string, float> miestuKainorasciai){
    for(int i = 0; i<abonentai.size(); i++){
        float kainorastis = miestuKainorasciai[abonentai[i].miestas];
        abonentai[i].saskaitaFaktura = kainorastis*abonentai[i].minutes;
    }
}

void surikiuotiAbeceliskai(vector<Abonentas>& unikalusAbonentai){
    for(int i = 0; i<unikalusAbonentai.size(); i++){
        for(int j = 0; j<unikalusAbonentai.size()-1-i; j++){
            if(unikalusAbonentai[j].vardas[0] > unikalusAbonentai[j+1].vardas[0]){
                swap(unikalusAbonentai[j], unikalusAbonentai[j+1]);
            }
        }
    }
}

float pajamuSumosRadimas(vector<Abonentas> unikalusAbonentai){
    float suma = 0;
    for(int i = 0; i<unikalusAbonentai.size(); i++){
        suma += unikalusAbonentai[i].saskaitaFaktura;
    }
    return suma;
}

void rez(float pajamuSuma, vector<Abonentas> unikalusAbonentai){
    ofstream rez("rez.txt");
    rez << left << setw(20) << "Vardas, Pavardė" << "Mokėti" << endl;
    rez << "-------------------------" << endl;
    for(int i = 0; i<unikalusAbonentai.size(); i++){
        rez << left << setw(22) << unikalusAbonentai[i].vardas << right << unikalusAbonentai[i].saskaitaFaktura << endl;
    }
    rez << "-------------------------" << endl;
    rez << right << setw(22) << "          Pajamos: " << pajamuSuma << endl;
    rez.close();
}

int main(){
    vector<Abonentas> abonentai;
    map<string, float> miestuKainorasciai;

    skaitytiAbonentus(abonentai);
    skaitytiKainorasti(miestuKainorasciai);
    apskaiciuotiFaktura(abonentai, miestuKainorasciai);
    vector<Abonentas> unikalusAbonentai = atrinktiUnikaliusAbonentus(abonentai);
    surikiuotiAbeceliskai(unikalusAbonentai);
    float pajamuSuma = pajamuSumosRadimas(unikalusAbonentai);
    rez(pajamuSuma, unikalusAbonentai);
    return 0;
}
