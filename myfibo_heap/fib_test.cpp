#include "fibheap_f.cpp"

int main(){

    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */
    Fib_Heap<int> fib = 20;
    Fib_Heap<int> fib2 = 10;

    fib.insert(8);
    fib.insert(7);
    fib.insert(9);
    fib.insert(6);
    fib.insert(4);
    fib.insert(3);
    fib.insert(2);
    fib.insert(1);

    fib.insert(0);
    fib.display();
    cout << fib.min_node->value << endl;
    fib.consolidate();
    fib.display();

    fib2.insert(11);
    fib2.insert(12);
    fib.fib_union(fib2);
    //fib.display();
    


    return 0;
}