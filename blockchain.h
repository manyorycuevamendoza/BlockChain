#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "node.h"

template <class T>
class BlockChain{
    private:
        Node<T>* head;//sentinel
        int nodes; 

    public:
        BlockChain(){ 
            this->head=new Node<T>();//Node() es el sentinela
            this->head->next=this->head;
            this->head->prev=this->head;
            this->nodes=0;
        }

        void insert(T data){
            Node<T>* temp = new Node<T>(data);
            temp->next=this->head; //hacemos que el nodo se cuelgue
            temp->prev=this->head->prev; //hacemos que el nodo se cueelgue del prev del head
            this->head->prev->next=temp;//hacemos que el nodo se cuelgue siguiente y atrás
            this->head->prev=temp;
            //aumentamos el contador de nodos
            this->nodes++;

        }

        
        void clear(){
            while ( this -> size() != 0 ) this -> pop_front();

        }

        ~BlockChain(){ 
         	this -> clear();
            delete this -> head;          
        }

        //insertar_bloque (vector){ nonce, }
};


#endif