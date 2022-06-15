//
//  graph.h
//  
//
//  Created by KD on 11.04.21.
//

#ifndef graph_h
#define graph_h

#include <set>
using namespace::std;


template<class T> class vertexlist;

template<class T> class edgelist;

template<class T> class edge;

template<class T> class elist;

template<class T> class bipartite_graph;

template<class T> class vertex
{
    friend class vertexlist<T>;
public:
    vertex(T item = 0, vertex<T> *pt_next = 0, vertex<T> *pt_prev = 0);
    int numoutedges(void);  // number of edges a node contains
    T getitem(void);
    vertex<T> * getnext(void);
    vertex<T> * getprevious(void);
    elist<T> * getedges(void);
    void setitem(T item);
    void setnext(vertex<T> * pt_next);
    void setprevious(vertex<T> * pt_prev);
    void setedges(elist<T> * pt_edges);
    int color;
private:
    T vertexid;
    vertex<T> * next;
    vertex<T> * previous;
    elist<T> * edgelist;    // the edges go out of the vertex
};

// vertexlist is ued to store all vertexes
template<class T> class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    int countedges(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    bool remove(T item);
    void addedge(T first, T second);
    void removeedge(T first, T second);
    edgelist<T> * outgoingedges(T item);
    void prettyprint(void); // only for testing

    int color(vertex<T>* node, int color);
    void clear_color();
    vertex<T>* find_vertex(T item);
    vertex<T>* get_dummy();     // get dummy
    void set_dummy(vertex<T> *newdummy);
    void set_length(int len);
    void display();
private:
    vertex<T> * dummy;
    int numvertices;
};




template<class T> class neighbour
{
    friend class elist<T>;
public:
    neighbour(T item = 0, neighbour<T> * pt_next = 0, neighbour<T> * pt_prev = 0);
    T getitem(void);
    neighbour<T> * getnext(void);
    neighbour<T> * getprevious(void);
    void setitem(T item);
    void setnext(neighbour<T> * pt);
    void setprevious(neighbour<T> * pt);
private:
    T secondvertex;
    neighbour<T> * next;
    neighbour<T> * previous;
};

template<class T> class elist
{
public:
    elist(T item);
    int getlength(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    void remove(T item);
    void addall(T item, edgelist<T> * pt);
    // addded function for ex4
    neighbour<T>* first_v();
private:
    neighbour<T> * first;
    int length;
};

template<class T> class edge
{
    friend class edgelist<T>;
public:
    edge(T first, T second);
    T origin(void);
    T destination(void);
    void setorigin(T item);
    void setdestination(T item);
    void prettyprint(void); // only for testing
private:
    T firstitem;
    T seconditem;
};

template<class T> class edgelist
{
public:
    edgelist(void);
    int getnumedges(void);
    void add(T item1, T item2);
    void prettyprint(void); // only for testing
    edge<T>** get_alledges();

    // functions for ex3
    int find_path(T boy, T girl, edgelist<T> *path);    // find path boy->girl from the digraph generated before
    int contains(T item);   // check if certain vertex has been matched
    int contain_edge(T boy, T girl);    // check if certain match exists

private:
    edge<T> ** reprarray;
    int numedges;
};




template<class T> class graph
{
    friend class bipartite_graph<T>;
public:
    graph(void);
    int numvertices(void);
    int numedges(void);
    void addedge(T origin, T destination);
    void addvertex(T item);
    void deleteedge(T origin, T destination);
    void deletevertex(T item);
    edgelist<T> * outgoingedges(T item);
    void prettyprint(void); // only for testing
    
    vertex<T>* get_dummy();     // get dummy
//private:
    vertexlist<T> * vertices;
};

template<class T> class bipartite_graph
{
public:
    bipartite_graph();
    graph<T> *graph_all;

    int insert_edge(T origin, T destination);
    int insert_vertex(T item);
    int delete_edge(T origin, T destination);
    int delete_vertex(T item);
    edgelist<T> * incident_edges(T item);

    // functions for ex3 
    int ex3_perfect_match(void);      // perfect matching function for ex3
    edgelist<T>* digraph(vertexlist<T> *boys, vertexlist<T> *girls);    // generate digraph, which stores all edges in a graph

    // functions for ex4
    int ex4_perfect_match(void); // perfect matching function for ex4 (Hall Theorem)
    // two vertices list seperated in the bipartite_graph
    vertexlist<T> * v1;
    vertexlist<T> * v2;
    vertexlist<T> * not_bi;  // vertices that dose not have a edge yet
private:
    int decide_tree(vertex<T> *current, vertexlist<T> *list, int layer, int edge_len, int sub_len);
    int separate();    // function used to separate the vertices into two lists
    
};

#endif /* graph_h */
