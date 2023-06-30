#ifndef FORWARD_AVL_H
#define FORWARD_AVL_H
#include <iostream>


// TODO: Implement all methods
template <class T>
class ForwardListAVL { //hereda de la clase List, el padre es List
    private:
        struct Node {
            T data;
            Node* next;

            Node(){ 
                this -> data = T();//T() es el constructor por defecto de T
                this -> next = nullptr;
            }

            Node(T value){
                this -> data = value;
                this -> next = nullptr;
            }

            void killSelf(){
                delete this;   
            }    
        };

    private:
        Node* head;
        int nodes;

    public:
        ForwardListAVL() { //constructor por defecto
            this -> head = nullptr;
            this -> nodes = 0;
        }

        ~ForwardListAVL(){ 
            this -> clear();
            delete this -> head;           
        }

        void display(){
            for (int i=0;i<this->size();i++){
                std:: cout<<(*this)[i]<<" ";
            }
        }

        T top(){
            if ( this -> size() == 0) throw ("sin definir"); //caso vacío
            else {
                return head -> data;
            }
        }

        T back(){
            if ( this -> size() == 0) throw ("sin definir"); //caso vacío
            else{
                Node* temp = head;
                while ( temp->next ) temp = temp -> next;
                return temp -> data;
            }
        }

        void push_front(T data){
            Node* temp = new Node(); //se crea un temp de tipo Node 
            temp -> data = data;
            temp -> next = head; // "temp" se cola antes de head
            head = temp;
            this -> nodes++;
        }

        void push_back(T data){
            Node* temp = head; // "temp" apunta a "head" (inicio de la lista)
            Node* nuevo = new Node; // nuevo Nodo (para agregar al final)
            nuevo -> next = nullptr; //el siguiente apunta a nullptr
            nuevo -> data = data;
            this -> nodes ++;
            while ( temp -> next ) temp = temp -> next;
            temp -> next = nuevo;  
            temp = nullptr;
            temp -> killSelf();       
        }

        T pop_front(){
            if ( this -> size() == 0 ) throw ("sin definir");
            else{
                Node* temp = head;
                head = head -> next;
                this -> nodes --;
                T result = temp -> data;
                temp -> killSelf();
                return result;
            }
        }

        T pop_back(){
            if ( size() == 0 ) throw ("sin definir");
            else{
                Node* temp = head;

                while( temp -> next -> next ) temp = temp -> next;
                T result = temp -> next -> data;
                (temp -> next) -> killSelf();//elimina el ultimo nodo
                temp -> next = nullptr;
                this -> nodes --;
                return result;
            }
        }

        void insert(T data, int pos){
            if ( size() < pos || pos<0 ) throw ("sin definir");
            else{
                Node* temp = head;
                Node* nuevo = new Node(data);
                for (int i=0; i<pos-1; i++) temp = temp -> next;
                nuevo -> next = temp -> next;
                temp -> next = nuevo;
                temp = nullptr;
                this -> nodes ++;
                temp -> killSelf();
            }
        }

        void remove(int pos){
            if ( size()-1 < pos || pos < 0 )throw ("sin definir");
            else{
                Node* temp = head;
                for (int i=0; i<pos-1 ; i++) temp = temp -> next;
                Node* elim = temp -> next; //nodo a eliminar
                temp -> next = elim -> next;
                elim -> killSelf();
                this -> nodes--;
            }
        }

        T& operator[](int pos){
            if ( size()-1 < pos )throw ("sin definir");
            else{
                Node* temp = head;
                for (int i = 0; i<pos;i++) temp = temp -> next;
                T& result = temp -> data;
                temp = nullptr;
                temp -> killSelf();
                return result;
            }
        }

        bool is_empty(){
            return !head; //si head es nullptr, retorna true
            
        }

        int size(){
            return this -> nodes;
        }

        void clear(){
            while(head){
                Node* temp = head;
                head = head -> next;
                delete temp;
            } 
        }
        
     

};

#endif