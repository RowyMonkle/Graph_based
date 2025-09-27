#ifndef CHECKGRAPH_H
#define CHECKGRAPH_H

#include "Graph.h"
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool checkPseudograph(Graph& graph);
bool checkWeightedGraph(Graph& graph);  
bool checkDisjointGraph(Graph& graph);

#endif