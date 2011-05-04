#include <algorithm>            // std::transform
#include <cctype>               // std::tolower
#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

static const char *wordlist_filename = "/var/tmp/twl06.txt";
//static const char *wordlist_filename = "wordlist.txt";

vector<string> load_post(const char *filename)
{
    ifstream input_file(filename);
    string word;
    vector<string> post;
 
    input_file >> word;
    while (input_file.good())
    {
        post.push_back(word);
        input_file >> word;
    }

    return post;
}

vector<string> load_words(const char *filename)
{
    ifstream input_file(filename);
    string word;
    vector<string> words;

    input_file >> word;
    while (input_file.good())
    {
        words.push_back(word);
        input_file >> word;
    }

    return words;
}

int find_diff(const string &w1, const string &w2, const int min_found)
{
    int total_cost;
    string word1 = w1;
    string word2 = w2;

    std::transform(word1.begin(), word1.end(), word1.begin(),
                   (int(*)(int)) std::tolower);
    std::transform(word2.begin(), word2.end(), word2.begin(),
                   (int(*)(int)) std::tolower);

    // Test for equality
    if (word1 == word2)
        return 0;

    int **v = (int **)malloc((word1.length() + 1) * sizeof(int *));
    for(int i = 0; i < word1.length() + 1; i++)
        v[i] = (int *)malloc((word2.length() + 1) * sizeof(int));

    // Initialize data table
    //cout << "Looking at " << word1 << " and " << word2 << endl;
    for (int i = 0; i <= word1.length(); i++) {
        v[i][0] = i;
    }
    for (int i = 0; i <= word2.length(); i++) {
        v[0][i] = i;
    }

    int match_cost;
    for (int i = 1; i <= word1.length(); i++) {
        for (int j = 1; j <= word2.length(); j++) {
            if (word1[i - 1] == word2[j - 1]) {
                match_cost = 0;
            } else {
                match_cost = 1;
            }
            v[i][j] = min(v[i - 1][j - 1] + match_cost,
                          min(v[i - 1][j] + 1, v[i][j - 1] + 1));
            if ((i == j) && (v[i][j] >= min_found)) {
                // Free the array
                for(int i = 0; i < word1.length() + 1; i++)
                    free(v[i]);
                free(v);

                return min_found;
            }
        }
    }

    // Print out the table
    /*
    for (int i = 0; i <= word1.length(); i++) {
        for (int j = 0; j <= word2.length(); j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    */

    total_cost = v[word1.length()][word2.length()];

    // Free the array
    for(int i = 0; i < word1.length() + 1; i++)
        free(v[i]);

    free(v);

    return total_cost;
}

int main(int argc, char **argv)
{
    vector<string> post;
    vector<string> words;
    int cost, total_cost, min_cost = 0;

    if (argc != 2) {
        cout << "Must specify wall post filename on command line" << endl;
        return 1;
    }

    post = load_post(argv[1]);
    words = load_words(wordlist_filename);

    for (vector<string>::const_iterator it = post.begin();
         it != post.end();
         ++it) {
        cout << *it << endl;
        min_cost = std::numeric_limits<int>::max();
        for (vector<string>::const_iterator it2 = words.begin();
             it2 != words.end();
             ++it2) {
            cost = find_diff(*it, *it2, min_cost);
//            cout << "cost for " << *it << " vs " << *it2 << ": " << cost
//                 << endl;
            if (cost < min_cost)
                min_cost = cost;
        }
        total_cost += min_cost;
    }

    cout << "Total min cost: " << total_cost << endl;

    return 0;
}
