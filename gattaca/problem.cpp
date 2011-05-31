#include <fstream>
#include <iostream>

#include "problem.h"

using namespace std;
using namespace jgerrish;

size_type Problem::size() const
{
    return predictions_by_start.size();
}

// Load a single integer from the file filename
int Problem::load_file(const char *filename)
{
    int num, cnt = 0;
    char line[80];
    Prediction pred;

    std::ifstream input_file(filename);

    // Input DNA string
    input_file >> num;
    while ((dna.length() < num) && input_file.good()) {
        input_file.getline(line, 81);
        dna += line;
    }

    // input predictions
    input_file >> num;

    for (int i = 0; i < num; i++) {
        input_file >> pred;
        predictions_by_start.insert(prediction_pair(pred.get_start(), pred));
    }

    return num;
}
