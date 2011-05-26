#include <iostream>
#include <fstream>
#include <vector>

#include "prediction.h"
#include "problem.h"

using namespace std;



int cost(Problem &prob, prediction_set::iterator &index,
         vector<int> &costs)
{
    
}

int main(int argc, char **argv)
{
    int num;
    Problem prob;

    if (argc != 2) {
        cout << "Error: Must specify a filename to load" << endl;
        return 1;
    }

    num = prob.load_file(argv[1]);

    vector<int> cost(prob.predictions.size());

    // reverse iterator
    int i = 0;
    for (prediction_set::reverse_iterator it = prob.predictions.rbegin();
         it != prob.predictions.rend();
         ++it) {
        cost[i] = it->get_score();
        cout << *it << endl;
        i++;
    }

    return 0;
}
