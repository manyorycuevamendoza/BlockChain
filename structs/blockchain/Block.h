#ifndef BLOCK_H
#define BLOCK_H
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
    bool hasheado; // atributo para saber si está bien hasheado

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
        } //huella tiene valor concatenado de todos los elementos (orden: nro, data)
        huella_padre="";
    }

    void recalculate(){
        huella = "";
        huella = to_string(nro); // nro de bloque 

        for (int i=0; i<cant_data; i++){
            huella += data[i];
        }
        //for (auto dato:data) huella += dato; //pasamos todos los datos
        //huella += huella_padre; //añadimos la huella del padre
        
        //(huella: nro+data+huella_padre)
        
        //modificando la huella
        SHA256 sha;
        uint8_t * digest = sha.digest();

        //actualizando huella y nonce
        nonce=sha.SHA256::findNonce(huella+huella_padre,huella); //aquí se envia huella del padre
        
        delete[] digest;
        this->hasheado = true; //el codigo hash es correcto
    }

    void print_huella(){
        for (int i=0; i<cant_data; i++) cout<<data[i]<<" ";
        cout<<" Huella: "<<huella<<endl;
    }

    T* get_data(){
        return data;
    }


};

#endif