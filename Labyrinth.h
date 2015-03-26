/*
 * Labyrinth.h
 *
 *  Created on: 26-Mar-2015
 *      Author: jaishankar
 */

#include <list>
#include <string>
#include <set>
#include <map>
#include <iostream>
#include <fstream>

#ifndef LABYRINTH_H_
#define LABYRINTH_H_

using namespace std;

class Labyrinth {
    public:
        Labyrinth(std::iostream &input);
        ~Labyrinth();
        char** getMatrix();
        int getNoRows();
        int getNoCols();
        std::set<Node*>* getExtremities();
        std::list<Node*>* getLongest_Path();

        void findLongest();
        void traverseToNext(Node* n, Node* root,std::list<Node*> *path);
        void findPath(Node* root,std::list<Node*> *path);
        void drawPath();
    private:
        //reads a file from the disk which contains the schema of the matrix... the #s and the dots..and load the other properties.
        void init_matrix(std::iostream &input);
        char** matrix;
        int no_rows;
        int no_cols;
        unsigned long max;
        //std::list< Node& > all_nodes;
        //std::list<Node*> *all_nodes;
        std::map<int, Node*> *nodes_map;
        std::list< std::set<Node*>* > *connected_components;
        std::set<Node*> *extremities;
        std::list<Node*> *longest_path;
};



#endif /* LABYRINTH_H_ */
