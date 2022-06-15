/* Put your decleration here */
#include <vector> 

class ch_node{
    public:
        
        ch_node(int key);
        Person_BP* people_pt;
        int value;
        ch_node *pointer_next;
};



class MultiSet_Chaining{
    public:
        MultiSet_Chaining(int size = 20);
        /* You should add other functions to make the structure work  */
        /* The following is required for this assignment */
        /* It is not complete, you should design the APIs by yourself */
        void insertion(int key, Person_BP* people);
        void deletion(int key, Person_BP* people);
        vector<Person_BP*> retrieval(int key);
        void display_chaining(void);

    private:
        int maxsize;
        int numitems;
        ch_node**reprarray;

};
