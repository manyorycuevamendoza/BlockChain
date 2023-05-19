#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <class T>
struct Node {
    T data;
    Node* next;
    Node* prev;

    Node(){ 
        data = T(); //base, para no guaradar basura
        next = prev = nullptr;
    }

    Node(T value){
        data = value;
        next = prev = nullptr;
    }

    void killSelf(){
        delete this;    
    }    
};

#endif