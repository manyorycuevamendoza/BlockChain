<<<<<<< HEAD
=======
//realizando una hash table
>>>>>>> 995cecee05b84e5fc402997ee109f94d98fefc00
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "structs/avl/avl.h"
#include "structs/blockchain/blockchain.h"
//#include "structs/tabla_hash/chainhash.h"


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
    AVLTree2<int,int> avl;
    int count =0;
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::getline(ss, item, ',');
        //std::cout<< item<<" ,";
        std::getline(ss, item, ',');
        //std::cout << item << " ,";
        //monto
        std::getline(ss, item, ',');
        int number=stoi(item);

        avl.insert(count,number);

        //--fecha
        std::getline(ss, item, ',');
        count ++;
        //std::cout << item<<std::endl;

    }

    file.close();

    //avl.displayPretty();
    cout<<endl;
    vector <int> result = avl.search_by_range(0,5);
    for (auto x:result) cout<<x<<" ";





    return 0;
}