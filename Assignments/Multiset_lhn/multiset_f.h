#include "multiset.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
using std::cout;
using std::cin;
using std::endl;
using std::hash;
using namespace std;

/* Put your implementation here */
//***********************************************************************


MultiSet_Chaining::MultiSet_Chaining(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new ch_node*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = NULL;
    }    
}


void MultiSet_Chaining::insertion(int key, Person_BP* people)
{
    hash<int> hashfunction;
    int index;
    index = hashfunction(key) % maxsize;
    ch_node* new_item = new ch_node(key);
    new_item->people_pt= people;

    if (reprarray[index] == NULL){
        reprarray[index] = new_item;
        numitems++;
        return;
    }
    ch_node* node = reprarray[index];
    while(node!=NULL){
        if (node->pointer_next == NULL){
            node->pointer_next=new_item;
            numitems++;
            return;
        }
        if (node->value==key){
            new_item->pointer_next = node->pointer_next;
            node->pointer_next = new_item;
            numitems++;
            return;
        }
        node = node->pointer_next;
    }
    cout<<"insertion bug";      
}

void MultiSet_Chaining::deletion(int key, Person_BP* people)
{
    hash<int> hashfunction;
    int index;
    index = hashfunction(key) % maxsize;
    if (reprarray[index] == NULL){
        cout<<key<<" is not in the hashtable";
        return;
    }
    ch_node* node = reprarray[index];
    if (node->value==key){
        reprarray[index]= node->pointer_next;
        numitems--;
        return;
    }
    while(node!=NULL){
        if ( node->pointer_next != NULL && (node->pointer_next)->value==key){
            (node->pointer_next) = (node->pointer_next)->pointer_next;
            numitems--;
            return;
        }
        node=node->pointer_next;
    }
    cout<<key<<" is not in the hashtable";
    return;
}

vector<Person_BP*> MultiSet_Chaining::retrieval(int key)
{
    vector<Person_BP*> vec;
    hash<int> hashfunction;
    int index;
    index = hashfunction(key) % maxsize;
    ch_node* node = reprarray[index];
    int count=0;
    cout<<"people of that key are: "; 
    while (node!=NULL){
        if (node->value==key){
            count++;
            vec.push_back(node->people_pt);            
        }
        node=node->pointer_next;
    }    
    return vec;
}

void MultiSet_Chaining::display_chaining(void) // only for test purposes
{
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == NULL){
        }
        else{
            cout << "The entry " << i + 1 << " is ";
            ch_node* node = reprarray[i];
            while(node != NULL){
                cout << node->value<<" ";
                node=node->pointer_next;
            }
            cout<<"\n";

        }
    }
    return;
}
ch_node::ch_node(int item)
{
    value = item;
    pointer_next=NULL;
    people_pt = NULL;
}