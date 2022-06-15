#include "multiset_f.h"


int main(){
    /******************* Put your own test here *******************/
    /* Your are expected to give adequate test to show the correctness of your implementation */
    /* Otherwise you may be deducted points */
    
    int input1[] = {1,1,1,21,21,21,3,3,7,6,6};
    int input2[] = {41,41,21,21,3,3,3,7,7,21,21};

    MultiSet<int> test1 = MultiSet<int>(20);
    MultiSet<int> test4 = MultiSet<int>(20);
    MultiSet<int> temp;

    MultiSet_Chaining <int> test2 = MultiSet_Chaining<int>(20);

    MultiSet_Chaining<int> test3 = MultiSet_Chaining<int>(20);
    
    cout << "################### Insertion test ############################" << endl;
    for(int i = 0; i < 15; i++){
        for (int j = 0; j < i; j++) {
            test1.insertion(j);
            test4.insertion(2*j);
        }
    }
    cout << "Multiset_1:" << endl;
    test1.display();
    cout << "\n\n\n";
    cout << "Multiset_2:" << endl;
    test4.display();

    cout << "\n\n################ Union test #####################" << endl;
    cout << "Union of the Multiset1 and Multiset2:\n";
    test1.setunion(test4);
    test1.display();


    cout << "\n\n################ Intersection test #####################" << endl;
    cout << "The intersected elements are:\n";
    test1.intersection(test4);
    

    cout << "\n\n################ Difference test #####################" << endl;
    cout << "The elements with different number are:" << endl;
    temp = test1.difference(test4);
    temp.display();

    


    

    /*for (auto i: input1){
        test3.insertion(i);
    }
    test3.setunion(test2);
    test3.display_chaining();*/



    /* Test for part(ii) */
    return 0;
}