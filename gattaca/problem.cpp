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
    string line;
    Prediction pred;

    std::ifstream input_file(filename);
    // Initialize DNS string
    dna.clear();

    // Input DNA string
    input_file >> num;
    while ((dna.length() < num) && input_file.good()) {
        getline(input_file, line);
        if (line.length() > (num - dna.length()))
            dna += line.substr(0, num - dna.length());
        else
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
