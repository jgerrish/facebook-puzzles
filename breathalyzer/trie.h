#include <map>
#include <string>
#include <vector>

using namespace std;

class Trie
{
private:
    typedef map<char, Trie*> TrieNodes;
    TrieNodes children;
    string word;
    string test_word;
    vector<int> *distance;
    int minimum;

public:
    Trie(const string &word);
    ~Trie();
    void insert(const string &word);
    int min_dist();
};
