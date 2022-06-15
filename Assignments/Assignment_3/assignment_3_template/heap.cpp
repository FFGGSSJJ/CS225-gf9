#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "heap.h"
using std::cout;
using std::cin;

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index >= 0) && (index < numitems))
    {
        reprarray[index] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index >= 0) && (index < numitems))
    {
        return reprarray[index];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index < numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool AList<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool AList<T>::equal(AList<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool AList<T>::sublist(AList<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                ++j;
    }
    return result;
}

//build the max heap using elements in the input array.
template<class T> void MaxHeap<T>::build_heap(AList<T> &array){
    //put your code below

    for (int i = 0; (i < array.getlength()) && (this->getlength() < array.getlength()); i++) 
        this->append (array[i]);    // copy the numbers in input array into the heap

    int mid = this->getlength()/2;
    for (int i = mid; i >= 0; i--) {
        sift_down(i, this->getlength());    // build max_heap using sift_down
    }
    
}

//sift down the element with index i within the first num_elements elements.
template<class T> void MaxHeap<T>::sift_down(int i, int num_elements){
    //put your code below
    int root = i;   // root index
    int left = 2*i + 1;     // left_child index
    int right = 2*i + 2;    // right_child index

    if ((left < num_elements) && (this->getitem(root) < this->getitem(left)))   root = left; 
    if ((right < num_elements) && (this->getitem(root) < this->getitem(right))) root = right;
    
    if (root != i) {
        swap(i, root);  // swap the biggest child with the root
        sift_down(root, num_elements);
    } return;
}

template<class T> void MaxHeap<T>::heap_sort(AList<T> &array){
    //put your code below
    build_heap(array);  // now a max_heap has been built
    for (int i = this->getlength() - 1; i >= 0; i--) {
        swap(0, i);     // swap the max top element with the bottom 
        sift_down(0, i);    // keep sift down to keep the propert of the max_heap
    }
}
/*template<class T> void MaxHeap<T>::sift_up(int i){
    int child = i;
    int parent = (i-1)/2;

    if ((parent >= 0) && (this->getitem(parent) < this->getitem(child))) {
        swap(child, parent);
        sift_up(parent);
    } return;
}

template<class T> void MaxHeap<T>::insert_lists(AList<T> &array){
    for (int i = 0; i < array.getlength(); i++){
        
    }
}*/

//sort the input array using max heap.


//swap elements with indices i and j.
template<class T> void MaxHeap<T>::swap(int i, int j){
    //put your code below 
    T temp = this->getitem(i);
    this->setitem(i, this->getitem(j));
    this->setitem(j, temp);
}

//return the root element. 
template<class T> T MaxHeap<T>::max(){
    //put your code below
    return this->getitem(0);
}

//print all elements in the heap in sequential order.
template<class T> void MaxHeap<T>::print_elements(){

    int n = this->getlength();
    cout << "[ ";
    for (int i=0; i<n; i++){
        cout << this->getitem(i) << " ";
    } cout << "]";
}

int main(){

    cout << "\npart1 test\n";
    //please feel free to add more test cases
    int input_list[8] = {9,8,7,3,-987,4356,3,4};
    AList<int> input_array;
    for (int i=0; i<8; i++){
        input_array.append(input_list[i]);
    }
    MaxHeap<int> max_heap;
    max_heap.build_heap(input_array);
    cout<< max_heap.max() << "\n\n";
    max_heap.print_elements();
    max_heap.heap_sort(input_array);
    max_heap.print_elements();

    cout << "\npart2 test\n";
    //please feel free to add more test cases
    int input_list_2[15] = {55, 32, 9, 46, 15, 22, 91, 18, 29, 77, 32, 16, 791, 45, 32};
    AList<int> input_array_2;
    for (int i=0; i<15; i++){
        input_array_2.append(input_list_2[i]);
    }
    MaxHeap<int> max_heap_2;
    max_heap_2.heap_sort(input_array_2);
    max_heap_2.print_elements();

    return 0;
}
