
//realizando una hash table
#include <iostream>
#include <string>
#include "SHA256.h"
#include "lectura.h"

using namespace std;

int main(){
        /*
                string s = "hello world";
        SHA256 sha;
        sha.update(s);
        uint8_t * digest = sha.digest();

        std::cout << SHA256::toString(digest) << std::endl;

        delete[] digest; 
        return 0;
        */

       readCSV("test1.csv");
        return 0;
}