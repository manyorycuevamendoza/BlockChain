#include <iostream>
#include <string>
#include <vector>
#include "SHA256.h"
using namespace std;

template <class T>
struct Block
{
    vector <T> data; // SHA256 solo funciona con strings
    int nro;
    string huella; // hash(huellapadre+datos) = huella
    string huella_padre;
    string nonce;
    Block* next;
    Block* prev;

    public:
    Block(){
        huella_padre = huella = nonce = "";
    }
    Block(initializer_list<T> _data,int _nro) {
        nro = _nro;
        nonce = "";
        next = prev = nullptr;

        huella = to_string(nro);
        
        for (auto a:_data) {
        data.push_back(a);
        huella += a;
        } //huella tiene valor concatenado de todos los elementos
        huella_padre="";
    }

    void print(){
        for (auto x:data) cout<<x<<" ";
        cout<<" Huella: "<<huella<<endl;
    }

};
