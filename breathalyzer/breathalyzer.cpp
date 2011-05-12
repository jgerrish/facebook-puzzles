/*
  Joshua Gerrish <jgerrish@gmail.com>

  Solution to breathalyzer Facebook engineering puzzle

  Use dynamic programming and a self-pruning trie to find minimum edit distance
  for multiple words given a dictionary of good words.
*/

#include <algorithm>            // std::transform
#include <cctype>               // std::tolower
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "trie.h"

using namespace std;

static const char *wordlist_filename = "/var/tmp/twl06.txt";
//static const char *wordlist_filename = "wordlist.txt";

// Load a file of words separated by whitespace into a vector of words
// Return the length of the longest word
int load_words(const char *filename, vector<string> &words)
{
    ifstream input_file(filename);
    string word;
    int max_len = 0;

    input_file >> word;
    while (input_file.good())
    {
        std::transform(word.begin(), word.end(), word.begin(),
                       (int(*)(int)) std::tolower);

        if (word.length() > max_len)
            max_len = word.length();

        words.push_back(word);
        input_file >> word;
    }

    return max_len;
}

int main(int argc, char **argv)
{
    vector<string> post;
    vector<string> words;
    Trie *dictionary = NULL;
    int cost, total_cost = 0, min_cost = 0;
    int max_dict_len, max_post_len;

    if (argc != 2) {
        cout << "Must specify wall post filename on command line" << endl;
        return 1;
    }

    /* Load and build the dictionary */
    max_dict_len = load_words(wordlist_filename, words);
    dictionary = new Trie();

    for (vector<string>::const_iterator it = words.begin();
         it != words.end();
         ++it) {
        dictionary->insert(*it);
    }

    max_post_len = load_words(argv[1], post);

    vector<int> rows(max_dict_len + 1);
    vector<vector<int> > distance(max_post_len + 1, rows);

    /* Initialize distance matrix */
    for (int i = 0; i <= max_dict_len; i++) {
        distance[0][i] = i;
    }
    for (int i = 0; i <= max_post_len; i++) {
        distance[i][0] = i;
    }

    /* Test each word */
    for (vector<string>::const_iterator it = post.begin();
         it != post.end();
         ++it) {
        cost = dictionary->test(*it, distance);
        total_cost += cost;
    }

    cout << total_cost << endl;

    if (dictionary != NULL)
        delete dictionary;

    return 0;
}
