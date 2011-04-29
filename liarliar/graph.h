// Class representing a graph

#include <iostream>
// Use an unordered_map (hash map) for the adjacency list
#include <tr1/unordered_map>
#include <vector>
#include <string>

using namespace std;
//using namespace std::tr1;

typedef std::tr1::unordered_map<string, vector<string> > adjacency_list;

// For now, don't templatize the Graph object.
// If I end up using it again in another puzzle, we can make it generic
class Graph
{
private:
    adjacency_list adj_list;

public:
    void add_edge(const string &v1, const string &v2);
    adjacency_list::iterator edges();
    adjacency_list::iterator end();
    vector<string> neighbors(const string &v);

    friend ostream &operator<<(ostream &stream, Graph graph);
};
