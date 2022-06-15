//
//  graph.cpp
//  
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.h"
using std::cout;

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template<class T> vertex<T>::vertex(T item, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    edgelist = 0;
    color = 0;
}

template<class T> int vertex<T>::numoutedges(void)
{
    if (edgelist != 0)
        return (*edgelist).getlength();
    return 0;
}

template<class T> T vertex<T>::getitem(void)
{
    return vertexid;
}

template<class T> vertex<T> * vertex<T>::getnext(void)
{
    return next;
}

template<class T> vertex<T> * vertex<T>::getprevious(void)
{
    return previous;
}

template<class T> elist<T> * vertex<T>::getedges(void)
{
    return edgelist;
}

template<class T> void vertex<T>::setitem(T item)
{
    vertexid = item;
    return;
}

template<class T> void vertex<T>::setnext(vertex<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void vertex<T>::setprevious(vertex<T> *pt_prev)
{
    previous = pt_prev;
    return;
}

template<class T> void vertex<T>::setedges(elist<T> *pt_edges)
{
    edgelist = pt_edges;
    return;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template<class T> vertexlist<T>::vertexlist(void)
{
    dummy = new vertex<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

template<class T> int vertexlist<T>::getlength(void)
{
    return numvertices;
}

/* For counting edges we must add up the counts of outgoing edges for each vertex */
template<class T> int vertexlist<T>::countedges(void)
{
    int count = 0;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        count = count + (*pt).numoutedges();
        pt = (*pt).getnext();
    }
    return count;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. */
template<class T> void vertexlist<T>::append(T item)
{
    vertex<T> * pt_last = (*dummy).getprevious();
    vertex<T> * pt_new = new vertex<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template<class T> void vertexlist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template<class T> bool vertexlist<T>::contains(T item)
{
    bool result = false;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

/* In order to remove a vertex we have to find it in the list of vertices. If it has a non-empty list of neighbours, it cannot be deleted. It cannot be deleted, if it appwars in any edgelist. */
template<class T> bool vertexlist<T>::remove(T item)
{
    bool result = false;
    vertex<T> * location = 0;
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            if ((*pt).getedges() != 0)
            {
                cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
                return result;
            }
            /* We may be able to delete the vertex at location pt, but we still have to check other edgelists. Therefore pt is stored in location. */
            location = pt;
            continue;
        }
        elist<T> * edges = (*pt).getedges();
        if (edges != 0 && (*edges).contains(item) == true)
            /* it is appears in an edgelist, there is no delete. */
        {
            cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
            return result;
        }
        pt = (*pt).getnext();
    }
    /* Finally, we get to the deletion from the veertexlist. */
    if (location != 0)
    {
        result = true;
        vertex<T> * pt_prev = (*location).getprevious();
        vertex<T> * pt_next = (*location).getnext();
        (*pt_prev).setnext(pt_next);
        (*pt_next).setprevious(pt_prev);
        --numvertices;
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, 
then inserting the destination vertex into the associated edgelist. */
template<class T> void vertexlist<T>::addedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second);
            else
            {
                elist<T> * newlist = new elist<T>(second);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first);
    pt = (*dummy).getprevious();
    elist<T> * newlist = new elist<T>(second);
    (*pt).setedges(newlist);
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template<class T> void vertexlist<T>::removeedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
            {
                (*pt_edges).remove(second);
                if ((*pt_edges).getlength() == 0)
                    (*pt).setedges(0);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

/* To build list of outgoing edges for a given vertex, a new edge sequence is created for the output, then by scanning the associated edgelist edges (pairs of vertices) are added one by one. */
template<class T> edgelist<T> * vertexlist<T>::outgoingedges(T item)
{
    edgelist<T> * result = new edgelist<T>;
    vertex<T> * ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {   
        if ((*ptv).getitem() == item)
        {
            elist<T> * edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addall(item, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

template<class T> edge<T>** edgelist<T>::get_alledges()
{
    return reprarray;
}




/* only for testing */
template<class T> void vertexlist<T>::prettyprint(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T> * pte = outgoingedges((*ptv).getitem());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, 
but the are no assiciated edgelists. The elements of the list are organised by the neighbour class. */
template<class T> neighbour<T>::neighbour(T item, neighbour<T> *pt_next, neighbour<T> *pt_prev)
{
    secondvertex = item;
    next = pt_next;
    previous = pt_prev;
}

template<class T> T neighbour<T>::getitem(void)
{
    return secondvertex;
}

template<class T> neighbour<T> * neighbour<T>::getnext(void)
{
    return next;
}

template<class T> neighbour<T> * neighbour<T>::getprevious(void)
{
    return previous;
}

template<class T> void neighbour<T>::setitem(T item)
{
    secondvertex = item;
    return;
}

template<class T> void neighbour<T>::setnext(neighbour<T> * pt)
{
    next = pt;
    return;
}

template<class T> void neighbour<T>::setprevious(neighbour<T> * pt)
{
    previous = pt;
    return;
}

/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) 
associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */

// added function for ex4
template<class T> neighbour<T>* elist<T>::first_v()
{
    return first;
}


template<class T> elist<T>::elist(T item)
{
    first = new neighbour<T>;
    (*first).setitem(item);
    length = 1;
    (*first).setnext(first);
    (*first).setprevious(first);
}

template<class T> int elist<T>::getlength(void)
{
    return length;
}

template<class T> void elist<T>::append(T item)
{
    neighbour<T> * pt_last = (*first).getprevious();
    neighbour<T> * pt_new = new neighbour<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template<class T> void elist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

template<class T> bool elist<T>::contains(T item)
{
    bool result = false;
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

template<class T> void elist<T>::remove(T item)
{
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            neighbour<T> * pt_prev = (*pt).getprevious();
            neighbour<T> * pt_next = (*pt).getnext();
            (*pt_prev).setnext(pt_next);
            (*pt_next).setprevious(pt_prev);
            --length;
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}
/* The function addall adds all pairs with the given item and the list members, i.e. all outgoing edges to the list given by the pointer pt. It exploit the function add on edgelists. */
template<class T> void elist<T>::addall(T item, edgelist<T> *pt)
{
    neighbour<T> * pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, (*pte).getitem());
        pte = (*pte).getnext();
    }
    return;
}

/* Edges are simply pairs of vertices with obvious get and set functions. */
template<class T> edge<T>::edge(T first, T second)
{
    firstitem = first;
    seconditem = second;
}

template<class T> T edge<T>::origin(void)
{
    return firstitem;
}

template<class T> T edge<T>::destination(void)
{
    return seconditem;
}

template<class T> void edge<T>::setorigin(T item)
{
    firstitem = item;
    return;
}

template<class T> void edge<T>::setdestination(T item)
{
    seconditem = item;
    return;
}

/* only for testing */
template<class T> void edge<T>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ") + ";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes. */
template<class T> edgelist<T>::edgelist(void)
{
    reprarray = new edge<T>*[100];
    numedges = 0;
}

template<class T> int edgelist<T>::getnumedges(void)
{
    return numedges;
}

template<class T> void edgelist<T>::add(T item1, T item2)
{
    edge<T> * newedge = new edge<T>(item1,item2);
    reprarray[numedges] = newedge;
    ++numedges;
    return;
}

template<class T> void edgelist<T>::prettyprint(void)
{
    for (int i = 0; i < numedges; i++)
    {
        edge<T> * pte = reprarray[i];
        (*pte).prettyprint();
    }
    cout << "\n      --------\n";
    return;
}

/* A graph object just contains a pointer to a vertexlist. */
template<class T> graph<T>::graph(void)
{
    vertices = new vertexlist<T>;
}

template<class T> int graph<T>::numvertices(void)
{
    return (*vertices).getlength();
}

template<class T> int graph<T>::numedges(void)
{
    return (*vertices).countedges();
}

template<class T> void graph<T>::addedge(T origin, T destination)
{
    (*vertices).addedge(origin, destination);
    (*vertices).addedge(destination, origin);
    return;
}

template<class T> void graph<T>::addvertex(T item)
{
    (*vertices).addvertex(item);
    return;
}

template<class T> void graph<T>::deleteedge(T origin, T destination)
{
    (*vertices).removeedge(origin, destination);
    (*vertices).removeedge(destination, origin);
    return;
}

template<class T> void graph<T>::deletevertex(T item)
{
    (*vertices).remove(item);
    return;
}

template<class T> edgelist<T> * graph<T>::outgoingedges(T item)
{
    return (*vertices).outgoingedges(item);
}

template<class T> void graph<T>::prettyprint(void)
{
    cout << "\n\n====== Graph ======\n\n";
    (*vertices).prettyprint();
    cout << "=================\n\n";
    return;
}

template<class T> vertex<T>* graph<T>::get_dummy() // get dummy
{
    return vertices->get_dummy();
}     


/*****************************************************************************************/
//#############   ADDED FUNCTIONS FOR EX3 AND EX4 START HERE     #####################
template<class T> vertex<T>* vertexlist<T>::get_dummy() 
{
    return dummy;
}

template<class T> void vertexlist<T>::set_dummy(vertex<T> *newdummy)
{
    dummy = newdummy;
}

template<class T> void vertexlist<T>::set_length(int len)
{
    numvertices = len;
}

template<class T> void vertexlist<T>::display()
{   
    vertex<T> *temp = dummy->getnext();
    cout << "V1: ";
    for (int i = 0; i < numvertices; i++, temp = temp->getnext()) {
        if (temp->color == 1) {
            cout << temp->getitem() << " ";
        } 
    }

    temp = dummy->getnext();
    cout << "\nV2: ";
    for (int i = 0; i < numvertices; i++, temp = temp->getnext()) {
        if (temp->color == -1) {
            cout << temp->getitem() << " ";
        } 
    }cout << "\n";
}


/*
 * color function is sed to color all vertices to
 * separate vertices into two subsets
 *
 */
template<class T> int vertexlist<T>::color(vertex<T> *node, int the_color)
{
    vertex<T> *temp = node;
    int result = 1;
    temp->color = the_color;
    if (temp->edgelist == NULL) return result;
    neighbour<T> *neighb = temp->getedges()->first_v();
    int origin_color = temp->color;

    for (int j = 0; j < temp->getedges()->getlength(); j++, neighb = neighb->getnext()) {
        if ( find_vertex(neighb->getitem())->color == 0) {
            find_vertex(neighb->getitem())->color = origin_color*(-1);     // color edge vertex as -1*origin_color
            result = color(find_vertex(neighb->getitem()), origin_color*(-1));      // recursive to color all vertices
        } else if (find_vertex(neighb->getitem())->color == origin_color) {
            cout << "Not Bipartite Graph.\n";
            return -1;
        }
    } return result;
}

// clear color is used to  clear all colors in the nodes
template<class T> void vertexlist<T>::clear_color()
{
    vertex<T> *temp = dummy->getnext();
    for (int i = 0; i < numvertices; i++, temp = temp->getnext()) {
        temp->color = 0;
    }
}

template<class T> vertex<T>* vertexlist<T>::find_vertex(T item)
{
    vertex<T> *temp = NULL;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            temp = pt;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return temp;
}


// separate the vertices in the graph into two parts
template<class T> bipartite_graph<T>::bipartite_graph()
{
    graph_all = new graph<T>;
    graph_all->vertices= new vertexlist<T>;
    v1 = new vertexlist<T>;
    v2 = new vertexlist<T>;
}
template<class T> int bipartite_graph<T>::separate()
{
    //cout << graph_all->vertices->color(graph_all->get_dummy()->getnext(), 1);
    graph_all->vertices->clear_color();     // clear all color before
    if (graph_all->vertices->color(graph_all->get_dummy()->getnext(), 1) == -1) {
        cout << "Fail\n";
        return 0;
    } else {
        vertex<T> *temp = graph_all->get_dummy()->getnext();
        for (int i = 0; i < graph_all->vertices->getlength(); i++, temp = temp->getnext()) {
            if (temp->color == 0 && -1 == graph_all->vertices->color(temp, 1)) {
                cout << "Fail\n";
                return 0;
            }
        }
    }
    vertexlist<T> *temp1 = new vertexlist<T>;
    vertexlist<T> *temp2 = new vertexlist<T>;
    
    vertex<T> *first = graph_all->get_dummy()->getnext();
    for (int i = 0; i < graph_all->vertices->getlength(); i++, first = first->getnext()) {
        //cout << first->getitem() << first->color << "\n";
        if (first->color == 1)  temp1->addvertex(first->getitem());
        if (first->color == -1) temp2->addvertex(first->getitem());
    }
    v1 = temp1;
    return 1;
    
}


/*insertion and deletion of vertices and edges*/
template<class T> int bipartite_graph<T>::insert_edge(T origin, T destination)
{
	/*Implement your code here*/
    graph_all->addedge(origin, destination);
    return separate();
}

template<class T> int bipartite_graph<T>::insert_vertex(T item)
{
	/*Implement your code here*/
    graph_all->addvertex(item);
    return separate();
}

template<class T> int bipartite_graph<T>::delete_edge(T origin, T destination)
{
	/*Implement your code here*/
    graph_all->deleteedge(origin, destination);
    return separate();
}

template<class T> int bipartite_graph<T>::delete_vertex(T item)
{
	/*Implement your code here*/
    graph_all->deletevertex(item);
    return separate();
}

/*the determination of edges incident to a given vertex*/
template<class T> edgelist<T> * bipartite_graph<T>::incident_edges(T item)
{
	/*Implement your code here*/
    edgelist<T> *result = new edgelist<T>;
    if (graph_all->vertices->find_vertex(item) == NULL) return NULL;
    if (graph_all->vertices->find_vertex(item)->getedges() != NULL) {
        graph_all->vertices->find_vertex(item)->getedges()->addall(item, result);
        return result;
    }
    return NULL;
}

// find a path of two given vertices
template<class T> int edgelist<T>::find_path(T boy, T girl, edgelist<T> *path)
{
    if (boy == girl)    return 0;
    int index, founded = 0;
    for (int i = 0; i < numedges; i++) {
        edge<T>* current = reprarray[i];
        index = i;
        if (current->origin() == boy) {
            if (current->destination() == girl) { // if the destination is the girl
                founded = 1;
                break;   
            } else { // if the destination is the girl, keep searching
                founded = find_path(current->destination(), girl, path);
                break;
            }
        }
    }   // 
    if (founded == 1) { // path founded, return back and generate the path
        path->add(girl, boy);   // I generate the path in a reverse order
        return founded;
    }  return 0;    // not found the path
}

// contains function for edgelist class
template<class T> int edgelist<T>::contains(T item)
{
    for (int i = 0; i < numedges; i++) {
        edge<T>* current = reprarray[i];
        if (current->origin() == item || current->destination() == item)    return 1;
    }
    return 0;
}

// check if certain edge exists
template<class T> int  edgelist<T>::contain_edge(T boy, T girl)
{
    for (int i = 0; i < numedges; i++) {
        edge<T>* current = reprarray[i];
        if (current->origin() == boy && current->destination() == girl)    return 1;
        if (current->origin() == girl && current->destination() == boy)    return 1;
    }
    return 0;
}


// generate digraph
template<class T> edgelist<T>* bipartite_graph<T>::digraph(vertexlist<T> *boys, vertexlist<T> *girls)\
{
    edgelist<T> *the_digraph = new edgelist<T>;
    vertex<T> *temp;
    // first add all boys' edges
    temp = boys->get_dummy()->getnext();
    for (int i = 0; i < boys->getlength(); i++, temp = temp->getnext()) {
        edgelist<T> *edges = graph_all->outgoingedges(temp->getitem());     // find all edges of current vertex
        edge<T>** alledges = edges->get_alledges();     // the list storing all edges, the firstitem represents current item
        for (int j = 0; j < edges->getnumedges(); j++) {
            if (boys->contains(alledges[j]->destination()))  continue;  
            else    the_digraph->add(temp->getitem(), alledges[j]->destination());
        }
    }
    // then add all girls' edges
    temp = girls->get_dummy()->getnext();
    for (int i = 0; i < girls->getlength(); i++, temp = temp->getnext()) {
        edgelist<T> *edges = graph_all->outgoingedges(temp->getitem());     // find all edges of current vertex
        edge<T>** alledges = edges->get_alledges();     // the list storing all edges, the firstitem represents current item
        for (int j = 0; j < edges->getnumedges(); j++) {
            if (girls->contains(alledges[j]->destination()))  continue;  
            else    the_digraph->add(temp->getitem(), alledges[j]->destination());
        }
    }
    return the_digraph;
}


/*
 *
 * is_perfect is used to determine the perfect match
 * for ex3
 * 
 */
template<class T> int bipartite_graph<T>::ex3_perfect_match()
{
    vertexlist<T>* girls = new vertexlist<T>;
    vertexlist<T>* boys  = new vertexlist<T>;
    edgelist<T>* partial_match = new edgelist<T>;   // stores currently matched vertices, will be updated every loop
    edgelist<T>* digraph = new edgelist<T>;

    if (graph_all->vertices->getlength() % 2 != 0) {
        return 0;
    }
    if (separate() == 0)    {return 0;} // call separate to generate bipartite graph using color

    vertex<T>* temp = new vertex<T>;    // a temp vertex pointer
    temp = graph_all->vertices->get_dummy()->getnext();
    for (int i = 0; i < graph_all->vertices->getlength(); i++) {
        if (temp->color == 1) { // color 1 represents girl
            girls->addvertex(temp->getitem());
            girls->find_vertex(temp->getitem())->setedges(temp->getedges());    // copy all edges
        } else {    // color -1 represents boy
            boys->addvertex(temp->getitem());
            boys->find_vertex(temp->getitem())->setedges(temp->getedges());
        }
    }

    digraph = this->digraph(boys, girls);   // generate the digraph, which stores all edges in a graph
    // now the main function begins to judge if it is a perfect match bipartite graph
    vertex<T>* boy = boys->get_dummy()->getnext();
    int branch = 0; // branch uses number to represent: 0-keep looping, 1-perfect match, -1-not perfect match
    int matched = 0;   // trymatch indicates whether ot not these two vertices should be tried to match
    // main loop starts here
    while (branch == 0) {    // if 1, perfect match founded; if 2, not perfect match
        if (boy == boys->get_dummy()) { // if loop back, all boys have been matched
            branch = 1; break;
        }
        // check if current boy has been matched
        if (partial_match->contains(boy->getitem()))   continue;   // if matched, continue to next
        // now try to match girl for current boy
        vertex<T> *girl = girls->get_dummy()->getnext();
        for (int i = 0, matched = 0; i < girls->getlength(); i++, girl = girl->getnext()) {
            if (1 == partial_match->contains(girl->getitem()) )  continue; // if current girl has been matched
            if (0 == partial_match->contains(girl->getitem()) && boy->getedges()->contains(girl->getitem())) {  // if current girl is an edge and has not been matched
                partial_match->add(boy->getitem(), girl->getitem());
                partial_match->add(girl->getitem(), boy->getitem());
                matched = 1;    // match founded
                break;
            } else {    // the last case is the girl has not been matched and is not an edge of the boy, try find a path to readjust all matches
                edgelist<T>* path = new edgelist<T>;
                if (1 == digraph->find_path(boy->getitem(), girl->getitem(), path)) {   // if path founded
                    edge<T>** the_path = path->get_alledges();
                    for (int j = 0; j < path->getnumedges(); j++) {
                        edge<T>* current = the_path[j];
                        if (0 == partial_match->contain_edge(current->origin(), current->destination())) {  // if a match not exists, add into partial match
                            partial_match->add(current->origin(), current->destination());
                            partial_match->add(current->destination(), current->origin());
                        }
                    }
                    matched = 1;    // match founded
                    break;
                } else {// if path not founded, continue to next girl
                    continue;
                }
            }
        }   // all girls have been looped, ended here
        if (matched == 0)  branch = -1;     // a boy failed to found match, not perfect match 
        boy = boy->getnext();   // update boy
    }   // while loop ended here
    return branch+1;
}


/*determine the perfect match for ex4*/
template<class T> int bipartite_graph<T>::ex4_perfect_match(void)
{
	/*Implement your code here*/
    if (graph_all->vertices->getlength()%2 != 0)    return -1;
    separate();
    // apply Hall theorem to determine if it is perfect matching
    int result = 1;
    for (int i = 1; i <= v1->getlength(); i++) {    // check subsets with length between 1 - length/2
        if (i == 1) { // first check all subsets with length = 1
            vertex<T> *temp = v1->get_dummy()->getnext();
            for (int j = 0; j < v1->getlength(); j++, temp = temp->getnext()) {
                if (graph_all->vertices->find_vertex(temp->getitem())->getedges() != NULL && graph_all->vertices->find_vertex(temp->getitem())->getedges()->getlength() < 1) {
                    result = -1;
                    return result;
                }
            } continue; // finish check of subset with length 1
        }
        // for subsets with length more than one, we call 'decide_tree' to check all subsetss
        vertex<T> *temp = v1->get_dummy()->getnext();
        for (int j = 0; j < v1->getlength(); j++, temp = temp->getnext()) {
            if (graph_all->vertices->find_vertex(temp->getitem())->getedges() != NULL)
                result = decide_tree(graph_all->vertices->find_vertex(temp->getitem()), graph_all->vertices, i-1, 
                                     graph_all->vertices->find_vertex(temp->getitem())->getedges()->getlength(), 1);
            if (result == -1) {
                cout << "Not Perfect Match, layer = " << i << "\n";
                return result;
            }
        }
    } return result;    // check loop ended here, return the result
}


/*
 * decide tree function use recursive to determine
 * whether a graph is perfect matching by applying 
 * Hall theorem
 *
 */
template<class T> int bipartite_graph<T>::decide_tree(vertex<T> *current, vertexlist<T> *list, int layer, int edge_len, int sub_len)
{
    int subset_length = 0;  // subset size
    int edge_length = 0;    // edge number
    int in_layer;   // input layer
    vertexlist<T> *input_list = new vertexlist<T>;  //list used to recursive
    vertex<T> *temp = list->get_dummy()->getnext();

    if (layer <=0)   return 1;
    if (layer == 0) {
        subset_length = sub_len + 1;
        for (int i = 0; i < list->getlength(); i++, temp = temp->getnext()){
            if (temp->getitem() == current->getitem() || temp->color != current->color)  continue;
            if (v1->contains(temp->getitem()) == false) continue;
            
            edge_length = edge_len + temp->getedges()->getlength();     // number of edges
            neighbour<T> *neighb1 = temp->getedges()->first_v();    
            neighbour<T> *neighb2 = current->getedges()->first_v();
            // check if there exists same edge, if exist, decrement from edge_length
            for (int j = 0; j < temp->getedges()->getlength(); j++, neighb1 = neighb1->getnext()) {
                for (int k = 0; k < current->getedges()->getlength(); k++, neighb2 = neighb2->getnext()) {
                    if (neighb1->getitem() == neighb2->getitem()) {
                        edge_length--;  // if same edges exist
                    }
                }
            }
            if (edge_length < subset_length) {return -1;}   // if the edge number is less than the subset size
            edge_length = 0;
        }
        return 1;
    }   
    // if not in the leaf layer
    subset_length = sub_len + 1;
    in_layer = layer-1;
    for (int i = 0; i < list->getlength(); i++, temp = temp->getnext()) {
        if (temp->getitem() == current->getitem() || temp->color != current->color)  continue;
        if (v1->contains(temp->getitem()) == false) continue;
        
        if (temp->getedges() == NULL)   continue;
        
        edge_length = edge_len + temp->getedges()->getlength();
        neighbour<T> *neighb1 = temp->getedges()->first_v();    
        neighbour<T> *neighb2 = current->getedges()->first_v();
        for (int j = 0; j < temp->getedges()->getlength(); j++, neighb1 = neighb1->getnext()) {
            for (int k = 0; k < current->getedges()->getlength(); k++, neighb2 = neighb2->getnext()) {
                if (neighb1->getitem() == neighb2->getitem())   edge_length--;
            }
        }
        if (edge_length < subset_length) {return -1;}   // if the subset size is less than the edge length

        // creat a new list to input into recursive function
        vertex<T> *tmp = list->get_dummy()->getnext();
        for (int k = 0; k < list->getlength(); k++, tmp = tmp->getnext()) {
            if (tmp->getitem() == temp->getitem() || tmp->getitem() == current->getitem())  continue;
            input_list->addvertex(tmp->getitem());
            input_list->find_vertex(tmp->getitem())->color = tmp->color;
            input_list->find_vertex(tmp->getitem())->setedges(tmp->getedges());
        }
        if (-1 == decide_tree(temp, input_list, in_layer, edge_length, subset_length)) 
            return -1;  // recursive to judge
        edge_length = 0;    // initialize
    }
    return 1;
}


/*********************************************************************************************/

