#include <map>
#include <string>
#include <vector>

using namespace std;

class Trie
{
private:
    typedef map<char, Trie*> TrieNodes;
    TrieNodes children;
    string *word;
    int minimum;

public:
    Trie();
    ~Trie();
    void insert(const string &word);
    int cost(vector<vector<int> > &distance, const char &c1, const char &c2,
             int dict_level, int test_pos);
    int test(const string &test_word, vector<vector<int> > &distance);
    int walk(const char dict_char, int dict_level,
             vector<vector<int> > &distance, const string &test_word,
             int &global_min);
    int min_dist();
};
