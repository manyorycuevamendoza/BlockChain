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


        template <class... Typenames>
        void insert_str(vector<T> data, T data1,Typenames... data_extra){
          data.push_back(data1);
          insert_str(data, data_extra...);
        }

        template <class... Typenames>
        void insert_string(string data,Typenames... data_extra){
          vector <T> result;
          result.push_back(data);
          insert_str(result, data_extra...);
        }

        
        void insert_str(vector<T> data, T data1){ // caso para 2
          data.push_back(data1);
          insert(data);
        }

        void insert(vector<T> data){
            Block<T>* temp = new Block<T>(data,this->nodes);
            temp->next=this->head; //hacemos que el nodo se cuelgue
            temp->prev=this->head->prev; //hacemos que el nodo se cueelgue del prev del head
            this->head->prev->next=temp;//hacemos que el nodo se cuelgue siguiente y atrás
            this->head->prev=temp;
            //aumentamos el contador de nodos
            this->nodes++;

          //actualizar huella del padre
          temp->huella_padre = temp->prev->huella;

          SHA256 sha;
          uint8_t * digest = sha.digest();

          //actualizando huella y nonce
          temp->nonce=sha.SHA256::findNonce(temp->huella+temp->huella_padre,temp->huella);
          delete[] digest;
        
        }
       /*
        string insert(T s1,T s2, T s3, T s4){
          return s1 + insert(...data_extra);;
        }

        template <class... Typenames> // caso general
        string insert(T s1, Typenames... data_extra){
          return s1 + "," insert(...data_extra);;
        }
        */

        vector <T> get_block(int ind){ // retorna un bloque de acuerdo a un indice que se pasa
                Block<T>* temp = head->next;
                for (int i=0;i<ind;i++){
                    temp = temp->next;
                }
                return temp->get_data();
        }

        void print_huellas(){
          Block<T>* temp = head->next;
          while(temp!=head) {
            cout<<"nro: "<<temp->nro<<" - "<<temp->huella;
            cout<<" - Nonce: "<<temp->nonce<<endl;
            temp = temp->next;
          }
        }

        bool proof_of_work(){
          Block<T>* temp = head->next->next; // empezamos desde segundo
          while (temp!=head){
            if (temp->prev->huella!=temp->huella_padre) return false;
            temp = temp->next;
          }
          return true;
        }

        ~BlockChain(){
            if(head) head->killSelf();
        }
};
#endif