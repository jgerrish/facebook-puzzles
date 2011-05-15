#include <graph.h>
#define BOOST_TEST_MODULE GraphTest
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>

using namespace std;
using namespace boost;
using namespace boost::unit_test;

BOOST_AUTO_TEST_CASE(load_file_test)
{
    Graph graph;
    adjacency_list::iterator edges;

    graph.load_file("test.txt");

    for (edges = graph.edges(); edges != graph.end(); ++edges) {
        
    }
}
