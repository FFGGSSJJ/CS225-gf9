//
//  test.cpp
//
//for testing the graph class
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.cpp"
using std::cout;
using std::cin;

int main()
{
    cout << "__________________________________________________________\n";
    cout << "|                                                        |\n";
    cout << "|           Test Cases For Assignment_8 Ex3              |\n";
    cout << "|                                                        |\n";
    cout << "|________________________________________________________|\n";
    cout << "\033[031m The code we write could judge arbitrary input graph\n";
    cout <<  " if it is bipartite by coloring its vertices\n\n\n\033[0m";

    bipartite_graph<int>* bi_graph3 = new bipartite_graph<int>;

    cout << "\033[33mWe insert several edges first: (1,4) (4,2) (1,6) (9,10) (11,12)\n\033[0m";
    bi_graph3->insert_edge(1,4);
    bi_graph3->insert_edge(4,2);
    bi_graph3->insert_edge(1,6);
    bi_graph3->insert_edge(9,10);
    bi_graph3->insert_edge(11,12);
    if(bi_graph3->ex3_perfect_match()) {
        cout << "Perfect Match!\n";
    } else {
        cout << "Not Perfect Match!\n";
    }
    bi_graph3->graph_all->vertices->display();

    cout << "\033[33mWe insert one more edge: (12,13)\n\033[0m";
    bi_graph3->insert_edge(12,13);
    if(bi_graph3->ex3_perfect_match()) {
        cout << "Perfect Match!\n";
    } else {
        cout << "Not Perfect Match!\n";
    }
    bi_graph3->graph_all->vertices->display();

    cout << "\033[33mWe insert one more edge: (13,14)\n\033[0m";
    bi_graph3->insert_edge(13,14);
    if(bi_graph3->ex3_perfect_match()) {
        cout << "Perfect Match!\n";
    } else {
        cout << "Not Perfect Match!\n";
    }
    bi_graph3->graph_all->vertices->display();

    cout << "\033[33mWe insert one more edge: (14,15)\n\033[0m";
    bi_graph3->insert_edge(14,15);
    if(bi_graph3->ex3_perfect_match() == 1) {
        cout << "Perfect Match!\n";
    } else {
        cout << "Not Perfect Match!\n";
    }
    bi_graph3->graph_all->vertices->display();


    bipartite_graph<int> *bi_graph = new bipartite_graph<int>;
    bipartite_graph<int> *bi_graph2 = new bipartite_graph<int>;

    cout << "__________________________________________________________\n";
    cout << "|                                                        |\n";
    cout << "|           Test Cases For Assignment_8 Ex4              |\n";
    cout << "|                                                        |\n";
    cout << "|________________________________________________________|\n";
    cout << "\033[031m The code we write could judge arbitrary input graph\n";
    cout <<  " if it is bipartite by coloring its vertices\n\n\n\033[0m";


    cout << "---- PART 1 ----\n";
    cout << "\033[33mWe insert several edges to judge if it is bipartite: (1,4) (6,2) (3,5) (9,10)\n\033[0m";
    bi_graph->insert_edge(1,4);
    bi_graph->insert_edge(6,2);
    bi_graph->insert_edge(3,5);
    bi_graph->insert_edge(9,10);
    bi_graph->insert_edge(11,12);
    bi_graph->insert_edge(12,13);
    cout<< "It is bipartite graph\n";
    bi_graph->graph_all->vertices->display();

    cout << "\033[33mWe insert several edges to judge if it is bipartite: (1,4) (6,2) (3,5) (5,6) (9,10)\n\033[0m";
    bi_graph->insert_edge(1,4);
    bi_graph->insert_edge(6,2);
    bi_graph->insert_edge(3,5);
    bi_graph->insert_edge(5,6);
    bi_graph->insert_edge(9,10);
    bi_graph->insert_edge(11,12);
    bi_graph->insert_edge(12,13);
    cout<< "It is bipartite graph\n";
    bi_graph->graph_all->vertices->display();

    cout << "\033[33mWe insert one more edge: (2,5)\n\033[0m";
    bi_graph->insert_edge(2,5);
    
    cout << "\n---- PART 2 ----\n";
    cout << "\033[33mWe insert several edges first: (1,4) (6,2) (3,5) (9,10) (11,12)\n\033[0m";
    bi_graph2->insert_edge(1,4);
    bi_graph2->insert_edge(6,2);
    bi_graph2->insert_edge(3,5);
    bi_graph2->insert_edge(9,10);
    bi_graph2->insert_edge(11,12);
    if(bi_graph2->ex4_perfect_match() == 1) {
        cout << "It is Perfect Match\n";
    } else {
        cout << "It is not Perfect Match\n";
    }
    bi_graph2->graph_all->vertices->display();
    cout << "\033[33mWe insert one more edge: (12,13)\n\033[0m";
    bi_graph2->insert_edge(12,13);
    if(bi_graph2->ex4_perfect_match() == 1) {
        cout << "It is Perfect Match\n";
    } else {
        cout << "It is not Perfect Match\n";
    }
    bi_graph2->graph_all->vertices->display();

    cout << "\033[33mWe insert one more edge: (13,14)\n\033[0m";
    bi_graph2->insert_edge(13,14);
    if(bi_graph2->ex4_perfect_match() == 1) {
        cout << "It is Perfect Match\n";
    } else {
        cout << "It is not Perfect Match\n";
    }
    bi_graph2->graph_all->vertices->display();

    cout << "\033[33mWe insert one more edge: (14,15)\n\033[0m";
    bi_graph2->insert_edge(14,15);
    if(bi_graph2->ex4_perfect_match() == 1) {
        cout << "It is Perfect Match\n";
    } else {
        cout << "It is not Perfect Match\n";
    }
    bi_graph2->graph_all->vertices->display();
    

}
