#include <iostream>
#include <limits>
#include <algorithm>            // std::transform
#include <cctype>               // std::tolower

#include "trie.h"

using namespace std;

// Construct the dictionary trie
// This contructor takes one argument, the word we're spellchecking
Trie::Trie(const string &word)
{
    test_word = word;
    std::transform(test_word.begin(), test_word.end(), test_word.begin(),
                   (int(*)(int)) std::tolower);

    distance = new vector<int>(word.length() + 1);
    for (int i = 0; i <= word.length(); ++i)
        distance->at(i) = i;

    minimum = std::numeric_limits<int>::max();
}

Trie::~Trie()
{
    for (TrieNodes::iterator it = children.begin(); it != children.end();
         ++it) {
        delete(it->second);
    }

    delete distance;
}

void Trie::insert(const string &word)
{
    int match_cost, cost;
    char c;
    Trie *next;

    cost = minimum;
    next = this;
    for (int i = 0; i < word.length(); ++i) {
        c = word[i];
        if (next->children.find(c) == next->children.end()) {
            // No child for this character yet
            next->children[c] = new Trie(test_word);

            // Fill out the distance vector
            next->children[c]->distance->at(0) = i + 1;

            for (int j = 0; j < test_word.length(); ++j) {
                if (word[i] == test_word[j]) {
                    match_cost = 0;
                } else {
                    match_cost = 1;
                }
                cost = min(next->distance->at(j) + match_cost,
                           min(next->distance->at(j + 1) + 1,
                               next->children[c]->distance->at(j) + 1));
                next->children[c]->distance->at(j + 1) = cost;
            }
        }

        next->word = word.substr(0, i + 1);

        next = next->children[c];

        // Prune
        int min_prune = std::numeric_limits<int>::max();
        for (int j = 0; j <= test_word.length(); ++j) {
            if (next->distance->at(j) < min_prune)
                min_prune = next->distance->at(j);
        }
        if (min_prune > minimum)
            return;
    }

    cost = next->distance->at(test_word.length());
    if (cost < minimum)
        minimum = cost;
}

int Trie::min_dist()
{
    return minimum;
}
