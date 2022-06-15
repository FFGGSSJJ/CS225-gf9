/* Put your decleration here */
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace::std;

template<class T> class Node
{
    public:
        Node();
        T value;        //key value of the node
        int degree;     //number of childs
        
        // two sibling nodes, initially as NULL;
        Node<T> *right;
        Node<T> *left;
        // parent and chile nodes
        Node<T> *parent;
        Node<T> *child;

};

template<class T> Node<T>::Node()
{
    value = degree = 0;     // initialize as 0
    right = left = parent = child = NULL;    // initialize as NULL
}




template<class T> class Fib_Heap
{
    public:
        Fib_Heap(int size);
        /* You should add other functions to make the structure as Fibonacci heap  */
        /* It is part of computing assignment, so we would not provide the basic implementation for you */
        Node<T>* min_node;      // the minmum root node in the heap;
        Node<T>* insert(T val);
        void fib_union(Fib_Heap<T> fib);
        void consolidate();
        Node<T>* root_link(Node<T>* p, Node<T>* c);   // work for consolidating
        void decrease_key(T keyval, T newkey); // decrease the key val of an node with keyval
        void extract_min();
        void display();

        /* The following is required for this assignment */
        /* It is not complete, you should design the API by yourself */
        void Change_Key(T keyval, T newkey);    // increase or decrease a node's key value
        void Prune(Node<T> r);
    
        int root_num;
        int node_num;
        int handle_size;   // size of handle list
        Node<T> *root_list;    // root list;
        Node<T> **handle_list;     // list used to store the pointer of the node
        hash<T> hashfunc;   // function used for hash the handle

};

template<class T> Fib_Heap<T>::Fib_Heap(int size)
{
    min_node = new Node<T>;
    node_num = root_num = 0;
    handle_size = size;
    if (handle_size < 10)  handle_size = 10;
    
    handle_list = new Node<T> *[handle_size];
    for (int i = 0; i < handle_size; i++) {
        handle_list[i] = NULL;
    }
}