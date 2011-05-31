#ifndef _problem_h_
#define _problem_h_

#include <string>
#include <map>
#include <vector>

#include "prediction.h"

using namespace std;

namespace jgerrish {

typedef unsigned int size_type;
typedef map<int, Prediction> prediction_start_set;
typedef pair<int, Prediction> prediction_pair;

class Problem
{
public:
    string dna;

    prediction_start_set predictions_by_start;

    size_type size() const;

    int load_file(const char *filename);
};

};

#endif
