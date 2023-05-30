/*
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
*/
#include "funciones.h"
/*
int main(){
    

    std::ifstream file("test1.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }
    //añandiendo arbol y insertando ----------------------------------
    AVLTree2<int,int> avl1; // id monto
    AVLTree2<int,time_t> avl2; //id fechas


    // hash 
    ChainHash<string,int> string1; //primer string
    ChainHash<string,int> string2; //segundo string
    ChainHash<int,int> numero; //para monto id/monto
    ChainHash<long,int> fecha; //para fecha/id 

    

    int count =0;
    std::string line;
    std::getline(file, line); // recibir datos

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::getline(ss, item, ','); // primer string
        string1.insert(item,count); 
        
        std::getline(ss, item, ','); 
        string2.insert(item,count);
        
        std::getline(ss, item, ',');//monto
        int number=stoi(item); 
        avl1.insert(count,number); // key: nro bloque  //  value:monto -- lo ordena por monto(por value)
        numero.insert(number,count);
       
        std::getline(ss, item, ','); //--fecha
        time_t date = convertToUnixTimestamp(item); 
        avl2.insert(count,date); // key: nro bloque   //  value:fecha -- lo ordena por fecha(por value)
        numero.insert(date,count);

        count ++; // nro de bloque aumenta
    } 

    file.close(); 

    //avl.displayPretty();
    cout<<endl; 
    vector <int> result = avl1.search_by_range(0,1000); 
    //for (auto x:result) cout<<x<<" "; 
    cout<<result.size()<<endl; 

    cout<<avl1.size()<<endl; 

    //cout<<"Size: "<<s1.get_size();
    //cout<<endl<<s1.search("Lily");
    //avl1.displayPretty();
    
    cout<<"\nSize - fechas: "<<avl2.size()<<endl;
    vector <int> res = avl2.search_by_range(convertToUnixTimestamp("2001-01-01"),convertToUnixTimestamp("2004-01-01"));
    cout<<"Mínimo: "<<avl1.minValue().key<<endl;
    cout<<"Máximo: "<<avl1.maxValue().key<<endl;
    for (auto x:res) cout<<x<<" ";
    cout<<"Size: "<<res.size()<<endl;
    return 0;
}
*/ 
int main(){
    begin();
    
}
 
