#include <string>
#include <set>

#include "prediction.h"

using namespace std;

typedef set<Prediction, PredictionComp> prediction_set;

class Problem
{
public:
    string dna;

    prediction_set predictions;
    int load_file(const char *filename);
};
