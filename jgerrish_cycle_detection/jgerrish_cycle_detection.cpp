// Cycle detection in graphs
// Author: Joshua Gerrish
// For Spiral Genetics interview 2011-05-12
//
#include <iostream>
#include <fstream>

#include "graph.h"

using namespace std;

int main(int argc, char **argv)
{
    class Graph graph;

    if (!graph.read_edgelist_file(cin))
        return 2;

    vector<string> cycle = graph.find_cycle();

    if (cycle.size() == 0)
        return 0;
    else {
        for (vector<string>::const_iterator it = cycle.begin();
             it != cycle.end();
             ++it) {
            cout << *it << endl;
        }
        return 1;
    }
}
