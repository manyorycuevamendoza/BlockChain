#ifndef NODE_BTREE_H
#define NODE_BTREE_H

using namespace std;

template <typename TK>
struct Node {
    //array de keys
    TK* keys;
    //array de punteros a hijos
    Node** children;
    //cantidad de keys
    int count;
    //indicador de nodo hoja
    bool leaf;
    //constructor por defecto
    Node(): keys(nullptr), children(nullptr), count(0), leaf(true) {}

    Node(int M, bool _leaf = true){//constructor con parametro M
    cout<<"Creando nodo con M = "<<M<<endl;
        count = 0;
        leaf = _leaf;
        keys = new TK[M-1];
        children = new Node<TK>*[M];
        for(int i=0;i<M;i++) children[i] = nullptr;
    }

    void display(){
        for (int i = 0; i < count; ++i)
            cout<<keys[i]<<", ";
        cout<<endl;
    }

    ~Node(){
        delete[] keys;
        delete[] children;
    }
};

/*
//tranformando el nodo de B que recibe solo un vector de llaves, a recibir vector de llaves y valores.

template< typename TK, typename TV>

struct Entry{
    TK key;
    TV value;

    Entry(){
        key = TK();
        value = TV();

    }

    Entry(TK k, TV v){
        this->key = k;
        this->value = v;
    }

    bool same_key(Entry a){
        return a.key == this->key;
    }

    friend ostream& operator<<(ostream& salida, Entry<TK, TV> e){
        salida<<e.key<<" "<<e.value;
        return salida;
    }
}

template <typename TK, typename TV>
struct Node{
    Entry<TK, TV>* data; //array de llaves y valores
    Node <TK,TV>** children; //array de punteros  a hijos
    int count;
    
}


*/

#endif