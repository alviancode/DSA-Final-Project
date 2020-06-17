#ifndef FINAL_PROJECT_TRIE_H
#define FINAL_PROJECT_TRIE_H

#include <utility>
#include <iostream>
#include <fstream>

using namespace std;
const int alphabetSize = 26;
string printTemp; // Temporary variable to store the character of the word

// Trie Node
struct TrieNode {
    struct TrieNode *children[alphabetSize];

    // isEndOfWord is true if the node presents the end of the word
    bool isEndOfWord;

    // variable of meaning and partOfSpeech
    string meaning;
    string partOfSpeech;
};


// Returns new trie node and initialized to NULL
struct TrieNode *getNode() {
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;
    for (int i = 0; i < alphabetSize; i++) {
        pNode->children[i] = nullptr;
    }
    return pNode;
}


// If key not present, insert key into trie
// If the key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root, const string &word, string partOfSpeech, string meaning) {
    struct TrieNode *pNode = root;

    for (char i : word) {
        int index = i - 'a';
        if (!pNode->children[index]) {
            pNode->children[index] = getNode();
        }

        pNode = pNode->children[index];
    }

    // Mark last node as leaf
    pNode->isEndOfWord = true;

    // Store meaning and partOfSpeech value at last node
    pNode->meaning = std::move(meaning);
    pNode->partOfSpeech = std::move(partOfSpeech);
}

// Edit word function
void edit(struct TrieNode *root, const string &word, string partOfSpeech, string meaning) {
    struct TrieNode *pNode = root;

    for (char i : word) {
        int index = i - 'a';
        pNode = pNode->children[index];
    }
    pNode->isEndOfWord = true;
    pNode->meaning = std::move(meaning);
    pNode->partOfSpeech = std::move(partOfSpeech);
}


// Function to search a word in a Trie and return the meaning if the word exists
string getMeaning(struct TrieNode *root, const string &key) {
    struct TrieNode *pNode = root;

    for (char i : key) {
        int index = i - 'a';
        pNode = pNode->children[index];
        if (pNode->isEndOfWord) {
            return key + '(' + pNode->partOfSpeech + ')' + " = " + pNode->meaning;
        }
    }
    return "";
}


// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const string &key) {
    struct TrieNode *pNode = root;

    for (char i : key) {
        int index = i - 'a';
        if (!pNode->children[index]) {
            return false;
        }
        pNode = pNode->children[index];
    }
    return (pNode != nullptr && pNode->isEndOfWord);
}


// Returns true if root has no children(root == NULL), else false
bool isEmpty(TrieNode *root) {
    struct TrieNode *pNode = root;

    for (int i = 0; i < alphabetSize; i++)
        if (pNode->children[i])
            return false;
    return true;
}


// Recursive function to delete a key from trie
TrieNode *remove(struct TrieNode *root, string key, int depth = 0) {
    struct TrieNode *pNode = root;

    // If tree is empty
    if (!pNode) {
        return nullptr;
    }

    // If last character is being processed
    if (depth == key.size()) {

        // The node is'n more end of the word after the key is remove
        if (pNode->isEndOfWord) {
            pNode->isEndOfWord = false;
        }

        // If given is not prefix of any other word
        if (isEmpty(pNode)) {
            delete (pNode);
            pNode = nullptr;
        }
        return pNode;
    }

    // Recur the child using ASCII value if not the last character
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(pNode) && !pNode->isEndOfWord) {
        delete (pNode);
        pNode = nullptr;
    }
    return pNode;
}


// Helper function to print all words
void printWord(struct TrieNode *root, char *str, int n) {
    struct TrieNode *pNode = root;
    for (int i = 0; i < n; i++) {
        printTemp += str[i];
    }
    cout << printTemp << '(' + pNode->partOfSpeech << ") = " << pNode->meaning << endl;
    printTemp = "";
}


// Function to display the content of trie
void view(struct TrieNode *root, char *str, int level = 0) {
    struct TrieNode *pNode = root;

    if (pNode->isEndOfWord) {
        printWord(root, str, level);
    }
    for (int i = 0; i < alphabetSize; i++) {
        // If non NULL child is present,
        // add parent key to str and call view function recursively
        if (pNode->children[i]) {
            str[level] = i + 'a';
            view(pNode->children[i], str, level + 1);
        }
    }
}

#endif //FINAL_PROJECT_TRIE_H
