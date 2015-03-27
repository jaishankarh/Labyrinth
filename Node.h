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

/**
 *  A class that encapsulates a Node that is connected in a graph. A collection of these form the Labyrinth
 */
class Node{
    private:
        //static int id_count = 0;
        int id;
        int row_no;
        int col_no;
        std::set<Node*> *adj_nodes;
        bool visited;
    public:

        /**
		 * A constructor with 2 parameters row and col.
		 * @param row_no an integer depicting the row of this node in the labyrinth
		 * @param col_no an integer depicting the column of this node in the labyrinth
		 * This constructor uses these two parameters and produces an id which is unique in the labyrinth. Every node can be retrieved using this id.
		 */
        Node(int row_no, int col_no);

        ~Node();

       /**
	    *A simple getter method returning the id
	    */
        int getId();
       /**
		*A simple getter method returning the Row No
		*/
        int getRowNo();
       /**
		*A simple getter method returning the Col no
		*/
        int getColNo();
       /**
		*A simple getter method returning the list of adjacent nodes
		*/
        std::set<Node*>* getAdj_Nodes();
       /**
		*A simple getter method to find out if the node is visited while traversal of finding the longest path.
		* This is useful only to the findPath function..which makes the traversal
		*/
        bool getVisited();
       /**
		*A simple getter method returning the id
		* This sets the state of the node to visited
		* @param v this parameter is a boolean value. If true, the node is visited, if false it is not visited.
		*/
        void setVisited(bool v);
        /**
         *function takes in a parameter which is the node that needs to be added as an adjacent node to the current node object. simply appends to the list
         */
        void add_adj(Node *n);
};




#endif /* NODE_H_ */
