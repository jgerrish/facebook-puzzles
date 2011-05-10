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
        std::transform(word.begin(), word.end(), word.begin(),
                       (int(*)(int)) std::tolower);
        words.push_back(word);
        input_file >> word;
    }

    return words;
}

int main(int argc, char **argv)
{
    vector<string> post;
    vector<string> words;
    Trie *dictionary = NULL;
    int cost, total_cost = 0, min_cost = 0;

    if (argc != 2) {
        cout << "Must specify wall post filename on command line" << endl;
        return 1;
    }

    post = load_post(argv[1]);
    words = load_words(wordlist_filename);

    for (vector<string>::const_iterator it = post.begin();
         it != post.end();
         ++it) {

        if (dictionary != NULL)
            delete dictionary;
        dictionary = new Trie(*it);

        for (vector<string>::const_iterator it2 = words.begin();
             it2 != words.end();
             ++it2) {
            dictionary->insert(*it2);
        }
        total_cost += dictionary->min_dist();
    }

    cout << total_cost << endl;

    if (dictionary != NULL)
        delete dictionary;

    return 0;
}
