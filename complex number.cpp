#include <iostream>
#include <math.h>
using namespace std;
class NumarComplex
{
    int re, im;

public:
    NumarComplex();
    NumarComplex(int real, int imaginar);
    int detModul();
    NumarComplex operator+(NumarComplex C2);
    NumarComplex operator*(NumarComplex C2);
    friend ostream &operator<<(ostream &output, const NumarComplex &obj);
    friend istream &operator>>(istream &input, NumarComplex &obj);
    int get_re()
    {
        return re;
    }
    int get_im()
    {
        return im;
    }
    void set_re(int real)
    {
        re = real;
    }
    void set_im(int imaginar)
    {
        imaginar = im;
    }

};

class VectorDeComplecsi:public NumarComplex
{
    int n;
public:
    int *vectorModule;
    NumarComplex *v;
    VectorDeComplecsi(int nr);
    friend istream &operator>>(istream &in, VectorDeComplecsi &A);
    friend ostream &operator<<(ostream &o, VectorDeComplecsi &A);
    void vectModule();
    void sortare();
    NumarComplex suma();
    void produs(VectorDeComplecsi &A, VectorDeComplecsi &B);
    ~VectorDeComplecsi();
};

int main()
{
    NumarComplex A, B;
    int menu, n, m, ok = 1;
    while(ok == 1)
    {
        cout<<" 1. Suma a doua numere complexe \n 2. Determinarea modulului unui numar complex \n 3. Produsul a doua numere complexe \n 4. Determinarea vectorului modulelor \n 5. Vectorul sortat \n 6. Suma elementelor vect. de complecsi \n 7. Produsul scalar a doi vectori de complecsi";
        cout<<"\n Meniu = ";
        cin>>menu;
        switch(menu)
        {
        case 1:
        {
            cout<<"Dati re & im pentru A: ";
            cin>>A;
            cout<<"Dati re & im pentru B: ";
            cin>>B;
            cout<<"Suma este: "<<A+B;
            break;
        }
        case 2:
        {
            cout<<"Dati re & im pentru A: ";
            cin>>A;
            cout<<"Modulul lui A este: "<<A.detModul();
            break;
        }
        case 3:
        {
            cout<<"Dati re & im pentru A: ";
            cin>>A;
            cout<<"Dati re & im pentru B: ";
            cin>>B;
            cout<<"Suma este: "<<A*B;
            break;
        }
        case 4:
        {
            cout<<"Dimensiune vector: ";
            cin>>n;
            VectorDeComplecsi C(n);
            cout<<"Dati re & im pentru fiecare numar complex din vector: ";
            cin>>C;
            C.vectModule();
            for(int i = 0; i < n; i++)
                cout<<C.vectorModule[i]<<" | ";

            break;
        }
        case 5:
        {
            cout<<"Dimensiune vector: ";
            cin>>n;
            VectorDeComplecsi C(n);
            cout<<"Dati re & im pentru fiecare numar complex din vector: ";
            cin>>C;
            C.sortare();
            cout<<C;
            break;
        }
        case 6:
        {
            cout<<"Dimensiune vector: ";
            cin>>n;
            VectorDeComplecsi C(n);
            cout<<"Dati re & im pentru fiecare numar complex din vector: ";
            cin>>C;
            cout<<"Suma este: "<<C.suma();
            break;
        }
        case 7:
        {
            cout<<"Dimensiune vector 1: ";
            cin>>n;
            VectorDeComplecsi C(n);
            cout<<"Dati re & im pentru fiecare numar complex din vector: ";
            cin>>C;
            cout<<"Dimensiune vector 2: ";
            cin>>m;
            VectorDeComplecsi D(n);
            cout<<"Dati re & im pentru fiecare numar complex din vector: ";
            cin>>D;
            VectorDeComplecsi E(n);
            E.produs(C, D);
            cout<<E;
            break;
        }
        }
        cout<<"\nContinui? (1/0)";
        cin>>ok;
    }

    return 0;
}

///////////////////////////////////// funtii

NumarComplex::NumarComplex()
{
    re = 0;
    im = 0;
}
NumarComplex::NumarComplex(int real, int imaginar)
{
    re = real;
    im = imaginar;
}

ostream &operator<<(ostream &output, const NumarComplex &obj)
{
    output<<obj.re<<" + i"<<obj.im;
    return output;
}

istream &operator>>(istream &input, NumarComplex &obj)
{
    input>>obj.re>>obj.im;
    return input;
}

int NumarComplex::detModul()
{
    return sqrt(pow(re, 2) + pow(im, 2));
}

NumarComplex NumarComplex::operator+(NumarComplex C2)
{
    NumarComplex S(0,0);
    S.re = this->re + C2.re;
    S.im = this->im + C2.im;
    return S;
}

NumarComplex NumarComplex::operator*(NumarComplex C2)
{
    NumarComplex P(0,0);
    P.re = (this->re * C2.re) + (this->im * C2.im * -1);
    P.im = (this->re * C2.im) + (this->im * C2.re);
    return P;
}

/////////////////// a doua clasa////////////////

VectorDeComplecsi::VectorDeComplecsi(int nr)
{
    n = nr;
    v = new NumarComplex[nr];
    vectorModule = new int[nr];
}

VectorDeComplecsi::~VectorDeComplecsi()
{
    delete[]v;
    delete[]vectorModule;
}

istream &operator>>(istream &in, VectorDeComplecsi &A)
{

    for(int i = 0; i < A.n; i++)
    {
        in>>A.v[i];
    }
    return in;
}


ostream &operator<<(ostream &o, VectorDeComplecsi &A)
{
    for(int i = 0; i < A.n; i++)
    {
        o<<A.v[i]<<"\n";
    }
    return o;
}

void VectorDeComplecsi::vectModule()
{

    for(int i = 0; i < this->n; i++)
    {
        this->vectorModule[i] = this->v[i].detModul();
    }

}

void VectorDeComplecsi::sortare()
{
    NumarComplex aux;
    for(int i = 1; i < this->n; i++)
        for(int j = 0; j < this->n - i; j++)
        {
            if(this->vectorModule[j] > this->vectorModule[j+1])
            {
                swap(this->v[j], this->v[j+1]);
            }

        }

}

NumarComplex VectorDeComplecsi::suma()
{
    NumarComplex S;
    for(int i = 0; i < this->n; i++)
    {
        S = S + this->v[i];
    }
    return S;
}


void VectorDeComplecsi::produs(VectorDeComplecsi &A, VectorDeComplecsi &B)
{
    for(int i = 0; i < this->n; i++)
        this->v[i] = A.v[i] * B.v[i];
}
