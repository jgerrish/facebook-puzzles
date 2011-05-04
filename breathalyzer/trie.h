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

public:
    Trie();
    ~Trie();
    void insert(const string word);
    
};
