/*
 * main.cpp
 *
 *  Created on: 22 giu 2019
 *      Author: edoar
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "../headers/NotOrientedGraph.h"
#include "../headers/OrientedGraph.h"
#include "../../List/headers/LinkedList.h"
#include "../../List/headers/sorting_algorithm.h"

int main(int argc, const char** argv){

	NotOrientedGraph<string> graph;
	graph.initGrafo(graph);
	graph.breath_first_search(graph.getVertex());
	cout << endl;
	graph.depth_first_search(graph.getVertex());

	return EXIT_SUCCESS;
}


