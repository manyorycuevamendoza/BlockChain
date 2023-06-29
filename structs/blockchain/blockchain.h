#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include "Block.h"
#include "../../structs/tabla_hash/chainhash.h"
//#include "../structs/tabla_hash/chainhash.h"
//#include "../structs/avl/date.h"

template <class T>
class BlockChain{
    friend class Block<T>;
    private:
        Block<T>* head;//sentinel
        int nodes; 
        string* atributos;
        int values; // cantidad de atributos



    public:
        BlockChain(int columnas=0){ 
            this->head=new Block<T>();//Node() es el sentinela
            this->head->next=this->head;
            this->head->prev=this->head;
            this->nodes=0;
            this->values = columnas;
        }

        BlockChain(string* _atributos, int _n){ 
          this->head=new Block<T>();//Node() es el sentinela
          this->head->next=this->head;
          this->head->prev=this->head;
          this->nodes=0;
          values = _n;
          atributos = new string[_n];
          for (int i = 0; i<values; i++) atributos[i] = _atributos[i];
        }

        void set_atributos(string* _atributos, int _n){
            values = _n;
            atributos = new string[_n];
            for (int i = 0; i<values; i++) atributos[i] = _atributos[i];
        }

        template <class... Typenames>
        void insert_string(int size,T data,Typenames... data_extra){ //al final recibe cantidad de valores
          T* result = new T[size];
          result[0] = data; // agregamos primer elemento
          insert_str(1,size,result, data_extra...);
        }

        template <class... Typenames>
        void insert_str(int indice,int size,T* data,T data1,Typenames... data_extra){ // recibe indice en el que se va a añadir
          data[indice] = data1; // agregamos valor en posicion especificada
          insert_str(indice+1,size,data, data_extra...);
        }
        
        void insert_str(int indice,int size,T* data, T data1){ // caso cuando solo falta añadir 1
          data[indice] = data1;
          insert(data,size);
        }

        void insert(T* data,int size){
            Block<T>* temp = new Block<T>(data,size,this->nodes);
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

        void get_block(int ind){ // retorna un bloque de acuerdo a un indice que se pasa
                Block<T>* temp = head->next;
                for (int i=0;i<ind;i++){
                    temp = temp->next;
                }
                //int i = 0;
                for (int i=0; i<temp->cant_data; i++) {
                  //cout<<temp->data[i]<<"\t";
                    cout<<atributos[i%values]<<": "<<temp->data[i]<<"\t";
                    if (i%values==values-1){ // ultimo elemento
                      cout<<endl;
                    }
                }
                cout<<"\n";
        }

        void print_huellas(){
          Block<T>* temp = head->next;
          while(temp!=head) {
            cout<<"nro: "<<temp->nro<<" - "<<temp->huella;
            cout<<" - Nonce: "<<temp->nonce<<endl;
            temp = temp->next;
          }
        }

        void display(){
          Block<T>* temp = head->next;
          while(temp!=head) {
            cout<<"Bloque nro: "<<temp->nro<<endl;
        
            for (int i=0;i<temp->cant_data;i++){//recorriendo cada atributo
            
              //cout<<temp->data[i]<<"\t"; // impresión simple
              
              //impresion con atributos
              cout<<atributos[i%values]<<": "<<temp->data[i]<<"\t";
              if (i%values==values-1){ // ultimo elemento
                cout<<endl;
              }
              
            }
            
            cout<<"Nonce: "<<temp->nonce<<"\t";
            cout<<"Huella: "<<temp->huella<<endl;
            cout<<" ---------------------------------- "<<endl;
            temp = temp->next;
          }
        }

        void recalculo_cascada(){
          //  caso sin padre
          Block<T>* temp = head->next;

          while (temp!=head){ //se recorre cada bloque
            temp->huella_padre = temp->prev->huella; // huella del bloque anterior
            temp->huella = temp->huella_padre;
            temp->recalculate();
            temp = temp->next; //avanzamos a la sig posicion
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

        int get_size(){
            return this->nodes;
        }

        ~BlockChain(){
            if(head) head->killSelf();
            delete [] atributos;
        }
};
#endif