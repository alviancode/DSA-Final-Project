#ifndef FINAL_PROJECT_TRIE_H
#define FINAL_PROJECT_TRIE_H

#include <utility>
#include <iostream>
#include <fstream>

using namespace std;
const int alphabetSize = 26;


struct TrieNode {
    struct TrieNode *children[alphabetSize];
    bool isEndOfWord;
    string meaning;
    string partOfSpeech;
};


struct TrieNode *getNode() {
    struct TrieNode *pNode = new TrieNode;

    pNode->isEndOfWord = false;
    for (int i = 0; i < alphabetSize; i++){
        pNode->children[i] = nullptr;
    }
    return pNode;
}


void insert(struct TrieNode *root, string word, string partOfSpeech, string meaning) {
    struct TrieNode *pNode = root;

    for (char i : word) {
        int index = i - 'a';
        if (!pNode->children[index]) {
            pNode->children[index] = getNode();
        }

        pNode = pNode->children[index];
    }
    pNode->isEndOfWord = true;
    pNode->meaning = std::move(meaning);
    pNode->partOfSpeech = std::move(partOfSpeech);
}


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


bool search(struct TrieNode *root, string key) {
    struct TrieNode *pNode = root;

    for (char i : key) {
        int index = i - 'a';
        if (!pNode->children[index]){
            return false;
        }
        pNode = pNode->children[index];
    }
    return (pNode != nullptr && pNode->isEndOfWord);
}


bool isEmpty(TrieNode *root) {
    struct TrieNode *pNode = root;

    for (int i = 0; i < alphabetSize; i++)
        if (pNode->children[i])
            return false;
    return true;
}


TrieNode *remove(struct TrieNode *root, string key, int depth = 0) {
    struct TrieNode *pNode = root;

    if (!pNode) {
        return nullptr;
    }
    if (depth == key.size()) {
        if (pNode->isEndOfWord) {
            pNode->isEndOfWord = false;
        }
        if (isEmpty(pNode)) {
            delete (pNode);
            pNode = nullptr;
        }
        return pNode;
    }
    int index = key[depth] - 'a';
    root->children[index] = remove(root->children[index], key, depth + 1);
    if (isEmpty(pNode) && !pNode->isEndOfWord) {
        delete (pNode);
        pNode = nullptr;
    }
    return pNode;
}


void view(struct TrieNode *root, char *str, int level = 0) {
    struct TrieNode *pNode = root;

    if (pNode->isEndOfWord) {
        cout << str << '(' + pNode->partOfSpeech << ") = " << pNode->meaning << endl;
    }
    for (int i = 0; i < alphabetSize; i++) {
        if (pNode->children[i]) {
            str[level] = i + 'a';
            view(pNode->children[i], str, level + 1);
        }
    }
}

#endif //FINAL_PROJECT_TRIE_H
