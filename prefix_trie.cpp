#define TRIE_MATCHING_EXTENDED
#ifdef TRIE_MATCHING_EXTENDED

#include <algorithm>
#include <cassert>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

using std::stack;
using std::string;
using std::vector;

const int ALPHABET_SIZE = 4;

class Trie {
    struct Node;

public:
    Trie() : root(nullptr) {
    }

    ~Trie() {
        clear(root);
    }

    Node *getRoot() const {
        return root;
    }

    void buildTrie(const vector<string> &patterns);
    void prefixTreeMatching(const string &text, const unsigned i) const;
    void solve(const string& text, const vector <string> &patterns) const;

    void printTriePreOrder(Node *node) const;
    void printTriePostOrder(Node *node) const;

    friend std::ostream &operator<<(std::ostream &os, Node *&node);

private:

    struct Node {

        /* Array of pointers to child nodes. */
        mutable struct Children {
            Node *&operator[](char letter) {
                switch (letter) {
                case 'A': return childPointers[0]; break;
                case 'C': return childPointers[1]; break;
                case 'G': return childPointers[2]; break;
                case 'T': return childPointers[3]; break;
                default: assert(false); break;
                }
            }
        private:
            Node *childPointers[ALPHABET_SIZE] = { nullptr,nullptr,nullptr,nullptr };
        } children;

        /* Key is unique node number. Root's key is always 0. */
        const int key;

        /* Value holds node's data: 'A', 'C', 'G', or 'T'. */
        const char value;

        /* True if this node is the end of a pattern. */
        bool isEndOfPattern;

        Node(const int nodeKey, const char nodeValue) : key(nodeKey), value(nodeValue), isEndOfPattern(false) {
        }

        bool isLeaf() const {
            return !(children['A'] || children['C'] || children['G'] || children['T']);
        }
    };

    Node *root;

    /* Destroys all nodes in post-order fashion. */
    void clear(Node *node);
};

void Trie::buildTrie(const vector<string> &patterns) {
    int counter = 0;
    root = new Node(counter++, ' ');
    for (const auto &pattern : patterns) {
        Node *currentNode = root;
        for (size_t i = 0; i < pattern.length(); i++) {
            char currentSymbol = pattern[i];
            Node *&nextNode = currentNode->children[currentSymbol];     // Needs reference (&) because of three lines down: nextNode = newNode;.
            if (!nextNode) {
                Node *newNode = new Node(counter++, currentSymbol);
                nextNode = newNode;     // currentNode->children[currentSymbol] = newNode;
                currentNode = newNode;
            }
            else {
                currentNode = nextNode;
            }
            if (i + 1 == pattern.length())
                currentNode->isEndOfPattern = true;
        }
    }
}

void Trie::prefixTreeMatching(const string &text, const unsigned i) const {
    int currentPosition = i;    // Position in text. i is starting position.
    char currentSymbol = text[currentPosition];     // Symbol at that position.
    Node *currentNode = root;   // Position in trie (currentNode).
    while (true) {
        if (currentNode->isEndOfPattern) {
            std::cout << i << ' ';
            return;
        }
        else if ((currentSymbol != '\0') && currentNode->children[currentSymbol]) {
            currentNode = currentNode->children[currentSymbol];
            currentSymbol = text[++currentPosition];
        }
        else {            
            return;
        }
    }
}

void Trie::solve(const string& text, const vector <string>& patterns) const {
    for (size_t i = 0; i < text.length(); i++) {
        prefixTreeMatching(text, i);
    }
}

void Trie::printTriePreOrder(Node *node) const {
    if (!node)
        return;
    stack<Node*> s;
    s.push(node);
    while (!s.empty()) {
        Node *current = s.top();
        s.pop();
        std::cout << current;   /* Visit */
        for (const auto &letter : { 'T', 'G', 'C', 'A' }) {
            if (auto nd = current->children[letter])
                s.push(nd);
        }
    }
}

void Trie::printTriePostOrder(Node *node) const {
    if (!node)
        return;
    printTriePostOrder(node->children['A']);
    printTriePostOrder(node->children['C']);
    printTriePostOrder(node->children['G']);
    printTriePostOrder(node->children['T']);
    std::cout << node;   /* Visit. Doesn't print in same order as clear(), because of operator<<. */
}

void Trie::clear(Node *node) {
    if (!node)
        return;
    clear(node->children['A']);
    clear(node->children['C']);
    clear(node->children['G']);
    clear(node->children['T']);

    /* Visit */
    //std::cout << "Testing dtor. Node: " << node->key << '\n';
    delete node;
    node = nullptr;
}

/* It doesn't use for loop because this way it has higher chance of being inlined by compiler. */
inline std::ostream &operator<<(std::ostream &os, Trie::Node *&node) {
    if (node->isLeaf())
        return os;
    if (node->children['A'])
        os << node->key << "->" << node->children['A']->key << ':' << node->children['A']->value << '\n';
    if (node->children['C'])
        os << node->key << "->" << node->children['C']->key << ':' << node->children['C']->value << '\n';
    if (node->children['G'])
        os << node->key << "->" << node->children['G']->key << ':' << node->children['G']->value << '\n';
    if (node->children['T'])
        os << node->key << "->" << node->children['T']->key << ':' << node->children['T']->value << '\n';
    return os;
}

int main(void) {
    std::ios::sync_with_stdio(false);   // Doesn't change execution time.
    std::cin.tie(NULL);      // Doesn't change execution time.

    string text;
    std::cin >> text;

    int n;  // number of patterns to search for
    std::cin >> n;

    vector <string> patterns(n);
    for (int i = 0; i < n; i++) {
        std::cin >> patterns[i];
    }

    Trie trie;
    trie.buildTrie(patterns);
    trie.solve(text, patterns);

    system("pause");
    return 0;
}

#endif  // TRIE_MATCHING_EXTENDED