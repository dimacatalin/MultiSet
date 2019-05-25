#include <iostream>
#include <stdlib.h>
using namespace std;

template <class T>

class Multiset
{
private:

    int nr_el;//numaruld e elemente din multiset
    T *array;//un vector prin care o sa reprezint multisetul

public:

    Multiset()//constructorul null
    {
        array=NULL;
        nr_el=0;
        //adaug acesti 2 "0" in vector pentru ca am intampinat o problema cu multiseturi mai mari de 2 elemente. Imi inlocuia primele 2 elemente cu adresele lor
        add_el(0);
        add_el(0);
    }

    Multiset(const Multiset &a)//construcotrul de copiere
    {
        nr_el=a.nr_el;
        array=a.array;
    }

    ~Multiset()//destructor
    {
        delete array;
    }

    friend ostream& operator<<(ostream& out,const Multiset &a)//supraincarcarea operatorului de afisare
    {
        if(a.nr_el==2)//adica daca raman cele 2 zerouri de la construcotr
            cout<<"Multiset gol."<<endl;
        else//daca nu este gol
        {
            int i;
            for(i=2; i<a.nr_el; i++)//afisez de la pozitia 2 la ultima pozitie
                out<<a.array[i]<<" ";
            out<<endl;
            return out;
        }

    }

    void operator=(const Multiset &a)//supraincarcarea operatorului =
    {
        int i;
        nr_el=a.nr_el;
        array=(T *) malloc(nr_el*sizeof(T));
        for(i=0; i<nr_el; i++)
            array[i]=a.array[i];
    }

    int nr_aparitii(T x)//returneaza numarul de aparitii al parametrului
    {
        int i,nr=0;
        for(i=0;i<nr_el;i++)
            if(array[i]==x)
                nr++;
        return nr;
    }

    void apare(T x)
    {
        int i;
        for(i=0;i<nr_el;i++)
            if(array[i]==x)
            {
                cout<<x<<" apare in multiset."<<endl;
                return;
            }
        cout<<x<<" nu pare in multiset."<<endl;
    }

    void delete_all(T x)//sterge toate aparitiile parametrului
    {
        while(nr_aparitii(x)!=0)
            delete_el(x);
    }

    int nr_el_distincte()//calculeaza nuamrul de elemente distincte
    {
        int i,j,n=0,ok;
        //declar un vector de maxim numarul de elemente din multiset pentru a stoca aparitia numerelor
        T *a;
        a=(T *) malloc(nr_el*sizeof(T));

        for(i=0;i<nr_el;i++)
        {
            ok=1;
            for(j=0;j<n;j++)
                if(array[i]==a[j])
                    ok=0;
            if(ok==1)//daca numarul curent din multiset nu apare deja in vector il introducem
            {
                a[n]=array[i];
                n++;
            }
        }
        free(a);//eliberam memoria alocata pentru vector
        return n-2;//returnez n-2 pentru ca a numarat si cele 2 adrese de la zerourile introduse in constructor
    }

    void add_el(T x)
    {
        int i;
        T *new_array;
        new_array=(T *) malloc((nr_el+1)*sizeof(T));
        for(i=0;i<nr_el;i++)
            new_array[i]=array[i];
        new_array[nr_el]=x;
        free(array);
        array=new_array;
        nr_el++;
        free(new_array);
    }

    void delete_el(T x)
    {
        int i,poz,ok=0;
        T *new_array;
        new_array=(T *) malloc((nr_el)*sizeof(T));
        for(i=0;i<nr_el;i++)
            if(array[i]==x)
            {
                poz=i;
                ok=1;
            }
        if(ok==0)
        {
            cout<<"Elementul nu este prezent in multiset."<<endl;
            return;
        }
        for(i=poz;i<nr_el;i++)
            array[i]=array[i+1];
        for(i=0;i<nr_el-1;i++)
            new_array[i]=array[i];
        free(array);
        array=new_array;
        nr_el--;
        free(new_array);
    }
};

int main()
{
    Multiset<int>x;
    cout<<x<<endl;
    x.add_el(1);
    x.add_el(2);
    x.add_el(3);
    x.add_el(4);
    x.add_el(5);
    x.add_el(6);
    x.add_el(7);
    x.add_el(7);
    x.add_el(8);
    x.add_el(9);
    x.add_el(10);
    x.add_el(11);
    cout<<x<<endl;
    x.delete_el(3);
    x.delete_el(4);
    cout<<"Dupa stergerea din multiset a nuemrelor 3 si 4:"<<x<<endl;
    x.apare(6);
    cout<<endl;
    cout<<"Nuamrul de aparitii a nuamrului 7: "<<x.nr_aparitii(7)<<endl<<endl;
    x.delete_all(7);
    cout<<"Multisetul dupa stergerea tuturor aparitiilor lui 7: "<<x<<endl;
    x.add_el(11);
    cout<<"Numarul de elemente distincte in multiset este "<<x.nr_el_distincte()<<endl<<endl;

    cout<<x;
}
