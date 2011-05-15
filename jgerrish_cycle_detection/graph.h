// Class representing a graph

#include <iostream>
// Use an unordered_map (hash map) for the adjacency list
#include <tr1/unordered_map>
#include <vector>
#include <string>

using namespace std;
//using namespace std::tr1;

typedef tr1::unordered_map<string, bool> neighbor_list;
typedef tr1::unordered_map<string, neighbor_list* > adjacency_list;

typedef tr1::unordered_map<string, bool> node_list;

typedef tr1::unordered_map<string, bool> coloring;
typedef tr1::unordered_map<string, int> visit_time;

typedef tr1::unordered_map<string, string> parent_map;

class Graph
{
private:
    adjacency_list adj_list;
    node_list nodes;
    bool directed;

    // DFS data structures
    coloring visited;
    coloring processed;
    visit_time entry_time;
    bool finished;
    parent_map parent;
    vector<string> cycle;

public:
    Graph();
    Graph(bool d);
    ~Graph();

    bool read_edgelist_file(istream &input_stream);

    vector<string> find_cycle();
    void dfs(const string &node, int &time);
    void process_edge(const string &v1, const string &v2);

    bool edge_exists(const string &v1, const string &v2);
    void add_edge(const string &v1, const string &v2);
    void find_path(const string &v1, const string &v2);

    // edge and neighbor iterator and access methods
    adjacency_list::iterator edges();
    adjacency_list::iterator end();
    neighbor_list *neighbors(const string &v);

    void print();
    friend ostream &operator<<(ostream &stream, Graph graph);
};
