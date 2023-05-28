#include <iostream>
#include "avl.h"

using namespace std;

int main()
{
    AVLTree<int> *avl = new AVLTree<int>();
    //Insertar elementos
    avl->insert(35);
    avl->insert(30);
    avl->insert(27);
    avl->insert(11);
    avl->insert(16);
    avl->insert(10);
    avl->insert(50);
    avl->insert(91);
    avl->insert(73);
    avl->insert(5);

    //eliminar un elemento
   // int elementoAEliminar = 30;
   // avl->remove(elementoAEliminar);

    cout<<"isBalanced: "<<avl->isBalanced()<<endl;//1 si el arbol esta balanceado, 0 si no lo esta
    cout<<"height: "<<avl->height()<<endl;//altura del AVL
    cout<<"getInOrder: "<<avl->getInOrder()<<endl;//valores del AVL en orden ascendente: 5 11 16 27 30 35 50 73 91 100     
    
    avl->displayPretty();

    return 0;
}