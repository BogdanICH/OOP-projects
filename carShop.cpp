#include <iostream>
#include <vector>
using namespace std;

class Automobil
{
    double lungime;
    string formaModel;
    bool stareActuala;
    int aniVechime;
    int tip;
    double pret;
public:
    void setLungime(double l){lungime = l;}
    double getLungime(){return lungime;}
    void setForma(string forma){formaModel = forma;}
    string getForma(){return formaModel;}
    void setStare(bool stare){stareActuala = stare;}
    bool getStare(){return stareActuala;}
    void setAni(int ani){aniVechime = ani;}
    int getAni(){return aniVechime;}
    void setTip(int t){tip = t;}
    int getTip(){return tip;}
    void setPret(double euro){pret = euro;}
    double getPret(){return pret;}
};

class Mini: public Automobil
{
public:
    Mini(double l, string model, bool sta, int ani, int tipp, double prett);
    Mini();
};

class Mica: public Automobil
{
public:
    Mica();
    Mica(double l, string model, bool sta, int ani, int tipp, double prett);
};

class Compacta: public Automobil
{

public:
    Compacta();
    Compacta(double l, string model, bool sta, int ani, int tipp, double prett);
};

class Monovolum: public Automobil
{
public:
    Monovolum();
    Monovolum(double l, string model, bool sta, int ani, int tipp, double prett);
};
// template clasa VANZARE
template <class T>
class Vanzare
{
    static int inStoc;
    static int masiniVandute;
    Automobil *stoc[100], *vandute[100];
public:
    void add();
    Vanzare operator-=(Vanzare& ob);
    void findd(int tip, int luna)
    {
        int ok = 0;
        for (int i = 0; i < inStoc; i++)
            if (stoc[i]->getTip() == tip)
            {
                ok = 1;
                if (luna == 1 || luna == 2 || luna == 3)
                {
                if (tip == 4 && stoc[i]->getStare() == false)
                {
                    cout<<"Felicitari! Ai achizitionat masina tip "<<stoc[i]->getTip()<<" la pretul de "<<stoc[i]->getPret() -  stoc[i]->getPret()/(10+stoc[i]->getAni())<<" euro.\n Pretul contine discount de vechime +"<<stoc[i]->getAni()<<" %\n";
                    cout<<"Informatii: \n - "<<stoc[i]->getAni()<<" ani vechime\n - Model: "<<stoc[i]->getForma()<<" \n - Lungime: "<<stoc[i]->getLungime()<<"m \n - Stare: "<<stoc[i]->getStare()<<" \n";

                } else {
                    cout<<"Felicitari! Ai achizitionat masina tip "<<stoc[i]->getTip()<<" la pretul de "<<stoc[i]->getPret() -  stoc[i]->getPret()/10<<" euro.\n";
                    cout<<"Informatii: \n - "<<stoc[i]->getAni()<<" ani vechime\n - Model: "<<stoc[i]->getForma()<<" \n - Lungime: "<<stoc[i]->getLungime()<<"m \n - Stare: "<<stoc[i]->getStare()<<" \n";
                }
                } else
                {
                    if (tip == 4 && stoc[i]->getStare() == false)
                    {
                        cout<<"Felicitari! Ai achizitionat masina tip "<<stoc[i]->getTip()<<" la pretul de "<<stoc[i]->getPret() -  stoc[i]->getPret()/stoc[i]->getAni()<<" euro.\n Pretul contine discount de vechime +"<<stoc[i]->getAni()<<" %\n";
                        cout<<"Informatii: \n - "<<stoc[i]->getAni()<<" ani vechime\n - Model: "<<stoc[i]->getForma()<<" \n - Lungime: "<<stoc[i]->getLungime()<<"m \n - Stare: "<<stoc[i]->getStare()<<" \n";

                    } else {
                        cout<<"Felicitari! Ai achizitionat masina tip "<<stoc[i]->getTip()<<" la pretul de "<<stoc[i]->getPret()<<" euro.\n";
                        cout<< "Informatii: \n - "<<stoc[i]->getAni()<<" ani vechime\n - Model: "<<stoc[i]->getForma()<<" \n - Lungime: "<<stoc[i]->getLungime()<<"m \n - Stare: "<<stoc[i]->getStare()<<" \n";
                    }
                }
                switch(tip)
                {
                    case 1: { vandute[masiniVandute] = new Mini(stoc[i]->getLungime(), stoc[i]->getForma(), stoc[i]->getStare(), stoc[i]->getAni(), stoc[i]->getTip(), stoc[i]->getPret()); break;}
                    case 2: { stoc[masiniVandute] = new Mica(stoc[i]->getLungime(), stoc[i]->getForma(), stoc[i]->getStare(), stoc[i]->getAni(), stoc[i]->getTip(), stoc[i]->getPret()); break;}
                    case 3: { vandute[masiniVandute] = new Compacta(stoc[i]->getLungime(), stoc[i]->getForma(), stoc[i]->getStare(), stoc[i]->getAni(), stoc[i]->getTip(), stoc[i]->getPret()); break;}
                    case 4: {vandute[masiniVandute] = new Monovolum(stoc[i]->getLungime(), stoc[i]->getForma(), stoc[i]->getStare(), stoc[i]->getAni(), stoc[i]->getTip(), stoc[i]->getPret());}
                }

                switch(stoc[inStoc-1]->getTip())
                {
                    case 1: { stoc[i] = new Mini(stoc[inStoc-1]->getLungime(), stoc[inStoc-1]->getForma(), stoc[inStoc-1]->getStare(), stoc[inStoc-1]->getAni(), stoc[inStoc-1]->getTip(), stoc[inStoc-1]->getPret()); break;}
                    case 2: { stoc[i] = new Mica(stoc[inStoc-1]->getLungime(), stoc[inStoc-1]->getForma(), stoc[inStoc-1]->getStare(), stoc[inStoc-1]->getAni(), stoc[inStoc-1]->getTip(), stoc[inStoc-1]->getPret()); break;}
                    case 3: { stoc[i] = new Compacta(stoc[inStoc-1]->getLungime(), stoc[inStoc-1]->getForma(), stoc[inStoc-1]->getStare(), stoc[inStoc-1]->getAni(), stoc[inStoc-1]->getTip(), stoc[inStoc-1]->getPret()); break;}
                    case 4: {stoc[i] = new Monovolum(stoc[inStoc-1]->getLungime(), stoc[inStoc-1]->getForma(), stoc[inStoc-1]->getStare(), stoc[inStoc-1]->getAni(), stoc[inStoc-1]->getTip(), stoc[inStoc-1]->getPret());}
                }
                i = inStoc;
                masiniVandute++;
            }

        if (ok == 0)
            cout << "Nu avem masina pe stoc!";
    }

    void afisare()
    {
        cout << "Masini in stoc: \n";
        for (int i = 0; i < inStoc; i++)
            cout << " - " << stoc[i]->getForma() << "\n";

        cout << "Masini vandute: \n";
        for (int i = 0; i < masiniVandute; i++)
            cout << " - " << vandute[i]->getForma() << "\n";
    }
};
template<class T>int Vanzare<T>::inStoc = 0;
template<class T>int Vanzare<T>::masiniVandute = 0;

template <>
class Vanzare<unsigned>{

public:

};

// ------------------------------- M    A   I   N ---------------------------------------
int main()
{
    int menu, ok = 1;
    Vanzare <Automobil> a;
    while (ok == 1)
    {
        cout << "Meniu:\n 1. Adauga masina in stoc \n 2. Cumpara masina (Mini, Mica, Compacta) \n 3. Afisare \n Alege: ";
        cin >> menu;
        switch(menu)
        {
            case 1: { a.add(); break;}
            case 2: { a-=a; break;}
            case 3: { a.afisare();}
        }
        cout << "\n Continui? (1/0)";
        cin >> menu;
    }
    Vanzare <unsigned> b;
    return 0;
}

//---------------- Mini  --------------------
    Mini::Mini()
    {
        double lu;
        cout << "Introduceti lungimea: ";
        cin >> lu;
        while (lu < 2 || lu >= 4)
        {
            try{throw 1;}
            catch(int x){
                cout << "Lungimea trebuie sa fie intre 2 - 3.99 \n";
                cout << "Introduceti din nou: ";
                cin >> lu;}
        }
        double euro;
        cout << "Pret: ";
        cin >> euro;
        while (euro < 1 || euro > 1000000)
        {
            try{throw 1;}
            catch(int x)
            {
                cout << "Pretul trebuie sa fie intre 1 - 1000000 euro \n Introduceti din nou: ";
                cin >> euro;
            }
        }
        setPret(euro);
        setLungime(lu);
        setForma("Mini");
        setStare(true);
        setAni(0);
        setTip(1);
    }
    Mini::Mini(double l, string model, bool sta, int ani, int tipp, double prett)
    {
        setLungime(l);
        setForma(model);
        setStare(sta);
        setAni(ani);
        setTip(tipp);
        setPret(prett);
    }

//---------------- Mica  --------------------

    Mica::Mica()
    {
        double lu;
        cout << "Introduceti lungimea: ";
        cin> > lu;
        while (lu < 3.85 || lu > 4.1)
        {
            try{throw 1;}
            catch(int x){
                cout<<"Lungimea trebuie sa fie intre 3.85 - 4.1 \n";
                cout<<"Introduceti din nou: ";
                cin>>lu;}
        }
        double euro;
        cout << "Pret: ";
        cin >> euro;
        while (euro < 1 || euro > 1000000)
        {
            try{throw 1;}
            catch(int x)
            {
                cout << "Pretul trebuie sa fie intre 1 - 1000000 euro \n Introduceti din nou: ";
                cin >> euro;
            }
        }
        setPret(euro);
        setLungime(lu);
        setForma("Mica");
        setStare(true);
        setAni(0);
        setTip(2);
    }
 Mica::Mica(double l, string model, bool sta, int ani, int tipp, double prett)
    {
        setLungime(l);
        setForma(model);
        setStare(sta);
        setAni(ani);
        setTip(tipp);
        setPret(prett);
    }
//---------------- Compacta  --------------------
Compacta::Compacta()
    {
        double lu;
        cout << "Introduceti lungimea: ";
        cin >> lu;
        while (lu < 4.2 || lu > 4.5)
        {
            try{throw 1;}
            catch(int x){
                cout << "Lungimea trebuie sa fie intre 4.2 - 4.5 \n";
                cout << "Introduceti din nou: ";
                cin >> lu;}
        }
        setLungime(lu);
        int forma;
        cout << "Alege forma model: \n 1 - Hatchback \n 2 - Combi \n 3 - Sedan \n Optiune: ";
        cin >> forma;

        while (forma!= 1 && forma!= 2 && forma != 3 )
        {
            try{throw 1;}
            catch(int x){
                cout << "Forma modelului trebuie sa fie una din cele trei (1, 2, 3)";
                cout << "Introduceti din nou: ";
                cin >> forma;}
        }
        switch(forma)
        {
            case 1: { setForma("Hatchback"); break;}
            case 2: { setForma("Combi"); break;}
            case 3: { setForma("Sedan "); break;}
        }
        setStare(true);
        double euro;
        cout << "Pret: ";
        cin >> euro;
        while (euro < 1 || euro > 1000000)
        {
            try{throw 1;}
            catch(int x)
            {
                cout << "Pretul trebuie sa fie intre 1 - 1000000 euro \n Introduceti din nou: ";
                cin >> euro;
            }
        }
        setPret(euro);
        setAni(0);
        setTip(3);
    }
     Compacta::Compacta(double l, string model, bool sta, int ani, int tipp, double prett)
    {
        setLungime(l);
        setForma(model);
        setStare(sta);
        setAni(ani);
        setTip(tipp);
        setPret(prett);
    }

//---------------- Monovolum  --------------------

Monovolum::Monovolum()
{
    int stare;
    cout << "Starea automobil: \n 1 - nou \n 2- second hand \n Optiune: ";
    cin >> stare;
    while (stare != 1 && stare != 2)
    {
        try{throw 1;}
        catch(int x)
        {
            cout << "Starea automobilului trebuie sa fie NOU sau SECOND HAND \n Introduceti din nou: ";
            cin >> stare;
        }
    }
    switch(stare)
    {
        case 1: { setStare(true); setAni(0); break;}
        case 2: { setStare(false);
        int ani;
        cout << "Vechime masina(ani): ";
        cin >> ani;
        while (ani<1 || ani>200)
        {
            try{throw 1;}
            catch(int x)
            {
                cout << "Vechimea masinii trebuie sa fie intre 1 si 200 \n Introduceti din nou: ";
                cin >> ani;
            }
        }
        setAni(ani);

        }
    }
        double euro;
        cout << "Pret: ";
        cin >> euro;
        while (euro < 1 || euro > 1000000)
        {
            try{throw 1;}
            catch(int x)
            {
                cout << "Pretul trebuie sa fie intre 1 - 1000000 euro \n Introduceti din nou: ";
                cin >> euro;
            }
        }
        setPret(euro);
    setLungime(6.00);
    setForma("Monovolum");
    setTip(4);
}

 Monovolum::Monovolum(double l, string model, bool sta, int ani, int tipp, double prett)
    {
        setLungime(l);
        setForma(model);
        setStare(sta);
        setAni(ani);
        setTip(tipp);
        setPret(prett);
    }
// -------------------- template ---------------------
template <class T>
void Vanzare<T>::add()
{
        int ad, optiune;
        cout<<"Cate masini adaugi? = ";
        cin>>ad;
        for (int i = inStoc; i < (inStoc + ad); i++)
        {
            cout<<"Ce adaugati? \n 1. Mini \n 2. Mica \n 3. Compacta \n 4. Monovolum \n Optiune: ";
            cin>>optiune;
            while (optiune != 1 && optiune != 2 && optiune != 3 && optiune != 4)
            {
                try{throw 1;}
                catch(int x)
                {
                    cout<<"Trebuie sa alegeti una din optiunile de mai sus. (1/2/3) \n Introduceti din nou: ";
                    cin>>optiune;
                }
            }
            switch(optiune)
            {
                case 1: { stoc[i] = new Mini(); break;}
                case 2: { stoc[i] = new Mica(); break;}
                case 3: { stoc[i] = new Compacta(); break;}
                case 4: { stoc[i] = new Monovolum();}
            }
        }
        inStoc = inStoc + ad;
}

template <class T>
Vanzare<T> Vanzare<T>::operator-=(Vanzare& ob)
{
    int luna, cumpar;
    double pret;
    string raspuns;
    cout << "Vrei sa cumperi o masina? ";
    cin >> raspuns;
    while (raspuns != "da" && raspuns != "nu")
    {
        cout << "Poti raspunde doar cu da sau nu \n Introduceti din nou: ";
        cin >> raspuns;
    }
    if (raspuns == "da")
    {
        cout << "Luna actuala: \n 1. Iunie \n 2. Iulie \n 3. August \n 4. Alta \n Optiune: ";
        cin >> luna;
        cout << "Ce tip de masina vrei sa cumperi? \n 1. Mini \n 2. Mica \n 3. Compacta \n 4. Monovolum \n";
        cin >> cumpar;
        if(luna == 1 || luna == 2 || luna == 3)
        {
            cout << "Pretul masinii va fi redus cu 10% deoarece cumperi intr-o luna de vara. \n";
        }
        findd(cumpar, luna);
        inStoc--;
    } else {cout<<"Ne pare rau! Te asteptam alta data.";}

     return *this;
}
