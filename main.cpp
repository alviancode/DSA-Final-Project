#include <iostream>
#include <string>
#include "trie.h"

#define MAX_WORD_SIZE 100
using namespace std;

string word, partOfSpeech, meaning;


int main() {
    TrieNode *root = getNode();
    char str[MAX_WORD_SIZE];

    string funcNames[6] = {"Add word", "Remove word", "Search word", "Edit word", "View all words", "Quit"};
    int selectNumber;

    while (true) {
        cout << endl;
        cout << "####################### WORD DICTIONARY #######################" << endl;
        for (int i = 0; i < 6; i++) {
            cout << (i + 1) << ". " << funcNames[i] << endl;
        }
        cout << "###############################################################" << endl;
        cout << "Select Number: ";
        cin >> selectNumber;
        cin.ignore();
        switch (selectNumber) {
            case 1:
                cout << "Enter new word: ";
                getline(cin, word);

                if (search(root, word)) {
                    cout << "Enter another word!" << endl;
                    break;
                } else {
                    cout << "Part of Speech: ";
                    getline(cin, partOfSpeech);
                    cout << "Enter meaning of the word: ";
                    getline(cin, meaning);
                    insert(root, word, partOfSpeech, meaning);
                    cout << "Success add new word.";
                    break;
                }

            case 2:
                if (isEmpty(root) == 1) {
                    cout << "Dictionary is empty!";
                    break;
                } else {
                    cout << "Enter word to be deleted: ";
                    getline(cin, word);
                    if (search(root, word)) {
                        remove(root, word);
                        cout << "Success remove word.";
                        break;
                    } else {
                        cout << "Word not found.";
                        break;
                    }
                }
            case 3:
                if (isEmpty(root) == 1) {
                    cout << "Dictionary is empty!";
                    break;
                } else {
                    cout << "Enter word to search: ";
                    getline(cin, word);
                    if (search(root, word)) {
                        cout << getMeaning(root, word);
                        break;
                    } else {
                        cout << "Word not found.";
                        break;
                    }
                }

            case 4:
                if (isEmpty(root) == 1) {
                    cout << "Dictionary is empty!";
                    break;
                } else {
                    cout << "Enter word to edit: ";
                    getline(cin, word);
                    if (search(root, word)) {
                        cout << "Enter New Part of Speech: ";
                        getline(cin, partOfSpeech);
                        cout << "Enter New Meaning: ";
                        getline(cin, meaning);
                        insert(root, word, partOfSpeech, meaning);
                        cout << "Success edit word.";
                        break;
                    } else {
                        cout << "Word not found.";
                        break;
                    }
                }
            case 5:
                view(root, str);
                break;
            case 6:
                cout << "See You Next Time!";
                exit(0);
            default:
                cout << "Input is not valid!";
                break;
        }
    }

    return 0;
}

