#include "BPlus_tree.cpp"


int main()
{
    CBPlusTree* bptree = new CBPlusTree();
    bptree->insert(0, 2);
    bptree->insert(1, 1);
    bptree->insert(21, 21);
    bptree->insert(4, 4);
    bptree->insert(23, 23);
    bptree->insert(5, 5);
    //bptree->insert(5, 5);
    bptree->print();
    if(bptree->search(12))  cout << "TRUE\n";
}