//
// Custom Trie class for calculating edit distance using dynamic programming
// Instead of building the memoization table all at once, we build it a column
// at a time as letters are inserted into the Trie.
// This eliminates redundant work when words have the same prefix.
// In addition, it allows easy pruning of the search tree

#include <iostream>
#include <limits>
#include <algorithm>            // std::transform
#include <cctype>               // std::tolower

#include "trie.h"

using namespace std;

// Construct the dictionary trie
// This contructor takes one argument, the word we're spellchecking
Trie::Trie()
{
    minimum = std::numeric_limits<int>::max();
    word = NULL;
}

Trie::~Trie()
{
    for (TrieNodes::iterator it = children.begin(); it != children.end();
         ++it) {
        delete(it->second);
    }

    if (word != NULL)
        delete word;
}

/* Insert a word into the trie */
void Trie::insert(const string &word)
{
    char c;
    Trie *next;

    next = this;
    for (int i = 0; i < word.length(); ++i) {
        c = word[i];

        if (next->children.find(c) == next->children.end()) {
            next->children[c] = new Trie();
        }

        next = next->children[c];
    }
    next->word = new string(word);
}

/* Compute the minimum cost up to a certain pair of points in the strings */
int Trie::cost(vector<vector<int> > &distance, const char &c1, const char &c2,
               int dict_level, int test_pos)
{
    int match_cost;

    if (c1 == c2)
        match_cost = 0;
    else
        match_cost = 1;

    return min(distance[test_pos][dict_level] + match_cost,
               min(distance[test_pos + 1][dict_level] + 1,
                   distance[test_pos][dict_level + 1] + 1));
}

/* Walk the trie comparing every node with the test character */
/* This is a destructive operation, since we update the memoization table at
   every step.

   level indicates what level or position we are at in the test word
   the level is 0-based
*/
int Trie::walk(const char dict_char, int dict_level,
               vector<vector<int> > &distance, const string &test_word,
               int &global_min)
{
    int node_cost, min_cost, minimum_found;

    for (int i = 0; i < test_word.length(); i++) {
        node_cost = cost(distance, dict_char, test_word[i],
                         dict_level, i);
        distance[i + 1][dict_level + 1] = node_cost;
    }

    if (word != NULL)
        minimum_found = distance[test_word.length()][dict_level + 1];
    else
        minimum_found = std::numeric_limits<int>::max();

    if (minimum_found < global_min)
        global_min = minimum_found;

    // Prune the trie
    // If every distance in this column is greater than the minimum
    // distance seen so far, we can stop adding characters from this word,
    // since we know any additional characters can only increase or keep
    // the distance score equal
    int min_prune = std::numeric_limits<int>::max();

    for (int i = 0; i <= test_word.length(); i++) {
        if (distance[i][dict_level + 1] < min_prune)
            min_prune = distance[i][dict_level + 1];
    }

    if (min_prune > global_min)
        return global_min;

    for (map<char, Trie*>::const_iterator it = children.begin();
         it != children.end();
         ++it) {
        node_cost = it->second->walk(it->first, dict_level + 1,
                                     distance, test_word, global_min);
        if (node_cost < minimum_found)
            minimum_found = node_cost;
    }

    return minimum_found;
}

/* Test a word against this Trie dictionary
   We build the memoiziation table a row at a time for each letter we see
*/
int Trie::test(const string &test_word, vector<vector<int> > &distance)
{
    int match_cost, cost, global_min;
    char c;

    minimum = std::numeric_limits<int>::max();
    global_min = std::numeric_limits<int>::max();

    // Walk the root node's children
    for (map<char, Trie*>::const_iterator it = children.begin();
         it != children.end();
         ++it) {
        cost = it->second->walk(it->first, 0, distance, test_word, global_min);
        if (cost < minimum)
            minimum = cost;
    }

    return minimum;

}

int Trie::min_dist()
{
    return minimum;
}
