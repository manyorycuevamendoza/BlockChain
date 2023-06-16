#ifndef NODE_BTREE_H
#define NODE_BTREE_H

#include <iostream>

template <typename TK, typename TV>
struct Entry
{
    TK key;
    TV value;

    Entry() {
        key = TK();
        value = TV();
    }

    Entry(TK k, TV v) {
        key = k;
        value = v;
    }

    bool same_key(Entry a) {
        return a.key == key;
    }

    friend std::ostream& operator<<(std::ostream& salida, Entry<TK, TV> e) {
        salida << e.key << " " << e.value;
        return salida;
    }
};

template <typename TK, typename TV>
struct Node {
    int degree;  // Degree of the B-tree
    Entry<TK, TV>* entries;  // Array de entries
    Node** children;  // Array of child pointers
    int count;  // Number of entries currently stored
    bool leaf;  // Indicator of leaf node

    Node(int deg, bool isLeaf = true)
        : degree(deg), entries(nullptr), children(nullptr), count(0), leaf(isLeaf)
    {
        entries = new Entry<TK, TV>[2 * degree - 1];
        children = new Node<TK, TV>*[2 * degree];
        for (int i = 0; i < 2 * degree; ++i)
            children[i] = nullptr;
    }

    void display() {
        for (int i = 0; i < count; ++i)
            std::cout << entries[i] << ", ";
        std::cout << std::endl;
    }

    ~Node() {
        delete[] entries;
        delete[] children;
    }
};

#endif  // NODE_BTREE_H
