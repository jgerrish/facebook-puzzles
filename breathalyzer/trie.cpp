#include "trie.h"

Trie::Trie()
{
}

Trie::~Trie()
{
    for (TrieNodes::iterator it = children.begin(); it != children.end();
         ++it) {
        delete(it->second);
    }
}

void Trie::insert(const string word)
{
    Trie *next;

    next = this;
    for (int i = 0; i < word.length(); ++i) {
        char c = word[i];
        if (children.find(c) == children.end()) {
            // No child for this character yet
            next->children[c] = new Trie();
            next = next->children[c];
        }
        next->word = word.substr(0, i + 1);
    }
}
