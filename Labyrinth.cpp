/*
 * labyrinth.cpp

 *
 *  Created on: 24-Mar-2015
 *      Author: jaishankar
 */


/*Author : Jaishankar Hebballi
This file is source that finds the longest path in a graph of connected components....
Date: 23.03.2015

*/

#include "Node.h"
#include "Labyrinth.h"


//the else part in the mainstack.push needs revision...it does not work as expected..
//need to keep popping out of the stack until we find another route...also when the loop reaches a loop where there exist other ajacent nodes but they are all visited..and the path currently formed is the longest, then also store this path..

/*
The Node class encpasulates the properties and methods of one particular single node..
id: this field stores a sequential number allocated from left to right.
adj_nodes: this property is a list of all the adjacent nodes to this node.
*/
#include <stack>

using namespace std;

typedef std::list<Node*> stdnodelist;

std::vector< std::vector<char>* >* Labyrinth::getMatrix(){return matrix;}
int Labyrinth::getNoRows(){return no_rows;}
int Labyrinth::getNoCols(){return no_cols;}
std::set<Node*>* Labyrinth::getExtremities(){return extremities;}
std::list<Node*>* Labyrinth::getLongest_Path(){return longest_path;}

Labyrinth::Labyrinth(std::iostream &input){
	max = 0;
	init_matrix(input);
}

Labyrinth::~Labyrinth(){
        	delete matrix;

        	delete nodes_map;
        	delete connected_components;
        	delete extremities;
        	delete longest_path;
        	for(std::map<int, Node*>::iterator it=nodes_map->begin(); it != nodes_map->end(); it++){
				Node* del = it->second;
				delete del;
			}
        	delete nodes_map;
        	std::cout << "I was here in the destructor" << endl;
        };



void Labyrinth::findLongest(){
	//this variable is to check if the connected_components to which the extremity belongs has at least max elements..if not there is not point in traversing those nodes
	bool no_need = false;
	for(std::set<Node*>::iterator it=extremities->begin(); it != extremities->end(); it++){
		Node* n = *it;
		//std::set<Node*> &found_comp;
		for(std::list< std::set<Node*>* >::iterator iter=connected_components->begin(); iter != connected_components->end(); iter++){
			std::set<Node*> *conn_comp =  *iter;
			if(conn_comp->count(n) == 1){

				if(conn_comp->size() <= max){
					connected_components->erase(iter);
					no_need = true;
					break;
				}

			}
		}
		if(!no_need) {
			//this path is empty and will store the path traversed
			std::list<Node*> *path = new std::list<Node*>();

			findPath(n, path);
			delete path;

		}
	}


}

void Labyrinth::findPath(Node* root,std::list<Node*> *path){
	std::stack<Node*> *mainStack = new std::stack<Node*>();
	mainStack->push(root);
	while(!mainStack->empty()){
		Node* n = mainStack->top();
		mainStack->pop();
		if(n->getVisited()){

			continue;
		}
		n->setVisited(true);
		path->push_back(n);
		std::list<Node*> *adjnodes = n->getAdj_Nodes();

		if(adjnodes->size() == 1 && n != root) {




			//if the currently traversed path is bigger than that of the longest one...
			if(path->size() > max){
				//copy path to longest path
				std::list<Node*> *to_be_deleted = longest_path;
				longest_path = new std::list<Node*>(*path);
				max = path->size();
				delete to_be_deleted;
				path->pop_back();
			}
			else{
				Node* last = path->back();
				last->setVisited(false);
				path->pop_back();

			}


		}
		else{
			bool pushed_one = false;
			for(std::list<Node*>::iterator it=adjnodes->begin(); it!=adjnodes->end(); it++ ){
				Node *n = *it;
				if(!n->getVisited()){
					pushed_one = true;
					mainStack->push(*it);
				}

			}
		}

	}



}

//void Labyrinth::traverseToNext(Node* n, Node* root, std::list<Node*> *path){
//	if(n != NULL){
//
//		//if it is an extremity node
//		if(n->getAdj_Nodes()->size() == 1 && root != n){
//			n->setVisited(true);
//			path->push_back(n);
//
//
//			//if the currently traversed path is bigger than that of the longest one...
//			if(path->size() > max){
//				//copy path to longest path
//				longest_path = new std::list<Node*>(*path);
//				max = path->size();
//			}
//			else{
//				Node* last = *(path->end());
//				last->setVisited(false);
//				path->pop_back();
//				return;
//			}
//		}
//		//if the node is already visited then just fall bback
//		else if(n->getVisited()){
//			path->pop_back();
//			return;
//		}
//		//traverse through other adjacent nodes..
//		else if(n->getAdj_Nodes()->size() > 1 || root == n){
//			n->setVisited(true);
//			path->push_back(n);
//			std::list<Node*> *adj = n->getAdj_Nodes();
//			for(std::list<Node*>::iterator it=adj->begin(); it != adj->end(); it++){
//				Node* temp = *it;
//				if(!temp->getVisited()){
//					traverseToNext(temp, root, path);
//				}
//
//
//			}
//		}
//
//		//n->setVisited(false);
//
//	}
//}

void Labyrinth::drawPath(){
	int count = 0;
	for(std::list<Node*>::iterator it=longest_path->begin(); it!=longest_path->end(); it++){
		Node* t = *it;
		int row = t->getId()/10;
		int col = t->getId() % 10;
		matrix->at(row)->at(col)= '*';

	}
}



void Labyrinth::init_matrix(std::iostream &input) {

    //get the size of the whole file in bytes..
    input.seekg( 0, ios::end );
    int size = input.tellg();
    input.seekg(0, ios::beg);

    char* buffer = new char[size];
    input.read (buffer,size);
    //get the first new line character...there by assuming a row length .. needed for allocation of the matrix property
    int len = 0;
    for(int i=0; i<size; i++) {
    	len++;
        //take care of other line endings too...
        if(buffer[i] == '\n'){
            break;
        }


    }
//    no_rows = size/len;
//    //-1 for the newline char
//    no_cols = len-1;
    matrix = new std::vector< std::vector<char>* >();
    std::vector<char>* temp = new std::vector<char>();
    //initialise the two dimensional array..
    int i=0,j = 0;
    //all_nodes = new std::list<Node*>();
    nodes_map = new std::map<int, Node*>();
    for(int k=0; k < size; k++) {

            if(buffer[k]=='\n' || k+1 == size){
            	if(k+1 == size){
            		temp->push_back(buffer[k]);
					Node* n = new Node(i,j);
					nodes_map->insert(std::pair<int, Node*>(n->getId(), n));
					matrix->push_back(temp);
					break;
            	}
            	matrix->push_back(temp);
            	temp = new std::vector<char>();
                i++;
                k++;
                j = 0;


            }
            temp->push_back(buffer[k]);

            Node* n = new Node(i,j);
            //all_nodes->add(n);
            nodes_map->insert(std::pair<int, Node*>(n->getId(), n));
            j++;


    }



    longest_path = new std::list<Node*>();
    connected_components = new std::list< std::set<Node*>* >();
    extremities = new std::set<Node*>();

    no_rows = matrix->size();
    no_cols = matrix->at(0)->size();

    for(i=0; i < no_rows; i++) {
        for(j=0; j < no_cols; j++) {
            char c = matrix->at(i)->at(j);
            if(c == '#'){


                continue;
            }
            //check all iterators for the end condition....could fail..
            else if(c == '.') {
            	int tid = i*10 + j;
            	Node* vertex = nodes_map->find(tid)->second;

                //check right
                char right_char;
                if(j+1 < no_cols) {
                	right_char = matrix->at(i)->at(j+1);
                	if(right_char == '.'){
                		int t_id = i*10 + j+1;
                		Node* n = nodes_map->find(t_id)->second;
                		vertex->add_adj(n);
                	}
                }
                char left_char;
                if(j-1 >= 0) {
                	left_char = matrix->at(i)->at(j-1);
                	if(left_char == '.'){
                		int t_id = i*10 + j-1;
                		Node* n = nodes_map->find(t_id)->second;
                		vertex->add_adj(n);
                	}
                }
                char down_char;
                if(i+1 < no_rows) {
                	down_char = matrix->at(i+1)->at(j);
                	if(down_char == '.'){
                		int t_id = (i+1)*10 + j;
                		Node* n = nodes_map->find(t_id)->second;
                		vertex->add_adj(n);
                	}
                }
                char up_char;
                if(i-1 >= 0) {
                	up_char = matrix->at(i-1)->at(j);
                	if(up_char == '.'){
                		int t_id = (i-1)*10 + j;
                		Node* n = nodes_map->find(t_id)->second;
                		vertex->add_adj(n);
                	}
                }

                //if vertex has only one connection then it is an extremity so add it to extremities...
                if(vertex->getAdj_Nodes()->size() == 1)
                {
                	extremities->insert(vertex);
                }


                std::list<Node*> *to_connect = new std::list<Node*>(*(vertex->getAdj_Nodes()));
                to_connect->push_back(vertex);

                //std::list<Node*> *to_connect = vertex->getAdj_Nodes();

                bool found = false;

                //the next for loops check if any element exists in any connected_components set..if yes then all are added to that set..else..a new set is made and all the elements are added to that set and that set is added to connected_components
                //found variable is to check if the elements were found in any of the sets...it will turn true if found..
                for(std::list< std::set<Node*>* >::iterator it=connected_components->begin(); it != connected_components->end(); it++){
                	std::set<Node*> *s = *it;

                	for(std::list<Node*>::iterator iter=to_connect->begin(); iter != to_connect->end(); iter++ ){
                		Node* n = *iter;
                		if(s->find(n) != s->end() ){
                			for(std::list<Node*>::iterator iter=to_connect->begin(); iter != to_connect->end(); iter++ ){
								Node* n = *iter;
								s->insert(n);

							}
                			//s->insert(vertex);
                			found = true;
                			break;
                		}
                	}
                	if(found)
                	{
                		break;
                	}


                }
                if(!found){
                	std::set<Node*> *s = new std::set<Node*>();
                	for(std::list<Node*>::iterator iter=to_connect->begin(); iter != to_connect->end(); iter++ ){
						Node* n = *iter;
						s->insert(n);

					}
                	connected_components->push_back(s);
                }


            }
        }

    }

    std::cout << "Connected components:" << connected_components->size() << endl;
    delete[] buffer;


}


int main(int args, char** argv) {
	if(args != 2){
		std::cout << "Error no parameter passed!\nUsage: <executable> <filename>";
		return 1;

	}

    //initialise the matrix...with characters
    // run through the 2 dimensional array and load the adjacency matrix
    // simultaneously in this loop store all the extremities in a queue list
    // finally start dequeuing the extremeties queue and follow and calculate path length..
    // finally will have the longest path..
//    std::string str("##.##.#\n#..##.#\n#.#####\n#..####\n#######\n");
//    std::stringstream instream (str);
	std::fstream instream(argv[1]);
    Labyrinth lb(instream);
    std::vector< std::vector<char>* >* mat = lb.getMatrix();
    int rows = lb.getNoRows();
    int cols = lb.getNoCols();
    for(int i=0; i < rows; i++){
        for(int j=0; j < cols; j++) {
            std::cout << mat->at(i)->at(j) << " ";
        }
        std::cout << endl;
    }
//    std::set<Node*> *ex = lb.getExtremities();
//    for(std::set<Node*>::iterator it=ex->begin(); it != ex->end(); it++){
//    	Node *n = *it;
//    	cout << n->getId() << " " << endl;
//    }
    lb.findLongest();
    std::list<Node*> *longest = lb.getLongest_Path();
    for(std::list<Node*>::iterator it=longest->begin(); it != longest->end(); it++){
		Node *n = *it;
		std::cout << n->getId() << ", ";
	}
    std::cout << "Hello World"<<endl;

    lb.drawPath();

    for(std::vector< std::vector<char>* >::iterator it=mat->begin(); it != mat->end(); it++){
    	std::vector<char>* inner = *it;
    	for(std::vector<char>::iterator iter=inner->begin(); iter != inner->end(); iter++){
    		char c = *iter;
    		std::cout << c << " ";
    	}
    	std::cout << endl;

    }

//    for(int i=0; i < rows; i++){
//            for(int j=0; j < cols; j++) {
//                std::cout << mat->at(i)->at(j) << " ";
//            }
//            std::cout << endl;
//        }

}



