// Facebook liarliar puzzle solution
// This is a basic 2-color graph coloring problem.
// We'll use two basic data structures to solve the problem.
// The first is a graph with adjacency-list representation
// The second is a hash (unordered_map) of vertices and their color
// The color can be either liar or non-liar
#include <iostream>
#include <fstream>
#include <queue>                // for the BFS
#include <tr1/unordered_map>    // for the colorings and visited maps
#include <utility>              // for pair

#include "graph.h"

using namespace std;

typedef tr1::unordered_map<string, bool> coloring;

// Load a file containing community information
// The format of the file is below:
// The first line is an integer indicating the number n of veteran members
// This is followed by n records, one for each member.
// The first line of each record is the member name followed by the number m 
// of liars.
// This is followed by m lines, each line contains the name of a supposed liar.
void load_file(char *filename, Graph &liar_graph)
{
    int n, num_targets;
    string accuser;
    string target;

    std::ifstream input_file(filename);
    input_file >> n;
    for (int i = 0; i < n; ++i) {
        input_file >> accuser >> num_targets;
        for (int j = 0; j < num_targets; ++j) {
            input_file >> target;
            liar_graph.add_edge(accuser, target);
        }
    }

    return;
}

// Use breadth-first search to color a component
bool color_component(const string &node,
                     Graph &liar_graph,
                     coloring &liars,
                     coloring &visited)
{
    queue<pair <string,bool> > q;
    pair <string,bool> v;

    v = make_pair(node, true);
    q.push(v);

    while (!q.empty()) {
        v = q.front();
        q.pop();
        if (visited.find(v.first) != visited.end()) {
            continue;
        }
        visited[v.first] = true;
        liars[v.first] = v.second;
        bool color = !v.second;
        neighbor_list *neighbors = liar_graph.neighbors(v.first);

        for (neighbor_list::iterator it = neighbors->begin();
             it != neighbors->end();
             ++it) {
            if (liars.find(it->first) != liars.end())
                if (liars[it->first] != color) {
                    //cout << "Found contradiction " << it->first << endl;
                    return false;
                }
            if (visited.find(it->first) == visited.end()) {
                q.push(make_pair(it->first, color));
            }
        }
    }

    return true;
}

bool find_liars(Graph &liar_graph, coloring &liars)
{
    coloring visited;
    adjacency_list::iterator edges;
    bool color, accuser_color;
    edges = liar_graph.edges();

    // Iterate through each source vertex
    // If the vertex hasn't been visited, do a BFS starting from it.
    // This should ensure we visit every disconnected component
    for (edges = liar_graph.edges(); edges != liar_graph.end(); ++edges) {
        if (visited.find(edges->first) == visited.end())
            color_component(edges->first, liar_graph, liars, visited);
    }

    return true;
}

int main(int argc, char **argv)
{
    class Graph liar_graph(false);
    coloring liars;

    //cout << "Loading file" << endl;
    if (argc == 2) {
        load_file(argv[1], liar_graph);
    } else {
        cout << "Error: Must specify a filename to load" << endl;
        return 1;
    }
    //liar_graph.print();

    //cout << "Finding liars" << endl;
    find_liars(liar_graph, liars);

    //cout << "Finding solution" << endl;
    int liar_cnt = 0, honest_cnt = 0;
    for (coloring::iterator it = liars.begin(); it != liars.end(); ++it) {
        if (it->second == false)
            liar_cnt++;
        else
            honest_cnt++;
    }

    cout << max(liar_cnt, honest_cnt) << " " << min(liar_cnt, honest_cnt) <<
        endl;

    return 0;
}
