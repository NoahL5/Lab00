#include <iostream>
#include <string>
#include <cstring>
#include <forward_list>
#include <map>
#include <cmath>
#include <ctype.h>

using namespace std;

//DECLARARE FUNCTII
int Disjunctie(int el1, int el2);
int Conjunctie(int el1, int el2);
int Negatie(int el1);
int Echivalenta(int el1, int el2);
int Implicatie(int el1, int el2);

int main(){
    forward_list<char> *Variabile = new forward_list<char>;
    int *dimVariabile = new int; *dimVariabile = 0;
    forward_list<char> *MultimeaVariabilelor = new forward_list<char>;
    map<char, int> VarSiAparitii;
    multimap<char, int> VarSiVal;
    string Formula; string CFormula;
    int *subformule = new int; *subformule = 0;
    int *aparitii = new int; 
    int *variabileDistincte = new int; *variabileDistincte = 0;
    int *implicatie = new int; *implicatie = 0;
    int *conjunctie = new int; *conjunctie = 0;
    int *disjunctie = new int; *disjunctie = 0;
    int *negatie = new int; *negatie = 0;
    int *echivalenta = new int; *echivalenta = 0;
    int *sumaConectori = new int; *sumaConectori = 0;
    int *neg = new int; *neg = 0;
    int *poz = new int; *poz = 1;
    int *index = new int; *index = 0;
    cout << "Student: Antohi Andi-Ionel\n";
    cout << "Specializarea: Informatica, anul 2, grupa 1\n";
    cout << "Lab: 01-02\n\n";

    cout << "Introduceti formula: ";
    getline(cin, Formula);
    CFormula = Formula;
    for(int i = 0; i < CFormula.length(); i++) {
        if(CFormula.at(i) == '-' && CFormula.at(i+1) == '>') {(*implicatie)++;}
            else if(CFormula.at(i) == 'v') {(*disjunctie)++;}
            else if(CFormula.at(i) == '!') {(*negatie)++;}
            else if(CFormula.at(i) == '~') {(*echivalenta)++;}
            else if(CFormula.at(i) == '&') {(*conjunctie)++;}
        if(isalpha(CFormula.at(i)) && CFormula.at(i) != 'v') {
            Variabile -> push_front(CFormula.at(i));
            MultimeaVariabilelor -> push_front(CFormula.at(i));
        }
    }
    Variabile -> sort();
    Variabile -> unique();
    for(auto &el : *Variabile) {
        *aparitii = 0;
        (*variabileDistincte)++;
        for(auto &el2 : *MultimeaVariabilelor) {
            if(el2 == el) {(*aparitii)++;}
        }
        VarSiAparitii[el] = *aparitii;
    }
    *sumaConectori = *implicatie + *conjunctie + *disjunctie +
    *negatie + *echivalenta;
    *subformule += *sumaConectori;
    for(auto &el : VarSiAparitii) 
        *subformule += el.second;
    *dimVariabile = distance(Variabile -> begin(), Variabile -> end());
    cout << "Date initiale:\n---\nFormula = ";
    cout << Formula;
    cout << "\nunde:\n\t-> : implicatie\n\t & : conjunctie\n\t v : disjunctie\n\t ! : negatie\n\t ~ : echivalenta\n---\n\nSolutii:\n---\n";
    cout << "a. # subformule = " << *subformule << '\n'; 
    cout << "b. # de variabile distincte = " << *variabileDistincte << '\n';
    cout << "c. # aparitii variabile : ";
    for(auto &el : VarSiAparitii)
        cout << el.first << "-" << el.second << ' ';
    cout << '\n';
    cout << "d. ordinul formulei (# conectori logici) = " << *sumaConectori << "\n\n";
    cout << "e. Tabelul de adevar\n";
    Variabile -> push_front('F');
    Variabile -> sort();
    for(auto &el : *Variabile)
        cout << el << " ";

    for(auto &el : *Variabile)
    {
        (*index)++;
        if(*index == 1)
        {
            for(int i = 0; i < pow(2, *dimVariabile); i++)
            {
                if(i >= 0 && i < pow(2, *dimVariabile)/2)
                {
                    VarSiVal.insert(pair<char, int>(el, *neg));
                } else if(i >= pow(2, *dimVariabile)/2 && i < pow(2, *dimVariabile)) {
                    VarSiVal.insert(pair<char, int>(el, *poz));
                }
            }
        } else if(*index == 2) {
            int *index_elseif = new int; *index_elseif = 0;
            for(int i = 0; i < pow(2, *dimVariabile); i++)
            {
                if(*index_elseif == 4){*index_elseif = 0;}
                if(*index_elseif >= 0  && *index_elseif < 2)
                {
                    VarSiVal.insert(pair<char, int>(el, *neg));
                    (*index_elseif)++;
                } else if(*index_elseif >= 2  && *index_elseif < 4) {
                    VarSiVal.insert(pair<char, int>(el, *poz));
                    (*index_elseif)++;
                }
            }
            delete(index_elseif);
        } else if(*index == 3) {
            for(int i = 0; i < pow(2, *dimVariabile); i++)
            {
                if(i %2 == 0)
                {
                    VarSiVal.insert(pair<char, int>(el, *neg));
                } else if(i % 2 == 1) {
                    VarSiVal.insert(pair<char, int>(el, *poz));
                }
            }
        } 
    }
    cout << "\n--------\n";

    char *Chei = new char[*dimVariabile];
    int *indexTmp = new int; *indexTmp = 0;
    for(auto &el : *Variabile)
    {
        *(Chei + *indexTmp) = el;
        (*indexTmp)++;
    }
    auto range0 = new pair<multimap<char, int>::iterator, multimap<char, int>::iterator>;
    *range0 = VarSiVal.equal_range(*(Chei + 0));
    auto range1 = new pair<multimap<char, int>::iterator, multimap<char, int>::iterator>;
    *range1 = VarSiVal.equal_range(*(Chei + 1));
    auto range2 = new pair<multimap<char, int>::iterator, multimap<char, int>::iterator>;
    *range2 = VarSiVal.equal_range(*(Chei + 2));

    *index = 0;
    for(auto &el : *Variabile){
        (*index)++;
        if(*index == 4) {
            int *formula = new int;
            for(auto el0 = range0 -> first, el1 = range1 -> first, el2 = range2 -> first; el0 != range1 -> first && el1 != range2 -> first && el2 != VarSiVal.end(); ++el0, ++el1, ++el2) {
                int A = el0 -> second; int B = el1 -> second; int C = el2 -> second;
                //*formula = Echivalenta(Conjunctie(Implicatie(B, A), Implicatie(B, Disjunctie(Negatie(A), C))), Implicatie(B, Disjunctie(Negatie(B), C))) ;
                *formula = Echivalenta(Implicatie(A, B), Implicatie(Disjunctie(Negatie(B), C), Disjunctie(Negatie(A), C)));
                VarSiVal.insert(pair<char, int>(el, *formula));
            }
            delete(formula);
        }
    }

    *indexTmp = 0;
    for(auto &el : *Variabile)
    {
        *(Chei + *indexTmp) = el;
        (*indexTmp)++;
    }
    auto range3 = new pair<multimap<char, int>::iterator, multimap<char, int>::iterator>;
    *range3 = VarSiVal.equal_range(*(Chei + 3));
    delete(Chei);
    delete(indexTmp);

    for(auto el = range0 -> first, el1 = range1 -> first, el2 = range2 -> first, el3 = range3 -> first; el != range1 -> first && el1 != range2 -> first && el2 != range3 -> first && el3 != VarSiVal.end(); ++el, ++el1, ++el2, ++el3) {
        cout << el -> second << ' ' << el1 -> second << ' ' << el2 -> second << ' ' << el3 -> second << '\n';
    }
    cout << "\n--------\n";


    //Dealocarea
    delete(implicatie);
    delete(conjunctie);
    delete(disjunctie);
    delete(negatie);
    delete(echivalenta);
    delete(sumaConectori);
    delete(variabileDistincte);
    delete(aparitii);
    delete(subformule);
    delete(dimVariabile);
    delete(poz);
    delete(neg);
    delete(index);
    delete(range0);
    delete(range1);
    delete(range2);
    delete(range3);
    delete(Variabile);
    delete(MultimeaVariabilelor);
    return 0;
}

//ZONA DE FUNCTII
int Disjunctie(int el1, int el2) {
    return el1 || el2;
}

int Conjunctie(int el1, int el2){
    return el1 && el2;
}

int Negatie(int el1){
    return !el1;
}

int Echivalenta(int el1, int el2){
    if(el1 == 0 && el2 == 0) {return 1;}
        else if(el1 == 0 && el2 == 1) {return 0;}
        else if(el1 == 1 && el2 == 0) {return 0;}
        else if(el1 == 1 && el2 == 1) {return 1;}
    return -1;
}

int Implicatie(int el1, int el2){
    if(el1 == 0 && el2 == 0) {return 1;}
        else if(el1 == 0 && el2 == 1) {return 1;}
        else if(el1 == 1 && el2 == 0) {return 0;}
        else if(el1 == 1 && el1 == 1) {return 1;}
    return -1;
}