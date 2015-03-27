/*
 * Labyrinth.h
 *
 *  Created on: 26-Mar-2015
 *      Author: jaishankar
 */

#include <list>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#ifndef LABYRINTH_H_
#define LABYRINTH_H_

using namespace std;


/**
 *  A class that encapsulates a labyrinth...
 */
class Labyrinth {
    public:
		/**
		 * A constructor with 1 parameter, an input stream. This stream provides the input for initialising the labyrinth
		 * @param input of type std::iostream used for initialising the matrix of the labyrinth.
		 * This constructor takes in one parameter an input stream and initialises the Labyrinth, internally it also initialises all the components, like the connected_components, extremities, nodes_map.
		 */
        Labyrinth(std::iostream &input);
        ~Labyrinth();
        std::vector< std::vector<char>* >* getMatrix();
        int getNoRows();
        int getNoCols();

      /**
		* A simple getter method returning the list of extremities. Extremities are nodes that have only one adjacent node. Basically like a dead end in a labyrinth
		*/
        std::set<Node*>* getExtremities();

       /**
		* A simple getter method returning the list nodes that represent the longest path.
		* Note that this function does not find the longest path, it simply returns it. The programmer needs to call, findLongestPath before getting this list.
		*/
        std::list<Node*>* getLongest_Path();

       /**
		* A method that finds the longest path in the labyrinth. It traverses through connected nodes only.
		*/
        void findLongest();

        void drawPath();
    private:
        //reads a file from the disk which contains the schema of the matrix... the #s and the dots..and load the other properties.
        void init_matrix(std::iostream &input);

        /**
		* A method that helps the getLongestPath() to find the longest path in the labyrinth. It traverses through connected nodes only.
		*/
		void findPath(Node* root,std::list<Node*> *path);
        std::vector< std::vector<char>* > *matrix;

        /**
		  * a private variable.
		  * Number of rows in the matrix representing the labyrinth
		  */
        int no_rows;
        /**
		  * a private variable.
		  * Number of columns in the matrix representing the labyrinth
		  */
        int no_cols;

        /**
		  * a private variable.
		  * Length of the longest path. NUmber of nodes in that list
		  */
        unsigned long max;

        /**
		  * a private variable.
		  * A map that stores nodes against their id as key. This is used for fast and easy fetching of a node, to fetch its details
		  */
        std::map<int, Node*> *nodes_map;
        /**
		  * a private variable.
		  * A collection of connected_components. connected_components is a set of nodes. Note that two nodes are connected, even if they are indirectly connected through other nodes. All such nodes that are part of one network belong to this collection. The labyrinth can have many such collections.
		  */
        std::list< std::set<Node*>* > *connected_components;

        /**
		  * a private variable.
		  * A collection of extremities. An extremity is defined as a node that has only one adjacent node. Basically like a dead end in a labyrinth.
		  */
        std::set<Node*> *extremities;

        /**
		  * a private variable.
		  * A collection of nodes that represent the longest path in the labyrinth.
		  */
        std::list<Node*> *longest_path;
};



#endif /* LABYRINTH_H_ */
