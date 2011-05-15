#include <iostream>
#include <fstream>

#include "graph.h"

Graph::Graph()
{
    directed = true;
    finished = false;
}

Graph::Graph(bool d)
{
    directed = d;
}

Graph::~Graph()
{
    adjacency_list::iterator edges;

    for (edges = adj_list.begin(); edges != adj_list.end(); ++edges) {
        delete edges->second;
    }
}

bool Graph::edge_exists(const string &v1, const string &v2)
{
    neighbor_list *neighbors;

    adjacency_list::iterator it = adj_list.find(v1);
    if (it != adj_list.end()) {
        neighbors = adj_list[v1];
        neighbor_list::iterator it2 = neighbors->find(v2);
        if (it2 != neighbors->end())
            return true;
        else
            return false;
    } else
        return false;
}

void Graph::add_edge(const string &v1, const string &v2)
{
    neighbor_list *neighbors;
    string *vertex;

    //cout << "Adding edge " << v1 << " to " << v2 << endl;
    if (edge_exists(v1, v2)) {
        //cout << "Edge already exists" << endl;
        return;
    }

    adjacency_list::iterator it = adj_list.find(v1);
    if (it == adj_list.end()) {
        neighbors = new neighbor_list();
        adj_list[v1] = neighbors;
    } else
        neighbors = adj_list[v1];

    vertex = new string(v2);
    neighbors->insert(make_pair(*vertex, true));

    nodes[v1] = true;
    nodes[*vertex] = true;

    if (!directed) {
        add_edge(v2, v1);
    }
}

adjacency_list::iterator Graph::edges()
{
    return adj_list.begin();
}

adjacency_list::iterator Graph::end()
{
    return adj_list.end();
}

void Graph::dfs(const string &node, int &time)
{
    adjacency_list::iterator e;
    neighbor_list *neighbors;

    if (finished)
        return;

    visited[node] = true;
    time = time + 1;
    entry_time[node] = time;

    if (adj_list.find(node) != adj_list.end()) {
        neighbors = adj_list[node];
        for (neighbor_list::iterator it = neighbors->begin();
             it != neighbors->end();
             ++it) {
            if (visited.find(it->first) == visited.end()) {
                parent[it->first] = node;
                process_edge(node, it->first);
                dfs(it->first, time);
            } else {
                process_edge(node, it->first);
            }
        }
    }

    time = time + 1;
    processed[node] = true;
}

void Graph::process_edge(const string &v1, const string &v2)
{
    if ((parent.find(v2) == parent.end()) || (parent[v2] != v1)) {
        // Found a back edge
        find_path(v2, v1);
        finished = true;
    }
}

void Graph::find_path(const string &v1, const string &v2)
{
    if ((v1 == v2) || (parent.find(v2) == parent.end())) {
        cycle.push_back(v1);
    } else {
        find_path(v1, parent[v2]);
        cycle.push_back(v2);
    }
}

// Find any cycles in the graph
// Returns a vector containing the cyclic path
// If the vector is empty, the graph doesn't contain a cycle
vector<string> Graph::find_cycle()
{
    adjacency_list::iterator e;
    int time = 0;

    finished = false;
    cycle.clear();
    visited.clear();
    entry_time.clear();
    parent.clear();

    for (node_list::const_iterator n = nodes.begin();
         n != nodes.end();
         ++n) {
        if (finished)
            return cycle;
        if (visited.find(n->first) == visited.end()) {
            dfs(n->first, time);
        }
    }

    return cycle;
}

void Graph::print()
{
    adjacency_list::iterator edges;

    for (edges = adj_list.begin(); edges != adj_list.end(); ++edges) {
        cout << edges->first << " -> ";
        for (neighbor_list::iterator target_it = edges->second->begin();
             target_it != edges->second->end();
             ++target_it) {
            cout << target_it->first << ", ";
        }
        cout << endl;
    }
}

ostream &operator<<(ostream &stream, Graph graph)
{
    adjacency_list::iterator edges;

    edges = graph.edges();

    for (edges = graph.edges(); edges != graph.end(); ++edges) {
        stream << edges->first << " -> ";
        for (neighbor_list::iterator target_it = edges->second->begin();
             target_it != edges->second->end();
             ++target_it) {
            stream << target_it->first << ", ";
        }
        stream << endl;
    }

}

neighbor_list *Graph::neighbors(const string &v)
{
    return adj_list[v];
}

// Load a file containing graph information in edgelist format
// An edgelist format file contains a list of edges, with one edge per line
// The first field is the source node, the second is the target node
bool Graph::read_edgelist_file(istream &input_stream)
{
    string source, target;

    input_stream >> source >> target;

    if ((source == "") || (target == ""))
        return false;

    if (input_stream.good())
        add_edge(source, target);

    while (input_stream.good()) {
        input_stream >> source >> target;
        if ((source == "") || (target == ""))
            return false;
        add_edge(source, target);
    }

    return true;
}
