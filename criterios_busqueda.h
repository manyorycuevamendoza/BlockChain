#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "structs/blockchain/blockchain.h"
#include "structs/tabla_hash/chainhash.h"
#include "structs/avl/date.h"
using namespace std;
void readCSV(const string, AVLTree2<int,int>* , AVLTree2<int,long>* , ChainHash<string,int>* , ChainHash<string,int>* , ChainHash<int,int>* , ChainHash<long,int>* );

template <class TK, class TV>
TV search(ChainHash<TK,TV>*, TK);

template <class TK,class TV>
TK max_value(AVLTree2<TK,TV>* arbol);

template <class TK,class TV>
TK min_value(AVLTree2<TK,TV>* arbol);

template <class TK,class TV>
vector <TK> range_search(AVLTree2<TK,TV>* arbol, TV begin, TV end);


void readCSV(const string archivo, string* atributos, AVLTree2<int,int>* avl1, AVLTree2<int,long>* avl2, ChainHash<string,int>* string1, ChainHash<string,int>* string2, ChainHash<int,int>* numero, ChainHash<long,int>* fecha){
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    int count =0;
    std::string line;
    std::string item;
    std::getline(file, line); // recibir atributos
    std::stringstream ss(line);
    for (int i=0;i<4;i++){
        std::getline(ss, item, ','); // primer string
        atributos[i] = item;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, item, ','); // primer string
        string1->insert(item,count); 
        
        std::getline(ss, item, ','); 
        string2->insert(item,count);
        
        std::getline(ss, item, ',');//monto
        int number=stoi(item); 
        avl1->insert(count,number); // key: nro bloque  //  value:monto -- lo ordena por monto(por value)
        numero->insert(number,count);
       
        std::getline(ss, item, ','); //--fecha
        time_t date = convertToUnixTimestamp(item); 
        avl2->insert(count,date); // key: nro bloque   //  value:fecha -- lo ordena por fecha(por value)
        fecha->insert(date,count);

        count ++; // nro de bloque aumenta
    } 

    file.close(); 

    /*
    //avl.displayPretty();
    cout<<endl; 
    vector <int> result = avl1->search_by_range(0,1000); 
    //for (auto x:result) cout<<x<<" "; 
    cout<<result.size()<<endl; 

    cout<<avl1->size()<<endl; 

    //cout<<"Size: "<<s1.get_size();
    //cout<<endl<<s1.search("Lily");
    //avl1.displayPretty();
    
    cout<<"\nSize - fechas: "<<avl2->size()<<endl;
    vector <int> res = avl2->search_by_range(convertToUnixTimestamp("2001-01-01"),convertToUnixTimestamp("2004-01-01"));
    cout<<"Mínimo: "<<avl1->minValue().key<<endl;
    cout<<"Máximo: "<<avl1->maxValue().key<<endl;
    for (auto x:res) cout<<x<<" ";
    cout<<"Size: "<<res.size()<<endl;
    */
}
 

template <class TK, class TV>
TV search(ChainHash<TK,TV>* tabla, TK key) {
    return tabla->search(key);
}

template <class TK,class TV>
vector <TK> range_search(AVLTree2<TK,TV>* arbol, TV begin, TV end){
    return arbol->search_by_range(begin,end);
}


template <class TK,class TV>
TK max_value(AVLTree2<TK,TV>* arbol){
    return arbol->maxValue().key;
}

template <class TK,class TV>
TK min_value(AVLTree2<TK,TV>* arbol){
    return arbol->minValue().key;
}