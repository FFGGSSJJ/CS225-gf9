#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include "fibheap.h"
using namespace::std;


template<class T> void Fib_Heap<T>::display()
{
    Node<T> *temp = root_list;
    for (int i = 0; i < root_num; i++, temp = temp->right) {
        cout << temp->left->value << "<->" << temp->value << "<->" << temp->right->value << " ";
        cout << "degree = " << temp->degree << "  ";
        if (temp->degree > 0) {
            Node<T> *temp2 = temp->child;
            for (int j = 0; j < temp->degree; j++) {
                cout << temp2->left->value << "<->" << temp2->value << "<->" << temp2->right->value << " ";
                cout << "child degree:" << temp2->degree << " ";
                temp2 = temp2->right;
            }
        }
        cout << "\n";
    } cout << "\n";

}

template<class T> Node<T>* Fib_Heap<T>::insert(T val)
{
    Node<T> *newnode = new Node<T>;
    Node<T> *temp;
    int index = hashfunc(val)%handle_size;

    newnode->value = val;
    newnode->degree = 0;
    temp = handle_list[index];
    while (temp != NULL) {
        temp = handle_list[index];
        if (temp->value != val)     index = (index+1)%handle_size;
        else if (temp->value == val)    return temp;    // node already exists
    }
    handle_list[index] = newnode;   // add this node's pointer into the handle list
    node_num++;
    root_num++;
    

    if (root_num == 1) {
        root_list = newnode;    //only one node in the root list;
        newnode->right = newnode;
        newnode->left = newnode;
        min_node = newnode;
    } else {
        newnode->left = root_list;
        newnode->right = root_list->right;
        root_list->right->left = newnode;
        root_list->right = newnode;
    }

    if (newnode->value < min_node->value)       // compare with current minimum root
        min_node = newnode; // change the min_node
    return newnode;
}


template<class T> void Fib_Heap<T>::fib_union(Fib_Heap<T> fib)
{
    Node<T> *temp = fib.root_list;
    
    for (int i = 0; i < fib.root_num; i++) {
        Node<T> *union_node;
        union_node = insert(temp->value);
        union_node->child = temp->child;
        union_node->degree = temp->degree;
        temp = temp->right;
    }
}

template<class T> void Fib_Heap<T>::consolidate()
{
    Node<T> **check_list = new Node<T>*[root_num];
    Node<T> *temp = root_list;
    int degree, original_size = root_num;
    T min_val;
    for (int i = 0; i < root_num; i++)
        check_list[i] = NULL;
    for (int i = 0; i < original_size*2; i++){
        Node<T> *current;
        degree = temp->degree;
        current = check_list[degree];
        if (NULL == current) {
            check_list[degree] = temp;
        }
        else if (NULL != current && root_num > 1 && current->value != temp->value){
            temp = root_link(temp, current);    // link root nodes with same degree and decrease the root_num
            root_list = temp;   // keep updating root_list
            display();
            check_list[degree] = NULL;
        }
        temp = temp->right;
       
    } 
    for (temp = root_list->right, min_val = root_list->value; temp != root_list; temp = temp->right) {
        if (temp->value < min_val)      // search for the minimum root node in modified root list
            min_node = temp;
    }
}

template<class T> Node<T>* Fib_Heap<T>::root_link(Node<T>* p, Node<T>* c)
{
    Node<T> *parent;
    Node<T> *child;

    if (p->value >= c->value) { // determine which to be parent and which to be child
        parent = c;
        child = p;
    } else {
        parent = p;
        child = c;
    }

    if (parent->degree == 0) {  // if no child exists, just link the child to parent
        parent->child = child;
        child->parent = parent; // link the child and parent directly
        child->left->right = child->right;
        child->right->left = child->left;   // link the child's original right and left sibling in root list
        child->left = child->right = child; // as only one child exists, link itself;
        parent->degree++; 
        root_num--;
    } else {
        child->parent = parent;     // link child to parent first
        child->left->right = child->right;
        child->right->left = child->left;   // link the child's original right and left sibling in root list
        child->left = parent->child;
        child->right = parent->child->right;    // link the child's right and left to the child list of the parent
        parent->child->right->left = child; 
        parent->child->right = child;   
        parent->degree++;
        root_num--;
    } return parent;
}

