#include "graph.h"

void Graph::add_edge(const string &v1, const string &v2)
{
    vector<string> neighbors;

    adjacency_list::iterator it = adj_list.find(v1);
    if (it != adj_list.end())
        neighbors = adj_list[v1];

    neighbors.push_back(v2);
    adj_list[v1] = neighbors;
}

adjacency_list::iterator Graph::edges()
{
    return adj_list.begin();
}

adjacency_list::iterator Graph::end()
{
    return adj_list.end();
}

ostream &operator<<(ostream &stream, Graph graph)
{
    adjacency_list::iterator edges;

    edges = graph.edges();

    for (edges = graph.edges(); edges != graph.end(); ++edges) {
        stream << edges->first << " -> ";
        for (vector<string>::iterator target_it = edges->second.begin();
             target_it != edges->second.end();
             ++target_it) {
            stream << *target_it << ", ";
        }
        stream << endl;
    }

}

vector<string> Graph::neighbors(const string &v)
{
    return adj_list[v];
}
