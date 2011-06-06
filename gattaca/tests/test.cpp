#include "prediction.h"
#include "problem.h"

#define BOOST_TEST_MODULE GattacaTest
#include <boost/test/unit_test.hpp>
#include <boost/test/included/unit_test_framework.hpp>

using namespace std;
using namespace boost;
using namespace boost::unit_test;
using namespace jgerrish;

BOOST_AUTO_TEST_CASE(load_file_test)
{
    Problem prob;

    prob.load_file("tests/test1.txt");
    BOOST_CHECK_EQUAL(prob.dna, "AB");

    BOOST_CHECK_EQUAL(prob.predictions_by_start.size(), 1);
    prediction_start_set::iterator it;

    BOOST_CHECK(prob.predictions_by_start.find(1) != prob.predictions_by_start.end());
    Prediction p = prob.predictions_by_start[1];
    BOOST_CHECK_EQUAL(p.get_start(), 1);
    BOOST_CHECK_EQUAL(p.get_end(), 2);
    BOOST_CHECK_EQUAL(p.get_score(), 5);

    prob.load_file("tests/test2.txt");
    BOOST_CHECK_EQUAL(prob.dna, "AB");

    prob.load_file("tests/test3.txt");
    BOOST_CHECK_EQUAL(prob.dna, "AB1");

}
