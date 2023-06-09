#include <iostream>
#include <string>
//#include <vector>
#include "SHA256.h"
using namespace std;

template <class T>
struct Block
{
    //vector <T> data; // SHA256 solo funciona con strings
    T* data;
    int cant_data; // nro de valores por bloque
    int nro;
    string huella; // hash(huellapadre+datos) = huella
    string huella_padre;
    string nonce;
    Block* next;
    Block* prev;

    public:
    void killSelf(){
        if(next) next->killSelf();
        delete next;
        delete prev;
    }

    Block(){
        huella_padre = huella = nonce = "";
    }
    
    Block(T* _data,int size_data,int _nro_bloque) {
        nro = _nro_bloque;
        nonce = "";
        next = prev = nullptr;

        //para valores que almacenará el bloque
        cant_data = size_data;
        data = new T[cant_data];

        huella = to_string(nro);
        
        for (int i=0; i<cant_data; i++) {
            data[i] = _data[i];
            huella += _data[i];
        } //huella tiene valor concatenado de todos los elementos
        huella_padre="";
    }

    void print_huella(){
        for (int i=0; i<cant_data; i++) cout<<data[i]<<" ";
        cout<<" Huella: "<<huella<<endl;
    }

    T* get_data(){
        return data;
    }

};
