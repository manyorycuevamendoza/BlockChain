#ifndef PATRICIA_TRIE_H
#define PATRICIA_TRIE_H
#include <iostream>
#include "../circular_array/circular_array.h"
using namespace std;

const unsigned ALPHA_SIZE = 256;//tamanio del alfabeto

template <typename TK>
class TriePatricia{
private:
    struct TrieNode{         
        TrieNode **children;           
        string preffix;
        bool endWord; //indica si es final de una palabra
        TK id; // para representar el numero de bloque

        TrieNode(){
            children = new TrieNode*[ALPHA_SIZE](); endWord=false; preffix="";
        }
        ~TrieNode(){
            for(int i=0;i<ALPHA_SIZE;i++){
                if(children[i])
                    delete children[i];
            }
            delete[] children;
        }
    };
    TrieNode* root;
    
public:
    TriePatricia(): root(nullptr) {}
    void insert(TK id, string key);
    bool search(string key);
    void remove(string key);
    
    //imprime ordenado
    string toString(string sep);
    void toString_recursivo(TrieNode* node, string prefijo, string& chain, string sep);
    //CircularArray<TK> start_with(CircularArray<TK>& result, const string& preffix, TrieNode* node);
    void start_with(CircularArray<TK>& result, const string& preffix, TrieNode* node);
    void start_with(CircularArray<TK>& result, string preffix);
};

template <typename TK>
void TriePatricia<TK>::insert(TK id,string key){
    if (!root) root = new TrieNode(); // creamos en caso sea nullptr
    int ind_prefix = 0; // para recorrer key
    int size = int(key.size()); // para tamaño de string key

    if (!root->children[int(key[ind_prefix])]){ // caso base
        TrieNode* nuevo = new TrieNode(); nuevo->preffix = key; nuevo->endWord = true;
        root->children[int(key[ind_prefix])] = nuevo;
        
        nuevo->id = id; // se asigna id (nro bloque)
        //std::cout<<"Base: "<<nuevo->preffix<<std::endl;
        return; 
    } 
   
    
    TrieNode* temp = root; //recorremos desde raiz
    while (temp->children[int(key[ind_prefix])]){// mientras que tenga un hijo asociado
        temp = temp->children[int(key[ind_prefix])]; // se recorre
        int temp_size = int(temp->preffix.size()); // tamaño del prefijo del nodo actual
        for (int ind=0; ind<temp_size; ind++){ // recorremos el valor que tiene el nodo
            char x = temp->preffix[ind];
            //if (ind_prefix!=size-1){ // si es distinto a size-1
                if (x==key[ind_prefix] && ind_prefix!=size) {
                    ind_prefix++; // si coinciden indice solo avanza
                     
                    if (ind_prefix==size){ // se intenta insertar palabra similar con menos  longitud
                        if(ind==temp_size-1){ return; } //repetidos
                        TrieNode* nuevo = new TrieNode();  // creamos un nod basandonos en temp
                        nuevo->preffix = "";
                        int size_temp_actual = int(temp->preffix.size());
                        for (int nuevo_ind = ind+1; nuevo_ind<size_temp_actual; nuevo_ind++){ // recorremos lo que falta para añadir al nuevo hijo
                            nuevo->preffix+=temp->preffix[nuevo_ind];
                        }
                        for (int nuevo_ind = ind+1; nuevo_ind<size_temp_actual; nuevo_ind++){ // recorremos lo que falta para añadir al nuevo hijo
                            temp->preffix.pop_back();
                        }
                        temp->endWord = nuevo->endWord = true; 

                        // liberamos los hijos de nuevo
                        for (int i=0;i<ALPHA_SIZE;i++) {
                            nuevo->children[i]=temp->children[i];
                            temp->children[i] = nullptr;
                        }

                        // cambiar valores de temp y nuevo
                        /*
                        std::string p = nuevo->prefix;
                        nuevo->prefix = temp->prefix;
                        temp->prefix = p;
                        */
                        temp->children[int(nuevo->preffix[0])] = nuevo;
                        //std::cout<<"Palabra : "<<temp->preffix<<" " <<nuevo->preffix<<std::endl;
                        return;
                    }
                }
               
                
                else if(x!=key[ind_prefix] && ind_prefix<size){ // caso contrario, debe crear un nuevo nodo y cuidar dependencias del actual
                  
                    TrieNode* nuevo = new TrieNode();
                    nuevo->preffix = "";
                    for (int i = ind_prefix; i<size; i++) nuevo->preffix+=key[i]; //lo que se debe añadir
                    nuevo->endWord = true; 
                    //std::cout<<"Temp: "<<temp->preffix<<"\tEn else: "<<nuevo->preffix<<std::endl;

                    // enviar lo que se encuentra despues del prefijo como otro hijo
                    if (ind<temp_size){
                        TrieNode* otro_hijo = new TrieNode(); // nuevo nodo
                        otro_hijo->preffix = ""; otro_hijo->endWord=false;
                        for (int i=ind; i<temp_size; i++) otro_hijo->preffix+=temp->preffix[i]; // añadimos valor para el nuevo hijo (lo que había en nodo)
                        for (int i=ind; i<temp_size; i++){ // borramos lo de más
                            temp->preffix.pop_back();
                        }
                        if(temp->endWord){
                            otro_hijo->endWord = true;
                        }
                        temp->endWord = false; // temp deja de ser endWord(si lo era)
                        
                        //std::cout<<"Otro hijo: "<<otro_hijo->preffix<<"\t";
                        
                        // pasamos todas las dependencias al nuevo nodo
                        for (int i=0; i<ALPHA_SIZE; i++) {
                            otro_hijo->children[i] = temp->children[i];
                            temp->children[i] = nullptr;
                        }
                       // temp = temp->children[int(otro_hijo->prefix[0])];
                        temp->children[int(otro_hijo->preffix[0])] = otro_hijo; // añadimos el hijo
                        temp->children[int(nuevo->preffix[0])] = nuevo;     
                        //std::cout<<"Nuevo: "<<nuevo->preffix<<std::endl;
                        return;
                    }
                
                    else temp->children[int(nuevo->preffix[0])] = nuevo; 
                    return;
                }
        }
    } // llega aqui si ya no tiene un hijo asociado
    TrieNode* nuevo = new TrieNode();
    nuevo->preffix = "";
    for (int i = ind_prefix; i<size; i++) nuevo->preffix+=key[i]; //lo que se debe añadir
    nuevo->endWord = true; 
    temp->children[int(nuevo->preffix[0])] = nuevo;
    //std::cout<<"Fuera del while: "<<nuevo->preffix<<"\tTemp: "<<temp->preffix<<std::endl;
}

template <typename TK>
bool TriePatricia<TK>::search(string key){
    int size = int(key.size());
    int ind_prefix = 0;  // para recorrer el prefijo
    TrieNode* temp = root; // para recorrer cada nodo

    while (temp->children[int(key[ind_prefix])]){ // mientras se pueda recorrer
        temp = temp->children[int(key[ind_prefix])]; // se obtiene el temp
        for (auto x:temp->preffix){ // recorremos cada valor de temp
            if (x!=key[ind_prefix]) return false;
            ind_prefix++;
        } // se coincide en palabra
        if (ind_prefix==size && temp->endWord) return true; // se retorna true si se encuentra la palabra en el arbol
    }
    return false;
}


template <typename TK>
void TriePatricia<TK>::remove(string key){
    if (!root) return; // caso base
    int size = int(key.size());
    int ind_prefix = 0; // para recorrer el prefijo
    TrieNode* temp = root; // para recorrer cada nodo

    while (temp->children[int(key[ind_prefix])]){ // mientras se pueda recorrer
        temp = temp->children[int(key[ind_prefix])]; // se obtiene el temp
        for (auto x:temp->preffix){ // recorremos cada valor de temp
            if (x!=key[ind_prefix]) return;
            ind_prefix++;
        } // se coincide en palabra
        if (ind_prefix==size && temp->endWord) { // se encuentra la palabra en el arbol
            temp->endWord = false; // se cambia el valor de endWord
            return;
        }
    }
    return;
}



template <typename TK>
string TriePatricia<TK>::toString(string sep){
    //print();
    string chain = "";
    toString_recursivo(root, "", chain, sep);
    return chain;
}

template <typename TK>
void TriePatricia<TK>::toString_recursivo(TrieNode* node, string prefijo, string& chain, string sep){
    if(node->endWord)
        chain += prefijo + sep;
    for(int i=0;i<ALPHA_SIZE;i++){
        if(node->children[i])
            toString_recursivo(node->children[i], prefijo + node->children[i]->preffix, chain, sep);
    }
}

template <typename TK>
void TriePatricia<TK>::start_with(CircularArray<TK>& result, string preffix) {
    result.clear();
    TrieNode* node = root;
    for(char c : preffix){
        if(node->children[c-'a'])
            node = node->children[c-'a'];
    }
    //result = start_with(result,preffix,node);
    start_with(result,preffix,node);
}

template <typename TK>
//CircularArray<TK> TriePatricia<TK>::start_with(CircularArray<TK>& result, const string& preffix, TrieNode* node) {
void TriePatricia<TK>::start_with(CircularArray<TK>& result, const string& preffix, TrieNode* node) {
    if(node->endWord)
        result.push_back(node->id); // añadimos el id

    for(int i=0;i<ALPHA_SIZE;i++){
        if(node->children[i]){
            string newpreffix = preffix + node->children[i]->preffix;
            start_with(result, newpreffix, node->children[i]);
        }
    }
}

#endif
