#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <algorithm>

/*
1           // cardinal stari finale
e           // multimea stari finale
2           // cardinal alfabet
0 1         // alfabet
6           // numar tranzitii
*/
using namespace std;
int strlen(string s);

class automat
{
    int numarT;         // numar tranzitii
    int f;              // cardinal stari finale
    char *F;           // multimea starilor finale
    int cardAlfabet;
    char* Alfabet;

    struct tranzitie
    {
        string a;  // plec de aici
        char c;     // cu acest caracter
        string b;  // si ajung aici
    }*T;

    vector <tranzitie> nT;


public:
    automat();
    void genereaza();
    void creaza(string s, int &ir);
    int verific(string s, int &ir);
    void concateneaza(string &s1, string s2);
    int stareFinala(char c, string s);
    ~automat();

};

int main()
{
    automat A;
    A.genereaza();
    return 0;
}

///////////////////////////////////// F U N C T I I /////////////////////////////////////////

automat::automat()
{
    ifstream fin("automat");
    fin>>f;
    F = new char[f];
    for(int i = 0; i < f; i++)
        fin>>F[i];

    fin>>cardAlfabet;
    Alfabet = new char[cardAlfabet];
    for(int i = 0; i < cardAlfabet; i++)
        fin>>Alfabet[i];

    fin>>numarT;
    T = new tranzitie[numarT];
    for(int i = 0; i < numarT; i++)
    {
        fin>>T[i].a;
        fin>>T[i].c;
        fin>>T[i].b;
    }
    fin.close();
}

int automat::stareFinala(char c, string s)
{
    int lungime = strlen(s);
    for(int i = 0; i < lungime; i++)
        if(c == s[i])
            return 1;
    return 0;
}
void automat::genereaza()
{
    int ir = 0;
    string temp = T[0].a;
    while(temp == T[ir].a)
        nT.push_back(T[ir++]);

    for(int i = 0; i < ir; i++)
        if(verific(nT[i].b, ir) == 0)
            creaza(nT[i].b, ir);

    ofstream fout("DFA");
    for(int i = 0; i < ir; i++)
        fout<<nT[i].a<<" "<<nT[i].c<<" "<<nT[i].b<<"\n";

    string ver = "";
    fout<<"Stari finale: \n";
    for(int i = 0; i < nT.size(); i++)
    {
        for(int j = 0; j < f; j++)
        {
            if(stareFinala(F[j], nT[i].a) == 1)
                if(ver != nT[i].a)
                {
                    ver = nT[i].a;
                    fout<<nT[i].a<<"\n";
                }
;

        }
    }
    fout.close();

}

int automat::verific(string s, int &ir)
{
    int j = 0;
    for(int i = 0; i < ir; ++i)
        if(s == nT[i].a)
            j = 1;
    if(j > 0)
        return 1;
    else
        return 0;

}


void automat::concateneaza(string &s1, string s2)
{
    int k;
    if(s1 != "")
    for(int i = 0; i < strlen(s2); i++)
    {
        k = 0;
        for(int j = 0; j < strlen(s1); j++)
        {
            if(s2[i] == s1[j])
                k = 1;
        }
        if(k != 1)
            s1 = s1 + s2[i];

    }
    else
        s1 = s2;
    sort(s1.begin(), s1.end());
}

void automat::creaza(string s, int &ir)
{

    int lungime = strlen(s);
    tranzitie B;
    string temp, concat;
    for(int y = 0; y < cardAlfabet; y++)
    {
        concat = "";
        for(int i = 0; i < lungime; i++) // pentru fiecare litera
        {
            temp = s[i];
            for(int j = 0; j < numarT; j++)
            {
                if(T[j].a == temp && T[j].c == Alfabet[y])
                {
                    concateneaza(concat, T[j].b);
                    j = numarT;
                }
            }
        }
        if(concat != "")
        {
            B.a = s;
            B.c = Alfabet[y];
            B.b = concat;
            nT.push_back(B);
            ir++;

        }
    }
}



int strlen(string s)
{
    int len = 0;

    while (s[len])
        len++;

    return len;
}


automat::~automat()
{
    delete[]T;
}


