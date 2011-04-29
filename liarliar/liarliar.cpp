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

// breadth-first search to check this accusers accusations
// If we find a contradiction, return false, otherwise return true
bool check_accusations(const string &accuser,
                       Graph &liar_graph,
                       coloring &liars)
{
    coloring visited;
    queue<pair <string,bool> > q;
    pair <string,bool> v;

    v = make_pair(accuser, true);
    q.push(v);
    visited[accuser] = true;

    while (!q.empty()) {
        v = q.front();
        q.pop();
        vector<string> neighbors = liar_graph.neighbors(v.first);
        bool color = !v.second;
        for (vector<string>::iterator it = neighbors.begin();
             it != neighbors.end();
             ++it) {
            if (liars.find(*it) != liars.end())
                if (liars[*it] != color)
                    return false;
            if (visited.find(*it) == visited.end()) {
                visited[*it] = true;
                q.push(make_pair(*it, color));
            }
        }
    }

    return true;
}

void find_liars(Graph &liar_graph, coloring &liars)
{
    // Iterator through the accusers
    adjacency_list::iterator edges;
    bool color, accuser_color;
    edges = liar_graph.edges();

    for (edges = liar_graph.edges(); edges != liar_graph.end(); ++edges) {
        accuser_color = check_accusations(edges->first, liar_graph, liars);

        color = !accuser_color;
        liars[edges->first] = accuser_color;
        for (vector<string>::iterator target_it = edges->second.begin();
             target_it != edges->second.end();
             ++target_it) {
            liars[*target_it] = color;
        }
    }

}

int main(int argc, char **argv)
{
    class Graph liar_graph;
    coloring liars;

    if (argc == 2) {
        load_file(argv[1], liar_graph);
    } else {
        cout << "Error: Must specify a filename to load" << endl;
        return 1;
    }

    // cout << liar_graph;

    find_liars(liar_graph, liars);

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
