#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "structs/blockchain/blockchain.h"
#include "structs/tabla_hash/chainhash.h"
#include "structs/avl/date.h"
#include <initializer_list>
using namespace std;

BlockChain<string>* cadena_bloques = new BlockChain<string>(); // blockchain

void readCSV(const string, AVLTree2<int,int>* , AVLTree2<int,long>* , ChainHash<string,int>* , ChainHash<string,int>* , ChainHash<int,int>* , ChainHash<long,int>* );

template <class TK, class TV>
TV search(ChainHash<TK,TV>*, TK);

template <class TK,class TV>
TK max_value(AVLTree2<TK,TV>* arbol);

template <class TK,class TV>
TK min_value(AVLTree2<TK,TV>* arbol);

template <class TK,class TV>
vector <TK> range_search(AVLTree2<TK,TV>* arbol, TV begin, TV end);


void begin(){
    //añandiendo arbol y insertando ----------------------------------
    AVLTree2<int,int>* avl1 = new AVLTree2<int,int>(); // id monto
    AVLTree2<int,long>* avl2 = new AVLTree2<int,long>(); //id fechas

    // hash 
    ChainHash<string,int>* string1 = new ChainHash<string,int>(); //primer string
    ChainHash<string,int>* string2 = new ChainHash<string,int>(); //segundo string
    ChainHash<int,int>* numero = new ChainHash<int,int>(); //para monto id/monto
    ChainHash<long,int>* fecha = new ChainHash<long,int>(); //para fecha/id
    string archivo = "test1.csv";
    readCSV(archivo,avl1,avl2, string1, string2, numero, fecha); // creando estructuras

    /*
    cout<<search(numero, 100)<<endl;
    string f = "Mallory";
    cout<<search(string1, f);
     cout<<min_value(avl1); // minimo
    */
    long a=convertToUnixTimestamp("2002-01-01");
    long  b=convertToUnixTimestamp("2003-01-01");
    cout<<avl2->size()<<endl;
    vector <int> res = range_search(avl2, a,b);
    for (auto x:res) cout<<x<<" ";
    // la consola debe llamar a las funciones y retornar info sobre el bloque(con get_block)
}

void readCSV(const string archivo, AVLTree2<int,int>* avl1, AVLTree2<int,long>* avl2, ChainHash<string,int>* string1, ChainHash<string,int>* string2, ChainHash<int,int>* numero, ChainHash<long,int>* fecha){
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return;
    }

    int count =0;
    std::string line;
    std::getline(file, line); // recibir datos

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
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
