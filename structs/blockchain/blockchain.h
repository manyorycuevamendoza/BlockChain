#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "Block.h"
#include <vector>

template <class T>
class BlockChain{
    friend class Block<T>;
    private:
        Block<T>* head;//sentinel
        int nodes; 

    
    public:
        BlockChain(){ 
            this->head=new Block<T>();//Node() es el sentinela
            this->head->next=this->head;
            this->head->prev=this->head;
            this->nodes=0;
        }

        void insert(initializer_list<T> data){
            Block<T>* temp = new Block<T>(data,this->nodes);
            temp->next=this->head; //hacemos que el nodo se cuelgue
            temp->prev=this->head->prev; //hacemos que el nodo se cueelgue del prev del head
            this->head->prev->next=temp;//hacemos que el nodo se cuelgue siguiente y atrás
            this->head->prev=temp;
            //aumentamos el contador de nodos
            this->nodes++;

          //actualizar huella del padre
          temp->huella_padre = temp->prev->huella;

          // hallar la huella
          /*
          SHA256 sha;
          string huella = temp->huella+temp->huella_padre;
          uint8_t * digest = sha.digest();

          //actualizando huella y nonce
					temp->nonce=sha.SHA256::findNonce(huella,huella); 
          temp->huella = huella;
          delete[] digest;
        
          */

          SHA256 sha;
          uint8_t * digest = sha.digest();

          //actualizando huella y nonce
          temp->nonce=sha.SHA256::findNonce(temp->huella+temp->huella_padre,temp->huella);
          delete[] digest;
        
        }

        void print_huellas(){
          Block<T>* temp = head->next;
          while(temp!=head) {
            cout<<"nro: "<<temp->nro<<" - "<<temp->huella;
            cout<<" - Nonce: "<<temp->nonce<<endl;
            temp = temp->next;
          }
        }
};
#endif