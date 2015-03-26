/*
 * Node.cpp
 *
 *  Created on: 26-Mar-2015
 *      Author: jaishankar
 */


#include "Node.h"

using namespace std;

Node::Node(int row_no, int col_no){


	this->row_no = row_no;
	this->col_no = col_no;
	this->id = row_no*10 + col_no;
	adj_nodes = new std::list<Node*>();
	visited =false;
}

Node::~Node(){
	delete adj_nodes;
}

int Node::getId(){return id;}
int Node::getNoRows(){return row_no;}
int Node::getNoCols(){return col_no;}
std::list<Node*>* Node::getAdj_Nodes(){return adj_nodes;}
bool Node::getVisited(){return visited;}
void Node::setVisited(bool v){this->visited = v;}
//function takes in a parameter which is the node that needs to be added as an adjacent node to the current node object. simply appends to the list
void Node::add_adj(Node* n){
	adj_nodes->push_back(n);
}

