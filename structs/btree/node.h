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

    Node(): keys(nullptr), children(nullptr), count(0), leaf(true) {}

    Node(int M, bool _leaf = true){
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

#endif