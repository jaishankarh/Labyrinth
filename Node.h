/*
 * Node.h
 *
 *  Created on: 26-Mar-2015
 *      Author: jaishankar
 */




#ifndef NODE_H_
#define NODE_H_

#include <list>
#include <string>
#include <set>
#include <map>

using namespace std;

class Node{
    private:
        //static int id_count = 0;
        int id;
        int row_no;
        int col_no;
        std::list<Node*> *adj_nodes;
        bool visited;
    public:

        Node(int row_no, int col_no);

        ~Node();
        int getId();
        int getNoRows();
        int getNoCols();
        std::list<Node*>* getAdj_Nodes();
        bool getVisited();
        void setVisited(bool v);
        //function takes in a parameter which is the node that needs to be added as an adjacent node to the current node object. simply appends to the list
        void add_adj(Node *n);
};




#endif /* NODE_H_ */
