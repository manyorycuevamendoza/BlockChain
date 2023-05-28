#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
//#include "structs/avl/avl.h"
#include "structs/blockchain/blockchain.h"
#include "structs/tabla_hash/chainhash.h"
#include "structs/avl/date.h"

//#include "SHA256.h"
//#include "lectura.h"

using namespace std;

int main(){
    

    std::ifstream file("test1.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open the file." << std::endl;
        return 1;
    }
    //añandiendo arbol y isertando ----------------------------------
    AVLTree2<int,int> avl1;
    AVLTree2<int,time_t> avl2;
    ChainHash<string,int> s1;

    int count =0;
    std::string line;
    std::getline(file, line); // recibir datos

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::getline(ss, item, ','); // primer string
        s1.insert(item,count);
        //std::cout<< item<<" ,";
        std::getline(ss, item, ',');
        //std::cout << item << " ,";
        //monto
        std::getline(ss, item, ',');
        int number=stoi(item);

        avl1.insert(count,number); // key: nro bloque   //  value:monto -- lo ordena por monto(por value)
        //cout<<number<<"|";
        //--fecha
        std::getline(ss, item, ',');
        time_t fecha = convertToUnixTimestamp(item);
        avl2.insert(count,fecha); // key: nro bloque   //  value:fecha -- lo ordena por fecha(por value)
        //std::cout << item<<std::endl;

        count ++; // nro de bloque aumenta
    }

    file.close();

    //avl.displayPretty();
    cout<<endl;
    vector <int> result = avl1.search_by_range(0,1000);
    //for (auto x:result) cout<<x<<" ";
    cout<<result.size()<<endl;

    cout<<avl1.size();

    //cout<<"Size: "<<s1.get_size();
    //cout<<endl<<s1.search("Lily");
    //avl1.displayPretty();
    
    cout<<"\nSize - fechas: "<<avl2.size()<<endl;
    vector <int> res = avl2.search_by_range(convertToUnixTimestamp("2001-01-01"),convertToUnixTimestamp("2004-01-01"));
    for (auto x:res) cout<<x<<" ";
    cout<<"Size: "<<res.size()<<endl;
    return 0;
}