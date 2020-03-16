#include <iostream>
using namespace std;

class Arbore
{
    int N;
public:
    Arbore(int nrNoduri);
    int getN();
    virtual ~Arbore() = 0;
};

class Nod
{
public:
    int data;
    Nod *left,*right;
    Nod (int x);
    virtual ~Nod() {}
};

class ABC: public Arbore, public Nod
{
public:
    ABC (int nrNoduri, int radacina):Arbore(nrNoduri), Nod(radacina){root = new Nod(radacina);}
    friend ostream &operator<<(ostream &o, ABC &ob);
    friend istream &operator>>(istream &i, ABC &ob);
    bool cauta(int x);
    void creaza();
    ~ABC();

protected:
    Nod* root;
    bool cauta(int x, Nod* curr);
    bool add(int item, Nod* curr);
};
int main()
{
    int nrNoduri, radacina;
    cout<<"Numar de noduri & radacina: ";
    cin>>nrNoduri>>radacina;

    ABC A(nrNoduri, radacina);
    cin>>A;
    cout<<A;
}
//////////////////////////////////////////
//             Clasa Arbore
Arbore::~Arbore(){}
Arbore::Arbore(int nrNoduri){ N = nrNoduri;}
int Arbore::getN(){return N;}


//////////////////////////////////////////
//             Clasa Nod
Nod::Nod (int x){data = x; left = right = NULL;}


//////////////////////////////////////////
//             Clasa ABC
istream &operator>>(istream &i, ABC &ob)
{
    ob.creaza();
    return i;
}

ostream &operator<<(ostream &o, ABC &ob)
{
    int y;
    cout<<"Caut: ";
    cin>>y;
    ob.cauta(y);
    return o;
}

bool ABC::cauta(int x){return cauta(x, root);}
bool ABC::cauta(int x, Nod *root)
{
    if (root == NULL)
    {
        cout<<"Nu";
        return false;
    }
    else if(root->data == x)
    {
        cout<<"Da";
        return true;
    }

    if(x > root->data)
        return cauta(x, root->right);

    return cauta(x, root->left);
}
void ABC::creaza()
{
    int x;
    for(int i = 1; i < getN(); i++)
    {
        cout<<"Nod = ";
        cin>>x;
        add(x, root);
    }
}

bool ABC :: add(int item, Nod *currNod)
{
    if (root == NULL)
    {
        root = new Nod(item);
        return true;
    }
    else if (item < currNod->data)
    {
        if (currNod->left == NULL)
        {
            currNod->left = new Nod(item);
            return true;
        }
        else
        {
            return add(item, currNod->left);
        }
    }
    else if (item > currNod->data)
    {
        if (currNod->right == NULL)
        {
            currNod->right = new Nod(item);
            return true;
        }
        else
        {
            return add(item, currNod->right);
        }
    }
    else
        return false;
}
ABC::~ABC(){delete root;}
