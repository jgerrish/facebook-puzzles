#include "graph.h"

Graph::Graph()
{
    directed = true;
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
