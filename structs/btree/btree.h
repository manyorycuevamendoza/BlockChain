#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include "node.h"

using namespace std;

template <typename TK>
class BTree
{
private:
    Node<TK> *root;
    int M; // grado u orden del arbol

    struct ExtractionResult
    {
        TK key;
        Node<TK> *right_tree;
        Node<TK> *left_tree;

        ExtractionResult() : left_tree(nullptr), right_tree(nullptr) {}

        ExtractionResult(TK _k, Node<TK> *_left_tree, Node<TK> *_right_tree) : key(_k), left_tree(_left_tree),
                                                                               right_tree(_right_tree) {}
    };

public:
    BTree(int _M) : M(_M), root(nullptr) {}

    bool search(TK key)
    {
        return search(root, key);
    }

    void insert(TK key)
    {
        if (root == nullptr)
        {
            root = new Node<TK>(M, true);
            root->keys[0] = key;
            root->count = 1;
        }
        else
        {
            ExtractionResult *split_result = insert(root, key);
            if (split_result != nullptr)
            {
                Node<TK> *parent = new Node<TK>(M, false);
                parent->keys[0] = split_result->key;
                parent->children[0] = root;
                parent->children[1] = split_result->right_tree;
                parent->count = 1;
                root = parent;
            }
        }
    }

    void remove(TK key)
    {
			if(root != nullptr){
        remove(root, key);
        if (root->count == 0)
        {
            Node<TK> *temp = root;
            root = root->children[0];
            delete temp;
        }
			}
    }

    int height()
    {
        if (this->root == nullptr)
            return -1;
        Node<TK> *node = this->root;
        int h = 0;
        while (!node->leaf)
        {
            node = node->children[0];
            h++;
        }
        return h;
    }

    // inorder
    string toString(string sep)
    { 
        return toString(root, sep);
    }

    void display_pretty()
    {
        display_tree(root);
    }

    // liberar memoria
    ~BTree()
    {
        if (root != nullptr)
            root->killSelf();
    }

private:
    string toString(Node<TK> *node, string sep)
    { // inorder
        if (node == nullptr)
            return "";
        string result = "";
        int i;
        for (i = 0; i < node->count; i++)
        {
            // se busca por la rama izquierda
            if (!node->leaf)
                result += toString(node->children[i], sep);
            // luego se concantena la key
            result += std::to_string(node->keys[i]) + sep;
        }
        // al final, se recorre el ultimo hijo
        if (!node->leaf)
            result += toString(node->children[i], sep);
        return result + "";
    }

    bool search(Node<TK> *node, TK key)
    {
        // se ubica la key coicidente
        int i = 0;
        while (i < node->count && key > node->keys[i])
            i++;
        if (node->keys[i] == key)
            return true;
        else if (node->leaf)
            return false;
        else
            return search(node->children[i], key);
    }

    ExtractionResult *insert(Node<TK> *&node, TK key)
    {
        int i;

        // verificar si es llave repetida
        i = 0;
        while (i < node->count && key > node->keys[i])
            i++;
        if (i < node->count && node->keys[i] == key)
            return nullptr;

        // es nodo hoja
        if (node->leaf)
        {
            // si la hoja tiene espacio, insertar
            if (node->count < M - 1)
                relocate(node, key);
            // dividir y retornar el resultado al antecesor
            else if (M % 2 == 0)
                return split_par(node, key);
            else
                return split_impar(node, key);
        }
        // es nodo interno
        else
        {
            // insertar en el hijo respectivo
            ExtractionResult *split_result = insert(node->children[i], key);
            // si split_result != null es porque se produjo un split en el children[i]
            if (split_result != nullptr)
            {
                // si hay espacio, reubicar el split_result
                if (node->count < M - 1)
                    relocate_right(node, split_result->key, split_result->right_tree);
                // caso, dividir y retornar el nuevo nodo al antecesor
                else if (M % 2 == 0)
                    return split_par(node, split_result->key, split_result->right_tree);
                else
                    return split_impar(node, split_result->key, split_result->right_tree);
            }
        }
        return nullptr;
    }

    void relocate(Node<TK> *&node, TK key)
    {
        int i = node->count - 1;
        // se  mueve las keys para dejar espacio para la nueva key
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        i++;
        node->keys[i] = key;
        node->count++;
    }

    void relocate_right(Node<TK> *&node, TK key, Node<TK> *right_tree)
    {
        int i = node->count - 1;
        // se  mueve las keys y children para dejar espacio para la nueva key
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            node->children[i + 2] = node->children[i + 1];
            i--;
        }
        i++;
        node->keys[i] = key;
        node->children[i + 1] = right_tree;
        node->count++;
    }

    void relocate_left(Node<TK> *&node, TK key, Node<TK> *left_tree)
    {
        int i = node->count - 1;
        // se  mueve las keys y children para dejar espacio para la nueva key
        while (i >= 0 && key < node->keys[i])
        {
            node->keys[i + 1] = node->keys[i];
            node->children[i + 2] = node->children[i + 1];
            i--;
        }
        node->children[i + 2] = node->children[i + 1];
        i++;
        node->keys[i] = key;
        node->children[i] = left_tree;
        node->count++;
    }

    Node<TK> *generate_right_node(Node<TK> *&node, int from)
    {
        Node<TK> *right_node = new Node<TK>(M, node->leaf);
        // copiar llaves e hijos desde el nodo original
        int i = from, j = 0;
        while (i < M - 1) // recordar que el nodo esta lleno
        {
            right_node->keys[j] = node->keys[i];
            right_node->children[j] = node->children[i];
            i++;
            j++;
        }
        right_node->children[j] = node->children[i];
        right_node->count = j;
        return right_node;
    }

    ExtractionResult *split_par(Node<TK> *&node, TK key, Node<TK> *right_tree = nullptr)
    {
        // calcular el elemento central
        int m = (M - 1) / 2;
        TK middle = node->keys[m];
        // crear nodo derecho desde m+1
        Node<TK> *right_node = generate_right_node(node, m + 1);
        // actualizar la cantidad de elementos del nodo
        node->count = m;
        // insertar la key en el lado respectivo
        if (key < middle)
            relocate_right(node, key, right_tree);
        else
            relocate_right(right_node, key, right_tree);
        // retornar el elemento central y el nodo derecho
        return new ExtractionResult(middle, nullptr, right_node);
    }

    ExtractionResult *split_impar(Node<TK> *&node, TK key, Node<TK> *right_tree = nullptr)
    {
        Node<TK> *right_node;
        TK middle;
        // calcular el elemento central correctamente
        int m = (M - 1) / 2;
        if (key > node->keys[m])
        {
            right_node = generate_right_node(node, m + 1);
            middle = node->keys[m];
            node->count = m;
            relocate_right(right_node, key, right_tree);
        }
        else
        {
            m = m - 1;
            right_node = generate_right_node(node, m + 1);
            if (key < node->keys[m])
            {
                middle = node->keys[m];
                node->count = m;
                relocate_right(node, key, right_tree);
            }
            else
            { // en caso que la llave a insertar ocupe la mitad
                middle = key;
                node->count = m + 1;
                right_node->children[0] = right_tree;
            }
        }
        // retornar el elemento central y el nodo derecho
        return new ExtractionResult(middle, nullptr, right_node);
    }

    void remove(Node<TK> *&node, TK key)
    {
        // hallar la posicion de la llave
        int i = 0;
        while (i < node->count && key > node->keys[i])
            i++;

        // nodo hoja
        if (node->leaf)
        {
            // caso 0: si la key se encuentra en la hoja, retirarlo
            if (i < node->count && node->keys[i] == key)
                popElement(node, i);
        }
        // nodo interno
        else
        {
            // caso 3: reeamplazar por el sucesor y eliminar en el hijo derecho
            if (i < node->count && node->keys[i] == key)
            {
                key = minKey(node->children[i + 1]); // traer el sucesor
                node->keys[i] = key;                 // reemplazar como nueva llave
                i = i + 1;                           // eliminar sucesor en el hijo derecho
            }
            remove(node->children[i], key);

            // verificar propiedad del minimo
            if (node->children[i]->count < (M - 1) / 2)
            {
                ExtractionResult extract_result;
                // caso 1: rotar con el hijo izquierdo children[i-1]
                if (i > 0 && node->children[i - 1]->count > (M - 1) / 2)
                {
                    // retirar el ultimo elemento del nodo izquierdo
                    extract_result = extractLast(node->children[i - 1]);
                    // insertar la llave del padre en el nodo derecho
                    relocate_left(node->children[i], node->keys[i - 1], extract_result.right_tree);
                    // subir el ultimo elemento del nodo izquierdo hacia el padre
                    node->keys[i - 1] = extract_result.key;
                }
                // caso 1: rotar con el hijo derecho children[i+1]
                else if (i < node->count && node->children[i + 1]->count > (M - 1) / 2)
                {
                    // retirar el primer elemento del nodo derecho
                    extract_result = extractFirst(node->children[i + 1]);
                    // insertar la llave del padre en el nodo izquierdo
                    relocate_right(node->children[i], node->keys[i], extract_result.left_tree);
                    // subir el primer elemento del nodo derecho hacia el padre
                    node->keys[i] = extract_result.key;
                }
                // caso 2: join con el hijo izquierdo
                else if (i > 0)
                {
                    // pasamos del children[i] hacia children[i-1]
                    join(node->children[i - 1], node->keys[i - 1], node->children[i]);
                    // liberamos children[i]
                    delete node->children[i];
                    // quitamos la llave del padre
                    popElement(node, i - 1);
                }
                // caso 2: join con el hijo derecho
                else
                {
                    // pasamos del children[i+1] hacia children[i]
                    join(node->children[i], node->keys[i], node->children[i + 1]);
                    // liberamos children[i+1]
                    delete node->children[i + 1];
                    // quitamos la llave del padre
                    popElement(node, i);
                }
            }
        }
    }

    TK minKey(Node<TK> *node)
    {
        while (!node->leaf)
            node = node->children[0];
        return node->keys[0];
    }

    ExtractionResult extractLast(Node<TK> *&node)
    {
        ExtractionResult result;
        result.key = node->keys[node->count - 1];
        result.right_tree = node->children[node->count];
        node->count--;
        return result;
    }

    ExtractionResult extractFirst(Node<TK> *&node)
    {
        ExtractionResult result;
        result.key = node->keys[0];
        result.left_tree = node->children[0];
        int i = 0;
        for (; i < node->count - 1; i++)
        {
            node->keys[i] = node->keys[i + 1];
            node->children[i] = node->children[i + 1];
        }
        node->children[i] = node->children[i + 1];
        node->count--;
        return result;
    }

    void popElement(Node<TK> *&node, int pos)
    {
        int i = pos;
        for (; i < node->count - 1; i++)
        {
            node->keys[i] = node->keys[i + 1];
            node->children[i + 1] = node->children[i + 2];
        }
        node->count--;
    }

    void join(Node<TK> *&left_nodo, TK middle, Node<TK> *&right_node)
    {
        relocate_right(left_nodo, middle, right_node->children[0]);
        for (int i = 0; i < right_node->count; ++i)
            relocate_right(left_nodo, right_node->keys[i], right_node->children[i + 1]);
    }

    void display_tree(Node<TK> *node, string indent = " ", bool last = true)
    {
        cout << indent;
        if (last)
        {
            cout << "-";
            indent += "  ";
        }
        else
        {
            cout << "-";
            indent += "| ";
        }
        int j;
        cout << "[";
        for (j = 0; j < node->count - 1; j++)
            cout << node->keys[j] << ",";
        cout << node->keys[j];
        cout << "]";
        cout << endl;
        if (!node->leaf)
        {
            for (j = 0; j <= node->count; j++)
                display_tree(node->children[node->count - j], indent, j == node->count);
        }
    }

};

#endif