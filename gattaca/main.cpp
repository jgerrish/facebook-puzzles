#include <iostream>
#include <fstream>
#include <vector>

#include "prediction.h"
#include "problem.h"

using namespace std;
using namespace jgerrish;

int main(int argc, char **argv)
{
    int num;
    Problem prob;
    prediction_start_set::reverse_iterator it, prev_it;
    prediction_start_set::iterator it_low;

    if (argc != 2) {
        cout << "Error: Must specify a filename to load" << endl;
        return 1;
    }

    num = prob.load_file(argv[1]);

    // reverse iterator
    int i = prob.size();
    for (it = prob.predictions_by_start.rbegin();
         it != prob.predictions_by_start.rend();
         ++it) {
        if (i == prob.size()) {
            it->second.set_cost(it->second.get_score());
        } else {
            // Find the next sequence that doesn't overlap this one
            it_low =
                prob.predictions_by_start.upper_bound(it->second.get_end());
            if (it_low != prob.predictions_by_start.end())
                it->second.set_cost(max(it->second.get_score() +
                                        it_low->second.get_cost(),
                                        prev_it->second.get_cost()));
            else
                it->second.set_cost(it->second.get_score());
        }
        i--;
        prev_it = it;
    }

    cout << prev_it->second.get_cost() << endl;

    return 0;
}
