
#include <iostream>
#include <vector>
#include <ctime>
#include "btree.h"
using namespace std;

int main(){
    cout<<"BTree\n";
    srand(time(nullptr));
    cout<<"Creando arbol\n";
    BTree<int>* btree = new BTree<int>(3);

    /*
    vector<int> elements;
    for(int i=0;i<55;i++){
        int k = 1 + rand() % 100;
        elements.push_back(k);
        btree->insert(k);
    }
    */
   cout<<"Insertando elementos\n";
   cout<<"Insertando 2\n"; btree->insert(2); 
    cout<<"Insertando 4\n";btree->insert(4); 
    cout<<"Insertando 3\n"; btree->insert(3); 
    cout<<"Insertando 7\n"; btree->insert(7);
    cout<<"Insertando 9\n"; btree->insert(9); 
    cout<<"Insertando 11\n"; btree->insert(11); 
    cout<<"Insertando 13\n"; btree->insert(13); 
    cout<<"Insertando 1\n"; btree->insert(1); 
    cout<<"Insertando 0\n"; btree->insert(0); 
    cout<<"Insertando 80\n"; btree->insert(80); 
    cout<<"Insertando 90\n"; btree->insert(90); 
    cout<<"Insertando 95\n"; btree->insert(95);
    cout<<"Insertando 105\n"; btree->insert(105); 
    cout<<"Insertando 5\n"; btree->insert(5); 
    cout<<"Insertando 6\n"; btree->insert(6);


    btree->display_pretty();

    /*
    for(int i=0;i<3;i++){
        int k = elements[rand()%elements.size()];
        cout<<"\nEliminar "<<k<<"\n";
        btree->remove(k);
        btree->display_pretty();
    }
    */

    return 0;
}