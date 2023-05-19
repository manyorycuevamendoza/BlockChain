#ifndef NODE_H
#define NODE_H

using namespace std;
template <typename T>
struct NodeBT {
    T data;
    NodeBT* left; 
    NodeBT* right;        
    int height;
    NodeBT() : left(nullptr), right(nullptr), height(0) {}   
    NodeBT(T value) : data(value), left(nullptr), right(nullptr), height(0) {}   

    void killSelf(){
        if(left != nullptr) left->killSelf();
        if(right != nullptr) right->killSelf();
        delete this;
    }
};

#endif